public class Relique {
    private String nom;
    private int puissance;
    private boolean estMaudite;

    public Relique(String nom, int puissance, boolean estMaudite) {
        this.nom = nom;
        this.puissance = puissance;
        this.estMaudite = estMaudite;
    }
    public String getNom()        { return nom; }
    public int getPuissance()     { return puissance; }
    public boolean estMaudite()   { return estMaudite; }
}

public enum Direction { NORD, SUD, EST, OUEST }

public interface Predicate<E> {
    boolean test(E e);
}

public interface Function<T, R> {
    R apply(T t);
}