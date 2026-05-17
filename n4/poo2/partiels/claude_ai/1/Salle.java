import java.util.*;

public class Salle implements Iterable<Tresor> {
    private Tresor[] tresors;
    private int nbTresors;

    public Salle(){
        tresors = new Tresor[20];
        nbTresors = 0;
    }

    public void ajouterTresor(Tresor t){
        tresors[nbTresors++] = t;
    }

    public Iterator<Tresor> iterator(){
        return new SalleIterator(tresors, nbTresors);
    }

    public Salle salleSuivante(Direction d) {/* Renvoie null si pas de voisin */}
}