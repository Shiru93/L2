import java.util.Iterator;

public class ArrayIterator<E> implements Iterator<E>{
    protected E[] tab;
    protected int size;
    protected int index;

    public ArrayIterator(E[] tab, int size){
        this.tab = tab;
        this.size = size;
        this.index = 0;
    }

    public boolean hasNext(){
        return this.index < size;
    }

    public E next(){
        return tab[index++];
    }
}