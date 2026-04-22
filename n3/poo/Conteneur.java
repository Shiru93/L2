import java.util.ArrayList;
import java.util.List;

public abstract class Conteneur {
    // Méthodes abstraites (que les enfants DOIVENT coder)
    public abstract void ajouter(ObjetZork oz);
    public abstract boolean retirer(ObjetZork oz);
    public abstract List<ObjetZork> getContenu();

    /**
     * Transfère tout le contenu d'un autre conteneur vers celui-ci.
     */
    public void ajouterTout(Conteneur source) {
        // On fait une copie de la liste pour éviter les bugs pendant la boucle
        List<ObjetZork> copie = new ArrayList<>(source.getContenu());
        
        for (ObjetZork oz : copie) {
            // Si on arrive à le retirer de la source, on l'ajoute ici
            if (source.retirer(oz)) {
                this.ajouter(oz);
            }
        }
    }
}