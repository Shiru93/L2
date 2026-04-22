package p2_20janvier2021;

import java.util.*;

public class AbstractPureList<E> implements PureList<E> {
	@Override
    public abstract List<E> asList();

    @Override
    public abstract PureList<E> addLast(E elt);

    @Override
    public abstract Iterator<E> iterator();
	
	@Override
	public PureList<E> append(Collection <? extends E> l){
		if(l == null || l.contains(null)) {
			throw new NullPointerException();
		}
		
		PureList<E> res = this;
		
		for(E element : l) {
			res = res.addList(element);
		}
		
		return res;
	}
	
	@Override
	public E get(int index) {
		if(this.isEmpty()) {
			throw new NoSuchElementException();
		}
		
		if(index < 0 || index >= this.size()) {
			throw new IndexOutOfBoundsException();
		}
		
		int courant = 0;
		
		for(E element : this) {
			if(courant == index) {
				return element;
			}
			
			courant++;
		}
		
		throw new IndexOutOfBoundsException();
	}
	
//	public E get(int index) {
//	    Iterator<E> it = this.iterator();
//	    int curseur = 0;
//
//	    while(it.hasNext()) {
//	        E element = it.next();
//	        
//	        if (curseur == index) {
//	            return element;
//	        }
//	        curseur++;
//	    }
//	    throw new IndexOutOfBoundsException();
//	}
	
	@Override
	public int indexOf(Object elt) {
		int courant = 0;
		
		for(Object element : this) {
			if(elt == null ? element == null : elt.equals(element)) {
				return courant;
			}
			
			courant++;
		}
		
		return -1;
	}
	
//	@Override
//	public PureList<E> remove(Object o){
//		PureList<E> res = PureList.emptyList();
//		boolean removed = false;
//		
//		for(E element : this) {
//			if(element.equals(o) && !removed) {
//				removed = true;
//			} else {
//				res = res.addLast(element);
//			}
//		}
//		
//		return res;
//	}
	
	@Override
    public PureList<E> remove(Object o) {
        if (!contains(o)) return this;

        PureList<E> res = PureList.emptyList();
        boolean removed = false;

        for (E e : this) {
            if (removed) {
            	res = res.addLast(e);
            } else {
                if (o == null ? e == null : o.equals(e)) {
                    removed = true;
                } else {
                	res = res.addLast(e);
                }
            }
        }
        return res;
    }
	
//	@Override
//	public PureList<E> removeFirst(){
//		PureList<E> res = PureList.emptyList();
//		Iterator<E> it = this.iterator();
//		E element = it.next();
//		
//		while(it.hasNext()) {
//			element = it.next();
//			
//			res = res.addLast(element);
//		}
//		
//		return res;
//	}
	
	@Override
	public PureList<E> removeFirst(){
		if(this.isEmpty()){
			throw new NoSuchElementException();
		}
		
		PureList<E> res = PureList.emptyList();
		Iterator<E> it = this.iterator();
		it.next();
		
		while(it.hasNext()) {
			res = res.addLast(it.next());
		}
		
		return res;
	}
	
//	@Override
//	public int size() {
//		int taille = 0;
//		Iterator<E> it = this.iterator();
//		
//		while(it.hasNext()) {
//			it.next();
//			taille++;
//		}
//		
//		return taille;
//	}
	
	@Override
	public int size() {
		int taille = 0;
		for(E element : this) {
			taille++;
		}
		
		return taille;
	}
	
	@Override
	public boolean equals(Object obj) {
		if(this == obj) {
			return true;
		}
		
		if(!(obj instanceof PureList)) {
			return false;
		}
		
		PureList<?> other = (PureList<?>) obj;
		if(this.size() != other.size()) {
			return false;
		}
		
		Iterator<E> it1 = this.iterator();
		Iterator<?> it2 = other.iterator();
		
		while(it1.hasNext()) {
			E e1 = it1.next();
			Object e2 = it2.next();
			
			if(!(e1 == null ? e2 == null : e1.equals(e2))) {
				return false;
			}
		}
		
		return true;
	}
	
	@Override
	public int hashCode() {
	    int hashCode = 1;
	    for (E e : this) {
	        hashCode = 31 * hashCode + e.hashCode();
	    }
	    return hashCode;
	}
}
