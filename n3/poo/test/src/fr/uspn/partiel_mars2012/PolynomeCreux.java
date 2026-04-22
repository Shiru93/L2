package fr.uspn.partiel_mars2012;

import java.util.*;

public class PolynomeCreux {
	private final ArrayList<Monome> termes;
	
	public PolynomeCreux() {
		this.termes = new ArrayList<>();
	}
	
	public PolynomeCreux(Monome m) {
		if(m == null) throw new IllegalArgumentException("Le monôme ne peut pas être null");
		if(m.estZero()) throw new IllegalArgumentException("Le monôme ne peut pas être null");
		
		this.termes = new ArrayList<>(termes);
		this.termes.add(m);
	}
	
	public boolean estZero() {
		return termes.isEmpty();
	}
	
	public int getCoefficient(int exposant) {
		if(exposant < 0) throw new IllegalArgumentException("L'exposant doit être positif ou nul");
		
		for(Monome m : termes)
			if(m.getExposant() == exposant)
				return m.getCoefficient();
		
		return 0;
	}
	
	public int getDegre() {
		if(estZero()) return 0;
		
		int max = 0;
		for(Monome m : termes)
			if(!m.estZero() && m.getCoefficient() > max) max = m.getExposant();
		
		return max;
	}
	
	@Override
	public boolean equals (Object o) {
		if(!(o instanceof Monome)) return false;
		if(this == o) return true;
		
		PolynomeCreux pc = (PolynomeCreux) o;
		if(this.getDegre() != pc.getDegre()) return false;
		
		int maxDegre = Math.max(this.getDegre(), pc.getDegre());
		for(int i = 0; i <= maxDegre; i++)
			if(this.getCoefficient(i) != pc.getCoefficient(i))
				return false;
		
		return true;
	}
	
	@Override
	public int hashCode() {
		int result = 1;
		
		for(Monome m : termes)
			if(!m.estZero())
				result = 31 * result + m.hashCode();
		
		return result;
	}
	
	/**
	 * On peut aussi faire :
	 * @Override
	 * public int hashCode(){
	 * 	return Objects.hash(termes);
	 * }
	 */
	
	public PolynomeCreux additionner(PolynomeCreux p) {
		if(p == null || this == null) throw new IllegalArgumentException("Le polynôme ne peut pas être null");
		if(this.estZero()) return p;
		if(p.estZero()) return this;
		
		ArrayList<Monome> additionTermes = new ArrayList<>();
		for(Monome m : this.termes)
			if(!m.estZero())
				additionTermes.add(m);
		
		for(Monome n : p.termes) {
			if(!n.estZero()) {
				
			}
		}
	}
	
	public String toString() {
		
	}
}