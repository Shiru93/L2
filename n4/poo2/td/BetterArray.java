public class BetterArray<E> extends Array<E> {
    public BetterArray(int size){
        super(size);
    }

    @Override
    public String toString(){
        if (length == 0) return "[]";

        int i = 0;
        String res = "[";
        
        for(; i < this.length - 1; i++){
            res += this.get(i) + ",";
        }

        return res += this.get(i) + "]";
    }

    @Override
    public boolean equals(Object obj){
        // Est-ce que ce sont exactement les mêmes objets en mémoire ?
        if(this == obj) return true;

        // L'objet fourni est-il null ou d'une class différente ?
        if(obj == null || getClass() != obj.getClass()) return false;

        BetterArray<?> other = (BetterArray<?>) obj;

        // On vérifie la taille
        if(this.length != other.length) return false;

        // On compare les éléments un par un
        for(int i = 0; i < length; i++){
            if(!(this.get(i).equals(other.get(i)))){
                return false;
            }
        }

        return true;
    }
}