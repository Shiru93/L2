public class Visibilite {
    static int variable_de_classe = 2;
    static int variable = 1;
    public static void main(String [] args){
        // Déclaration des variables
        int variable_locale = 2;
        int variable = 9;

        System.out.println("variable_locale = " + variable_locale + " avant modifier()");
        modifier(variable_locale);
        System.out.println("variable_locale = " + variable_locale + " après modifier()");

        System.out.print("\n");

        System.out.println("variable_de_classe = " + variable_de_classe + " avant modifier()");
        modifier(variable_de_classe);
        System.out.println("variable_de_classe = " + variable_de_classe + " après modifier()");

        System.out.print("\n");

        System.out.println("variable (locale) = " + variable + " avant modifier()");
        modifier(variable);
        System.out.println("variable (locale) = " + variable + " après modifier()");

        System.out.print("\n");

        System.out.println("variable (classe) = " + Visibilite.variable + " avant modifier()");
        modifier(Visibilite.variable);
        System.out.println("variable (classe) = " + Visibilite.variable + " après modifier()");
    }

    public static void modifier(int valeur){
        valeur = 3;
        System.out.println("Valeur = " + valeur + " dans modifier()");
    }
}