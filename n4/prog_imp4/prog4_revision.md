# Programmation Impérative 4 — Fiche de révision complète
> L2 N4 info-DL · Institut Galilée · Université Paris 13

---

## Structures de données

### `struct binary_tree` — `BT.h`
```c
typedef struct binary_tree {
    item               label;  /* étiquette du nœud */
    struct binary_tree *left;  /* fils gauche (NULL si absent) */
    struct binary_tree *right; /* fils droit  (NULL si absent) */
} *link;
```
- `link` = pointeur vers ce struct. `NULL` = arbre vide.
- `item` = `char` (TP1–4) ou `int` (TP5).

### `struct node_Q` + `struct queue` — `queue_link.h`
```c
struct node_Q {
    link          value; /* valeur stockée */
    struct node_Q *next; /* maillon suivant */
};
struct queue {
    struct node_Q *first; /* sortie (défilage) */
    struct node_Q *last;  /* entrée (enfilage)  */
};
```
- File **chaînée** FIFO. Le double pointeur `last` permet l'enfilage en O(1).

### `struct stack` — `stack_link.h`
```c
struct stack {
    int  top;      /* nombre d'éléments actuellement empilés */
    link *contents; /* tableau de liens alloué à l'init       */
};
```
- Pile sur **tableau fixe**. Taille maximale fixée à `init_stack(maxTop)`.

### `struct llrbt_node` — `llrbt.h` (TP5)
```c
typedef struct llrbt_node {
    item              label;
    int               color;  /* RED = 1, BLACK = 0 */
    struct llrbt_node *left;
    struct llrbt_node *right;
} *llrbt_link;
```
- Comme `binary_tree` mais avec un champ `color` (couleur du lien **entrant**).

### Macros `item.h`
| Macro | Définition |
|---|---|
| `less(A,B)` | `key(A) < key(B)` |
| `eq(A,B)` | `!less(A,B) && !less(B,A)` |
| `key(A)` | `A` |
| `display(A)` | `printf("%c ", A)` |

---

## `binary_tree.c` — Bibliothèque d'arbres binaires

### Construction / destruction
```c
link empty_tree()
// Retourne NULL. Arbre vide.

link cons_binary_tree(item h, const link t1, const link t2)
// Alloue un nœud avec label=h, left=t1, right=t2.    O(1)

void delete_binary_tree(link *bt)
// Libère récursivement tous les nœuds (postordre).
// Met *bt à NULL.                                     O(n)
```

### Accès
```c
link left(const link bt)              // bt->left          O(1)
link right(const link bt)             // bt->right         O(1)
item get_binary_tree_root(const link bt) // bt->label      O(1)
int  is_empty_binary_tree(const link bt) // !bt            O(1)
```

### Mesures
```c
int size_binary_tree(const link bt)
// 0 si vide, sinon 1 + size(gauche) + size(droite)    O(n)

int height_binary_tree(const link bt)
// -1 si vide, 0 si feuille,
// sinon 1 + max(h_gauche, h_droite)                   O(n)
```

### Affichage
```c
void print_label(const link bt)
// Affiche bt->label via display(). Ne fait rien si vide. O(1)

void show_binary_tree(const link bt, int lvl)
// Arbre tourné -90° (droite en haut, gauche en bas).
// Appel initial : lvl = 0.                              O(n)
```

### Parcours récursifs
```c
void traverse_preorder_binary_tree(link bt, void (*visit)(link))
// Racine → Gauche → Droite                             O(n)

void traverse_inorder_binary_tree(link bt, void (*visit)(link))
// Gauche → Racine → Droite                             O(n)

void traverse_postorder_binary_tree(link bt, void (*visit)(link))
// Gauche → Droite → Racine                             O(n)
```

### Parcours itératifs
```c
void traverse_preorder_it_BT(link bt, void (*visit)(link))
// Pile. Empile droite puis gauche (LIFO → gauche en premier). O(n)

void traverse_inorder_it_BT(link bt, void (*visit)(link))
// Pile + pointeur current. Descend gauche, remonte, part droite. O(n)

void traverse_level_BT(link bt, void (*visit)(link))
// File FIFO. Niveau par niveau.                         O(n)
```

