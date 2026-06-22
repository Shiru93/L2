# Correction Détaillée — Partiel Programmation 4
**L2 Informatique · Institut Galilée · USPN**  
*Arbres binaires · Tas · ABR · LLRBT*

---

## Rappel : La structure utilisée dans tout le partiel

Tout le partiel repose sur UNE SEULE structure C :

```c
struct node {
    int label;          /* étiquette (valeur entière) du noeud */
    struct node *left;  /* pointeur vers le sous-arbre GAUCHE  */
    struct node *right; /* pointeur vers le sous-arbre DROIT   */
};
typedef struct node *link;  /* 'link' = pointeur vers un noeud (NULL = arbre vide) */
```

`link h` signifie que `h` est un pointeur vers la racine d'un arbre. Si `h == NULL`, l'arbre est vide. C'est la convention de base de tout le sujet.

---

# EXERCICE 1 — Arbres Binaires [3 pts]

## Question 1.A — `nbre_etiquette_AB` [2 pts]

**Énoncé :** Compter le nombre de nœuds dont l'étiquette vaut `v` dans un arbre binaire.

### Schéma général d'une fonction récursive sur arbre binaire

Toute fonction récursive sur un arbre binaire suit toujours le même schéma :
- **Cas de base :** si l'arbre est vide (`h == NULL`), retourner la valeur neutre (ici 0)
- **Sinon :** traiter la racine + appel récursif gauche + appel récursif droit

```c
int nbre_etiquette_AB(link h, int v) {
    int res = 0;
    if (h) {                          /* si l'arbre n'est pas vide */
        if (h->label == v) ++res;     /* la racine porte l'étiquette v ? */
        res += nbre_etiquette_AB(h->left,  v)   /* chercher à gauche  */
             + nbre_etiquette_AB(h->right, v);  /* chercher à droite  */
    }
    return res;   /* si h==NULL : res=0, on renvoie 0 (cas de base) */
}
```

### Explication ligne par ligne

- `if (!h)` : h est NULL (arbre vide) → res vaut 0, on retourne 0. C'est le **cas de base**.
- `if (h->label == v) ++res` : on regarde si la **racine** de l'arbre courant porte `v`.
- `res += ... gauche + ... droit` : on ajoute le résultat du même calcul sur les deux sous-arbres. La récursion visite ainsi tous les nœuds exactement une fois.

> **Trace :** arbre `[5 -> gauche:3, droit:5]`, `v=5` → compte = 1 (racine) + 0 (gauche) + 1 (droit) = **2** ✓

---

## Question 1.B — Nombre de comparaisons d'entiers [1 pt]

À chaque appel sur un nœud **non vide**, on fait exactement **1 comparaison** : `h->label == v`.  
On appelle la fonction une fois par nœud. Un arbre de taille `n` a `n` nœuds.

**Relation de récurrence :**
- `C(0) = 0`
- `C(n+1) = 1 + C(m) + C(n-m)` pour un certain `m`, `0 ≤ m ≤ n`

Par récurrence simple : **C(n) = n**.

> **Note :** le test `!h` n'est pas une comparaison d'entiers, il n'est pas compté.

---

# EXERCICE 2 — Tas Binaire [4 pts]

> ⚠️ **ATTENTION : priorité au PLUS GRAND entier (max-tas) dans cet exercice.**

## Question 2.A — Définition d'un tas binaire [1 pt]

Un tas binaire (max-tas) vérifie **DEUX propriétés** :

**Propriété 1 — FORME :** L'arbre est **complet et tassé à gauche**. Tous les niveaux sont pleins sauf éventuellement le dernier, qui est rempli de **gauche à droite**.

**Propriété 2 — ORDRE :** L'étiquette de chaque nœud est **supérieure ou égale** à celles de ses fils. La racine contient donc le **maximum global**.

> Ces deux propriétés permettent d'implémenter le tas dans un tableau avec fils gauche en `2i` et fils droit en `2i+1`.

---

## Question 2.B — Construction du tableau après 16 insertions [2 pts]

**Principe :** `t[0]` = taille. Pour le nœud d'indice `i` : fils gauche = `2i`, fils droit = `2i+1`, père = `i/2`.

**Insertion de la valeur `v` :**
```
1. t[++t[0]] = v   (placer en fin)
2. i = t[0]
3. Tant que i > 1 et t[i] > t[i/2] :
     échanger t[i] et t[i/2]
     i = i/2
```

