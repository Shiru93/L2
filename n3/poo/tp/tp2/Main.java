public class Main {

	public static void main(String[] args) {
		Carte maCarte = new Carte();
		Carte maCarte2 = new Carte(Carte.Famille.COEUR, Carte.Rang.DAME);
		
		System.out.println("Ma 1ère carte est : " + maCarte.toString());
		System.out.println("Ma 2e carte est : " + maCarte2.toString());
	}

}