// --- TD 29 Sept & 13 Octobre : Objets & Identité ---
class ObjetZork {
    private String nom;
    private int poids;

    public ObjetZork(String nom, int poids) {
        if (poids <= 0) throw new IllegalArgumentException("Poids positif requis");
        this.nom = nom;
        this.poids = poids;
    }

    public int getPoids() { return poids; }

    // --- TD 13 Oct : Redéfinition stricte de equals/hashCode ---
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

// --- TD 20 Octobre : ArrayList & TD 3 Nov : Contrats ---
class Piece extends Conteneur {
    private String description;
    private ArrayList<ObjetZork> objets; // Utilisation de ArrayList

    public Piece(String description) {
        this.description = description;
        this.objets = new ArrayList<>();
    }

    // Implémentation des méthodes abstraites
    @Override
    public List<ObjetZork> getContenu() { return objets; }

    /**
     * @requires oz != null
     * @ensures contient(oz)
     */
    @Override
    public void ajouter(ObjetZork oz) {
        objets.add(oz);
    }

    @Override
    public boolean retirer(ObjetZork oz) {
        return objets.remove(oz);
    }

    @Override
    public String toString() { return "Piece: " + description + " | Objets: " + objets; }
}

class Joueur extends Conteneur {
    private String nom;
    private int chargeMax;
    private ArrayList<ObjetZork> sacADos;

    public Joueur(String nom, int chargeMax) {
        this.nom = nom;
        this.chargeMax = chargeMax;
        this.sacADos = new ArrayList<>();
    }

    public int getPoidsActuel() {
        int total = 0;
        for (ObjetZork oz : sacADos) total += oz.getPoids();
        return total;
    }

    @Override
    public List<ObjetZork> getContenu() { return sacADos; }

    @Override
    public void ajouter(ObjetZork oz) {
        if (getPoidsActuel() + oz.getPoids() <= chargeMax) {
            sacADos.add(oz);
            System.out.println(nom + " ramasse : " + oz);
        } else {
            System.out.println(nom + " : Trop lourd !");
        }
    }

    @Override
    public boolean retirer(ObjetZork oz) {
        return sacADos.remove(oz);
    }
}