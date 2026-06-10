import java.util.Collection;
import java.util.Objects;
import java.util.Iterator;

public class Bibliotheque<E> extends FilteredContainer<Cadenas, ObjetZork> {
    private final String titre;
    private final int emptyWeight;

    /**
     * Constructeur 1 : Bibliotheque vide.
     *
     * @requires cadenas != null
     * @requires titre != null
     * @requires emptyWeight >= 0
     * @ensures getTitre().equals(titre)
     * @ensures getEmptyWeight() == emptyWeight
     * @throws NullPointerException si cadenas ou titre est null
     */
    public Bibliotheque(Cadenas cle, String titre, int emptyWeight){
        super(cle);
        Objects.requireNonNull(titre, "Le titre ne peut pas être null");
        assert emptyWeight >= 0 : "Le poids à vide doit être positif ou nul";
        this.titre = titre;
        this.emptyWeight = emptyWeight;
    }

    /**
     * Constructeur 2 : Bibliotheque initialisée avec une collection d'ObjetZork.
     *
     * @requires cadenas != null
     * @requires titre != null
     * @requires emptyWeight >= 0
     * @requires elements != null
     * @requires !elements.contains(null)
     * @ensures getTitre().equals(titre)
     * @ensures getEmptyWeight() == emptyWeight
     * @throws NullPointerException si cadenas, titre ou elements est null,
     *         ou si elements contient null
     */
    public Bibliotheque(Cadenas cle, String titre, int emptyWeight, Collection<? extends E> desObjets){
        super(cle, desObjets);
        Objects.requireNonNull(titre, "Le titre ne peut pas être null");
        assert emptyWeight >= 0 : "Le poids à vide doit être positif ou nul";
        this.titre = titre;
        this.emptyWeight = emptyWeight;
    }

    public String getTitre(){
        return this.titre;
    }

    public int getEmptyWeight(){
        return this.emptyWeight;
    }

    public int getWeight(){
        int total = emptyWeight;
        Iterator<ObjetZork> it = iteratorInterne();
        while (it.hasNext()) {
            total += it.next().getWeight();
        }
        return total;
    }
}