### Implémentations itératives
```c
/* PRÉORDRE itératif */
void traverse_preorder_it_BT(link bt, void (*visit)(link)) {
    if (is_empty_binary_tree(bt)) return;
    struct stack *s = init_stack(size_binary_tree(bt));
    push_stack(s, bt);
    while (!is_empty_stack(s)) {
        link node = pop_stack(s);
        (*visit)(node);
        if (!is_empty_binary_tree(node->right)) push_stack(s, node->right);
        if (!is_empty_binary_tree(node->left))  push_stack(s, node->left);
    }
    delete_stack(&s);
}

/* INFIXE itératif */
void traverse_inorder_it_BT(link bt, void (*visit)(link)) {
    struct stack *s = init_stack(size_binary_tree(bt) + 1);
    link current = bt;
    while (!is_empty_binary_tree(current) || !is_empty_stack(s)) {
        while (!is_empty_binary_tree(current)) {
            push_stack(s, current);
            current = current->left;
        }
        current = pop_stack(s);
        (*visit)(current);
        current = current->right;
    }
    delete_stack(&s);
}

/* LARGEUR itératif */
void traverse_level_BT(link bt, void (*visit)(link)) {
    if (is_empty_binary_tree(bt)) return;
    struct queue *q = init_queue();
    enqueue(q, bt);
    while (!is_empty_queue(q)) {
        link node = dequeue(q);
        (*visit)(node);
        if (!is_empty_binary_tree(node->left))  enqueue(q, node->left);
        if (!is_empty_binary_tree(node->right)) enqueue(q, node->right);
    }
    delete_queue(&q);
}
```

---

## `stack_link.c` — Pile

```c
struct stack *init_stack(int maxTop)
// Alloue une pile de capacité maxTop.               O(1)

void delete_stack(struct stack **s)
// Libère contents puis s. Met *s à NULL.            O(1)

int is_empty_stack(const struct stack *s)
// s->top == 0 ?                                     O(1)

void push_stack(struct stack *s, link val)
// contents[top++] = val                             O(1)

link pop_stack(struct stack *s)
// return contents[--top]  (requiert pile non vide)  O(1)
```

---

## `queue_link.c` — File

```c
struct node_Q *new_node_Q(link h)
// Alloue maillon value=h, next=NULL.                O(1)

void delete_node_Q(struct node_Q **nq)
// free(*nq); *nq = NULL.                            O(1)

struct queue *init_queue()
// Alloue file vide (first=last=NULL).               O(1)

void delete_queue(struct queue **q)
// Libère tous les maillons puis la file.            O(n)

int is_empty_queue(const struct queue *q)
// q->first == NULL ?                                O(1)

void enqueue(struct queue *q, link h)
// Ajoute en fin via q->last.                        O(1)

link dequeue(struct queue *q)
// Retire et retourne q->first (requiert non vide).  O(1)
```

---

## Expressions arithmétiques — TP2/TP3

### Principe
La **notation préfixe** place l'opérateur avant ses opérandes.
- Infixe : `(3 * 4) + 5` → Préfixe : `+ * 3 4 5`
- L'arbre syntaxique = opérateurs aux nœuds internes, chiffres aux feuilles.

### Fonctions
```c
int is_operator(char c)
// c == '+' || '-' || '*' || '/'                     O(1)

link parse_expr(const char *expr, int *pos)
// Construit l'arbre depuis la chaîne préfixe.
// pos avance globalement à travers tous les appels.
// Opérateur → parse_expr(gauche) + parse_expr(droite)
// Chiffre   → feuille                               O(n)

int eval_tree(const link bt)
// Parcours POSTORDRE. Feuille : c - '0'.
// Nœud interne : eval(gauche) OP eval(droite)       O(n)

void tree_to_expr(const link bt, char *buf, int *pos)
// Reconstruit la chaîne PRÉFIXE (parcours PRÉORDRE).
// Résultat identique à l'entrée.                    O(n)

void tree_to_infix(const link bt, char *buf, int *pos)
// Reconstruit la chaîne INFIXE (parcours INFIXE).
// Parenthèse chaque sous-expression opérateur.
// Ex : + * 3 4 5  →  ((3 * 4) + 5)                 O(n)
```

