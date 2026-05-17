# Programmation Impérative 4 — Toutes les fonctions avec implémentations
> L2 N4 info-DL · Institut Galilée · Université Paris 13

---

## Structures de données

### `struct binary_tree` — `BT.h`
```c
typedef struct binary_tree {
    item               label;   /* étiquette du nœud     */
    struct binary_tree *left;   /* fils gauche            */
    struct binary_tree *right;  /* fils droit             */
} *link;
```

### `struct node_Q` + `struct queue` — `queue_link.h`
```c
struct node_Q {
    link          value;
    struct node_Q *next;
};
struct queue {
    struct node_Q *first;   /* sortie (défilage) */
    struct node_Q *last;    /* entrée (enfilage) */
};
```

### `struct stack` — `stack_link.h`
```c
struct stack {
    int  top;       /* nombre d'éléments empilés */
    link *contents; /* tableau alloué à l'init   */
};
```

### `struct llrbt_node` — `llrbt.h` (TP5)
```c
typedef struct llrbt_node {
    item              label;
    int               color;   /* RED = 1, BLACK = 0 */
    struct llrbt_node *left;
    struct llrbt_node *right;
} *llrbt_link;

#define RED   1
#define BLACK 0
```

### Macros `item.h`
```c
typedef char item;          /* TP1-4 : char  |  TP5 : int */

#define key(A)     (A)
#define less(A, B) (key(A) < key(B))
#define eq(A, B)   (!less(A,B) && !less(B,A))
#define exch(A, B) { char tmp = A; A = B; B = tmp; }
#define display(A) { printf("%c ", key(A)); }
#define destroy(A)
```

---

## `binary_tree.c` — Bibliothèque d'arbres binaires

### `empty_tree`
```c
/* Retourne un arbre vide (NULL).
   Complexité : O(1) */
link empty_tree() {
    return NULL;
}
```

### `cons_binary_tree`
```c
/* Alloue un nouveau nœud avec l'étiquette h,
   le fils gauche tree1 et le fils droit tree2.
   Complexité : O(1) */
link cons_binary_tree(item h, const link tree1, const link tree2) {
    link tree = malloc(sizeof(struct binary_tree));
    if (!tree) return NULL;
    tree->label = h;
    tree->left  = tree1;
    tree->right = tree2;
    return tree;
}
```

### `delete_binary_tree`
```c
/* Libère récursivement tous les nœuds de l'arbre.
   Ordre : postordre (fils gauche, fils droit, racine).
   Met *bt à NULL après libération.
   Complexité : O(n) */
void delete_binary_tree(link *bt) {
    if (!bt || *bt == NULL) return;
    delete_binary_tree(&((*bt)->left));
    delete_binary_tree(&((*bt)->right));
    free(*bt);
    *bt = NULL;
}
```

### `left`
```c
/* Retourne le fils gauche du nœud bt.
   Requiert bt non vide.
   Complexité : O(1) */
link left(const link bt) {
    return bt->left;
}
```

### `right`
```c
/* Retourne le fils droit du nœud bt.
   Requiert bt non vide.
   Complexité : O(1) */
link right(const link bt) {
    return bt->right;
}
```

### `get_binary_tree_root`
```c
/* Retourne l'étiquette de la racine.
   Requiert bt non vide.
   Complexité : O(1) */
item get_binary_tree_root(const link bt) {
    return bt->label;
}
```

### `is_empty_binary_tree`
```c
/* Retourne 1 si bt == NULL, 0 sinon.
   Complexité : O(1) */
int is_empty_binary_tree(const link bt) {
    return !bt;
}
```

### `size_binary_tree`
```c
/* Retourne le nombre total de nœuds.
   Récursif : 0 si vide, sinon 1 + size(gauche) + size(droite).
   Complexité : O(n) */
int size_binary_tree(const link bt) {
    if (is_empty_binary_tree(bt)) return 0;
    return 1 + size_binary_tree(bt->left) + size_binary_tree(bt->right);
}
```

