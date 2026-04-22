import java.util.ArrayList;
import java.util.List;

public class Piece extends Conteneur {
    private String description;
    private ArrayList<ObjetZork> objets; 

    public Piece(String description) {
        this.description = description;
        this.objets = new ArrayList<>();
    }

    @Override
    public List<ObjetZork> getContenu() { return objets; }

    @Override
    public void ajouter(ObjetZork oz) {
        if (oz != null) {
            objets.add(oz);
        }
    }

    @Override
    public boolean retirer(ObjetZork oz) {
        return objets.remove(oz);
    }

    @Override
    public String toString() { 
        return "Piece: " + description + " | Objets: " + objets; 
    }
}