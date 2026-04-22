#include "fonctions.h"

// Retourne 1 si c est un opérateur arithmétique, 0 sinon
int is_operator(char c){
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

/* ------------------------------------------------------------------ */
/*  Question 1.b — parse_expr                                          */
/* ------------------------------------------------------------------ */
/*
 * Construit récursivement l'arbre syntaxique d'une expression préfixe.
 *
 * Paramètres :
 *   expr — la chaîne à analyser (ex. "+ * 3 4 5")
 *   pos  — pointeur sur l'index courant dans expr (modifié en place)
 *
 * Idée récursive :
 *   1. On saute les espaces.
 *   2. On lit le caractère courant c et on avance pos.
 *   3. Si c est un opérateur :
 *        - on parse récursivement le sous-arbre GAUCHE (premier opérande)
 *        - on parse récursivement le sous-arbre DROIT (deuxième opérande)
 *        - on crée un nœud interne c avec ces deux sous-arbres
 *   4. Si c est un chiffre :
 *        - on crée un nœud feuille (pas d'enfants)
 *
 * Exemple de déroulement pour "+ * 3 4 5", pos=0 :
 *   - c='+' → opérateur
 *     - parse_expr(pos=2) : c='*' → opérateur
 *       - parse_expr(pos=4) : c='3' → feuille('3')
 *       - parse_expr(pos=6) : c='4' → feuille('4')
 *       → retourne nœud('*', '3', '4')
 *     - parse_expr(pos=8) : c='5' → feuille('5')
 *   → retourne nœud('+', nœud('*','3','4'), '5')
 */
link parse_expr(const char *expr, int *pos){
    /* 1. Sauter les espaces */
    while(expr[*pos] == ' ')
        (*pos)++;

    /* 2. Lire le caractère courant */
    char c = expr[*pos];
    (*pos)++;

    if(is_operator(c)){
        /* 3. Noeud interne : on parse les deux sous-expressions */
        link left_tree = parse_expr(expr, pos);
        link right_tree = parse_expr(expr, pos);

        return cons_binary_tree(c, left_tree, right_tree);
    } else {
        /* 4. Feuille : chiffre ou variable */
        return cons_binary_tree(c, empty_tree(), empty_tree());
    }
}

/* ------------------------------------------------------------------ */
/*  Question 1.c — eval_tree                                           */
/* ------------------------------------------------------------------ */
/*
 * Évalue récursivement l'arbre syntaxique et retourne le résultat
 * entier de l'expression.
 *
 * Idée récursive :
 *   - Si le nœud est une feuille (chiffre) : on retourne c - '0'
 *     (conversion char → int : '3' - '0' = 3)
 *   - Si le nœud est un opérateur :
 *       val_gauche  = eval_tree(fils gauche)
 *       val_droite  = eval_tree(fils droit)
 *       on applique l'opérateur et on retourne le résultat
 *
 * Exemple sur l'arbre de "+ * 3 4 5" :
 *   eval('+') = eval('*') + eval('5')
 *             = (eval('3') * eval('4')) + 5
 *             = (3 * 4) + 5
 *             = 17
 */
int eval_tree(const link bt){
    if(is_empty_binary_tree(bt))
        return 0;

    char c = get_binary_tree_root(bt);


    if(is_operator(c)){
        int left_val = eval_tree(bt->left);
        int right_val = eval_tree(bt->right);

        switch(c){
            case '+':
                return left_val + right_val;
            
            case '-':
                return left_val - right_val;

            case '*':
                return left_val * right_val;

            case '/':
                if(right_val == 0){
                    fprintf(stderr, "Erreur : division par zéro\n");
                    exit(EXIT_FAILURE);
                }

                return left_val / right_val;
        }
    }

    /* Feuille : c est un chiffre ('0'...'9') */
    return c - '0';
}

/* ------------------------------------------------------------------ */
/*  Question 1.d — tree_to_expr                                        */
/* ------------------------------------------------------------------ */
/*
 * Reconstruit récursivement la chaîne préfixe à partir de l'arbre.
 *
 * C'est exactement un PARCOURS EN PRÉORDRE (racine, gauche, droite) :
 *   1. On écrit le label du nœud courant dans buf[*pos].
 *   2. Si le fils gauche existe, on ajoute un espace puis on
 *      reconstruit récursivement le sous-arbre gauche.
 *   3. Idem pour le fils droit.
 *
 * Paramètres :
 *   bt  — l'arbre (ou sous-arbre) à convertir
 *   buf — tampon de sortie (doit être assez grand)
 *   pos — index d'écriture courant dans buf (modifié en place)
 *
 * Exemple sur l'arbre de "+ * 3 4 5" :
 *   - Écrire '+', pos=1
 *   - Espace, pos=2 ; tree_to_expr(fils gauche = *)
 *     - Écrire '*', pos=3
 *     - Espace, pos=4 ; tree_to_expr(3) → Écrire '3', pos=5
 *     - Espace, pos=6 ; tree_to_expr(4) → Écrire '4', pos=7
 *   - Espace, pos=8 ; tree_to_expr(fils droit = 5) → Écrire '5', pos=9
 *   buf = "+ * 3 4 5"
 */
void tree_to_expr(const link bt, char *buf, int *pos){
    if(is_empty_binary_tree(bt))
        return;

    // Écrire le label du noeud courant
    buf[(*pos)++] = get_binary_tree_root(bt);

    // Sous-arbre gauche (s'il existe)
    if(!is_empty_binary_tree(bt->left)){
        buf[(*pos)++] = ' ';
        tree_to_expr(bt->left, buf, pos);
    }

    // Sous-arbre droit (s'il existe)
    if(!is_empty_binary_tree(bt->right)){
        buf[(*pos)++] = ' ';
        tree_to_expr(bt->right, buf, pos);
    }
}

/* ------------------------------------------------------------------ */
/*  tree_to_infix  —  arbre → chaîne INFIXE  (TP3, NOUVEAU)          */
/* ------------------------------------------------------------------ */
/*
 * Parcours INFIXE : gauche, racine, droite.
 *
 * On ajoute des parenthèses autour de chaque sous-expression qui
 * contient un opérateur, pour qu'il n'y ait aucune ambiguïté.
 *
 * Exemple sur l'arbre de "+ * 3 4 5" :
 *
 *        +            infixe :  ((3 * 4) + 5)
 *       / \
 *      *   5          Pour le nœud '+' :
 *     / \               → '('
 *    3   4               → infixe(*)  =  "(3 * 4)"
 *                        → " + "
 *                        → infixe(5)  =  "5"
 *                        → ')'
 *
 * Pour une feuille : on écrit juste le chiffre, sans parenthèses.
 */
void tree_to_infix(const link bt, char *buf, int *pos){
    if(is_empty_binary_tree(bt))
        return;

    char c = get_binary_tree_root(bt);

    if(is_operator(c)){
        buf[(*pos)++] ='(';
        tree_to_infix(bt->left, buf, pos);
        buf[(*pos)++] = ' ';
        buf[(*pos)++] = c;
        buf[(*pos)++] = ' ';
        tree_to_infix(bt->right, buf, pos);
        buf[(*pos)++] = ')';
    } else {
        buf[(*pos)++] = c;
    }
}