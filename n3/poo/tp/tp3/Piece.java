/**
 * Un pièce du jeu contenant des objets
 * Gestion interne via un tableau fixe
 * 
 * @invariant getNbObjets() >= 0
 * @invariant getNbObjets() <= getCapaciteMax()
 */
public class Piece{
    private String description;
    private ObjetZork[] objets;
    private int nbObjets;
    private static final int CAPACITE_MAX = 10;

    /**
     * Constructeur simple
     * @param description Description de la pièce
     */
    public Piece(String description){
        this.description = description;
        this.objets = new ObjetZork[CAPACITE_MAX];
        this.nbObjets = 0;
    }

    /**
     * Constructeur avec initialisation d'objets
     * 
     * @param description Description de la pièce
     * @param objetsInitiaux Tableau d'objets à mettre au départ
     * 
     * @requires objetsInitiaux != null
     * @requires objetsInitiaux.lenght <= CAPACITE_MAX
     */

    public Piece(String description, ObjetZork[] objetsInitiaux){
        this(description);

        for(int i = 0; i < objetsInitiaux.length; i++){
            if(objetsInitiaux[i] != null){
                this.ajouterObjet(objetsInitiaux[i]);
            }
        }
    }

    /**
     * Ajoute un objet dans la pièce
     * 
     * @param oz L'objet à ajouter
     * @return true si l'ajout a réussi, false si la pièce est pleine
     * 
     * @requires oz != null
     * @ensures \result == true ==> contient(oz)
     */
    public boolean ajouterObjet(ObjetZork oz){
        if(this.nbObjets >= this.objets.length){
            return false;
        }

        this.objets[this.nbObjets] = oz;
        this.nbObjets++;
        
        return true;
    }

    /**
     * Retire un objet de la pièce
     * Note : Avec un tableau, c'est pénible, il faut décaler les éléments ou échanger avec le dernier 
     * Ici, on utilise la technique de l'échange avec le dernier élément pour être efficace
     * 
     * @param oz L'objet à retirer
     * @return true si l'objet était présent et a été retiré
     */
    public boolean retirerObjet(ObjetZork oz){
        for(int i = 0; i < this.nbObjets; i++){
            if(this.objets[i] == oz){
                this.objets[i] = this.objets[this.nbObjets - 1];
                this.objets[this.nbObjets - 1] = null;
                this.nbObjets--;

                return true;
            }
        }

        return false;
    }     
}