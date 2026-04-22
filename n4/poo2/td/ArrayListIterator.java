import java.util.ListIterator;

public class ArrayListIterator<E> extends ArrayIterator<E> implements ListIterator<E>{
    public ArrayListIterator(E[] tab, int size){
        super(tab, size);
    }

    public int nextIndex(){
        return this.index;
    }

    public boolean hasPrevious(){
        return this.index > 0;
    }

    public int previousIndex(){
        if(!hasPrevious()) return -1;

        return this.index - 1;
    }
}