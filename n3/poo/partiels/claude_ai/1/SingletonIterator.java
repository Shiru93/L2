import java.util.Iterator;
import java.util.NoSuchElementException;

public class SingletonIterator<E> implements Iterator<E>{
    private final E element;
    private boolean dejaLu;

    public SingletonIterator(E element){
        this.element = element;
        this.dejaLu = false;
    }

    @Override
    public boolean hasNext(){
        return !dejaLu;
    }

    @Override
    public E next(){
        if(dejaLu){
            throw new NoSuchElementException();
        }

        dejaLu = true;

        return element;
    }

    @Override
    public void remove(){
        throw new UnsupportedOperationException();
    }
}