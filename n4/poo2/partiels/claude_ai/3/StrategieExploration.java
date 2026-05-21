import java.util.*;

public interface StrategieExploration{
    /*
     * Renvoie la salle voisine recommandée depuis la salle p en fonction d'un critère pred sur les Reliques ou null si aucune salle voisine n'existe 
     */
    Salle choisirSalle(salle p, Predicate<? super Relique> pred);
}