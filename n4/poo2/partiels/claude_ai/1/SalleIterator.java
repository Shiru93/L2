
import java.util.Iterator;

public class SalleIterator implements Iterator<Tresor> {
    private Tresor[] tab;
    private int nbElts;
    private int index;

    public SalleIterator(Tresor[] tab, int nbElts) {
        this.tab = tab;
        this.nbElts = nbElts;
        this.index = 0;
    }

    public boolean hasNext(){
        return index < nbElts;
    }

    public Tresor next(){
        return tab[index++];
    }
}