### `height_binary_tree`
```c
/* Retourne la hauteur de l'arbre.
   Convention : -1 si vide, 0 si feuille.
   Complexité : O(n) */
int height_binary_tree(const link bt) {
    if (is_empty_binary_tree(bt)) return -1;
    int hl = height_binary_tree(bt->left);
    int hr = height_binary_tree(bt->right);
    return 1 + (hl > hr ? hl : hr);
}
```

### `print_label`
```c
/* Affiche l'étiquette de la racine via la macro display().
   Ne fait rien si bt est vide.
   Complexité : O(1) */
void print_label(const link bt) {
    if (!is_empty_binary_tree(bt))
        display(bt->label);
}
```

### `show_binary_tree`
```c
/* Affiche l'arbre tourné de -90° :
   - le sous-arbre DROIT est affiché en premier (en haut)
   - le sous-arbre GAUCHE est affiché en dernier (en bas)
   - chaque niveau est indenté de 4 espaces × lvl
   Appel initial : show_binary_tree(bt, 0)
   Complexité : O(n) */
void show_binary_tree(const link bt, int lvl) {
    if (is_empty_binary_tree(bt)) return;
    show_binary_tree(bt->right, lvl + 1);
    for (int i = 0; i < lvl; i++) printf("    ");
    printf("%c\n", bt->label);
    show_binary_tree(bt->left, lvl + 1);
}
```

### `traverse_preorder_binary_tree`
```c
/* Parcours récursif PRÉORDRE : Racine → Gauche → Droite.
   visit = pointeur de fonction appelé sur chaque nœud.
   Complexité : O(n) */
void traverse_preorder_binary_tree(link bt, void (*visit)(link)) {
    if (is_empty_binary_tree(bt)) return;
    (*visit)(bt);
    traverse_preorder_binary_tree(bt->left,  visit);
    traverse_preorder_binary_tree(bt->right, visit);
}
```

### `traverse_inorder_binary_tree`
```c
/* Parcours récursif INFIXE : Gauche → Racine → Droite.
   Pour un ABR, donne les valeurs en ordre croissant.
   Complexité : O(n) */
void traverse_inorder_binary_tree(link bt, void (*visit)(link)) {
    if (is_empty_binary_tree(bt)) return;
    traverse_inorder_binary_tree(bt->left, visit);
    (*visit)(bt);
    traverse_inorder_binary_tree(bt->right, visit);
}
```

### `traverse_postorder_binary_tree`
```c
/* Parcours récursif POSTORDRE : Gauche → Droite → Racine.
   Utilisé par delete_binary_tree.
   Complexité : O(n) */
void traverse_postorder_binary_tree(link bt, void (*visit)(link)) {
    if (is_empty_binary_tree(bt)) return;
    traverse_postorder_binary_tree(bt->left,  visit);
    traverse_postorder_binary_tree(bt->right, visit);
    (*visit)(bt);
}
```

### `traverse_preorder_it_BT`
```c
/* Parcours PRÉORDRE itératif avec une pile.
   On empile d'abord le fils DROIT puis le fils GAUCHE :
   comme la pile est LIFO, le gauche ressort en premier.
   Complexité : O(n) */
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
```

### `traverse_inorder_it_BT`
```c
/* Parcours INFIXE itératif avec pile + pointeur current.
   Deux mouvements alternent :
     - Descente gauche : empile chaque nœud jusqu'à NULL.
     - Remontée : dépile, visite, repart à droite.
   Complexité : O(n) */
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
```

### `traverse_level_BT`
```c
/* Parcours en LARGEUR (BFS) avec une file FIFO.
   On enfile la racine, puis à chaque défilement on visite
   et on enfile les fils gauche et droit.
   Complexité : O(n) */
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

### `init_stack`
```c
/* Alloue une pile de capacité maximale maxTop.
   Initialise top = 0 et alloue le tableau contents.
   Complexité : O(1) */
