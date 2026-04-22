package p2_20janvier2021;

import java.util.*;

public class PureLinkedList<E> extends AbstractPureList<E> {
	private final LinkedList<E> innerList;
	
	/*
	 * Construit une liste vide
	 */
	public PureLinkedList() {
		this.innerList = new LinkedList<>();
	}
	
	/*
	 * Construit une liste vide contenant les éléments de la collection spécifiée
	 * @param c La collection à copier
	 */
	public PureLinkedList(Collection<? extends E> c) {
		if (c == null) {
			throw new NullPointerException();
		}
		this.innerList = new LinkedList<>(c);
	}
	
	// Constructeur privé utile pour les méthodes
	private PureLinkedList(LinkedList<E> inner) {
		this.innerList = inner;
	}
	
	@Override
	public List<E> asList(){
		return new LinkedList<>(this.innerList);
	}
	
//	@Override
//	public Iterator<E> iterator(){
//		return innerList.iterator();
//	}
	
	@Override
	public Iterator<E> iterator(){
		return Collection.unmodifiableList(his.innerList).iterator();
	}
	
	@Override
	public PureList<E> addLast(E elt){
		if(elt == null) {
			throw new NullPointerException();
		}
		
		LinkedList<E> newList = new LinkedList<>(this.innerList);
		newList.addLast(elt);
		
		return new PureLinkedList<>(newList);
	}
	
	@Override
	public PureList<E> addFirst(E elt){
		if(elt == null) {
			throw new NullPointerException();
		}
		
		LinkedList<E> newList = new LinkedList<>(this.innerList);
		newList.addFirst(elt);
		
		return new PureLinkedList<>(newList);
	}
	
	@Override
	public boolean isEmpty() {
		return this.innerList.isEmpty();
	}
	
	@Override
	public int size() {
		return this.innerList.size();
	}
	
	@Override
	public E getFirst() {
		return this.innerList.getFirst();
	}
	
	@Override
	public E getLast() {
		return this.innerList.getLast();
	}
	
	@Override
	public boolean contains(Object elt) {
		return this.innerList.contains(elt);
	}
	
	@Override
	public E get(int index) {
		return this.innerList.get(index);
	}
	
	@Override
	public String toString() {
		return this.innerList.toString();
	}
	
	@Override
	public int hashCode() {
		return this.innerList.hashCode();
	}
}
