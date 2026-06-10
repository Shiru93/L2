import java.util.Iterator;
import java.util.NoSuchElementException;

public class PairIterator<E> implements Iterator<E> {

    private final E premier;
    private final E second;
    private int index; // 0 = rien lu, 1 = premier lu, 2 = tout lu

    public PairIterator(E premier, E second) {
        this.premier = premier;
        this.second = second;
        this.index = 0;
    }

    @Override
    public boolean hasNext() {
        return index < 2;
    }

    @Override
    public E next() {
        if (index == 0) {
            index = 1;
            return premier;
        }
        if (index == 1) {
            index = 2;
            return second;
        }
        throw new NoSuchElementException();
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }
}