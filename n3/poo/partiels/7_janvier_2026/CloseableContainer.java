
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Objects;

public class CloseableContainer<K,E> extends Object implements Iterable<E>{
    private final K key;
    private boolean ouvert;
    private List<E> elements;   

    public CloseableContainer(K cle){
        Objects.requireNonNull(cle, "La clé ne peut pas être null");
        // Ce que Objects.requireNonNull fait en interne :
        // if (cle == null) {
        //     throw new NullPointerException("La clé ne peut pas être null");
        // }

        this.elements = new ArrayList<>();
        this.key = cle;
        this.ouvert = true;
    }

    public CloseableContainer(K cle, Collection<? extends E> desObjets){
        Objects.requireNonNull(cle, "La clé ne peut pas être null");
        Objects.requireNonNull(desObjets, "La collection ne peut pas être null");
        if(desObjets.contains(null)){
            throw new NullPointerException("La collection ne peut pas contenir null");
        }

        this.elements = new ArrayList<>(desObjets);
        this.key = cle;
        this.ouvert = true;
    }

    public void add(E elt){
        Objects.requireNonNull(elt, "L'élément ne peut pas être null");

        if(!this.ouvert){
            throw new IllegalStateException("Le CloseableContainer est fermé");
        }

        elements.add(elt);
    }

    public boolean hasKey(K cle){
        if(cle == null) return false;

        return this.key.equals(cle);
    }

    public boolean open(K cle){
        if(this.hasKey(cle)) {
            this.ouvert = true;
            return true;
        }

        return false;
    }

    public boolean close (K cle){
        if(this.hasKey(cle)){
            this.ouvert = false;
            return true;
        }

        return false;
    }

    public boolean isOpen(){
        return this.ouvert;
    }

    public int frequencyOf(Object obj){
        Objects.requireNonNull(obj, "L'objet ne doit pas être null");

        if(this.ouvert == false) return 0;

        int count = 0;
        for (E elt : elements) {
            if (elt.equals(obj)) count++;
        }
        return count;
    }

    // public int frequencyOf(Object obj) {
    //     if (!ouvert) return 0;
    //     return Collections.frequency(elements, obj);
    // }

    public boolean contains(Object obj){
        Objects.requireNonNull(obj, "L'objet ne doit pas être null");

        if(!this.ouvert) return false;

        for(E elt : elements){
            if(elt.equals(obj)) return true;
        }

        return false;
    }

    public int size(){
        if(!this.ouvert) return 0;
        return this.size();
    }

    public boolean remove(Object obj){
        if(!ouvert){
            throw new IllegalStateException("Le CloseableContainer est fermé");
        }

        return elements.remove(obj);
    }

    @Override
    public Iterator<E> iterator(){
        if(!ouvert){
            return new EmptyIterator<>();
        }

        return elements.iterator();
    }

    public boolean hasSameContent(Collection<?> c){
        if(c == null) return false;
        if(!ouvert) return c.isEmpty();
        if(element.size() != c.size()) return false;

        for(E elt : elements){
            if(Collections.frequency(elements, elt) != Collections.frequency(c, elt))
                return false;
        }

        return true;
    }

    protected Iterator<E> iteratorInterne() {
        return elements.iterator(); // sans vérification isOpen
    }
}