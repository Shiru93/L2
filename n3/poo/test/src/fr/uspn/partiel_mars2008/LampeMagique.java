package fr.uspn.partiel_mars2008;
import java.util.Objects;

public class LampeMagique {
	private final String couleur;
	private final int poids;
	private int vie;
	private boolean active;
	private boolean aEteActive;
	
    public LampeMagique(String couleur, int poids, int vie, boolean active, boolean aEteActive) {
        Objects.requireNonNull(couleur);
        if(poids <= 0 || vie <= 0)
          throw new IllegalArgumentException();

        this.couleur = couleur;
        this.poids = poids;
        this.vie = vie;
        this.active = false;
        this.aEteActive = false;
    }
	
	public void activer() {
		if(!this.aEteActive) {
			this.active = true;
			this.aEteActive = true;
		}
	}
	
	public int eclairer() {
		if(this.vie > 2) {
			this.vie--;
			return vie;
		}
		
		this.active = false;
		
		return 0;
	}
	
	@Override
	public boolean equals(Object obj) {
		// Vérifie si c'est la même référence en mémoire
		if(this == obj) return true;
		
		// Vérifie si l'objet est null ou de classe différente
		if(obj == null || getClass() != obj.getClass()) return false;
		
		// Caster l'objet vers le bon type
		LampeMagique other = (LampeMagique) obj;
		
		// Comparer tous les attributs significatifs
		return poids == other.poids &&
				aEteActive == other.aEteActive &&
				active == other.active &&
				couleur.equals(other.couleur);
	}
	
	@Override
	public int hashCode() {
		int result = couleur.hashCode();
		result = 31 * result + poids;
		result = 31 * result + vie;
		result = 31 * result + (active ? 1 : 0);
		return result;
	}
}