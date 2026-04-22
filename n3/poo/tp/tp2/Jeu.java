public class Jeu {
    /**
     * Affiche uniquement la carte du dessus et le nombre de cartes
     * 
     * @param pile La pile à afficher
     * @require pile != null
     */
    public static void afficherSommet(PileDeCartes pile){
        System.out.println("Nombre de cartes dans la pile : " + pile.getNbCartes());

        if(pile.estFaceVisible()){
            Carte sommet = pile.getSommet();
            if(sommet != null){
                System.out.println("Carte visible : " + sommet.toString());
            } else {
                System.out.println("La pile est vide");
            }
        } else {
            System.out.println("Carte face cachée");
        }
    }

    public static void main(String[] args){
        Carte c1 = new Carte();
        System.out.println("Carte 1 : " + c1.toString());

        Carte c2 = new Carte();
        System.out.println("Carte 2 : " + c2.toString());

        System.out.println("-------------------");

        PileDeCartes maPile = new PileDeCartes(52, true);

        maPile.creerPileDeCartes();

        afficherSommet(maPile);
    }
}