### Implémentations
```c
link parse_expr(const char *expr, int *pos) {
    while (expr[*pos] == ' ') (*pos)++;
    char c = expr[*pos]; (*pos)++;
    if (is_operator(c)) {
        link g = parse_expr(expr, pos);
        link d = parse_expr(expr, pos);
        return cons_binary_tree(c, g, d);
    }
    return cons_binary_tree(c, empty_tree(), empty_tree());
}

int eval_tree(const link bt) {
    if (is_empty_binary_tree(bt)) return 0;
    char c = get_binary_tree_root(bt);
    if (is_operator(c)) {
        int vg = eval_tree(bt->left);
        int vd = eval_tree(bt->right);
        switch (c) {
            case '+': return vg + vd;
            case '-': return vg - vd;
            case '*': return vg * vd;
            case '/': return vg / vd;
        }
    }
    return c - '0';
}

void tree_to_infix(const link bt, char *buf, int *pos) {
    if (is_empty_binary_tree(bt)) return;
    char c = get_binary_tree_root(bt);
    if (is_operator(c)) {
        buf[(*pos)++] = '(';
        tree_to_infix(bt->left, buf, pos);
        buf[(*pos)++] = ' '; buf[(*pos)++] = c; buf[(*pos)++] = ' ';
        tree_to_infix(bt->right, buf, pos);
        buf[(*pos)++] = ')';
    } else {
        buf[(*pos)++] = c;
    }
}
```

---

## Tri par tas — TP3

### Stockage dans un tableau (segment `t[lo..hi]`)
| Formule | Expression |
|---|---|
| Racine | `lo` |
| Fils gauche de `t[i]` | `2*(i-lo)+1+lo` |
| Fils droit de `t[i]` | `2*(i-lo)+2+lo` |
| Parent de `t[i]` | `lo + (i-lo-1)/2` |

**Propriété tas-max** : `t[parent] >= t[fils]` → la racine est toujours le maximum.

### Fonctions
```c
void swap(int *a, int *b)
// Échange *a et *b via tmp.                         O(1)

void print_array(const int *t, int n)
// Affiche t[0..n-1].                               O(n)

void print_segment(const int *t, int lo, int hi)
// Affiche t[lo..hi].                               O(hi-lo)

void fixHeap(int *t, int lo, int hi, int i)
// Fait descendre t[i] pour restaurer le tas-max.
// Suppose les sous-arbres de i déjà valides.       O(log n)

void buildHeap(int *t, int lo, int hi)
// Transforme t[lo..hi] en tas-max.
// Appelle fixHeap de (lo+(hi-lo-1)/2) vers lo.    O(n)

void heap_sort(int *t, int lo, int hi)
// Phase 1 : buildHeap.
// Phase 2 : n-1 fois : échange t[lo]↔t[end],
//           end--, fixHeap depuis lo.              O(n log n)
```

### Implémentations
```c
void fixHeap(int *t, int lo, int hi, int i) {
    while (1) {
        int fg = 2 * (i - lo) + 1 + lo;
        if (fg > hi) break;
        int j = fg, fd = fg + 1;
        if (fd <= hi && t[fd] > t[fg]) j = fd;
        if (t[i] >= t[j]) break;
        swap(&t[i], &t[j]);
        i = j;
    }
}

void buildHeap(int *t, int lo, int hi) {
    int dernier_interne = lo + (hi - lo - 1) / 2;
    for (int i = dernier_interne; i >= lo; i--)
        fixHeap(t, lo, hi, i);
}

void heap_sort(int *t, int lo, int hi) {
    if (lo >= hi) return;
    buildHeap(t, lo, hi);
    int end = hi;
    while (end > lo) {
        swap(&t[lo], &t[end]);
        end--;
        fixHeap(t, lo, end, lo);
    }
}
```

---

## ABR — Arbres Binaires de Recherche — TP4

### Propriété ABR
Pour tout nœud `h` : `gauche < h->label <= droite`.
Le parcours infixe donne les valeurs en **ordre croissant**.

