public class Couple<E, F> {
    private final E premier;
    private final F second;

    public Couple(E premier, F second) {
        this.premier = premier;
        this.second = second;
    }
    
    @Override
    public String toString() { 
        return "(" + premier + ", " + second + ")"; 
    }
}