struct stack *init_stack(int maxTop) {
    struct stack *s = malloc(sizeof(struct stack));
    s->top      = 0;
    s->contents = malloc(maxTop * sizeof(link));
    return s;
}
```

### `delete_stack`
```c
/* Libère le tableau contents puis la structure elle-même.
   Met *s à NULL.
   Complexité : O(1) */
void delete_stack(struct stack **s) {
    free((*s)->contents);
    free(*s);
    *s = NULL;
}
```

### `is_empty_stack`
```c
/* Retourne 1 si la pile est vide (top == 0), 0 sinon.
   Complexité : O(1) */
int is_empty_stack(const struct stack *s) {
    return (s->top == 0);
}
```

### `push_stack`
```c
/* Empile val : écrit contents[top] = val puis incrémente top.
   Ne vérifie pas le débordement.
   Complexité : O(1) */
void push_stack(struct stack *s, link val) {
    s->contents[s->top++] = val;
}
```

### `pop_stack`
```c
/* Dépile : décrémente top puis retourne contents[top].
   Requiert que la pile ne soit pas vide.
   Complexité : O(1) */
link pop_stack(struct stack *s) {
    return s->contents[--s->top];
}
```

---

## `queue_link.c` — File

### `new_node_Q`
```c
/* Alloue un maillon avec value = h et next = NULL.
   Complexité : O(1) */
struct node_Q *new_node_Q(link h) {
    struct node_Q *nq = malloc(sizeof(struct node_Q));
    nq->value = h;
    nq->next  = NULL;
    return nq;
}
```

### `delete_node_Q`
```c
/* Libère le maillon *nq et met *nq à NULL.
   Complexité : O(1) */
void delete_node_Q(struct node_Q **nq) {
    free(*nq);
    *nq = NULL;
}
```

### `init_queue`
```c
/* Alloue une file vide (first = last = NULL).
   Complexité : O(1) */
struct queue *init_queue() {
    struct queue *q = malloc(sizeof(struct queue));
    q->first = NULL;
    q->last  = NULL;
    return q;
}
```

### `delete_queue`
```c
/* Libère tous les maillons un à un, puis la file.
   Met *q à NULL.
   Complexité : O(n) */
void delete_queue(struct queue **q) {
    while (!is_empty_queue(*q)) {
        struct node_Q *nq = (*q)->first;
        (*q)->first = nq->next;
        delete_node_Q(&nq);
    }
    free(*q);
    *q = NULL;
}
```

### `is_empty_queue`
```c
/* Retourne 1 si q->first == NULL, 0 sinon.
   Complexité : O(1) */
int is_empty_queue(const struct queue *q) {
    return (NULL == q->first);
}
```

### `enqueue`
```c
/* Ajoute h en fin de file via q->last.
   Si la file est vide, met aussi q->first.
   Complexité : O(1) */
void enqueue(struct queue *q, link h) {
    struct node_Q *nq = new_node_Q(h);
    if (is_empty_queue(q)) q->first      = nq;
    else                   q->last->next = nq;
    q->last = nq;
}
```

### `dequeue`
```c
/* Retire et retourne le premier élément (q->first).
   Avance q->first. Si la file devient vide, met q->last = NULL.
   Requiert que la file ne soit pas vide.
   Complexité : O(1) */
