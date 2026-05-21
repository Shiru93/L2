// Transforme les éléments d'un itérateur via une fonction
public class MappingIterator<T, R> implements Iterator<R> {
    public MappingIterator(Iterator<? extends T> iter, Function<? super T, ? extends R> f) { ... }
    // hasNext() et next() déjà implémentés
}