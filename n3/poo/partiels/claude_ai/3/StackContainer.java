import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;

public class StackContainer<K, E> extends Object implements Iterable<E> {
    private final K cle;
    private List<E> elements;
    private boolean ouvert;

    public StackContainer(K cle) {
        if(cle == null){
            throw new NullPointerException();
        }

        this.cle = cle;
        ouvert = true;
        elements = new ArrayList<>();
    }

    public StackContainer(K cle, Collection<? extends E> desObjets){
        if(cle == null || desObjets == null || desObjets.contains(null)){
            throw new NullPointerException();
        }

        this.cle = cle;
        ouvert = true;
        elements = new ArrayList<>(desObjets);
    }

    public boolean hasKey(K cle){
        if(cle == null) return false;
        return this.cle.equals(cle);
    }

    public boolean open(K cle){
        if(hasKey(cle)){
            ouvert = true;
            return true;
        }

        return false;
    }

    public boolean close(K cle){
        if(hasKey(cle)){
            ouvert = false;
            return true;
        }

        return false;
    }

    public boolean isOpen(){
        return this.ouvert;
    }

    public void add(E elt){
        if(elt == null) throw new NullPointerException();
        if(!isOpen()) throw new IllegalStateException();

        this.elements.add(elt);
    }

    public boolean remove(Object obj){
        if(!isOpen()) throw new IllegalStateException();
        return this.elements.remove(obj);
    }

    public boolean contains(Object obj){
        if(!ouvert || obj == null) return false;
        return this.elements.contains(obj);
    }

    public int size(){
        return this.elements.size();
    }

    public int frequencyOf(Object obj){
        if(!ouvert) return 0;

        int count = 0;
        for(E elt : elements){
            if(elt.equals(obj)) count++;
        }

        return count;
    }

    public Iterator<E> iterator(){
        if(!ouvert) return new EmptyIterator<>();
        return new ReverseIterator<>(elements);
    }

    protected Iterator<E> iteratorInterne() {
        return elements.iterator();
    }
}   