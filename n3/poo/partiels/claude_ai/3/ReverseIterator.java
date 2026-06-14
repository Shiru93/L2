import java.util.Iterator;
import java.util.List;
import java.util.NoSuchElementException;

public class ReverseIterator<E> implements Iterator<E> {

    private final List<E> liste;
    private int index;

    public ReverseIterator(List<E> liste) {
        this.liste = liste;
        this.index = liste.size() - 1; // on commence à la fin
    }

    @Override
    public boolean hasNext() {
        return index >= 0;
    }

    @Override
    public E next() {
        if (!hasNext()) {
            throw new NoSuchElementException();
        }
        return liste.get(index--); // retourne l'élément puis décrémente
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }
}