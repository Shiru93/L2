/**
 * Représente un objet transportable ou non dans le jeu Zork
 * Classe immuable pour simplifier la gestion
 * 
 * @invariant getNom() != null
 * @invariant getPoids() > 0
 */
public class ObjetZork{
    private String nom;
    private int poids;
    private boolean transportable;

    /**
     * Crée un nouvel objet
     * 
     * @param nom Le nom de l'objet
     * @param poids Le poids de l'objet (doit être > 0)
     * @param transportable true si le joueur peut le prendre
     * 
     * @requires nom != null
     * @requires poids > 0
     * 
     * @ensures this.nom == nom
     * @ensures this.poids == poids
     */

    public ObjetZork(String nom, int poids, boolean transportable){
        if(nom == null){
            throw new NullPointerException("Le nom ne peut être null");
        }

        if(poids <= 0){
            throw new IllegalArgumentException("Le poids doit être positif");
        } 

        this.nom = nom;
        this.poids = poids;
        this.transportable = transportable;
    }

    public String getNom(){
        return nom;
    }

    public int getPoids(){
        return poids;
    }

    public boolean transportable(){
        return transportable;
    }

    @Override
    public String toString(){
        return nom + " (" + poids + "kg)";
    }

    /**
     * Teste l'égalité sémantique
     * 
     * @param o L'objet à comparer
     * 
     * @return true si même type, même nom, même poids
     */
    @Override
    public boolean equals(Object o){
        if(this == o) {
            return true;
        }

        if(o == null || getClass() != o.getClass()){
            return false;
        }

        ObjetZork other = (ObjetZork) o;

        return poids == other.poids && (nom == null ? other.nom == null : nom.equals(other.nom));
    }

    /**
     * Calcule le hashCode
     * INDISPENSABLE car on a redéfini equals
     * 
     * @return Un entier unique basé sur nom et poids
     */
    @Override
    public int hashCode(){
        int result = 17;
        result = 31 * result + poids;
        result = 31 *result + (nom != null ? nom.hashCode() : 0);

        return result;
    }
}