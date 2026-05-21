import java.util.Iterator;

public class SalleIterator implements Iterator<Relique> {
    private Relique[] tab;
    private int size;
    private int index;

    public SalleIterator(Relique[] tab, int size) {
        this.tab   = tab;
        this.size  = size;
        this.index = 0;          // le curseur commence au début
    }

    @Override
    public boolean hasNext() {
        return index < size;     // il reste des éléments si le curseur n'a pas atteint la fin
    }

    @Override
    public Relique next() {
        return tab[index++];     // renvoie l'élément courant et avance le curseur
    }
}