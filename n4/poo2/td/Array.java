import java.util.Iterator;

public class Array<E> implements Cloneable, Iterable<E>, java.io.Serializable {
    private E[] elements;
    public final int length;

    public E[] clone(){
        try {
            return (E[])super.clone();
        } catch (CloneNotSupportedException e) {
            throw new InternalError(e.getMessage());
        }
    }

    public Array(int size){
        length = size;
        elements = (E[]) new Object[size];
    }

    public E get(int index){
        return this.elements[index];
    }
    
    public void set(int index, E elt){
        this.elements[index] = elt;
    }

    public Iterator<E> iterator(){
        return new ArrayIterator<E>(elements, length);
    }
}