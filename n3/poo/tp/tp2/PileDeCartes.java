/**
 * Gère une pile de carte
 * 
 * @invariant getNbCartes() >= 0
 * @invariant getCartes() != null
 */
public class PileDeCartes{
    private Carte[] cartes;
    private int nbCartes;
    private boolean faceVisible;

    /**
     * Constructeur : initialise une pile vide
     * @param capaciteMax La taille maximale de la pile
     */
    public PileDeCartes(int capaciteMax, boolean faceVisible){
        this.cartes = new Carte[capaciteMax];
        this.nbCartes = 0;
        this.faceVisible = faceVisible;
    }

    /**
     * Remplit la pile avec un jeu complet tiré par famille et rang
     * 
     * @ensures La pile est pleine (selon la taille du jeu défini par les enums)
     * @ensures Les cartes sont ordonnées
     */

    public void creerPileDeCartes(){
        this.nbCartes = 0;
        for(Carte.Famille f : Carte.Famille.values()){
            for(Carte.Rang r : Carte.Rang.values()){
                if(this.nbCartes < this.cartes.length){
                    this.cartes[this.nbCartes] = new Carte(f, r);
                    this.nbCartes++;
                }
            }
        }
    }

    /**
     * Accesseur pour le sommet de la pile (utilisé par Jeu)
     * @return La carte au sommet ou null si vide
     */
    public Carte getSommet(){
        if(nbCartes > 0){
            return cartes[nbCartes - 1];
        }

        return null;
    }

    public boolean estFaceVisible(){
        return faceVisible;
    }

    public int getNbCartes(){
        return nbCartes;
    }
}