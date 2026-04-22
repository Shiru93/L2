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
}