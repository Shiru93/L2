import java.util.Scanner;

public class Menu{
        String typeCompte = "", numeroCompte = "";
        double premiereValeur, taux;
        static Scanner lectScanner = new Scanner(System.in);

        public static void main(String[] args) {
        byte choix = 0;
        Menu menu = new Menu();

        do{
            choix = menuPrincipal();

            switch (choix) {
                case 1:
                    menu.creerCompte();
                    break;

                case 2:
                    menu.afficherCompte();
                    break;

                case 3:
                    menu.creerLigneComptable();
                    break;

                case 4:
                    sortir();

                case 5:
                    menu.aide();
                    break;

                default:
                    System.out.println("Choix invalide");
                    break;
            }
        } while(choix != 4);
    }

    public static byte menuPrincipal(){
        byte choix;
        
        System.out.println("1. Créer un compte");
        System.out.println("2. Afficher un compte");
        System.out.println("3. Créer une ligne comptable");
        System.out.println("4. Sortir");
        System.out.println("5. De l'aide");

        System.out.print("Votre choix : ");
        choix = lectScanner.nextByte();

        lectScanner.nextLine();

        System.out.print("\n");

        return choix;
    }

    public void creerCompte(){
        System.out.print("Type du compte [Types possibles : courant, joint, épargne] : ");
        typeCompte = lectScanner.nextLine();

        System.out.print("Numéro du compte : ");
        numeroCompte = lectScanner.nextLine();

        System.out.print("Première valeur créditée : ");
        premiereValeur = lectScanner.nextDouble();

        if(typeCompte.equals("épargne")){
            System.out.print("Taux de placement : ");
            taux = lectScanner.nextDouble();
        } else {
            taux = 0;
        }

        lectScanner.nextLine();

        System.out.println("\n--> Compte créé avec succès !");
    }

    public void afficherCompte(){
        String numeroSaisi;

        System.out.print("Veuillez saisir votre numéro de compte : ");
        numeroSaisi = lectScanner.nextLine();

        if(numeroSaisi.equals(numeroCompte) && !numeroCompte.equals("")) {
            System.out.println("Numéro : " + numeroCompte);
            System.out.println("Type : " + typeCompte);
            System.out.println("Solde : " + premiereValeur);

            if(typeCompte.equals("épargne")){
                System.out.println("Taux : " + taux + "%");
            }
        } else {
            System.out.println("Erreur : numéro invalide !");
        }

        System.err.print("\n");
    }

    public void creerLigneComptable(){
        System.out.println("Option non programmée");
    }

    public static void sortir(){
        System.out.println("Bye Bye.");
        System.exit(0);
    }

    public void aide(){
        System.out.println("Ceci est fait pour vous aider");
    }
}