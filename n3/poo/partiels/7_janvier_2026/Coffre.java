import java.util.Collection;
import java.util.Iterator;
import java.util.Objects;

public class Coffre extends CloseableContainer<Cle, ObjetZork> {

    private final String description;
    private final int emptyWeight;

    /**
     * Constructeur 1 : Coffre vide.
     *
     * @requires description != null
     * @requires emptyWeight >= 0
     * @requires cle != null
     * @ensures getDescription().equals(description)
     * @ensures getEmptyWeight() == emptyWeight
     */
    public Coffre(String description, int emptyWeight, Cle cle) {
        super(cle);
        Objects.requireNonNull(description, "La description ne peut pas être null");
        assert emptyWeight >= 0 : "Le poids à vide doit être positif ou nul";
        this.description = description;
        this.emptyWeight = emptyWeight;
    }

    /**
     * Constructeur 2 : Coffre initialisé avec une collection d'ObjetZork.
     *
     * @requires description != null
     * @requires emptyWeight >= 0
     * @requires cle != null
     * @requires elements != null
     * @requires !elements.contains(null)
     * @ensures getDescription().equals(description)
     * @ensures getEmptyWeight() == emptyWeight
     */
    public Coffre(String description, int emptyWeight, Cle cle, Collection<? extends ObjetZork> elements) {
        super(cle, elements);
        Objects.requireNonNull(description, "La description ne peut pas être null");
        assert emptyWeight >= 0 : "Le poids à vide doit être positif ou nul";
        this.description = description;
        this.emptyWeight = emptyWeight;
    }

    public String getDescription() {
        return description;
    }

    public int getEmptyWeight() {
        return emptyWeight;
    }

    /**
     * Renvoie le poids total = poids à vide + somme des poids des objets contenus.
     * Fonctionne même si le coffre est fermé (via iteratorInterne).
     */
    public int getWeight() {
        int total = emptyWeight;
        Iterator<ObjetZork> it = iteratorInterne();
        while (it.hasNext()) {
            total += it.next().getWeight();
        }
        return total;
    }
}