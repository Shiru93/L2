package p2_7janvier2026;

import java.util.*;

public class EmptyIterator<E> implements Iterator<E> {
    public EmptyIterator() {
    }

    @Override
    public boolean hasNext() {
        return false;
    }

    @Override
    public E next() {
        throw new NoSuchElementException("L'itérateur est vide.");
    }

    @Override
    public void remove() {
        throw new IllegalStateException("Impossible de supprimer : next() n'a pas été appelé.");
    }
}
