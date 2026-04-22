import java.util.Scanner;

public class FonctionMathématique {
    public static void main(String [] args){
        double résultat, a, b;
        Scanner lectureClavier = new Scanner(System.in);

        System.out.print("Entrez une première valeur : ");
        a = lectureClavier.nextDouble();

        System.out.print("Entrez une seconde valeur : ");
        b = lectureClavier.nextDouble();

        // Calcule du cosinus
        résultat = Math.cos(a);
        System.out.println("cos(" + a + ") = " + résultat);

        // Calcul du sinus
        résultat = Math.sin(a);
        System.out.println("sin(" + a + ") = " + résultat);
        
        // Calcule de la tangente
        résultat = Math.tan(a);
        System.out.println("tan(" + a + ") = " + résultat);

        // Calcule du logarithme
        résultat = Math.log(a);
        System.out.println("log(" + a + ") = " + résultat);

        // Calcule de l'exponentielle
        résultat = Math.exp(a);
        System.out.println("exp(" + a + ") = " + résultat);

        // Arondir à l'entier inférieur
        résultat = Math.floor(a);
        System.out.println("floor(" + a + ") = " + résultat);

        // Arrondir à l'entier supérieur
        résultat = Math.ceil(a);
        System.out.println("ceil(" + a + ") = " + résultat);

        // Calculer la racine carré d'un nombre
        résultat = Math.sqrt(a);
        System.out.println("sqrt(" + a + ") = " + résultat);

        // Calcule de a à la puissance b
        résultat = Math.pow(a, b);
        System.out.println("pow(" + a + ") = " + résultat);

        // Valeur absolue de a
        résultat = Math.abs(a);
        System.out.println("abs(" + a + ", " + b + ") = " + résultat);

        // Trouver la plus grande valeur entre a et b
        résultat = Math.max(a, b);
        System.out.println("max(" + a + ", " + b + ") = " + résultat);

        // Trouver la plus petite valeur entre a et b
        résultat = Math.min(a, b);
        System.out.println("min(" + a + ", " + b + ") = " + résultat);

        // Tirer un nombre au hasard entre 0 et 1
        résultat = Math.random();
        System.out.println("Random() = " + résultat);
    }

    public static double périmètre(int r){
        double p;

        // Math.PI correspond à la valeur PI
        p = 2 * Math.PI * r;

        return p;
    }
}