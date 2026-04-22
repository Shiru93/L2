package p2_7janvier2026;

import java.util.*;

public class CloseableContainer<K, E> implements Iterable<E> {
	private K key;
	private boolean open;
	protected Collection<E> desObjets;
	
	/*
	 * public CloseableContainer(K cle, Collection<? extends E> desObjets) {
	    if (cle == null) {
	        throw new NullPointerException("La clé ne peut pas être null.");
	    }
	    if (desObjets == null) {
	        throw new NullPointerException("La collection fournie ne peut pas être null.");
	    }
	    if (desObjets.contains(null)) {
	        throw new NullPointerException("La collection ne doit pas contenir d'éléments null.");
	    }
	    
	    this.key = cle;
	    this.open = true;
	    
	    this.desObjets = new ArrayList<>();
	    this.desObjets.addAll(desObjets);
	}
	
	public CloseableContainer(K cle) {
	    this(cle, new ArrayList<E>()); 
	}
	 */
	
	public CloseableContainer(K cle) {
		if(cle == null) {
			throw new NullPointerException();
		}
		
		key = cle;
		open = true;
		desObjets = new ArrayList<>();
	}
	
	public CloseableContainer(K cle, Collection <? extends E> desObjets) {
		this(cle);
		
		if(desObjets == null || desObjets.contains(null)) {
			throw new NullPointerException();
		}
		
		this.desObjets.addAll(desObjets);
	}
	
	public boolean hasKey(K cle) {
		if(cle == null) return false;
		return key.equals(cle);
	}
	
	public boolean open(K cle) {
		if(hasKey(cle)) {
			this.open = true;
			return true;
		}
		
		return false;
	}
	
	public boolean close(K cle) {
		if(hasKey(cle)) {
			this.open = false;
			return true;
		}
		
		return false;
	}
	
	public boolean isOpen() {
		return this.open;
	}
	
	public int frequencyOf(Object obj) {
		int compteur = 0;
		
		for(E elt : this) {
			if(elt.equals(obj)) compteur++;
		}
		
		return compteur;
	}
	
	public boolean contains(Object obj) {
		if(obj == null || !isOpen()) {
			return false;
		}
		
		for(E elt : this) {
			if(elt.equals(obj)) {
				return true;
			}
		}
		
		return false;
	}
	
	public int size() {
		if(!isOpen()) {
			return 0;
		}
		
		int compteur = 0;
		for(E elt : this) {
			compteur++;
		}
		
		return compteur;
	}
	
	public void add(E elt) {
		if(elt == null) throw new NullPointerException();
		if(!isOpen()) throw new IllegalStateException();
		
		this.desObjets.add(elt);
	}
	
	public boolean remove(Object obj) {
		if(!isOpen()) throw new IllegalStateException();
		
		Iterator<E> it = this.iterator();
		while(it.hasNext()) {
			E element = it.next();
			if(element.equals(obj)) {
				it.remove();
				return true;
			}
		}
		
		return false;
	}
	
//	public boolean remove(Object obj) {
//	    if(!isOpen()) throw new IllegalStateException();
//	    return this.desObjets.remove(obj); 
//	}
	
	public Iterator<E> iterator(){
		if(!isOpen()) {
			return new EmptyIterator<E>();
		}
		
		return this.desObjets.iterator();
	}
	
	public boolean hasSameContent(Collection <?> c) {
		if(c == null) return false;
		if(!isOpen()) return c.isEmpty();
		if(this.size() != c.size()) return false;
		
		for (E elt : this) {
	        if (this.frequencyOf(elt) != Collections.frequency(c, elt)) {
	            return false;
	        }
	    }
		
	    return true;
	}
}