**Résultat final** après insertion de `33, 77, 43, 71, 36, 88, 12, 11, 6, 9, 58, 0, 67, 0, 15, 50` :

| idx | 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|-----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|-----|
| val | 16 | 88 | 71 | 77 | 50 | 58 | 67 | 15 | 33 | 6 | 9  | 36 | 0  | 43 | 0  | 12 | 11 |

> **Vérification :** `t[1]=88` est bien le max. `t[2]=71 ≥ t[4]=50` et `t[5]=58`. `t[3]=77 ≥ t[6]=67` et `t[7]=15`. Propriété de tas respectée partout ✓

---

## Question 2.C — `test_tas` [1 pt]

**Idée :** Dans le tableau, seuls les nœuds d'indice `1` à `⌊n/2⌋` ont des fils. Il suffit de vérifier pour chacun que `t[i] ≥ t[2i]` et (si existe) `t[i] ≥ t[2i+1]`.

```c
int test_tas(int *t, int n) {
    for (int i = 1; 2*i <= n; ++i) {
        if (t[i] < t[2*i]) return 0;                    /* fils gauche toujours présent */
        if (2*i+1 <= n && t[i] < t[2*i+1]) return 0;   /* fils droit si existe */
    }
    return 1;
}
```

> **Pourquoi s'arrêter à `n/2` :** les nœuds d'indice `> n/2` sont des feuilles (pas de fils). Rien à vérifier pour eux.

---

# EXERCICE 3 — Arbres Binaires de Recherche (ABR) [11 pts]

> ⚠️ **ATTENTION : priorité au PLUS GRAND entier dans cet exercice.**  
> Cela **INVERSE** l'ordre habituel : les grandes valeurs sont à **GAUCHE**, les petites à **DROITE**.

```
Convention de ce sujet (priorité plus grand) :
  Pour tout noeud de valeur v :
    sous-arbre GAUCHE  -->  toutes les valeurs >= v   (les grandes valeurs vont à gauche)
    sous-arbre DROIT   -->  toutes les valeurs <= v   (les petites valeurs vont à droite)

  Conséquence : le MAXIMUM est la feuille la plus à GAUCHE
                le MINIMUM est la feuille la plus à DROITE
```

---

## Question 3.A — Définition d'un ABR [1 pt]

Un arbre binaire T est un ABR (pour la priorité au plus grand) si, pour tout nœud :

- son étiquette est **inférieure ou égale** à celles de tous les nœuds de son sous-arbre **GAUCHE**
- son étiquette est **supérieure ou égale** à celles de tous les nœuds de son sous-arbre **DROIT**

---

## Question 3.B — `fusion_ABR` [3 pts]

**Énoncé :** Fusionner deux ABR `h` et `k` avec la garantie que `min(h) ≥ max(k)`. Complexité requise : O(hauteur de k).

### Pourquoi cette stratégie ?

Toutes les valeurs de `h` sont plus grandes que toutes les valeurs de `k`. Dans un ABR "priorité plus grand", les grandes valeurs vont à gauche. Donc `h` doit s'accrocher quelque part dans le sous-arbre **GAUCHE** de `k`.

Plus précisément : le nœud **le plus à gauche** de `k` est celui qui a la plus grande valeur de `k`. `h` doit devenir son fils gauche (car `h` a des valeurs encore plus grandes).

```c
/* Version itérative */
link fusion_ABR(link h, link k) {
    link courant = k;
    if (!h) return k;   /* h vide -> résultat = k */
    if (!k) return h;   /* k vide -> résultat = h */

    /* Descendre jusqu'au noeud le plus à GAUCHE de k */
    while (courant->left) {
        courant = courant->left;
    }
    /* Accrocher h comme fils gauche de ce noeud */
    courant->left = h;
    return k;
}

/* Version récursive (plus élégante) */
link fusion_ABR(link h, link k) {
    if (!h) return k;
    if (!k) return h;
    k->left = fusion_ABR(h, k->left);  /* enfoncer h dans le sous-arbre gauche de k */
    return k;
}
```

> **Complexité :** on parcourt uniquement la branche gauche de `k` (longueur ≤ hauteur de k). Total : **O(hauteur de k)** ✓

---

## Question 3.C — `suppression_noeud_ABR` [3 pts]

**Énoncé :** Supprimer un nœud d'étiquette `v`. Complexité O(hauteur).

### Deux étapes

**Étape 1 — Rechercher `v` :** descendre dans l'arbre.
- Si `v > racine` → aller à **GAUCHE** (les grandes valeurs sont à gauche)
- Si `v < racine` → aller à **DROITE**
- Si `v == racine` → on l'a trouvé

