public class SuperProgramme {
    public static void main(String[] args) {
        System.out.println("=== 1. TEST JEU (Objets & Héritage) ===");
        
        // Création des objets
        ObjetZork epee = new ObjetZork("Excalibur", 10);
        ObjetZork potion = new ObjetZork("Potion", 2);

        // Création de la pièce
        Piece donjon = new Piece("Donjon Sombre");
        donjon.ajouter(epee);
        donjon.ajouter(potion);
        System.out.println(donjon);

        // Création du joueur
        Joueur hero = new Joueur("Arthur", 15);
        
        // Action : Le héros prend tout le contenu du donjon
        System.out.println("-> Arthur prend tout ce qu'il y a dans le donjon...");
        hero.ajouterTout(donjon); 
        
        System.out.println("Sac du héros : " + hero.getContenu());
        System.out.println("Reste dans le donjon : " + donjon.getContenu());

        System.out.println("\n=== 2. TEST OUTILS (Généricité) ===");
        
        // Utilisation de la classe générique Couple
        Couple<Joueur, String> mission = new Couple<>(hero, "Tuer le Dragon");
        System.out.println("Mission actuelle : " + mission);

        System.out.println("\n=== 3. TEST DECOR (Géométrie) ===");
        
        // Utilisation de la classe Polygone
        Figure decoration = new Polygone(4, 5.0); // Un carré
        System.out.println("Décoration : " + decoration);
        System.out.printf("Surface : %.2f m²\n", decoration.surface());
    }
}