link dequeue(struct queue *q) {
    struct node_Q *nq = q->first;
    link res = nq->value;
    q->first = nq->next;
    if (NULL == nq->next) q->last = NULL;
    delete_node_Q(&nq);
    return res;
}
```

---

## Expressions arithmétiques — TP2/TP3

> **Notation préfixe** : l'opérateur précède ses opérandes.
> Infixe : `(3 * 4) + 5` → Préfixe : `+ * 3 4 5`
> L'arbre syntaxique place les opérateurs aux nœuds internes, les chiffres aux feuilles.

### `is_operator`
```c
/* Retourne 1 si c est un opérateur +, -, *, /, sinon 0.
   Complexité : O(1) */
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}
```

### `parse_expr`
```c
/* Construit récursivement l'arbre syntaxique d'une expression préfixe.
   pos avance dans la chaîne à travers tous les appels récursifs.
   - Opérateur → parse_expr(gauche) + parse_expr(droite) → nœud interne
   - Chiffre   → feuille (pas d'enfants)
   Complexité : O(n) */
link parse_expr(const char *expr, int *pos) {
    while (expr[*pos] == ' ') (*pos)++;
    char c = expr[*pos];
    (*pos)++;
    if (is_operator(c)) {
        link g = parse_expr(expr, pos);
        link d = parse_expr(expr, pos);
        return cons_binary_tree(c, g, d);
    }
    return cons_binary_tree(c, empty_tree(), empty_tree());
}
```

### `eval_tree`
```c
/* Évalue récursivement l'arbre syntaxique.
   Parcours POSTORDRE : évalue gauche, droite, applique l'opérateur.
   Feuille chiffre : c - '0'  (ex : '3' - '0' = 3)
   Complexité : O(n) */
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
```

### `tree_to_expr`
```c
/* Reconstruit la chaîne PRÉFIXE depuis l'arbre.
   Parcours PRÉORDRE : racine, espace, gauche, espace, droite.
   Le résultat est identique à l'expression d'entrée.
   Complexité : O(n) */
void tree_to_expr(const link bt, char *buf, int *pos) {
    if (is_empty_binary_tree(bt)) return;
    buf[(*pos)++] = get_binary_tree_root(bt);
    if (!is_empty_binary_tree(bt->left)) {
        buf[(*pos)++] = ' ';
        tree_to_expr(bt->left, buf, pos);
    }
    if (!is_empty_binary_tree(bt->right)) {
        buf[(*pos)++] = ' ';
        tree_to_expr(bt->right, buf, pos);
    }
}
```

### `tree_to_infix`
```c
/* Reconstruit la chaîne INFIXE depuis l'arbre.
   Parcours INFIXE avec parenthèses autour de chaque
   sous-expression opérateur.
   Ex : + * 3 4 5  →  ((3 * 4) + 5)
   Complexité : O(n) */
