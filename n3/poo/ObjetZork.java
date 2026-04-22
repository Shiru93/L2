import java.util.Objects;

public class ObjetZork {
    private String nom;
    private int poids;

    public ObjetZork(String nom, int poids) {
        if (poids <= 0) throw new IllegalArgumentException("Poids positif requis");
        this.nom = nom;
        this.poids = poids;
    }

    public int getPoids() { return poids; }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        ObjetZork objetZork = (ObjetZork) o;
        return poids == objetZork.poids && Objects.equals(nom, objetZork.nom);
    }

    @Override
    public int hashCode() {
        return Objects.hash(nom, poids);
    }

    @Override
    public String toString() { return nom + "(" + poids + "kg)"; }
}