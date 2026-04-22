/** À COMPLÉTER AVEC LE NOM, LE PRÉNOM ET LE N° D'ÉTUDIANT(E) **/
/** DE CHAQUE ÉTUDIANT(E) AYANT TRAVAILLÉ SUR LE FICHIER **/
/* Etudiant(e) n°1, NOM :                Prénom :               N° :             */
/* Etudiant(e) n°2, NOM :                Prénom :               N° :             */

/** À COMPLÉTER AVEC LES BONNES INCLUSIONS DE FICHIERS **/

char* alloc_init_string_rand (int);
void usage_bst(char *);

int main(int argc, char **argv) {
  /** À COMPLÉTER AVEC LES DÉCLARATIONS DE VARIABLES LOCALES **/

  if (argc != 3) {
    printf("Nombre d'arguments erroné. Recommencez ! \n");
    usage_bst(argv[0]);
    return EXIT_FAILURE;
  }

  /** À COMPLÉTER AVEC LE CODE IMPLÉMENTANT CHACUNE DES ÉTAPES DU PROGRAMME DEMANDÉ **/

  return EXIT_SUCCESS;
}

/** Affiche le "format" de la ligne de commande en cas d'erreur */
void usage_bst(char *s) {
  printf("%s int int \n", s);
  printf("1er argument : taille du premier ABR\n");
  printf("2nd argument : taille du second ABR\n");
}

/** Initialise de manière pseudo-aléatoire une chaîne de caractères constituées */
/* de lettres majuscules de l'alphabet latin et renvoie la chaîne */
char* alloc_init_string_rand (int n) {
    /** À COMPLÉTER **/
}