**Étape 2 — Supprimer :** remplacer le nœud par `fusion_ABR(sous-arbre-gauche, sous-arbre-droit)`. C'est valide car par propriété ABR, toutes les valeurs du sous-arbre gauche sont ≥ celles du droit.

```c
link suppression_noeud_ABR(link h, int v) {
    link nouveau;
    if (!h) return h;   /* arbre vide : v introuvable, rien à faire */

    if (v > h->label) {
        /* v plus grand que la racine --> chercher à GAUCHE */
        h->left = suppression_noeud_ABR(h->left, v);
        return h;
    }
    if (v < h->label) {
        /* v plus petit que la racine --> chercher à DROITE */
        h->right = suppression_noeud_ABR(h->right, v);
        return h;
    }
    /* Ici h->label == v : on supprime ce noeud */
    nouveau = fusion_ABR(h->left, h->right);
    free(h);       /* libérer la mémoire */
    return nouveau;
}
```

> **Complexité :** on descend dans une seule branche O(hauteur), puis `fusion_ABR` est aussi O(hauteur). Total : **O(hauteur)** ✓

---

## Question 3.D — `test_bornes_ABR` [3 pts]

**Énoncé :** Vérifier si un arbre est un ABR avec toutes les étiquettes entre `*b` et `*a`. Convention : `a=NULL` → `+∞`, `b=NULL` → `-∞`.

### Pourquoi ne pas juste vérifier père ≥ fils ?

Cette vérification **naïve est insuffisante**. Exemple d'arbre invalide qui la passerait :

```
       5
      / \
    10   3
   /
  1         <- 1 est dans le sous-arbre gauche de 5, il devrait être >= 5 !
               Mais 10 >= 1 et 5 >= 3, donc la vérif naïve ne détecte pas le problème.
```

### La bonne approche : propager des BORNES

En allant à gauche depuis un nœud de valeur `v`, toutes les valeurs à gauche doivent être `>= v`. En allant à droite, toutes doivent être `<= v`.

```c
int test_bornes_ABR(link h, int *a, int *b) {
    /* a = borne supérieure (NULL = +infini)  */
    /* b = borne inférieure (NULL = -infini)  */
    if (!h) return 1;   /* arbre vide : toujours valide */

    /* Vérifier que la racine est dans [*b, *a] */
    if (a && h->label > *a) return 0;   /* dépasse la borne haute */
    if (b && h->label < *b) return 0;   /* dépasse la borne basse */

    /* Récursion avec propagation des bornes :
       - sous-arbre GAUCHE : valeurs >= h->label --> nouvelle borne basse = h->label
       - sous-arbre DROIT  : valeurs <= h->label --> nouvelle borne haute = h->label */
    return test_bornes_ABR(h->left,  a,           &(h->label))
        && test_bornes_ABR(h->right, &(h->label), b          );
}
```

### Trace pour comprendre les bornes

```
Appel initial : test_bornes_ABR(h, NULL, NULL)
  --> a=NULL (+inf), b=NULL (-inf) : aucune contrainte initiale

Au noeud racine de valeur 5 :
  --> appel gauche : test_bornes_ABR(gauche, NULL, &5)
       "les valeurs à gauche doivent être entre 5 et +inf"
  --> appel droit  : test_bornes_ABR(droit,  &5,   NULL)
       "les valeurs à droite doivent être entre -inf et 5"

  Au noeud gauche de valeur 10 :
    --> appel gauche : test_bornes_ABR(gauche_de_10, NULL, &10)
         "ici les valeurs doivent être entre 10 et +inf"
    --> La feuille 1 : 1 >= 10 ? NON --> return 0 (arbre invalide détecté !)
```

---

## Question 3.E — `test_ABR` [1 pt]

```c
int test_ABR(link h) {
    return test_bornes_ABR(h, NULL, NULL);
}
```

On appelle `test_bornes_ABR` avec `a=NULL` (+∞) et `b=NULL` (-∞) : pas de contrainte initiale. La fonction propage ensuite les bornes au fil de la récursion.

---

# EXERCICE 4 — Arbres Rouge-Noir LLRBT [4 pts]

> ⚠️ **ATTENTION : priorité au PLUS PETIT entier dans cet exercice (convention classique).**

## Question 4.A — Définition d'un LLRBT [1 pt]

Un **LLRBT** (Left-Leaning Red-Black Tree) est un arbre rouge-noir avec **4 propriétés** :