### Fonctions fournies (`bst_cm5_2026.c`)
```c
link search_BST(link h, item v)
// Recherche récursive de v. Retourne le nœud ou NULL. O(n) pire

link insert_BST(link h, item v)
// Insère v comme feuille (récursif).                  O(n) pire

link insert_BST_it(link h, item v)
// Insère v comme feuille (itératif, sans pile).       O(n) pire

link select_BST(link h, int k)
// Nœud de rang k (0-indexé).
// t = size(gauche) ; t>k→gauche ; t<k→droite k-t-1   O(n²) pire

link rotate_right(link h)
// Fait monter le fils gauche.                         O(1)

link rotate_left(link h)
// Fait monter le fils droit.                          O(1)

link insert_BST_root(link h, item v)
// Insère v à la racine (récursif + rotations).        O(n) pire
```

### Fonctions TP4 (`bst.c`)
```c
link insert_BST_root_it(link h, item v)
// Insère v à la racine (itératif).
// Crée le nœud v, puis répartit les nœuds à gauche
// (<v) ou droite (>=v) via left_ptr/right_ptr.       O(n) pire

link partition_BST(link h, int k)
// Amène le rang k à la racine.
// t = size(gauche) ; t>k→partition gauche+rotateRight
//                  ; t<k→partition droite+rotateLeft  O(n)

link delete_node_BST(link h, item v)
// Supprime v. Fusionne L et R avec join_BST(L,R) :
// partition(R,0) pour amener le min de R, L→fils g.  O(n)

link balance_BST(link h)
// Amène le médian (n/2) à la racine via partition,
// rééquilibre récursivement gauche et droite.
// Hauteur finale ≈ log₂(n).                          O(n²)
```

### Implémentations TP4
```c
link insert_BST_root_it(link h, item v) {
    link new_node = cons_binary_tree(v, NULL, NULL);
    if (h == NULL) return new_node;
    link *left_ptr  = &(new_node->left);
    link *right_ptr = &(new_node->right);
    link cur = h;
    while (cur != NULL) {
        if (less(v, get_binary_tree_root(cur))) {
            *right_ptr = cur; right_ptr = &(cur->left); cur = cur->left;
        } else {
            *left_ptr  = cur; left_ptr  = &(cur->right); cur = cur->right;
        }
    }
    *left_ptr = NULL; *right_ptr = NULL;
    return new_node;
}

link partition_BST(link h, int k) {
    if (h == NULL) return NULL;
    int t = size_binary_tree(h->left);
    if (t > k) { h->left  = partition_BST(h->left,  k);       h = rotate_right(h); }
    else if (t < k) { h->right = partition_BST(h->right, k-t-1); h = rotate_left(h);  }
    return h;
}

static link join_BST(link L, link R) {
    if (L == NULL) return R;
    if (R == NULL) return L;
    R = partition_BST(R, 0);
    R->left = L;
    return R;
}

link delete_node_BST(link h, item v) {
    if (h == NULL) return NULL;
    item r = get_binary_tree_root(h);
    if (eq(v, r)) { link L = h->left, R = h->right; free(h); return join_BST(L, R); }
    else if (less(v, r)) h->left  = delete_node_BST(h->left,  v);
    else                 h->right = delete_node_BST(h->right, v);
    return h;
}

link balance_BST(link h) {
    int n = size_binary_tree(h);
    if (n <= 1) return h;
    h = partition_BST(h, n / 2);
    h->left  = balance_BST(h->left);
    h->right = balance_BST(h->right);
    return h;
}
```

---

## LLRBT — Left-Leaning Red-Black Tree — TP5

### Règles
1. Propriété ABR préservée.
2. Un lien rouge penche **toujours à gauche** (jamais à droite).
3. Pas deux liens rouges **consécutifs** sur un chemin.
4. La racine est toujours **noire**.
5. Même nombre de liens noirs sur tout chemin racine→feuille.

**Conséquence** : hauteur ≤ 2·log₂(n). Toutes les opérations en O(log n).  
Tout nouveau nœud est créé **rouge**.

