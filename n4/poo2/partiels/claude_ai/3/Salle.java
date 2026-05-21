public class Salle implements Iterable<Relique> {
    private Relique[] reliques;
    private int nbReliques;

    public Salle() {
        reliques = new Relique[20];
        nbReliques = 0;
    }
    public void ajouterRelique(Relique r) {
        reliques[nbReliques++] = r;
    }
    public Salle salleSuivante(Direction d) { /* fourni, peut renvoyer null */ }

    @Override
    public Iterator<Relique> iterator() {
        return new SalleIterator(reliques, nbReliques);
    }
}