package fr.uspn.partiel_mars2008;
import java.util.*;

public class PersonnageMobile {
	private String nom;
	private ArrayList<Piece> pieces;
	private Piece pieceCourante;
	private ArrayList<Piece> piecesAjouteesDepuisDernierDeplacement;
	
	public PersonnageMobile(String nom, Piece p1, Piece p2, Piece p3) {
		if(nom == null || p1 == null || p2 == null || p3 == null) 
			throw new IllegalArgumentException("Aucun paramètre ne peut être null");
		
		if(p1.equals(p2) || p1.equals(p3) || p2.equals(p3))
			throw new IllegalArgumentException("Les trois pièces doivent être distinctes");
		
		this.nom = nom;
		this.pieces = new ArrayList<>();
		this.pieces.add(p1);
		this.pieces.add(p2);
		this.pieces.add(p3);
		this.pieceCourante = p1;
		this.piecesAjouteesDepuisDernierDeplacement = new ArrayList<>();
	}
	
	public PersonnageMobile(String nom, Piece[] tabPieces) {
		if(nom == null || tabPieces == null) 
			throw new IllegalArgumentException("Aucun paramètre ne peut être null");
		
		if(tabPieces.length < 3)
			throw new IllegalArgumentException("Les trois pièces doivent être distinctes");
		
		 for(int i = 0; i < tabPieces.length; i++) {
			 if(tabPieces[i] == null)
				 throw new IllegalArgumentException("Aucune pièce dans le tableau ne peut être null");
			 
			 for(int j = i + 1; j < tabPieces.length; j++)
				 if(tabPieces[i].equals(tabPieces[j]))
					 throw new IllegalArgumentException("Toutes les pièces doivent être distinctes");
		 }
			 
		 this.nom = nom;
		 this.pieceCourante = new ArrayList<>();
		 
		 for(Piece piece : tabPieces)
			 this.pieces.add(piece);
		 
		 this.pieceCourante = tabPieces[0];
		 this.piecesAjouteesDepuisDernierDeplacement = new ArrayList<>();
	}
	
	public String getNom() {
		return nom;
	}
	
	public Piece getPieceCourante() {
		return pieceCourante;
	}
	
	public int getNbPieces() {
		return piece.size();
	}
}
