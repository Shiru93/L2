import java.util.Scanner;

public class Cercle {
    public static void main(String[] arg){
        // 1. Déclarer les variables
        double unRayon, lePerimetre, laSurface;
        Scanner lectureClavier = new Scanner(System.in);

        // 2.a Afficher le message "Valeur du rayon : " à l'écran
        System.out.print("Valeur du rayon : ");

        // 2.b Lire au clavier une valeur, placer cette valeur dans la variable unRayon
        unRayon = lectureClavier.nextDouble();

        // 3.a Calculer la circonférence en utilisant la formule consacrée
        lePerimetre = 2 * Math.PI * unRayon;

        // 3.b Calculer la surface en utilisant la formule consacrée
        laSurface = Math.PI * unRayon * unRayon;

        // 4. Afficher le résultat
        System.out.print("Le cercle de rayon " + unRayon + " a pour perimetre : " + lePerimetre + "\n");

        // 4. Afficher le résultat
        System.out.print("Le cercle de rayon " + unRayon + " a pour surface : " + laSurface + "\n");
    }
}