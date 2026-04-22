package fr.uspn.partiel_mars2007;

import java.util.ArrayList;
import java.util.Objects;
import java.util.Random;

public class Magicien {
	public enum StrategieInvocation {LIFO, FIFO, ALEATOIRE, PLUS_PUISSANT}
	
	private final String nom;
	private final ArrayList<Sortilege> sorts = new ArrayList<>();
	private final Random random = new Random();
	private StrategieInvocation strategie = StrategieInvocation.LIFO;
	
	public Magicien(String nom) {
		Objects.requireNonNull(nom);
		this.nom = nom;
	}
	
	public Magicien(String nom, Sortilege unSort) {
		Objects.requireNonNull(nom);
		Objects.requireNonNull(unSort);
		
		this.nom = nom;
		sorts.add(unSort);
	}
	
	public String getNom() {
		return nom;
	}
	
	public boolean reserveEstVide() {
		return sorts.isEmpty();
	}
	
	public int getNbSorts() {
		return sorts.size();
	}
	
	public void setStrategie(StrategieInvocation strategie) {
		this.strategie = strategie;
	}
	
	public int invoquer() {
		if(reserveEstVide()) {
			return 0;
		}
		
		switch(strategie){
		case FIFO:
			return invoquerFIFO();
			
		case ALEATOIRE:
			return invoquerAleatoire();
			
		case PLUS_PUISSANT:
			return invoquerPlusPuissant();
			
		case LIFO:
		default:
			return invoquerLIFO();
		}
	}
	
	private int invoquerLIFO() {
		Sortilege sortInvoque = sorts.remove(sorts.size() - 1);
		return sortInvoque.getPuissance();
	}
	
	private int invoquerFIFO() {
		Sortilege sortInvoque = sorts.remove(0);
		return sortInvoque.getPuissance();
	}
	
	private int invoquerAleatoire() {
		int i = random.nextInt(sorts.size());
		Sortilege sortInvoque = sorts.remove(i);
		return sortInvoque.getPuissance();
	}
	
	private int invoquerPlusPuissant() {
		int i = 0;
		for(int j = 0; j < sorts.size(); j++) {
			if(sorts.get(j).getPuissance() > sorts.get(i).getPuissance()) {
				i = j;
			}
		}
		
		Sortilege sortInvoque = sorts.remove(i);
		return sortInvoque.getPuissance();
	}
	
	public boolean possede(Sortilege sort) {
		Objects.requireNonNull(sort);
		return possedeCombienDe(sort) > 0;
	}
	
	public int possedeCombienDe(Sortilege sort) {
		Objects.requireNonNull(sort);
		int count = 0;
		for(Sortilege spell : sorts) {
			if(spell.equals(sort)) {
				count++;
			}
		}
		
		return 0;
	}
	
	public void ajouter(Sortilege unSort) {
		Objects.requireNonNull(unSort);
		sorts.add(unSort);
	}
	
	public int getPuissance() {
		int somme = 0;
		for(Sortilege spell : sorts) {
			somme += spell.getPuissance();
		}
		
		return somme;
	}
	
	@Override
	public boolean equals(Object obj) {
		if(this == obj) {
			return true;
		}
		
		if(obj == null || getClass() != obj.getClass()) {
			return false;
		}
		
		Magicien magicien = (Magicien) obj;
		if(!nom.equals(magicien.nom)) {
			return false;
		}
		
		if(sorts.size() != magicien.sorts.size()) {
			return false;
		}
		
		for(Sortilege spell : sorts) {
			if(possedeCombienDe(spell) != magicien.possedeCombienDe(spell)) {
				return false;
			}
		}
		
		return true;
	}
	
	public Magicien clone() {
		try {
            Magicien clone = (Magicien) super.clone();
            // Cloner la liste des sorts (clonage profond)
            ArrayList<Sortilege> sortsClones = new ArrayList<>();
            for (Sortilege sort : this.sorts) {
                sortsClones.add(new Sortilege(sort.getNom(), sort.getPuissance()));
            }
            // Utiliser la réflexion pour modifier le champ privé 'sorts'
            java.lang.reflect.Field field = Magicien.class.getDeclaredField("sorts");
            field.setAccessible(true);
            field.set(clone, sortsClones);
            return clone;
        } catch (CloneNotSupportedException | NoSuchFieldException | IllegalAccessException e) {
            throw new AssertionError(); // Ne devrait pas arriver
        }
	}
	
	@Override
	public int hashCode() {
		int res = Objects.hash(nom);
		for(Sortilege spell : sorts) {
			res = 31 * res + spell.hashCode();
		}
		
		return res;
	}
	
	public String toString() {
		return "Magicien{" + "nom = '" + '\'' + ", nbSorts = " + getNbSorts() + ", puissance = " + getPuissance() + '}';
	}
}