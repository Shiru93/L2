public interface StrategieDeplacement {
    /*
     * Renvoie la salle voisine recommandée depuis la sall p,
     * ou null si aucune salle voisine n'existe
     * @param pred le critère de sélection des trésors d'intérêt
     */
    Salle choisirSalle(Salle p, Predicate<? super Tresor> pred);
}
