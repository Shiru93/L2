public enum TypeMonstre {
    GOBELIN("Gobelin", 5),
    DRAGON("Dragon", 30),
    ZOMBIE("Zombie", 10),
    SPECTRE("Spectre", 15);

    private final String nomAffiche;
    private final int degatsBase;

    TypeMonstre(String nomAffiche, int degatsBase) {
        this.nomAffiche = nomAffiche;
        this.degatsBase = degatsBase;
    }

    public String getNomAffiche(){
        return this.nomAffiche;
    }

    public int getDegatsBase(){
        return this.degatsBase;
    }
}