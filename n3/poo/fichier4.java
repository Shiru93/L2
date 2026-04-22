public class SuperProgramme {
    public static void main(String[] args) {
        System.out.println("=== 1. CRÉATION DU MONDE (TD CONCEPT) ===");
        
        // Création des objets (avec hashcode/equals qui tournent en fond)
        ObjetZork epee = new ObjetZork("Excalibur", 10);
        ObjetZork potion = new ObjetZork("Potion", 2);
        ObjetZork epeeFausse = new ObjetZork("Excalibur", 10); // Même nom/poids

        // Test d'identité (TD Equals)
        if (epee.equals(epeeFausse)) {
            System.out.println("-> Test Equals : Les deux épées sont identiques sémantiquement.");
        }

        // Création Piece (TD ArrayList)
        Piece donjon = new Piece("Donjon Sombre");
        donjon.ajouter(epee);
        donjon.ajouter(potion);
        System.out.println(donjon);

        System.out.println("\n=== 2. JOUEUR ET INTERACTION (TD ABSTRAIT) ===");
        
        Joueur hero = new Joueur("Arthur", 15);
        
        // Polymorphisme : On traite donjon et hero comme des Conteneurs
        // Le héros prend tout ce qu'il y a dans le donjon
        System.out.println("-> Transfert des objets du donjon vers le joueur...");
        hero.ajouterTout(donjon); 
        
        System.out.println("Sac du héros : " + hero.getContenu());
        System.out.println("Reste dans le donjon : " + donjon.getContenu());

        System.out.println("\n=== 3. OUTILS GÉNÉRIQUES (TD GENERICITE) ===");
        
        // On associe le joueur à une mission via un Couple générique
        Couple<Joueur, String> mission = new Couple<>(hero, "Tuer le Dragon");
        System.out.println("Statut Mission : " + mission);

        System.out.println("\n=== 4. DÉCOR ET HÉRITAGE (TD HÉRITAGE) ===");
        
        Figure decoration = new Polygone(4, 5.0); // Un carré (4 côtés de 5m)
        // Dynamic Binding : Java appelle surface() de Polygone
        System.out.println("Il y a une décoration au mur : " + decoration);
        System.out.printf("Surface de la déco : %.2f m²\n", decoration.surface());
    }
}