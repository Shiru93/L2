import java.util.ArrayList;
import java.util.List;

// --- TD 8 Décembre : Généricité ---
/**
 * Classe générique représentant une paire d'éléments.
 * @param <E> Type du premier élément
 * @param <F> Type du second élément
 */
class Couple<E, F> {
    private final E premier;
    private final F second;

    public Couple(E premier, F second) {
        this.premier = premier;
        this.second = second;
    }
    
    @Override
    public String toString() { return "(" + premier + ", " + second + ")"; }
}

// --- TD 24 Novembre : Classes Abstraites ---
/**
 * Abstraction regroupant Piece et Joueur.
 * @invariant getPoidsTotal() >= 0
 */
abstract class Conteneur {
    // Chaque conteneur gère sa liste différemment (ArrayList vs autre)
    public abstract void ajouter(ObjetZork oz);
    public abstract boolean retirer(ObjetZork oz);
    public abstract List<ObjetZork> getContenu();

    /**
     * Méthode concrète utilisant le polymorphisme.
     * Transfère tout le contenu d'un conteneur source vers celui-ci.
     */
    public void ajouterTout(Conteneur source) {
        // On copie pour éviter les erreurs de modification concurrente
        List<ObjetZork> copie = new ArrayList<>(source.getContenu());
        for (ObjetZork oz : copie) {
            if (source.retirer(oz)) {
                this.ajouter(oz);
            }
        }
    }
}