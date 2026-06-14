import java.util.Collection;
import java.util.Iterator;
import java.util.Objects;

public class Armoire extends StackContainer<Serrure, ObjectZork>{
    private String couleur;
    private int poidsAVide;

    /**
     * Constructeur 1 : Armoire vide.
     *
     * @requires serrure != null
     * @requires couleur != null
     * @requires emptyWeight >= 0
     * @ensures getCouleur().equals(couleur)
     * @ensures getEmptyWeight() == emptyWeight
     * @throws NullPointerException si serrure ou couleur est null
     */
    public Armoire(Serrure cle, String couleur, int poidsAVide){
        super(cle);
        Objects.requireNonNull(couleur, "La couleur ne peut pas être null");
        assert poidsAVide >= 0 : "Le poids à vide doit être positif ou nul";
        this.couleur = couleur;
        this.poidsAVide = poidsAVide;
    }

    /**
     * Constructeur 2 : Armoire initialisée avec une collection d'ObjetZork.
     *
     * @requires serrure != null
     * @requires couleur != null
     * @requires emptyWeight >= 0
     * @requires elements != null
     * @requires !elements.contains(null)
     * @ensures getCouleur().equals(couleur)
     * @ensures getEmptyWeight() == emptyWeight
     * @throws NullPointerException si serrure, couleur ou elements est null,
     *         ou si elements contient null
     */
    public Armoire(Serrure cle, String couleur, int poidsAVide, Collection<? extends ObjetZork> desObjets){
        super(cle, desObjets);
        Objects.requireNonNull(couleur, "La couleur ne peut pas être null");
        assert poidsAVide >= 0 : "Le poids à vide doit être positif ou nul";
        this.couleur = couleur;
        this.poidsAVide = poidsAVide;
    }

    public String getCouleur(){
        return this.couleur;
    }
    
    public int getEmptyWeight(){
        return this.poidsAVide;
    }

    public int getWeight(){
        int total = poidsAVide;
        Iterator<ObjectZork> it = iteratorInterne();
        while(it.hasNext()){
            total += it.next().getWeight();
        }

        return total;
    }
}
