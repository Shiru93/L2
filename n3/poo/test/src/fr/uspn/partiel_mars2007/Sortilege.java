package fr.uspn.partiel_mars2007;

import java.util.Objects;

public class Sortilege {
	private final String nom;
	private final int puissance;
	
	public Sortilege(String nom, int puissance) {
		Objects.requireNonNull(nom);
		
		this.nom = nom;
		this.puissance = puissance;
	}
	
	public String getNom() {
		return nom;
	}
	
	public int getPuissance() {
		return puissance;
	}
	
	@Override
	public boolean equals(Object obj) {
		if(this == obj) {
			return true;
		}
		
		if(obj == null || getClass() != obj.getClass()) {
			return false;
		}
		
		Sortilege sortilege = (Sortilege) obj;
		
		return puissance == sortilege.puissance && 
				Objects.equals(nom,  sortilege.nom);
	}
	
	@Override
	public int hashCode() {
		return Objects.hash(nom, puissance);
	}
	
	@Override
	public String toString() {
		return nom + " (" + puissance + ")";
	}
}
