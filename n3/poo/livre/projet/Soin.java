public class Soin {
    private final String nom;
    private final int valeur;

    public Soin(String nom, int valeur) {
        this.nom = nom;
        this.valeur = valeur;
    }

    public String getNom(){
        return this.nom;
    }

    public int getValeur(){
        return this.valeur;
    }
}