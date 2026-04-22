import java.util.Scanner;

public class Maximum {
    public static void main(String [] args) {
        int valeur1 = 0, valeur2 = 0, max = 0;
        Scanner lectureClavier = new Scanner(System.in);

        System.out.print("Veuillez entrer une première valeur : ");
        valeur1 = lectureClavier.nextInt();

        System.out.print("Veuillez entrer une seconde valeur : ");
        valeur2 = lectureClavier.nextInt();

        if (valeur1 > valeur2) {
            System.out.println("Affichage des valeurs dans l'ordre croissant : " + valeur2 + " " + valeur1);
            max = valeur1;
        } else {
            System.out.println("Affichage des valeurs dans l'ordre croissant : " + valeur1 + " " + valeur2);
            max = valeur2;
        }

        System.out.println("La plus grande valeur est : " + max);
    }
}