### Fonctions
```c
llrbt_link new_llrbt_node(item v)
// Alloue nœud avec color=RED, left=right=NULL.      O(1)

void delete_llrbt(llrbt_link *h)
// Libère récursivement (postordre). Met *h à NULL.  O(n)

int isRed(llrbt_link h)
// h != NULL && h->color == RED. NULL → BLACK.       O(1)

llrbt_link rotateLeft(llrbt_link h)
// Fils droit rouge → le faire monter.
// x=h->right ; h->right=x->left ; x->left=h
// x hérite couleur de h, h devient RED.             O(1)

llrbt_link rotateRight(llrbt_link h)
// Deux rouges consécutifs à gauche → corriger.
// Symétrique de rotateLeft.                         O(1)

void flipColors(llrbt_link h)
// Deux fils rouges → inverser les 3 couleurs.
// Fils deviennent noirs, h devient rouge.           O(1)

llrbt_link insert_LLRBT(llrbt_link h, item v)
// Descente BST, puis en remontant dans cet ordre :
// 1. rotateLeft  si droit rouge et gauche noir
// 2. rotateRight si gauche rouge et gauche.gauche rouge
// 3. flipColors  si les deux fils rouges
// Forcer racine à BLACK après l'appel top-level.    O(log n)

void inorder_LLRBT(llrbt_link h, item *t, int *idx)
// Parcours infixe → remplit t[] en ordre croissant. O(n)

void show_llrbt(llrbt_link h, int lvl)
// Affiche l'arbre, 'R' si lien rouge, '.' si noir. O(n)
```

### Implémentations clés
```c
llrbt_link rotateLeft(llrbt_link h) {
    llrbt_link x = h->right;
    h->right = x->left;
    x->left  = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

llrbt_link rotateRight(llrbt_link h) {
    llrbt_link x = h->left;
    h->left  = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

void flipColors(llrbt_link h) {
    h->color        = !(h->color);
    h->left->color  = !(h->left->color);
    h->right->color = !(h->right->color);
}

llrbt_link insert_LLRBT(llrbt_link h, item v) {
    if (h == NULL) return new_llrbt_node(v);
    if      (less(v, h->label)) h->left  = insert_LLRBT(h->left,  v);
    else                        h->right = insert_LLRBT(h->right, v);
    if ( isRed(h->right) && !isRed(h->left))           h = rotateLeft(h);
    if ( isRed(h->left)  &&  isRed(h->left->left))     h = rotateRight(h);
    if ( isRed(h->left)  &&  isRed(h->right))          flipColors(h);
    return h;
}
```

---

## Complexités à retenir

| Opération | Complexité |
|---|---|
| Rotation (gauche ou droite) | O(1) |
| Push / Pop pile | O(1) |
| Enfile / Défile file | O(1) |
| isRed, flipColors | O(1) |
| Parcours complet (n nœuds) | O(n) |
| size / height | O(n) |
| buildHeap | O(n) |
| fixHeap | O(log n) |
| insert ABR (moy / pire) | O(log n) / O(n) |
| insert LLRBT (garanti) | O(log n) |
| select_BST | O(n²) pire |
| balance_BST | O(n²) |
| heap_sort | O(n log n) |
| Tri par LLRBT | O(n log n) |

---

## C essentiel

### Allocation mémoire
```c
link t = malloc(sizeof(struct binary_tree));
if (!t) return NULL;   /* toujours vérifier */
free(ptr);
ptr = NULL;            /* éviter le dangling pointer */
```

### Lecture d'une ligne entière
```c
fgets(buf, sizeof(buf), stdin);
int len = strlen(buf);
if (len > 0 && buf[len-1] == '\n')
    buf[len-1] = '\0';  /* '\0' et non '\n' ! */
```

### Pointeur de fonction
```c
void traverse_inorder_binary_tree(link bt, void (*visit)(link));
/* Déclaration : void (*visit)(link) */
/* Passage    : traverse_inorder(bt, print_label) */
/* Appel      : (*visit)(node) */
```

### Passage par pointeur (modifier depuis une fonction)
```c
void parse_expr(const char *expr, int *pos) {
    (*pos)++;   /* modifier la variable de l'appelant */
}
/* Appel : parse_expr(expr, &pos) */
```

### Makefile minimal
```makefile
CC     = gcc
CFLAGS = -Wall -Wextra -std=c99

OBJS = main.o lib.o

main: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

main.o: main.c lib.h
	$(CC) $(CFLAGS) -c main.c

lib.o: lib.c lib.h
	$(CC) $(CFLAGS) -c lib.c

clean:
	rm -f $(OBJS) main

.PHONY: clean
```
- `-c` : compiler sans lier → produit `.o`
- `-I"chemin"` : dossier supplémentaire de recherche des headers
- `-o nom` : nom de l'exécutable
- Les recettes doivent commencer par une **tabulation** (pas des espaces)
