public class StrategieMaxTresors implements StrategieDeplacement {
    public static final StrategieMaxTresors INSTANCE = new StrategieMaxTresors();
    
    private StrategieMaxTresors(){}

    @Override
    public Salle choisirSalle(Salle p, Predicate<? super Tresor> pred){
        /*
         * Version 1 (boucles for classique)
         */
        Salle res = null;
        int max = 0;

        for(Direction d : Direction.values()){
            Salle voisine = p.salleSuivante(d);
            if(voisine != null){
                int count = 0;

                for(Tresor t : voisine){
                    if(pred.test(t)){
                        count++;
                    }
                }

                if(count > max){
                    max = count;
                    res = voisine;
                }
            }
        }

        return res;


        /*
         * Version 2 - Avec Stream (TD4)
         * 
         * Plus concis mais max() renvoie un Optionnal<Salle>
         * Il faut donc .orElse(null) pour récupérer null si aucune salle n'existe
         */
        /*
        return Stream.of(Direction.values())
            .map(d -> p.salleSuivante(d))
            .filter(v -> v != null)
            .max(Comparator.comparingInt(
                v -> (int) StreamSupport.stream(v.spliterator(), false)
                                        . filter(pred)
                                        .count()
            ))
            .orElse(null);
        */


        /*
         * Version 3 - Stream + countPred() (La plus propre)
         *
         * Si on a déjà une méthode countPred() séparée comme dans le TP4
         */
        // Méthode utilitaire
        /*
        public static int countPred(Salle s, Predicate<? super Tresor> pred){
            return (int) Stream.Support.stream(s.spliterator(), false).filter(pred).count();
        }
        */
        // choisirSalle devient ultra-lisible
        /*
        return Stream.of(Direction.value())
            .map(d -> p.salleSuivante(d))
            .filter(v -> v != null)
            .max(Comparator.comparingInt(v -> countPred(v, pred)))
            .orElse(null);
        */


        /*
         * Version 4 - Avec FilterIterator(Decorator)
         *
         * On peut aussi utiliser les itérateurs décorateurs du TD3
         */
        /*
        Salle res = null;
        int max = 0;
        for(Direction d : Direction.values()){
            Salle voisine = p.salleSuivante(d);
            if(voisine != null){
                * On décore l'intérieur de la salle avec un filtre
                Iterator<Tresor> filtered = new FilterIterator<>(voisine.iterator(), pred);
                int count = 0;
                while(filtered.hasNext()){
                    filtered.next();
                    count++;
                }

                if(count > max){
                    max = count;
                    res = voisine;
                }
            }
        }

        return res;
        */
    }

}