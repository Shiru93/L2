public class LoggerCombat{
    public static final LoggerCombat theInstance = new LoggerCombat();

    private LoggerCombat(){} 

    public void logAttaque(Monstre m, Héros h){
        System.out.println(m.getNom() + " attaque" + h.getNom + " pour " + m.getType().getDegatsBase() + " dégâts");
    }
}