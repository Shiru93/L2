public class Tresor {
    private final String nom;
    private final int valeur;
    private final boolean rare;

    public Tresor(String nom, int valeur, boolean rare){
        this.nom = nom;
        this.valeur = valeur;
        this.rare = rare;
    }

    public String getNom(){
        return nom;
    }

    public int getValue(){
        return valeur;
    }

    public boolean estRare(){
        return rare;
    }
}