void tree_to_infix(const link bt, char *buf, int *pos) {
    if (is_empty_binary_tree(bt)) return;
    char c = get_binary_tree_root(bt);
    if (is_operator(c)) {
        buf[(*pos)++] = '(';
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
```

---

## Tri par tas — TP3

> Formules pour le segment `t[lo..hi]` :
> - Racine = `lo`
> - Fils gauche de `t[i]` = `2*(i-lo)+1+lo`
> - Fils droit de `t[i]`  = `2*(i-lo)+2+lo`
> - Parent de `t[i]`      = `lo + (i-lo-1)/2`
> - Dernier nœud interne  = `lo + (hi-lo-1)/2`
>
> **Propriété tas-max** : `t[parent] >= t[fils]` → la racine = maximum.

### `swap`
```c
/* Échange les valeurs pointées par a et b.
   Complexité : O(1) */
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
```

### `print_array`
```c
/* Affiche le tableau t[0..n-1] entre crochets.
   Complexité : O(n) */
void print_array(const int *t, int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) printf("%d ", t[i]);
    printf("]\n");
}
```

### `print_segment`
```c
/* Affiche le segment t[lo..hi] inclus entre crochets.
   Complexité : O(hi - lo) */
void print_segment(const int *t, int lo, int hi) {
    printf("[ ");
    for (int i = lo; i <= hi; i++) printf("%d ", t[i]);
    printf("]\n");
}
```

### `fixHeap`
```c
/* Fait descendre t[i] dans t[lo..hi] pour restaurer le tas-max.
   Suppose que les sous-arbres de i sont déjà des tas valides.
   À chaque étape : trouve le plus grand fils j,
   échange si t[i] < t[j], continue depuis j.
   S'arrête si t[i] est une feuille ou t[i] >= t[j].
   Complexité : O(log n) */
void fixHeap(int *t, int lo, int hi, int i) {
    while (1) {
        int fg = 2 * (i - lo) + 1 + lo;  /* fils gauche */
        if (fg > hi) break;               /* i est une feuille */
        int j  = fg;
        int fd = fg + 1;                  /* fils droit */
        if (fd <= hi && t[fd] > t[fg]) j = fd;  /* j = plus grand fils */
        if (t[i] >= t[j]) break;         /* propriété respectée */
        swap(&t[i], &t[j]);
        i = j;                            /* continuer la descente */
    }
}
```

### `buildHeap`
```c
/* Transforme t[lo..hi] en tas-max en O(n).
   Appelle fixHeap sur chaque nœud interne,
   en partant du dernier parent vers la racine.
   Complexité : O(n) */
void buildHeap(int *t, int lo, int hi) {
    int dernier_interne = lo + (hi - lo - 1) / 2;
    for (int i = dernier_interne; i >= lo; i--)
        fixHeap(t, lo, hi, i);
}
```

### `heap_sort`
```c
/* Trie t[lo..hi] en ordre croissant par tri par tas.
   Phase 1 : buildHeap → t[lo] = maximum.
   Phase 2 : n-1 fois :
     - échange t[lo] (max actuel) avec t[end]
     - end--
     - fixHeap depuis lo pour restaurer le tas
   Complexité : O(n log n) */
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

> **Propriété ABR** : `gauche < racine <= droite`.
> Le parcours infixe donne les valeurs en ordre croissant.

### `search_BST`
```c
/* Recherche récursive de la valeur v dans l'ABR.
   Retourne le nœud si trouvé, NULL sinon.
   Complexité : O(n) pire cas */
link search_BST(link h, item v) {
    if (h == NULL) return NULL;
    item t = get_binary_tree_root(h);
    if (eq(v, t))   return h;
    if (less(v, t)) return search_BST(h->left,  v);
    else            return search_BST(h->right, v);
}
```

### `insert_BST`
```c
/* Insère v comme feuille dans l'ABR (version récursive).
   Descend jusqu'à NULL, crée un nœud, retourne h modifié.
   Complexité : O(n) pire cas */
link insert_BST(link h, item v) {
    if (h == NULL) return cons_binary_tree(v, NULL, NULL);
    if (less(v, get_binary_tree_root(h)))
        h->left  = insert_BST(h->left,  v);
    else
        h->right = insert_BST(h->right, v);
    return h;
}
```

### `insert_BST_it`
```c
/* Insère v comme feuille dans l'ABR (version itérative, sans pile).
   p = parent courant, x = nœud courant.
   À la sortie de la boucle, x == NULL et p est le futur parent.
   Complexité : O(n) pire cas */
link insert_BST_it(link h, item v) {
    link p, x = h;
    if (h == NULL) return cons_binary_tree(v, NULL, NULL);
    while (x != NULL) {
        p = x;
        x = less(v, get_binary_tree_root(x)) ? x->left : x->right;
    }
    x = cons_binary_tree(v, NULL, NULL);
    if (less(v, p->label)) p->left  = x;
    else                   p->right = x;
    return h;
}
```

### `select_BST`
```c
/* Retourne le nœud de rang k (0-indexé).
   t = size(gauche) = rang de la racine.
   t > k → chercher à gauche avec k
   t < k → chercher à droite avec k - t - 1
   t == k → retourner h
   Complexité : O(n²) pire cas */
link select_BST(link h, int k) {
    if (h == NULL) return NULL;
    int t = size_binary_tree(h->left);
    if      (t > k) return select_BST(h->left,  k);
    else if (t < k) return select_BST(h->right, k - t - 1);
    return h;
}
```

### `rotate_right`
```c
/* Fait monter le fils GAUCHE à la place de h.
   h descend comme fils droit du nouveau sommet.
   Le sous-arbre droit du nouveau sommet devient fils gauche de h.
   Complexité : O(1) */
link rotate_right(link h) {
    link x   = h->left;
    h->left  = x->right;
    x->right = h;
    return x;
}
```

### `rotate_left`
```c
/* Fait monter le fils DROIT à la place de h.
   h descend comme fils gauche du nouveau sommet.
   Symétrique de rotate_right.
   Complexité : O(1) */
link rotate_left(link h) {
    link x   = h->right;
    h->right = x->left;
    x->left  = h;
    return x;
}
```

### `insert_BST_root`
```c
/* Insère v à la RACINE de l'ABR (version récursive).
   Insère récursivement dans le sous-arbre approprié,
   puis fait une rotation pour ramener v à la racine.
   Complexité : O(n) pire cas */
link insert_BST_root(link h, item v) {
    if (h == NULL) return cons_binary_tree(v, NULL, NULL);
    if (less(v, get_binary_tree_root(h))) {
        h->left = insert_BST_root(h->left, v);
        h = rotate_right(h);
    } else {
        h->right = insert_BST_root(h->right, v);
        h = rotate_left(h);
    }
    return h;
}
```

### `insert_BST_root_it`
```c
/* Insère v à la RACINE de l'ABR (version itérative).
   Technique "split + recolle" :
   On crée le nœud v, puis on traverse l'arbre en répartissant
   chaque nœud rencontré à gauche (<v) ou à droite (>=v) de v
   via deux pointeurs left_ptr et right_ptr qui avancent.
   Complexité : O(n) pire cas */
link insert_BST_root_it(link h, item v) {
    link new_node = cons_binary_tree(v, NULL, NULL);
    if (h == NULL) return new_node;
    link *left_ptr  = &(new_node->left);
    link *right_ptr = &(new_node->right);
    link cur = h;
    while (cur != NULL) {
        if (less(v, get_binary_tree_root(cur))) {
            *right_ptr = cur;
            right_ptr  = &(cur->left);
            cur        = cur->left;
        } else {
            *left_ptr = cur;
            left_ptr  = &(cur->right);
            cur       = cur->right;
        }
    }
    *left_ptr  = NULL;
    *right_ptr = NULL;
    return new_node;
}
```

### `partition_BST`
```c
/* Amène le nœud de rang k à la RACINE en préservant la propriété ABR.
   t = size(gauche) = rang de la racine courante.
   t > k → partition récursif à gauche  + rotate_right
   t < k → partition récursif à droite  + rotate_left
   t == k → la racine est déjà le k-ème nœud
   Complexité : O(n) */
link partition_BST(link h, int k) {
    if (h == NULL) return NULL;
    int t = size_binary_tree(h->left);
    if (t > k) {
        h->left = partition_BST(h->left, k);
        h = rotate_right(h);
    } else if (t < k) {
        h->right = partition_BST(h->right, k - t - 1);
        h = rotate_left(h);
    }
    return h;
}
```

### `join_BST` (fonction locale)
```c
/* Fusionne deux ABR L et R où tous les éléments de L < tous ceux de R.
   Amène le minimum de R à la racine via partition_BST(R, 0),
   ce minimum n'a pas de fils gauche → on y attache L.
   Complexité : O(n) */
static link join_BST(link L, link R) {
    if (L == NULL) return R;
    if (R == NULL) return L;
    R = partition_BST(R, 0);   /* minimum de R à la racine */
    R->left = L;               /* R->left est NULL (c'était le min) */
    return R;
}
```

### `delete_node_BST`
```c
/* Supprime le nœud de valeur v dans l'ABR.
   Descente BST pour trouver v,
   puis fusionne ses deux sous-arbres L et R avec join_BST.
   Complexité : O(n) */
link delete_node_BST(link h, item v) {
    if (h == NULL) return NULL;
    item r = get_binary_tree_root(h);
    if (eq(v, r)) {
        link L = h->left;
        link R = h->right;
        free(h);
        return join_BST(L, R);
    } else if (less(v, r)) {
        h->left  = delete_node_BST(h->left,  v);
    } else {
        h->right = delete_node_BST(h->right, v);
    }
    return h;
}
```

### `balance_BST`
```c
/* Rééquilibre l'ABR par diviser-pour-régner.
   Amène le médian (rang n/2) à la racine via partition_BST,
   rééquilibre récursivement les sous-arbres gauche et droite.
   Hauteur finale ≈ log₂(n).
   Complexité : O(n²) */
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

> **Règles** :
> 1. Propriété ABR préservée.
> 2. Un lien rouge penche **toujours à gauche** (jamais à droite).
> 3. Pas deux liens rouges **consécutifs** sur un chemin.
> 4. La racine est toujours **noire**.
> 5. Même nombre de liens noirs sur tout chemin racine→feuille.
>
> Hauteur ≤ 2·log₂(n). Toutes les opérations en O(log n).
> Tout nouveau nœud est créé **rouge** (couleur du lien entrant).

### `new_llrbt_node`
```c
/* Alloue un nouveau nœud avec label = v, color = RED,
   left = right = NULL.
   Tout nouveau nœud est rouge car il représente
   une insertion dans un nœud existant.
   Complexité : O(1) */
llrbt_link new_llrbt_node(item v) {
    llrbt_link h = malloc(sizeof(struct llrbt_node));
    if (!h) { fprintf(stderr, "Erreur malloc\n"); exit(1); }
    h->label = v;
    h->color = RED;
    h->left  = NULL;
    h->right = NULL;
    return h;
}
```

### `delete_llrbt`
```c
/* Libère récursivement tous les nœuds (parcours postordre).
   Met *h à NULL après libération.
   Complexité : O(n) */
void delete_llrbt(llrbt_link *h) {
    if (!h || *h == NULL) return;
    delete_llrbt(&((*h)->left));
    delete_llrbt(&((*h)->right));
    free(*h);
    *h = NULL;
}
```

### `isRed`
```c
/* Retourne 1 si le lien entrant dans h est rouge, 0 sinon.
   Par convention, NULL est considéré BLACK.
   Complexité : O(1) */
int isRed(llrbt_link h) {
    if (h == NULL) return 0;
    return h->color == RED;
}
```

### `rotateLeft`
```c
/* Quand le fils DROIT est rouge (violation "left-leaning").
   Fait monter le fils droit x à la place de h :
   - x hérite la couleur de h
   - h devient rouge (il descend comme fils gauche de x)
   - le sous-arbre gauche de x devient fils droit de h
   Complexité : O(1) */
llrbt_link rotateLeft(llrbt_link h) {
    llrbt_link x = h->right;
    h->right = x->left;
    x->left  = h;
    x->color = h->color;
    h->color = RED;
    return x;
}
```

### `rotateRight`
```c
/* Quand le fils GAUCHE et son fils gauche sont tous deux rouges
   (deux liens rouges consécutifs à gauche).
   Symétrique de rotateLeft.
   Complexité : O(1) */
llrbt_link rotateRight(llrbt_link h) {
    llrbt_link x = h->left;
    h->left  = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    return x;
}
```

### `flipColors`
```c
/* Quand les DEUX fils sont rouges ("nœud 4").
   Inverse les couleurs de h et de ses deux fils :
   - les fils rouges deviennent noirs
   - h (noir) devient rouge → remonte vers son parent
   Complexité : O(1) */
void flipColors(llrbt_link h) {
    h->color        = !(h->color);
    h->left->color  = !(h->left->color);
    h->right->color = !(h->right->color);
}
```

### `insert_LLRBT`
```c
/* Insère v dans le LLRBT.
   Étape 1 — descente BST (doublons à droite).
   Étape 2 — corrections en remontant, TOUJOURS dans cet ordre :
     1. rotateLeft  si droit rouge et gauche noir
     2. rotateRight si gauche rouge ET gauche.gauche rouge
     3. flipColors  si les deux fils rouges
   Forcer la racine à BLACK après l'appel top-level.
   Complexité : O(log n) */
llrbt_link insert_LLRBT(llrbt_link h, item v) {
    if (h == NULL) return new_llrbt_node(v);

    if      (less(v, h->label)) h->left  = insert_LLRBT(h->left,  v);
    else                        h->right = insert_LLRBT(h->right, v);

    if ( isRed(h->right) && !isRed(h->left))          h = rotateLeft(h);
    if ( isRed(h->left)  &&  isRed(h->left->left))    h = rotateRight(h);
    if ( isRed(h->left)  &&  isRed(h->right))         flipColors(h);

    return h;
}
```

### `inorder_LLRBT`
```c
/* Parcours infixe récursif (gauche → racine → droite).
   Remplit t[*idx], t[*idx+1], ... en ordre croissant.
   Grâce à la propriété ABR, le tableau est trié à la fin.
   Complexité : O(n) */
void inorder_LLRBT(llrbt_link h, item *t, int *idx) {
    if (h == NULL) return;
    inorder_LLRBT(h->left,  t, idx);
    t[(*idx)++] = h->label;
    inorder_LLRBT(h->right, t, idx);
}
```

### `show_llrbt`
```c
/* Affiche le LLRBT tourné de -90° (même convention que show_binary_tree).
   'R' = lien rouge entrant, '.' = lien noir.
   Complexité : O(n) */
void show_llrbt(llrbt_link h, int lvl) {
    if (h == NULL) return;
    show_llrbt(h->right, lvl + 1);
    for (int i = 0; i < lvl; i++) printf("    ");
    printf("%c%d\n", h->color == RED ? 'R' : '.', h->label);
    show_llrbt(h->left, lvl + 1);
}
```

---

## Tableau des complexités

| Opération | Complexité |
|---|---|
| Rotation gauche ou droite | O(1) |
| Push / Pop pile | O(1) |
| Enfile / Défile file | O(1) |
| `isRed`, `flipColors` | O(1) |
| Parcours complet (n nœuds) | O(n) |
| `size_binary_tree`, `height_binary_tree` | O(n) |
| `buildHeap` | O(n) |
| `fixHeap` | O(log n) |
| Insert ABR (moy / pire) | O(log n) / O(n) |
| Insert LLRBT (garanti) | O(log n) |
| `select_BST` | O(n²) pire |
| `balance_BST` | O(n²) |
| `heap_sort` | O(n log n) |
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
    buf[len-1] = '\0';   /* '\0' et non '\n' ! */
```

### Pointeur de fonction
```c
/* Déclaration du paramètre */
void traverse_inorder_binary_tree(link bt, void (*visit)(link));

/* Passage */
traverse_inorder_binary_tree(bt, print_label);

/* Appel dans la fonction */
(*visit)(node);
```

### Passage par pointeur
```c
/* Pour modifier une variable depuis une fonction appelée */
void parse_expr(const char *expr, int *pos) {
    (*pos)++;   /* modifie la variable de l'appelant */
}
/* Appel */
parse_expr(expr, &pos);
```

### Makefile minimal
```makefile
CC     = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJS   = main.o lib.o

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
- `-I"chemin"` : ajouter un dossier de recherche des headers
- `-o nom` : nom de l'exécutable
- Les recettes commencent par une **tabulation** (jamais des espaces)
