

public class ParValeur {
    public static void main(String[] args){
        int valeur = 2;
        
        System.out.println("Valeur = " + valeur + " avant tripler()");

        valeur = tripler(valeur);
        System.out.println("Valeur = " + valeur + " après tripler()");
    }

    public static int tripler(int valeur){
        System.out.println("Valeur = " + valeur + " dans tripler()");
        
        valeur *= 3;
        System.out.println("Valeur = " + valeur + " dans tripler()");

        return valeur;
    }
}