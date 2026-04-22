public class Polygone extends Figure {
    private int nbCotes;
    private double longueurCote;

    public Polygone(int nbCotes, double longueurCote) {
        this.nbCotes = nbCotes;
        this.longueurCote = longueurCote;
    }

    @Override
    public double surface() {
        // Formule simplifiée pour l'exemple
        return (nbCotes * Math.pow(longueurCote, 2)) / (4 * Math.tan(Math.PI / nbCotes));
    }
    
    @Override
    public String toString() { 
        return "Polygone à " + nbCotes + " côtés"; 
    }
}