1. **ABR :** C'est un arbre binaire de recherche (valeurs croissantes gauche→droite).
2. **Équilibre noir :** Toutes les branches racine→feuille ont le même nombre de liens **NOIRS**.
3. **Pas de double rouge :** Jamais deux liens rouges consécutifs sur une même branche.
4. **Liens rouges à gauche :** Tout lien rouge va vers un fils **GAUCHE** (jamais vers un fils droit).

**Vérification sur l'arbre du sujet** (liens rouges : 10→4, 8→6, 24→18, 22→20, 28→26) :
- Tous vont vers un fils gauche ✓
- Hauteur noire = 3 pour toutes les branches ✓
- Pas de rouge→rouge ✓
- ABR ✓

---

## Question 4.B — Les 6 opérations pour insérer 23 [2 pts]

### Les 3 opérations élémentaires d'un LLRBT

```
ROTATION GAUCHE autour de X :
  Quand X a un lien rouge vers son fils DROIT (interdit en LLRBT).
  Le fils droit Y monte, X descend à gauche de Y.

ROTATION DROITE autour de X :
  Quand X a deux liens rouges consécutifs à gauche
  (X->rouge_gauche->Y et Y->rouge_gauche->Z).
  Le fils gauche Y monte, X descend à droite de Y.

COLOUR-FLIP autour de X :
  Quand X a ses DEUX fils avec des liens ROUGES.
  On inverse : les deux liens fils deviennent noirs, le lien vers X devient rouge.
```

### Insertion de 23 étape par étape

23 > 22, donc 23 se place comme fils **DROIT** de 22 en lien rouge.

```
Avant insertion : 22 a un fils gauche rouge (20). Après : 22 a deux fils rouges (20 et 23).
```

**Opération 1 — Insertion de 23 comme fils droit rouge de 22.**

**Opération 2 — Colour-flip autour de 22.**  
22 a deux fils rouges → colour-flip : le lien `18→22` devient rouge, les liens `22→20` et `22→23` deviennent noirs.

**Opération 3 — Rotation gauche de 18.**  
18 a maintenant un lien rouge vers son fils **DROIT** (22) : violation LLRBT. Rotation gauche : 22 monte, 18 descend à gauche de 22.

**Opération 4 — Rotation droite de 24.**  
Après la rotation, 24 a deux rouges consécutifs à gauche (`24→22` rouge et `22→18` rouge). Rotation droite : 22 monte, 24 descend à droite de 22.

**Opération 5 — Colour-flip autour de 22.**  
22 a maintenant deux fils rouges (18 à gauche et 24 à droite) → colour-flip : le lien `14→22` devient rouge, `22→18` et `22→24` deviennent noirs.

**Opération 6 — Rotation gauche de 14.**  
14 (la racine globale) a un lien rouge vers son fils **DROIT** (22) : violation LLRBT. Rotation gauche : 22 monte et devient la **nouvelle racine**, 14 descend à gauche de 22.

---

## Question 4.C — Arbre résultant après insertion de 23 [1 pt]

Après les 6 opérations, **22 est la nouvelle racine**.

```
                   22                   <- nouvelle racine
                 /       \
           14 (rouge)     24
           /    \        /   \
         10      18     23   28
        /  \   /   \         /
       4   12  16  20      26 (rouge)
  (rouge)
      /
     2
      \
       8
      /
     6 (rouge)
```

**Liens rouges dans l'arbre final :** `10→4`, `8→6`, `22→14` *(nouveau)*, `28→26`  
*(Les anciens liens `24→18` et `22→20` sont devenus noirs suite aux colour-flips.)*

> **Vérification :** 4 liens rouges, tous vers des fils gauches ✓. Pas de double rouge ✓. Hauteur noire = 3 pour toutes les branches ✓.

---

# Résumé des points clés

| Exercice | Point clé |
|----------|-----------|
| **Ex.1** | Récursion sur arbre = cas base (NULL) + traitement racine + récursion gauche/droite |
| **Ex.2** | Tas en tableau : indice `i` → fils en `2i` et `2i+1`. Vérifier `i` de 1 à `⌊n/2⌋` seulement |
| **Ex.3** | Priorité plus grand = grandes valeurs à **GAUCHE**. `fusion_ABR` descend la branche gauche de k. `test_bornes_ABR` propage des bornes (pas juste père/fils) |
| **Ex.4** | LLRBT = ABR + même hauteur noire partout + pas de double rouge + rouges seulement à gauche |
