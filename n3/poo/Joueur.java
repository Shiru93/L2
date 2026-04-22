import java.util.ArrayList;
import java.util.List;

public class Joueur extends Conteneur {
    private String nom;
    private int chargeMax;
    private ArrayList<ObjetZork> sacADos;

    public Joueur(String nom, int chargeMax) {
        this.nom = nom;
        this.chargeMax = chargeMax;
        this.sacADos = new ArrayList<>();
    }

    public int getPoidsActuel() {
        int total = 0;
        for (ObjetZork oz : sacADos) total += oz.getPoids();
        return total;
    }

    @Override
    public List<ObjetZork> getContenu() { return sacADos; }

    @Override
    public void ajouter(ObjetZork oz) {
        if (getPoidsActuel() + oz.getPoids() <= chargeMax) {
            sacADos.add(oz);
            System.out.println(nom + " ramasse : " + oz);
        } else {
            System.out.println(nom + " : Trop lourd ! Impossible de prendre " + oz);
        }
    }

    @Override
    public boolean retirer(ObjetZork oz) {
        return sacADos.remove(oz);
    }
}