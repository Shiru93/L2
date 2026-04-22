/**
 * Représente le joueur qui se déplace et porte des objets
 * 
 * @invariant getPoidsTotal() <= getPoidsMax()
 * @invariant getPieceCourant() != null
 */
public class Joueur{
    private String nom;
    private Piece pieceCourante;
    private ObjetZork[] inventaire;
    private int nbObjetsPossedes;
    private int poidsTotalCourant;
    private final int POIDS_MAX;

    /**
     * Constructeur 
     * @param nom Nom du joueur
     * @param pieceDeDepart La pièce o`u le joueur commence 
     * @param poidsMax Le poids maximum que le joueur peut porter 
     */
    public Joueur(String nom, Piece pieceDeDepart, int poidsMax){
        this.nom = nom;
        this.pieceCourante = pieceDeDepart;
        this.POIDS_MAX = poidsMax;

        this.inventaire = new ObjetZork[10];
        this.nbObjetsPossedes = 0;
        this.poidsTotalCourant = 0;
    }

    /**
     * @return Le poids total des objets portés
     */
    public int getPoidsTotal(){
        return this.poidsTotalCourant;
    }

    /**
     * @return La capacité maximale de port
     */
    public int getPoidsMax(){
        return this.POIDS_MAX;
    }

    /**
     * @return La pièce o`u se trouve le joueur actuellement
     */
    public Piece getPieceCourante(){
        return this.pieceCourante;
    }
}   