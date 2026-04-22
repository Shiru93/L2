package p2_8janvier2025;

import java.util.*;

public class ArraySortedList<E extends Comparable<E>> extends AbstractCollection<E> implements SortedList<E>, Cloneable {
	private ArrayList<E> listeElements;
	private Comparator<? super E> comparator;
	
	public ArraySortedList() {
		this.listeElements = new ArrayList<>();
		this.comparator = null;
	}
	
	/*
	 * @param comparator le comparateur utilisé pour trier cette liste, ou null pour l'ordre naturel 
	 */
	public ArraySortedList(Comparator<? super E> comparator) {
		this.listeElements = new ArrayList<>();
		this.comparator = comparator;
	}
	
	/*
	 * @param c la collection dont les éléments doivent être placés dans cette liste
	 * @throws NullPointerException si la collection spécifiée est null
	 */
	public ArraySortedList(Collection<? extends E> c) {
		if(c == null) {
			throw new NullPointerException();
		}
		
		this.listeElements = new ArrayList<>();
		this.comparator = null;
		this.addAll(c);
	}
	
	public Comparator<? super E> comparator(){
		return this.comparator;
	}
	
	private int compareElements(Object e1, Object e2) {
		if(comparator != null) {
			return comparator.compare((E) e1, (E) e2);
		} else {
			return ((Comparable<E>) e1).compareTo((E), e2);
		}
	}
	
	@Override
	public boolean add(E elt) {
		if(elt == null) {
			throw new NullPointerException();
		}
		
		if(listeElements.isEmpty() || compareElements(elt, listeElements.get(listeElements.size() - 1)) > 0) {
			return listeElements.add(elt);
		}
		
		for(int i = 0; i < listeElements.size(); i++) {
			if(compareElements(elt, listeElements.get(i)) <= 0) {
				listeElements.add(i, elt);
				return true;
			}
		}
		
		return listeElements.add(elt);
	}
	
	@Override
	public boolean addAll(Collection<? extends E> c) {
		if(c.isEmpty() || c.contains(null)) {
			throw new NullPointerException();
		}
		
		for(E e : c) {
			this.add(e);
		}
		
		return true;
	}
	
	@Override
	public boolean contains(Object obj) {
		if(this.isEmpty()) {
			return false;
		}
		
		try {
			if(compareElements(obj, listeElements.get(listeElements.size() - 1)) > 0 || compareElements(obj, listeElements.get(0)) < 0) {
				return false;
			}
			
			for(Object e : listeElements) {
				int tmp = compareElements(obj, e);
				
				if(tmp == 0) {
					return true;
				}
				
				if(tmp < 0) {
					return false;
				}
			}
		} catch (ClassCastException e) {
			return false;
		}
		
		return false;
	}
	
	@Override
	public boolean remove(Object obj) {
		if(this.isEmpty() || obj == null) {
			return false;
		}
		
		try {
			if(compareElements(obj, listeElements.get(listeElements.size() - 1)) > 0) {
				return false;
			}
			
			for(int i = 0; i < listeElements.size(); i++) {
				int tmp = compareElements(obj, listeElements.get(i));
				
				if(tmp == 0) {
					listeElements.remove(i);
					return true;
				}
				
				if(tmp < 0) {
					return false;
				}
			}
		} catch(ClassCastException e) {
			return false;
		}
		
		return false;
	}
	
	@Override
	public E remove(int i) {
		return listeElements.remove(i);
	}
	
	@Override
	public E get(int i) {
		return listeElements.get(i);
	}
	
	@Override
	public Iterator<E> iterator(){
		return listeElements.iterator();
	}
	
	@Override
	public boolean listEquals(List <?> l) {
		if(l == null || this.size() != l.size()) {
			return false;
		}
		
		Iterator<E> iter1 = this.iterator();
		Iterator<?> iter2 = l.iterator();
		while(iter1.hasNext()) {
			E e1 = iter1.next();
			Object e2 = iter2.next();
			
			if(!Objects.equals(e1, e2)) {
				return false;
			}
			
			return true;
		}
		
		return true;
	}
	
	@Override
	public boolean equals(Object o) {
		if(o == this) {
			return true;
		}
		
		if(!(o instanceof SortedList)) {
			return false;
		}
		
		SortedList<?> other = (SortedList<?>) o;
		
		if(this.size() != other.size()) {
			return false;
		}
		
		Iterator<E> iter1 = this.iterator();
		Iterator<?> iter2 = other.iterator();
		while(iter1.hasNext()) {
			if(!Objects.equals(iter1.next(), iter2.next())) {
				return false;
			}
		}
		
		return true;
	}
	
	@Override
	public int hashCode() {
		int hashCode = 1;
		for(E e : listeElements) {
			hashCode = 31 * hashCode + (e == null ? 0 : hashCode());
		}
		
		return hashCode;
	}
	
	@Override
	public String toString() {
		return listeElements.toString();
	}
	
	@Override
	public ArraySortedList<E> clone(){
		try {
			ArraySortedList<E> cloned = (ArraySortedList<E>) super.clone();
			cloned.listeElements = new ArrayList<>(this.listeElements);
			return cloned;
		} catch(CloneNotSupportedException e) {
			throw new InternalError(e);
		}
	}
}
