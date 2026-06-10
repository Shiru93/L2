
import java.util.Collection;
import java.util.HashSet;
import java.util.Set;

public class FilteredContainer<K, E> extends Object implements Iterable<E> {
    private final K cle;
    private boolean ouvert;
    private final Set<E> elements;

    public FilteredContainer(K cle){
        if(cle == null){
            throw new NullPointerException();
        }

        this.cle = cle;
        ouvert = true;
        elements = new HashSet<>();
    }

    public FilteredContainer(K cle, Collection<? extends E> desObjets){
        if(cle == null || desObjets == null || desObjets.contains(null)){
            throw new NullPointerException();
        }

        this.cle = cle;
        ouvert = true;
        elements = new HashSet<>(desObjets);
    }

    public boolean  hasKey(K cle){
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
        if(this.cle == cle) ouvert = false;
        return ouvert;
    }

    public boolean isOpen(){
        return this.ouvert;
    }

    public void add(E elt){
        if(!this.ouvert)
            throw new IllegalStateException();

        if(elt == null)
            throw new NullPointerException();

        if(!this.elements.contains(elt)) 
            this.elements.add(elt);
    }

    public boolean remove(Object obj){
        if(!this.ouvert)
            throw new IllegalStateException();

        return elements.remove(obj);
    }

    public boolean contains(Object obj){
        if(!ouvert || obj == null) return false;
        return elements.contains(obj);

        for(E elt : elements){
            if(elt.equals(obj))
                return true;
        }

        return false;
    }

    public int size(){
        if(!ouvert) return 0;

        int count = 0;
        for(E elt : elements)
            count++;

        return count;
    }

    public int frequencyOf(Object obj){
        if(!ouvert) return 0;
        
        int count = 0;
        for(E elt : elements){
            if(elt.equals(obj))
                count++;
        }

        return count;
    }

    public Iterator<E> iterator(){
        return this.iterator();
    }
}