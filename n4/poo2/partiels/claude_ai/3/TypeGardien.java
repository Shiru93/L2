public enum TypeGardien {
    SQUELETTE(10),
    VAMPIRE(50),
    SPECTRE(90);

    private final int dangerosité;

    // Le constructeur d'un enum est TOUJOURS private (implicitement ou explicitement)
    private TypeGardien(int dangerosité) {
        this.dangerosité = dangerosité;
    }

    public int getDangerosité() {
        return dangerosité;
    }
}