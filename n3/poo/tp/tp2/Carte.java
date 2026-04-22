/**
 * Représente une carte à jouer standard caractérisée par une famille et un rang
 * Cette classe est immuable (ses attributs ne changent pas après construction)
 * 
 * @invariant getFamille() != null
 * @invariant getRang() != null
 */

public class Carte {
	public enum Famille {PIQUE, COEUR, CARREAU, TREFLE}
	public enum Rang {AS, DEUX, TROIS, QUATRE, CINQ, SIX, SEPT, HUIT, NEUF, DIX, VALET, DAME, ROI}
	
    private Famille famille;
    private Rang rang;
    
    /**
     * Constructeur par défaut (Exercice 2 : Roi de Trèfle)
     * Permet de créer l'instance demandée "Roi de Trèfle"
     * 
     * @ensures getFamille() == Famille.TREFLE
     * @ensures getRang() == Rang.ROI
     */
    public Carte() {
    	this.famille = Famille.TREFLE;
    	this.rang = Rang.ROI;
    }

    /**
     * Seconde constructeur (Exercice 3)
     * Construit une nouvelle carte avec la famille et le rang spécifiés
     * 
     * @param famille La famille de la carte
     * @param rang Le rang de la carte
     * 
     * @requires famille != null
     * @requires rang != null
     * 
     * @ensures this.famille == famille
     * @ensures this.rang == rang
     */
    public Carte(Famille famille, Rang rang){
        if(famille == null || rang == null){
            throw new IllegalArgumentException("Famille et Rang requis");
        }

        this.famille = famille;
        this.rang = rang;
    }

    /**
     * Retourne une description textuelle de la carte
     * (Exercice 2 : méthode d'affichage
     */
    public String toString(){
        return rang + " de " + famille;
    }
    
    public Famille getFamille(){
    	return famille;
    }
    
    public Rang getRang() {
    	return rang;
    }
}