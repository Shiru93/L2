public class JournalChateau {

    // 1. L'unique instance, créée une seule fois, non modifiable
    public static final JournalChateau theInstance = new JournalChateau();

    // 2. Constructeur PRIVÉ : personne d'autre ne peut créer d'instance
    private JournalChateau() {
        // rien à initialiser ici
    }

    // 3. Interdire explicitement le clonage (même pour les sous-classes)
    @Override
    protected final JournalChateau clone() throws CloneNotSupportedException {
        throw new CloneNotSupportedException();
    }

    // 4. La méthode métier
    public void enregistrer(String message) {
        System.out.println("[LOG] " + message);
    }
}