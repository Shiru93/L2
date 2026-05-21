public class StrategieMaxReliques implements StrategieExploration {
    public static final StrategieMaxReliques theInstance = new StrategieMaxReliques();

    private StrategieMaxReliques(){}

    @Override
    public Salle choisirSalle(Salle p, Predicate<? super Relique> pred){
        Salle meilleure = null;
        int max = 0;

        for(Direction d : Direction.values()){
            Salle voisine = p.salleSuivante(d);

            if(voisine != null){
                int count = 0;
                for(Relique r : voisine){
                    if(pred.test(r)){
                        count++;
                    }
                }

                if(count > max){
                    max = count;
                    meilleure = voisine;
                }
            }
        }

        return meilleure;
    }

    // Question 3.a
    Predicate<Relique> pred = r -> !r.estMaudite() && r.getPuissance() > 50;

    // Question 3.b
    Predicate<Relique> pred = r -> r != null && r.getNom().startsWith("or");

    // Question 3.c
    Predicate<Relique> pred = r -> !r.estMaudite() && r.getPuissance() > 20 && r.getNom().startsWith("A");ù

    // Question 4
    /*
     * Predicate<E> est une functional interface car elle ne possède qu'une seule méthode abstraite (boolean test(E e)). 
     * Cela permet au compilateur Java d'accepter une lambda expression partout où un Predicate est attendu, sans avoir à créer une classe explicite : 
     * +la lambda est automatiquement convertie en instance anonyme de l'interface. 
     */
}
