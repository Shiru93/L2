import java.util.Scanner;

public class JourParMois {
    public static void main(String [] args) {
        byte mois, nbjours = 0;
        short année;
        Scanner lectureClavier = new Scanner(System.in);

        System.out.print("De quel mois s'agit-il ? : ");
        mois = lectureClavier.nextByte();

        System.out.print("De quelle année ? : ");
        année = lectureClavier.nextShort();

        switch(mois){
            // Pour les mois à 31 jours
            case 1 : case 3 : case 5 : case 7 : case 8 : case 10 : case 12 : 
                nbjours = 31;
                break;
            
            // Pour les mois de 30 jours
            case 4 : case 6 : case 9 : case 11 :
                nbjours = 30;
                break;

            // Pour le mois de février
            case 2 :
                if (année % 4 == 0 && année % 100 != 0 || année % 400 == 0) nbjours = 29;
                else nbjours = 28;
                break;

            default:
                System.out.println("Impossible, ce mois n'existe pas");
                System.exit(0);
        }

        System.out.println("En " + année + ", le mois numéro " + mois + " a " + nbjours + " jours");
    }
}