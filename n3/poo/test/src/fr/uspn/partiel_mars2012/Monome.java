package fr.uspn.partiel_mars2012;

import java.util.*;

public class Monome {
	private final int degre;
	private final int coeff;
	
	public void Monome() {
		this.degre = 0;
		this.coeff = 0;
	}
	
	public void Monome(int coefficient, int exposant) {
		this.degre = exposant;
		this.coeff = coefficient;
	}
	
	public PolynomeCreux additionner(Monome m) {
		if (m == null) throw new IllegalArgumentException("Le monôme ne doit pas être nul");
		if(this.degre != m.degre) {
			PolynomeCreux result = new PolynomeCreux(this)
			return result.additionner(new PolynomeCreux);
		}
		
		int nouveauCoefficient = this.coeff + m.coeff;
		if(nouveauCoefficient == 0) return new PolynomeCreux();
		else return new PolynomeCreux(new Monome(nouveauCoefficient, degre));
	}
	
	@Override
	public boolean equals(Object o) {
		if(!(o instanceof Monome))
			return false;
		
		if(this == o)
			return true;
		
		Monome autreMonome = (Monome) o;
		if(getDegre() != autreMonome.getDegre())
			return false;
		
		return getCoefficient() == autreMonome.getCoefficient;
	}
	
	@Override
	public int hashCode() {
		return (int) Math.pow(31, exposant) + exposant * getCoefficient;
	}
	
	public boolean estZero() {
		return coeff == 0;
	}
	
	public int getCoefficient() {
		return coeff;
	}
	
	public int getCoefficient(int exp) {
		if(exp < 0) throw new IllegalArgumentException("L'exposant doit être positif ou nul");
		return (exp == degre) ? coeff : 0;
	}
	
	public int getDegre() {
		return degre;
	}
	
	public int getExposant() {
		return degre;
	}
	
	public String toString() {
		String str = "Monome : ";
		return (getCoefficient() == 0) ? str + "zéro" : str + getCoefficient() + ".X^" + getDegre();
	}
	
	public double evaluer(double x) {
		return coeff * Math.pow(x, degre);
	}
}
