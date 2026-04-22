import java.util.Scanner;

public class Carre {
    public static void main (String[] args){
        // Déclaration des variables représentant le périmètre et le côté
        double lePerimetre, leCote;

        // Déclaration de la variable représentant la lecture au clavier
        Scanner lectureClavier = new Scanner(System.in);
        
        // Afficher le message "Valeur du côté : " à l'écran
        System.out.print("Valleur du côté : ");

        // Lire au clavier une valeur
        // Placer cette valeur dans la variable correspondante
        leCote = lectureClavier.nextDouble();

        // Calculer le pérmiètre du carré
        lePerimetre = 4 * leCote;

        // Afficher le résultat
        System.out.print("Le carré de côté " + leCote + " a pour périmètre " + lePerimetre + "\n");
    }
}