package p2_7janvier2026;

import java.util.*;

public class Coffre extends CloseableContainer<Cle, ObjetZork> {
	private String description;
	private int poidsVide;
	
	/**
     * Constructeur 1 : Initialise un Coffre vide.
     * * Requires:
     * cle != null;
     * * Ensures:
     * isOpen();
     * hasKey(cle);
     * size() == 0;
     * getDescription().equals(description);
     * getEmptyWeight() == poidsVide;
     */
	public Coffre(Cle cle, String description, int poidsVide) {
		super(cle);
		this.description = description;
		this.poidsVide = poidsVide;
	}
	
	/**
     * Constructeur 2 : Initialise un Coffre avec un contenu initial.
     * * Requires:
     * cle != null;
     * objets != null;
     * !objets.contains(null);
     * * Ensures:
     * isOpen();
     * hasKey(cle);
     * getDescription().equals(description);
     * getEmptyWeight() == poidsVide;
     * (\forall ObjetZork obj; objets.contains(obj); this.contains(obj));
     * this.size() == objets.size();
     */
	public Coffre(Cle cle, String description, int poidsVide, Collection<? extends ObjetZork> objets) {
		super(cle, objets);
		this.description = description;
		this.poidsVide = poidsVide;
	}
	
	public String getDescription() {
		return this.description;
	}
	
	public int getEmptyWeight() {
		return this.poidsVide;
	}
	
	public int getWeight() {
		int poidsTotal = this.poidsVide;
		if(this.desObjets != null) {
			for(ObjetZork obj : this.desObjets) {
				poidsTotal += obj.getWeight();
			}
		}
		
		return poidsTotal;
	}
}
