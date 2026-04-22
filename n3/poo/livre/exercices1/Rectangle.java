import java.util.Scanner;

public class Rectangle {
    public static void main(String[] args) {
        double surface, largeur, longueur;
        Scanner lectureClavier = new Scanner(System.in);

        System.out.print("Valeur de la largeur : ");
        largeur = lectureClavier.nextDouble();

        System.out.print("Valeur de la longueur : ");
        longueur = lectureClavier.nextDouble();

        surface = largeur * longueur;

        System.out.print("Le rectangle de largeur " + largeur + " et de longueur " + longueur + " a pour surface " + surface + "\n");
    }
}