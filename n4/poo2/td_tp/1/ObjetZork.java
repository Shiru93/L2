
public class ObjetZork {
	private String nom;
	private int poids;
	private boolean estTransportable;

	public ObjetZork(String nom, int poids, boolean estTransportable) {
		this.nom = nom;
		this.poids = poids;
		this.estTransportable = estTransportable;
	}

	public String getNom() {
		return nom;
	}

	public int getPoids() {
		return poids;
	}

	public boolean estTransportable() {
		return estTransportable;
	}

	@Override
	public boolean equals(Object obj) {
		if (!(obj instanceof ObjetZork)) {
			return false;
		}
		ObjetZork other = (ObjetZork) obj;
		if (!this.nom.equals(other.nom)) {
			return false;
		}
		if (this.poids != other.poids) {
			return false;
		}
		if (this.estTransportable != other.estTransportable) {
			return false;
		}
		return true;
	}

	@Override
	public int hashCode() {
		return this.nom.hashCode() + this.poids + (this.estTransportable ? 1 : 0);
	}

	@Override
	public String toString() {
		return this.nom + this.poids + (estTransportable ? "est " : "non ") + "transportable";
	}
}
