// --- TD 19 Novembre : Héritage ---
abstract class Figure {
    public abstract double surface();
}

/**
 * Représente un polygone (Carré, Rectangle...).
 * @invariant cotes > 2
 */
class Polygone extends Figure {
    private int nbCotes;
    private double longueurCote;

    public Polygone(int nbCotes, double longueurCote) {
        this.nbCotes = nbCotes;
        this.longueurCote = longueurCote;
    }

    // Exemple simple de polymorphisme
    @Override
    public double surface() {
        // Formule simplifiée pour polygone régulier (juste pour l'exemple)
        return (nbCotes * Math.pow(longueurCote, 2)) / (4 * Math.tan(Math.PI / nbCotes));
    }
    
    @Override
    public String toString() { return "Polygone à " + nbCotes + " côtés"; }
}