// Filtre les éléments d'un itérateur selon un prédicat
public class FilterIterator<E> implements Iterator<E> {
    public FilterIterator(Iterator<? extends E> iter, Predicate<? super E> p) { ... }
    // hasNext() et next() déjà implémentés
}