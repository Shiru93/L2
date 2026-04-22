import java.util.Scanner;

public class Rechercher{
    public static void main(String[] args){
        String phrase = "Mieux vaut tard que jamais";
        String soumo = "";
        int place;
        Scanner lectureClavier = new Scanner(System.in);

        System.out.println("Vous avez dit : " + phrase);

        // Extrait une sous-chaîne d'un mot
        soumo = phrase.substring(11, 15);
        System.out.println("De 11 à 15, la sous chaîne est : " + soumo);

        for(int i = 0; i < 5; i++)
            // Recherche le caractère placé à la position spécifiée en paramètre (Le 1er caractère occupe la position 0 et le dernier la position lenght()-1)
            System.out.println("en " + i + ", il y a : " + phrase.charAt(i));

        System.out.println("Entrez un mot : ");
        soumo = lectureClavier.next();

        // Recherche si le mot se termine par le ou les caractères passés en paramètres
        if(phrase.endsWith(soumo))
            System.out.println("La phrase se termine avec : " + soumo);
        else
            System.out.println("La phrase ne se finit pas avec : " + soumo);

        // Localise un caractère ou une sous-chaîne dans un mot, à partir du début du mot
        place = phrase.indexOf(soumo);
        if(place == -1)
            System.out.println("Ce mot n'existe pas dans : " + phrase);
        else
            System.out.println(soumo + " est à la position " + place);
    }
}