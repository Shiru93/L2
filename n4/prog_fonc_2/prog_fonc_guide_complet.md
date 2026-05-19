# Guide complet — Programmation Fonctionnelle 1 & 2
> **PF1** : Sergueï Lenglet & Pierre Rousselin — L1 Informatique  
> **PF2** : Pierre Rousselin — L2 Informatique, Université Sorbonne Paris Nord (Paris 13)  
> Année 2025–2026

---

## Table des matières

### Partie I — Programmation Fonctionnelle 1 (OCaml pur)
1. [C'est quoi PF1 ?](#partie-i--programmation-fonctionnelle-1-ocaml-pur)
2. [Syntaxe de base d'OCaml](#2-syntaxe-de-base-docaml)
3. [Fonctions et récursivité](#3-fonctions-et-récursivité)
4. [Pattern matching et types variants](#4-pattern-matching-et-types-variants)
5. [Induction structurelle](#5-induction-structurelle)
6. [Listes en OCaml](#6-listes-en-ocaml)
7. [Fonctions d'ordre supérieur : `map`, `filter`](#7-fonctions-dordre-supérieur--map-filter)
8. [Arbres binaires en OCaml](#8-arbres-binaires-en-ocaml)

### Partie II — Programmation Fonctionnelle 2 (OCaml + Rocq)
9. [C'est quoi PF2 ?](#partie-ii--programmation-fonctionnelle-2-ocaml--rocq)
10. [L'assistant de preuve Rocq](#10-lassistant-de-preuve-rocq)
11. [Semaine 1 — Variants et `match` en Rocq](#11-semaine-1--variants-et-match-en-rocq)
12. [Semaine 2 — La sorte `Prop`](#12-semaine-2--la-sorte-prop)
13. [Semaine 3 — Tuples, curryfication, `False`](#13-semaine-3--tuples-curryfication-false)
14. [Semaine 4 — `forall` et types dépendants](#14-semaine-4--forall-et-types-dépendants)
15. [Semaine 5 — Types récursifs, `nat`, listes, induction](#15-semaine-5--types-récursifs-nat-listes-induction)
16. [Semaine 6 — Réécriture et égalité](#16-semaine-6--réécriture-et-égalité)
17. [Semaine 8 — Arbres binaires et entiers en binaire (`positive`)](#17-semaine-8--arbres-binaires-et-entiers-en-binaire-positive)
18. [Semaine 9 — Propositions inductives](#18-semaine-9--propositions-inductives)
19. [Semaine 10 — `bool` versus `Prop`, réflexion booléenne](#19-semaine-10--bool-versus-prop-réflexion-booléenne)
20. [Semaine 11 — `apply`/`rewrite` avancés, listes triées](#20-semaine-11--applyrewrite-avancés-listes-triées)
21. [Semaine 12 — Fonctions d'ordre supérieur en Rocq](#21-semaine-12--fonctions-dordre-supérieur-en-rocq)
22. [Récapitulatif de toutes les tactiques Rocq](#22-récapitulatif-de-toutes-les-tactiques-rocq)
23. [Ce qui tombe aux examens](#23-ce-qui-tombe-aux-examens)

---

# PARTIE I — Programmation Fonctionnelle 1 (OCaml pur)

## 1. C'est quoi PF1 ?

PF1 est le premier cours de programmation fonctionnelle. Son objectif est d'apprendre à programmer en **OCaml**, un langage fonctionnel typé statiquement.

**Différence fondamentale avec la programmation impérative (C, Python…)**

| Impératif | Fonctionnel |
|-----------|-------------|
| On modifie des variables (`x = x + 1`) | Les valeurs sont **immuables** |
| On utilise des boucles (`for`, `while`) | On utilise la **récursion** |
| Les fonctions peuvent avoir des effets de bord | Les fonctions sont (quasi) des fonctions mathématiques |

```c
// Version impérative (C)
int array[4] = {10, 20, 30, 40};
for (int i = 0; i < 4; i++)
    array[i] = array[i] + 1;
```

```ocaml
(* Version fonctionnelle (OCaml) *)
let liste = [10; 20; 30; 40]
let liste_plus_1 = List.map (fun x -> x + 1) liste
(* liste n'est pas modifiée, liste_plus_1 est une nouvelle liste *)
```

---

## 2. Syntaxe de base d'OCaml

### 2.1 Types de base

| Type | Exemples | Opérations |
|------|----------|------------|
| `int` | `2`, `42`, `-3` | `+`, `-`, `*`, `/`, `mod` |
| `float` | `1.2`, `3.14` | `+.`, `-.`, `*.`, `/.` |
| `string` | `"coucou"`, `"salut"` | `^` (concaténation) |
| `char` | `'c'`, `'a'` | — |
| `bool` | `true`, `false` | `&&`, `\|\|`, `not` |
| `unit` | `()` | — (valeur "rien") |

> **Attention** : OCaml est **fortement typé**. `1 + 1.5` est une erreur ! Il faut `(float_of_int 1) +. 1.5` ou `1. +. 1.5`.

### 2.2 Opérateurs de comparaison

```ocaml
12 > 3       (* bool *)
12 = 3       (* test d'égalité : un seul '=' en OCaml, pas '==' *)
"ab" != "cd" (* différent *)
(12 > 3) || ("coucou" = "salut")
(12 > 3) && (not false)
```

### 2.3 La conditionnelle `if/then/else`

En OCaml, `if/then/else` est une **expression** (retourne une valeur), pas une instruction.

```ocaml
if 12 > 3 then "coucou" else "salut"  (* : string *)
(if 12 > 3 then "coucou" else "salut") ^ " wesh"

(* Les deux branches doivent avoir le même type *)
if 12 > 3 then "coucou" else 42  (* ERREUR de type *)

(* if sans else : uniquement si le then retourne unit *)
if x > 0 then print_int x  (* OK car print_int retourne unit *)
```

### 2.4 Nommer des valeurs : `let`

```ocaml
(* let global : définition permanente *)
let x = 2;;
let y = x + 2;;

(* let local : expression, retourne une valeur *)
let x = 2 in x * x    (* retourne 4, x n'existe que dans l'expression *)

(* Différence cruciale *)
let x = 2;;          (* instruction, x est disponible partout après *)
let x = 2 in x;;     (* expression, retourne 2 *)
(let x = 2) + 3;;    (* ERREUR : let sans in n'est pas une expression *)
(let x = 2 in x) + 3 (* OK : retourne 5 *)
```

> **Important** : En OCaml, `let x = nouvelle_valeur` ne modifie pas `x` — cela crée un **nouveau lien**. L'ancienne valeur de `x` reste accessible dans les fonctions définies avant.

```ocaml
let toto = 12;;
let add_toto x = x + toto;;
add_toto 0;;       (* retourne 12 *)
let toto = 28;;    (* nouveau lien, l'ancien toto=12 est "masqué" *)
add_toto 0;;       (* retourne toujours 12 ! add_toto capture l'ancien toto *)
```

### 2.5 Fonctions

```ocaml
(* Définition avec annotations de type *)
let incr (x : int) : int = x + 1

(* Définition sans annotations (OCaml infère les types) *)
let incr x = x + 1
(* val incr : int -> int = <fun> *)

(* Fonction à plusieurs arguments *)
let monplus x y = x + y
(* val monplus : int -> int -> int = <fun> *)

(* Fonction anonyme (lambda) *)
fun x -> x + 1
```

**Priorité de l'application** : l'application de fonction est plus prioritaire que les opérateurs.
```ocaml
incr 2 * 2    (* = (incr 2) * 2 = 6, pas incr (2*2) *)
incr (2 * 2)  (* = incr 4 = 5 *)
```

### 2.6 Affichage

```ocaml
print_int 42;;           (* affiche 42, retourne unit *)
print_string "coucou";;  (* affiche coucou *)
print_endline "coucou";; (* affiche coucou avec retour à la ligne *)
```

Le `;` (point-virgule simple) sert à **séquencer** deux expressions de type `unit` :
```ocaml
print_int 42; print_newline ()  (* affiche 42 puis saute une ligne *)
```

---

## 3. Fonctions et récursivité

### 3.1 Fonctions récursives : `let rec`

Pour qu'une fonction puisse s'appeler elle-même, il faut le mot-clé `rec` :

```ocaml
let rec somme n =
  if n = 0 then 0
  else n + somme (n - 1)
(* val somme : int -> int = <fun> *)
```

**Comment penser récursivement** : se demander comment résoudre le problème pour `n` en supposant qu'on sait le résoudre pour `n-1` (ou une valeur plus petite).

```
somme 3
= 3 + somme 2
= 3 + (2 + somme 1)
= 3 + (2 + (1 + somme 0))
= 3 + (2 + (1 + 0))
= 6
```

### 3.2 Fonctions mutuellement récursives : `and`

```ocaml
let rec pair n =
  if n = 0 then true
  else impair (n - 1)
and impair n =
  if n = 0 then false
  else pair (n - 1)
```

### 3.3 Imiter les boucles avec la récursion

**Boucle `for`** → fonction récursive avec un accumulateur :
```ocaml
(* Afficher la table de multiplication de nb *)
let tableMult nb =
  let rec aux i =
    if i <= 9 then (
      print_int (i * nb);
      print_newline ();
      aux (i + 1)
    )
  in aux 1
```

**Boucles imbriquées** → fonctions récursives imbriquées :
```ocaml
(* Affiche un triangle de * *)
let triangle n =
  let rec ligne j k =
    if j <= k then (print_string "*"; ligne (j+1) k)
  in
  let rec aux i =
    if i <= n then (ligne 1 i; print_newline (); aux (i+1))
  in aux 1
```

### 3.4 Exemples classiques

```ocaml
(* Puissance *)
let rec puissance x n =
  if n = 0 then 1
  else x * puissance x (n - 1)

(* Suite de Fibonacci *)
let rec fibonacci n =
  if n = 0 then 0
  else if n = 1 then 1
  else fibonacci (n-1) + fibonacci (n-2)

(* Factorielle *)
let rec factorielle n =
  if n = 0 then 1
  else n * factorielle (n - 1)
```

---

## 4. Pattern matching et types variants

### 4.1 Tuples (n-uplets)

Un **tuple** groupe plusieurs valeurs de types potentiellement différents :

```ocaml
type point = int * int

let p1 = (12, 28)        (* : int * int *)
let t  = ("coucou", 23, 'c', 12, 3.2)  (* : string * int * char * int * float *)

(* Décomposition avec let *)
let (x, y) = p1 in x + y   (* x=12, y=28 *)

(* Décomposition dans l'argument de la fonction *)
let estOrigine (x, y) = (x = 0) && (y = 0)
```

### 4.2 Types énumérés

```ocaml
type jour = Lun | Mar | Mer | Jeu | Ven | Sam | Dim
```

Les **constructeurs** commencent par une majuscule. Ici, ce sont des constantes sans argument.

```ocaml
let string_of_jour j =
  match j with
  | Lun -> "lundi"
  | Mar -> "mardi"
  | Mer -> "mercredi"
  | Jeu -> "jeudi"
  | Ven -> "vendredi"
  | Sam -> "samedi"
  | Dim -> "dimanche"
```

### 4.3 Pattern matching — règles importantes

- Les motifs sont **testés dans l'ordre** : le premier qui correspond est choisi.
- Le filtrage doit être **exhaustif** (couvrir tous les cas), sinon OCaml donne un avertissement.
- Toutes les branches doivent retourner le **même type**.
- Le **joker** `_` correspond à n'importe quelle valeur sans la lier.
- On peut **combiner des cas** avec `|` : `Lun | Mar | Mer | Jeu | Ven -> false`
- On peut ajouter une **garde** avec `when` : `| Rectangle (_, l, larg) when l = larg -> true`

```ocaml
(* Joker pour les cas restants *)
let enWeekend j =
  match j with
  | Sam | Dim -> true
  | _         -> false
```

### 4.4 Types variants avec données

Les constructeurs peuvent **transporter des données** :

```ocaml
type figure =
  | Ellipse   of point * int * int   (* centre, grand rayon, petit rayon *)
  | Rectangle of point * int * int   (* coin bas-gauche, longueur, largeur *)

let e1    = Ellipse ((12, 3), 10, 5)
let carre = Rectangle ((0, 0), 3, 3)

let dilate f c =
  match f with
  | Ellipse   (p, gr, pr)    -> Ellipse   (p, gr*c, pr*c)
  | Rectangle (p, long, larg) -> Rectangle (p, long*c, larg*c)

(* Immuabilité : dilate ne modifie pas f, elle crée une nouvelle figure *)

let estCarre f =
  match f with
  | Rectangle (_, long, larg) when long = larg -> true
  | _                                           -> false
```

### 4.5 Motifs imbriqués

On peut faire du pattern matching sur des structures imbriquées :

```ocaml
(* Extraire les coordonnées directement *)
let estSurXEgalY f =
  match f with
  | Rectangle ((x, y), _, _) -> x = y
  | Ellipse   ((x, y), _, _) -> x = y

(* Tester si la figure est à l'origine *)
let aLOrigine f =
  match f with
  | Rectangle ((0, 0), _, _) -> true
  | Rectangle _               -> false
  | Ellipse   ((0, 0), _, _) -> true
  | Ellipse   _               -> false
```

### 4.6 Type enregistrement (record)

Un **enregistrement** donne des noms aux champs (contrairement aux tuples) :

```ocaml
type personne = {
  nom : string;
  age : int;
}

let toto = { nom = "Toto"; age = 12 }
let n    = toto.nom   (* accès par nom de champ *)
let a    = toto.age
```

---

## 5. Induction structurelle

### 5.1 De la récurrence à l'induction

La **récurrence sur les entiers** est un cas particulier de l'**induction structurelle** sur une structure de données inductive.

Une structure de données inductive est définie par des **règles de construction** :
- Un **cas de base** (pas de récursion)
- Des **cas récursifs** (utilisant la structure elle-même)

**Exemples de structures inductives** :
```
Entiers de Peano :   0 ∈ ℕ       si n ∈ ℕ, alors n+1 ∈ ℕ
Listes d'entiers :   [] ∈ List   si l ∈ List, alors n :: l ∈ List (pour tout entier n)
Arbres binaires :    Vide ∈ ABin  si t1,t2 ∈ ABin, x∈X : alors Noeud(x,t1,t2) ∈ ABin
```

### 5.2 Preuves par induction sur les entiers (récurrence forte)

Pour prouver `P(n)` pour tout `n ∈ ℕ` :
1. **Cas de base** : prouver `P(0)` (et souvent `P(1)`)
2. **Cas héréditaire** : supposer `P(k)` vraie pour tout `k ≤ n` (hypothèse d'induction), prouver `P(n+1)`

**Exemple** : Prouver que si `pair(n) = vrai` (où `pair(0)=vrai, pair(1)=faux, pair(n)=pair(n-2)`), alors `∃k, n=2k`.

### 5.3 Preuves par induction sur les structures

**Exemple** : Prouver que pour tout `(x,y) ∈ E` (avec les règles ZZ, UN, DEUX), `x + y = 0`.

```
Cas de base (règle ZZ) : (x,y) = (0,0), et bien 0+0 = 0. ✓
Cas UN  : on suppose E x y avec x+y=0 (HI), on veut (x-1)+(y+1)=0. Calcul : x-1+y+1 = x+y = 0. ✓
Cas DEUX : on suppose E x y avec x+y=0 (HI), on veut (x+2)+(y-2)=0. Calcul : x+2+y-2 = x+y = 0. ✓
```

### 5.4 Piles (structure inductive en OCaml)

```ocaml
type 'a pile =
  | PVide
  | Empiler of 'a * 'a pile

(* Pile 3 8 12 4 (3 est au sommet) *)
let ma_pile = Empiler(3, Empiler(8, Empiler(12, Empiler(4, PVide))))

let rec hauteur p =
  match p with
  | PVide        -> 0
  | Empiler(_, p') -> 1 + hauteur p'

let rec appartient e p =
  match p with
  | PVide          -> false
  | Empiler(t, p') -> (t = e) || appartient e p'

(* dump p1 p2 empile p1 à l'envers sur p2 *)
let rec dump p1 p2 =
  match p1 with
  | PVide           -> p2
  | Empiler(t, p1') -> dump p1' (Empiler(t, p2))
```

---

## 6. Listes en OCaml

### 6.1 Définition et notation

```ocaml
(* Vision récursive : liste vide OU tête :: queue *)
[]                          (* liste vide *)
"coucou" :: "salut" :: []   (* = ["coucou"; "salut"] *)
1 :: 2 :: 3 :: []           (* = [1; 2; 3] *)

(* :: est associatif à droite *)
1 :: (2 :: (3 :: []))   (* même chose que 1 :: 2 :: 3 :: [] *)
```

### 6.2 Pattern matching sur les listes

```ocaml
let estVide l =
  match l with
  | []   -> true
  | _::_ -> false

let tete l =
  match l with
  | []    -> failwith "liste vide"  (* lève une exception *)
  | t::_  -> t

let rec longueur l =
  match l with
  | []    -> 0
  | _::q  -> 1 + longueur q
```

### 6.3 Motifs complexes sur les listes

```ocaml
(* Motifs sur les premiers éléments *)
let bla l =
  match l with
  | 1::2::q -> "commence par 1, 2"
  | [1]     -> "liste [1]"
  | 1::[]   -> "idem [1]"   (* jamais atteint car cas précédent *)
  | _       -> "autre"

(* Supprime les éléments d'indice impair *)
let rec supprimeImpairs l =
  match l with
  | []         -> []
  | t1::_::q   -> t1 :: supprimeImpairs q
  | [t1]       -> [t1]   (* ou t1::[] *)
```

### 6.4 Fonctions récursives fondamentales sur les listes

```ocaml
(* Concaténation *)
let rec append l1 l2 =
  match l1 with
  | []    -> l2
  | t::q  -> t :: append q l2

(* Supprime le n-ième élément *)
let rec supprime l n =
  match l with
  | []    -> []
  | _::q  when n = 0 -> q
  | t::q  -> t :: supprime q (n-1)

(* Nombre d'occurrences *)
let rec nbOccurrences e l =
  match l with
  | []    -> 0
  | t::q  -> (if t = e then 1 else 0) + nbOccurrences e q

(* Préfixe de longueur n *)
let rec prefixe n l =
  match l with
  | []   -> []
  | t::q -> if n = 0 then [] else t :: prefixe (n-1) q

(* Interclassement de deux listes triées *)
let rec interclasser l1 l2 =
  match (l1, l2) with
  | ([], _)           -> l2
  | (_, [])           -> l1
  | (t1::q1, t2::q2)  ->
    if t1 <= t2 then t1 :: interclasser q1 l2
    else             t2 :: interclasser l1 q2
```

### 6.5 Tri fusion

Le tri fusion est un algorithme récursif classique :
1. Couper la liste en deux moitiés
2. Trier chaque moitié récursivement
3. Interclasser les deux moitiés triées

```ocaml
let rec decoupe n l =
  match l with
  | [] -> ([], [])
  | t::q ->
    if n = 0 then ([], l)
    else
      let (gauche, droite) = decoupe (n-1) q in
      (t :: gauche, droite)

let rec fusion l =
  match l with
  | []  -> []
  | [x] -> [x]
  | _   ->
    let n = longueur l / 2 in
    let (l1, l2) = decoupe n l in
    interclasser (fusion l1) (fusion l2)
```

---

## 7. Fonctions d'ordre supérieur : `map`, `filter`

Une **fonction d'ordre supérieur** est une fonction qui prend une autre fonction en argument ou en retourne une.

### 7.1 `map` : appliquer une fonction à chaque élément

```ocaml
let rec map f l =
  match l with
  | []    -> []
  | t::q  -> (f t) :: map f q
(* val map : ('a -> 'b) -> 'a list -> 'b list *)

(* Exemples *)
map (fun x -> x + 1) [1; 2; 3]            (* [2; 3; 4] *)
map (fun x -> x * 2) [10; 20; 30]         (* [20; 40; 60] *)
map (fun p -> p.age) lPers                 (* liste des âges *)
map (fun c -> Char.uppercase_ascii c) ['a'; 'b']  (* ['A'; 'B'] *)
```

### 7.2 `filter` : garder les éléments satisfaisant un prédicat

```ocaml
let rec filter p l =
  match l with
  | []    -> []
  | t::q  -> if p t then t :: filter p q else filter p q
(* val filter : ('a -> bool) -> 'a list -> 'a list *)

(* Exemples *)
filter (fun x -> x > 0) [12; -1; 23; 0; -2]     (* [12; 23] *)
filter (fun x -> x >= 18) [12; 28; 24]            (* [28; 24] *)
filter (fun c -> c = 'a') ['a'; 'c'; 'a'; 'b']   (* ['a'; 'a'] *)
```

### 7.3 Enchaîner `map` et `filter`

```ocaml
(* Noms des personnes majeures *)
map (fun p -> p.nom) (filter (fun p -> p.age >= 18) lPers)

(* filter(p1, filter(p2, l)) = filter(fun x -> p1 x && p2 x, l) *)
```

### 7.4 Fonctions anonymes (`fun`)

```ocaml
(* Les deux définitions sont équivalentes *)
let selectAge p = p.age
let selectAge = fun p -> p.age
```

### 7.5 `forall` et `exists`

```ocaml
(* Tous les éléments vérifient p *)
let forall p l = (filter p l = l)  (* ou mieux avec fold *)
(* Au moins un élément vérifie p *)
let exists p l = filter p l <> []
```

### 7.6 Dictionnaire (liste associative)

```ocaml
type ('a, 'b) dict = ('a * 'b) list
(* Associe des clés de type 'a à des valeurs de type 'b *)

let domaine d = map fst d        (* liste des clés *)
let rec valeurDe c d =
  match d with
  | []         -> failwith "clé absente"
  | (k,v)::q  -> if k = c then v else valeurDe c q
let supprimer c d = filter (fun (k,_) -> k <> c) d
```

---

## 8. Arbres binaires en OCaml

### 8.1 Définition du type

```ocaml
type 'a abin =
  | ETree                           (* arbre vide *)
  | Node of 'a * 'a abin * 'a abin  (* valeur, fils gauche, fils droit *)
```

Le type est **polymorphe** (`'a`) : on peut avoir des arbres d'entiers, de chaînes, etc.

```ocaml
(* Exemples *)
let tc   = Node('C', ETree, ETree)
let tabc = Node('A',
             Node('B', ETree, ETree),
             Node('C', ETree, ETree))
let tbla = Node('B',
             Node('L',
               Node('A', ETree, ETree),
               ETree),
             ETree)
```

### 8.2 Fonctions récursives sur les arbres

```ocaml
(* Nombre de feuilles *)
let rec nbf t =
  match t with
  | ETree                -> 0
  | Node(_, ETree, ETree) -> 1
  | Node(_, t1, t2)       -> nbf t1 + nbf t2

(* Hauteur *)
let rec haut t =
  match t with
  | ETree          -> 0
  | Node(_, t1, t2) -> 1 + max (haut t1) (haut t2)

(* Nombre de nœuds *)
let rec nbNoeuds t =
  match t with
  | ETree          -> 0
  | Node(_, t1, t2) -> 1 + nbNoeuds t1 + nbNoeuds t2

(* map sur les arbres *)
let rec map_arbre f t =
  match t with
  | ETree          -> ETree
  | Node(x, t1, t2) -> Node(f x, map_arbre f t1, map_arbre f t2)
(* val map_arbre : ('a -> 'b) -> 'a abin -> 'b abin *)
```

### 8.3 Parcours d'arbres

```ocaml
(* Préfixe : racine, gauche, droite *)
let rec prefixe t =
  match t with
  | ETree          -> []
  | Node(x, t1, t2) -> [x] @ prefixe t1 @ prefixe t2

(* Infixe : gauche, racine, droite (donne un tri pour les ABR) *)
let rec infixe t =
  match t with
  | ETree          -> []
  | Node(x, t1, t2) -> infixe t1 @ [x] @ infixe t2

(* Suffixe : gauche, droite, racine *)
let rec suffixe t =
  match t with
  | ETree          -> []
  | Node(x, t1, t2) -> suffixe t1 @ suffixe t2 @ [x]
```

### 8.4 Arbres non enracinés (forêts)

```ocaml
(* Un arbre avec un nombre quelconque de fils *)
type 'a anr =
  | EAnr
  | Noeudnr of 'a * ('a anr) list   (* valeur + liste de sous-arbres *)
```

### 8.5 Arbres d'expressions arithmétiques

```ocaml
type op = Plus | Mult | Minus | Div

type eArith =
  | Num of int
  | Eop of op * eArith * eArith

(* Exemple : (3 + 4) * 2 *)
let exemple = Eop(Mult, Eop(Plus, Num 3, Num 4), Num 2)

let rec eval e =
  match e with
  | Num n          -> n
  | Eop(Plus,  a, b) -> eval a + eval b
  | Eop(Mult,  a, b) -> eval a * eval b
  | Eop(Minus, a, b) -> eval a - eval b
  | Eop(Div,   a, b) -> eval a / eval b
```

### 8.6 Arbres binaires de recherche (ABR)

Un **ABR** est un arbre binaire trié : pour chaque nœud, toutes les valeurs du sous-arbre gauche sont inférieures, et toutes celles du sous-arbre droit sont supérieures.

```ocaml
type abrint = Eabr | Noeudabr of int * abrint * abrint

let rec appartient_abr x t =
  match t with
  | Eabr                 -> false
  | Noeudabr(v, t1, t2) ->
    if x = v then true
    else if x < v then appartient_abr x t1
    else appartient_abr x t2

let rec inserer_abr x t =
  match t with
  | Eabr                 -> Noeudabr(x, Eabr, Eabr)
  | Noeudabr(v, t1, t2) ->
    if x <= v then Noeudabr(v, inserer_abr x t1, t2)
    else            Noeudabr(v, t1, inserer_abr x t2)
```

---

# PARTIE II — Programmation Fonctionnelle 2 (OCaml + Rocq)

## 9. C'est quoi PF2 ?

PF2 approfondit la programmation fonctionnelle OCaml et introduit l'**assistant de preuve Rocq**. Son mot-clé central est la **correspondance de Curry-Howard** :

> **Une preuve d'un énoncé logique = un programme d'un type correspondant**

Cela signifie que prouver `A ∧ B` (et logique), c'est exactement construire une paire `(preuve de A, preuve de B)`. Prouver `A → B`, c'est écrire une fonction qui transforme une preuve de `A` en preuve de `B`.

---

## 10. L'assistant de preuve Rocq

Rocq est à la fois un langage de programmation fonctionnel et un assistant de preuve.

### 10.1 Vocabulaire de base

| Terme | Signification |
|-------|---------------|
| **Vernaculaire** | Commandes globales (commencent par une majuscule, finissent par `.`) : `Inductive`, `Definition`, `Lemma`, `Check`, `Compute`... |
| **Gallina** | Le langage des expressions : `fun`, `match`, `let`... |
| **Sorte** | Le type d'un type. `Set` contient les types de données. `Prop` contient les propositions. `Type` contient tout. |
| **Tactique** | Commande interactive pour construire une preuve : `exact`, `simpl`, `destruct`... |

### 10.2 Les sortes de Rocq

```coq
Check true.   (* true : bool    — un terme *)
Check bool.   (* bool : Set     — un type de donnée *)
Check Set.    (* Set  : Type    — une sorte *)
Check Prop.   (* Prop : Type    — la sorte des propositions logiques *)
```

---

## 11. Semaine 1 — Variants et `match` en Rocq

### 11.1 `Inductive` : définir des types variants

```coq
(* Les booléens *)
Inductive bool := true | false.

(* Type à plusieurs constructeurs avec arguments *)
Inductive number :=
  | Real (r : R)
  | Int  (i : Z)
  | Error.

Inductive point := Point (x y : R).
```

En Rocq : `Definition` pour les fonctions non récursives, `Fixpoint` pour les récursives.

```coq
Definition negb (b : bool) : bool :=
  match b with
  | true  => false    (* => au lieu de -> dans les branches *)
  | false => true
  end.                (* end obligatoire pour fermer le match *)
```

### 11.2 Preuves par cas : tactique `destruct`

```coq
Lemma negb_negb (b : bool) : negb (negb b) = b.
Proof.
  destruct b.
  - simpl. reflexivity.   (* cas b = true *)
  - simpl. reflexivity.   (* cas b = false *)
Qed.
```

### 11.3 Tactiques de base

| Tactique | Ce qu'elle fait |
|----------|----------------|
| `exact t` | Donne directement le terme de preuve `t`. Termine la preuve. |
| `reflexivity` | Prouve `X = X`. |
| `simpl` | Réduit (calcule) dans le but. |
| `destruct b` | Preuve par cas (un sous-but par constructeur). |
| `rewrite H` | Réécrit le but en utilisant l'égalité `H`. |

---

## 12. Semaine 2 — La sorte `Prop`

### 12.1 Propositions comme types

`Prop` est la sorte des propositions logiques. Prouver une proposition `P`, c'est construire un **habitant** (un terme) de type `P`.

```coq
Print True.
(* Inductive True : Prop := I. *)
(* True a un seul constructeur I : pour prouver True, on donne I *)

Lemma True_est_vrai : True.
Proof. exact I. Qed.
```

### 12.2 La conjonction `A /\ B`

```coq
(* Définition : une paire de preuves *)
Inductive and (A B : Prop) : Prop := conj (hA : A) (hB : B).
Notation "A /\ B" := (and A B).
```

| Action | Terme de preuve | Tactique |
|--------|----------------|----------|
| Prouver `A /\ B` | `conj hA hB` | `split` |
| Utiliser `h : A /\ B` | `match h with conj hA hB => ...` | `destruct h as [hA hB]` |

```coq
Lemma and_comm (A B : Prop) (h : A /\ B) : B /\ A.
Proof.
  destruct h as [hA hB].
  split.
  - exact hB.
  - exact hA.
Qed.
```

### 12.3 La disjonction `A \/ B`

```coq
Inductive or (A B : Prop) : Prop :=
  or_introl (hA : A) | or_intror (hB : B).
Notation "A \/ B" := (or A B).
```

| Action | Terme de preuve | Tactique |
|--------|----------------|----------|
| Prouver `A \/ B` par le gauche | `or_introl hA` | `left` |
| Prouver `A \/ B` par le droit | `or_intror hB` | `right` |
| Utiliser `h : A \/ B` | `match h with \| or_introl hA => ... \| or_intror hB => ...` | `destruct h as [hA \| hB]` |

### 12.4 L'implication `A -> B`

En Rocq, `A -> B` **est** le type des fonctions de `A` vers `B`. Prouver `A -> B` = écrire une fonction.

| Action | Terme | Tactique |
|--------|-------|----------|
| Prouver `A -> B` | `fun hA => ...` | `intros hA` |
| Utiliser `h : A -> B` avec `hA : A` | `h hA` | `apply h` |

```coq
Lemma modus_ponens (A B : Prop) (h : A -> B) (hA : A) : B.
Proof.
  apply h.   (* le but A -> B devient A *)
  exact hA.
Qed.
```

### 12.5 Lien avec la déduction naturelle

Chaque tactique correspond à une règle de déduction naturelle :

```
Règle          Tactique (intro / élim)
-------        -------------------------
∧I  (prouver ∧)  →  split
∧E  (utiliser ∧) →  destruct h as [hA hB]
∨I-g (prouver ∨) →  left
∨I-d (prouver ∨) →  right
∨E  (utiliser ∨) →  destruct h as [hA | hB]
→I  (prouver →)  →  intros hA
→E  (utiliser →) →  apply h
```

---

## 13. Semaine 3 — Tuples, curryfication, `False`

### 13.1 Curryfication

En OCaml et Rocq, les fonctions "à deux arguments" sont en réalité des **fonctions qui retournent des fonctions** :

```ocaml
(* Curryfiée (préférable) *)
let add x y = x + y
(* val add : int -> int -> int  (i.e. int -> (int -> int)) *)

add 3      (* : int -> int — application partielle valide ! *)
add 3 4    (* : int = 7 *)
```

```ocaml
(* Avec un tuple (non curryfiée) *)
let add_tuple (x, y) = x + y
(* val add_tuple : int * int -> int — doit recevoir la paire entière *)
```

```ocaml
let curry   f x y = f (x, y)   (* type : ('a * 'b -> 'c) -> 'a -> 'b -> 'c *)
let uncurry f (x, y) = f x y   (* type : ('a -> 'b -> 'c) -> 'a * 'b -> 'c *)
```

**Règle** : `A -> B -> C` se lit `A -> (B -> C)` — association à droite.

### 13.2 `False` et la négation

```coq
Print False.
(* Inductive False : Prop := . — aucun constructeur, impossible à prouver *)

(* De False on peut déduire n'importe quoi (explosion) *)
Lemma exfalso (A : Prop) : False -> A.
Proof. intros h. destruct h. Qed.   (* aucun cas à traiter ! *)

(* La négation : ~A = A -> False *)
Definition not (A : Prop) := A -> False.
Notation "~ A" := (not A).
```

| Tactique | Usage |
|----------|-------|
| `exfalso` | Change le but en `False` |
| `unfold not` | Déplie `~A` en `A -> False` |
| `destruct h` sur `h : False` | Termine la preuve (aucun cas) |

### 13.3 Fonctions génériques standard en OCaml

```ocaml
let ignore  x     = ()                (* 'a -> unit *)
let const   c x   = c                 (* 'a -> 'b -> 'a *)
let compose f g x = f (g x)           (* ('b -> 'c) -> ('a -> 'b) -> 'a -> 'c *)
let flip    f x y = f y x             (* ('a -> 'b -> 'c) -> 'b -> 'a -> 'c *)
let ( |> )  x f   = f x               (* 'a -> ('a -> 'b) -> 'b *)
let ( @@ )  f x   = f x               (* ('a -> 'b) -> 'a -> 'b *)
```

---

## 14. Semaine 4 — `forall` et types dépendants

### 14.1 La quantification universelle

En Rocq, la quantification universelle est **explicite** via `forall` :

```coq
Definition id (A : Type) : A -> A := fun x => x.
Check id.  (* forall A : Type, A -> A *)

(* A -> B  est du sucre pour  forall _ : A, B  quand B ne dépend pas de l'argument *)
```

```coq
Lemma foo : forall (A : Prop), A -> A.
Proof.
  intros A.   (* Soit A une proposition *)
  intros hA.  (* Supposons hA : A *)
  exact hA.
Qed.
```

### 14.2 Types dépendants

Un type dépendant est un type dont la valeur dépend d'un terme :

```coq
Definition false_or_42 (b : bool) :=
  match b return (if b then bool else nat) with
  | true  => false
  | false => 42
  end.
(* Le type de retour dépend de la valeur de b *)
```

### 14.3 Types produits et sommes dans `Type`

```coq
(* Produit (analogue de /\ dans Prop) *)
Inductive prod (A B : Type) := pair (a : A) (b : B).
(* Somme (analogue de \/ dans Prop) *)
Inductive sum (A B : Type) := inl (a : A) | inr (b : B).
```

### 14.4 Le quantificateur existentiel

```coq
Lemma ex : exists n : nat, n + 1 = 2.
Proof.
  exists 1.        (* on choisit le témoin *)
  simpl. reflexivity.
Qed.

(* Pour utiliser h : exists x, P x *)
destruct h as [x hx].  (* x : le témoin, hx : P x *)
```

| Tactique | Usage |
|----------|-------|
| `exists t` | Prouve `∃x, P x` en choisissant `t` comme témoin |
| `destruct h as [x hx]` | Utilise une preuve de `∃x, P x` |
| `specialize H` | Instancie un `forall` dans `H` |

---

## 15. Semaine 5 — Types récursifs, `nat`, listes, induction

### 15.1 Les entiers naturels de Peano

```coq
Inductive nat : Set :=
  | O : nat         (* zéro *)
  | S : nat -> nat  (* successeur *)
(* 0 = O, 1 = S O, 2 = S(S O), etc. Rocq fournit les notations décimales *)

Fixpoint add (n m : nat) :=
  match n with
  | O   => m
  | S p => S (add p m)  (* add (S p) m = S (add p m) *)
  end.
```

### 15.2 Les listes en Rocq

```coq
Inductive list (A : Type) : Type :=
  | nil  : list A
  | cons : A -> list A -> list A.

(* Notations : [] pour nil, :: pour cons, [1; 2; 3] pour cons 1 (cons 2 (cons 3 nil)) *)

Fixpoint app {A : Type} (l1 l2 : list A) :=
  match l1 with
  | []     => l2
  | h :: q => h :: app q l2
  end.
Notation "l1 ++ l2" := (app l1 l2).
```

### 15.3 La preuve par induction

```coq
Lemma app_nil_r {A : Type} : forall (l : list A), l ++ [] = l.
Proof.
  intros l.
  induction l as [| h q IH].   (* IH : q ++ [] = q *)
  - simpl. reflexivity.          (* cas l = [] *)
  - simpl. rewrite IH. reflexivity.  (* cas l = h :: q *)
Qed.
```

**Syntaxe** : `induction l as [| h q IH]`
- Branche vide `[]` : rien à nommer
- Branche `h :: q` : `h` = tête, `q` = queue, `IH` = hypothèse d'induction

Sur `nat` : `induction n as [| p IH]` (cas `O`, cas `S p` avec `IH : P p`).

### 15.4 L'induction = un programme récursif

```coq
Fixpoint nat_ind (P : nat -> Prop)
    (h0    : P 0)
    (hered : forall k, P k -> P (S k))
    (n     : nat) :=
  match n with
  | 0   => h0
  | S p => hered p (nat_ind P h0 hered p)
  end.
(* Une preuve par induction sur nat EST une fonction récursive *)
```

---

## 16. Semaine 6 — Réécriture et égalité

### 16.1 Règles de réécriture élémentaires

```coq
(* Pour app *)
Lemma app_nil_l  {A} (l : list A)          : [] ++ l = l.
Lemma app_cons_l {A} (h : A) (q l : list A): (h::q) ++ l = h :: (q ++ l).
(* Pour length *)
Lemma length_nil  {A}                       : length (@nil A) = 0.
Lemma length_cons {A} (h : A) (q : list A) : length (h::q) = S (length q).
(* Pour add *)
Lemma add_0_l    (n : nat)   : 0 + n = n.
Lemma add_succ_l (n m : nat) : S n + m = S (n + m).
```

Ces lemmes permettent d'écrire des **preuves papier détaillées** où chaque étape est justifiée par un nom de lemme.

### 16.2 Égalité entre constructeurs

**Injectivité** (`injection`) : si deux termes construits avec le même constructeur sont égaux, leurs arguments le sont aussi.

```coq
Lemma ex (n m : nat) : S (S n) = S m -> S n = m.
Proof.
  intros H. injection H as H'. exact H'.
Qed.
```

**Discrimination** (`discriminate`) : deux constructeurs différents ne peuvent pas être égaux.

```coq
Lemma zero_neq_one : 0 <> 1.
Proof. intros H. discriminate H. Qed.
```

---

## 17. Semaine 8 — Arbres binaires et entiers en binaire (`positive`)

### 17.1 Arbres binaires en Rocq

```coq
Inductive btree (A : Type) :=
  | emptyTree
  | node (left : btree A) (key : A) (right : btree A).
Arguments emptyTree {A}.
Arguments node {A}.

Fixpoint height {A} (t : btree A) : nat :=
  match t with
  | emptyTree    => 0
  | node l _ r  => S (max (height l) (height r))
  end.

Fixpoint mirror {A} (t : btree A) :=
  match t with
  | emptyTree    => emptyTree
  | node l k r  => node (mirror r) k (mirror l)
  end.

Fixpoint prefixDFS {A} (t : btree A) : list A :=
  match t with
  | emptyTree    => []
  | node l k r  => [k] ++ prefixDFS l ++ prefixDFS r
  end.
```

### 17.2 Le type `positive` (entiers > 0 en binaire)

```coq
Inductive positive : Set :=
  | xI : positive -> positive   (* ajoute un bit 1 en poids faible : p -> 2p+1 *)
  | xO : positive -> positive   (* ajoute un bit 0 en poids faible : p -> 2p   *)
  | xH : positive.              (* représente 1 *)

Notation "1"     := xH.
Notation "p ~ 1" := (xI p).
Notation "p ~ 0" := (xO p).
```

**Lecture** : `1~1~0` = `xO (xI xH)` = bits `110` = **6** en décimal.

**Successeur** (exemple de récursion avec retenue) :
```coq
Fixpoint succ (p : positive) :=
  match p with
  | 1    => 1~0          (* 1 → 2 *)
  | q~0  => q~1          (* 2k → 2k+1 *)
  | q~1  => (succ q)~0   (* 2k+1 → 2(k+1), avec propagation de retenue *)
  end.
```

### 17.3 Les autres types d'entiers en Rocq

| Type | Représente | Construction |
|------|------------|--------------|
| `positive` | > 0 | `xH`, `xI`, `xO` |
| `N` | ≥ 0 | `N0`, `Npos p` |
| `Z` | entiers relatifs | `Z0`, `Zpos p`, `Zneg p` |

---

## 18. Semaine 9 — Propositions inductives

### 18.1 Prédicats inductifs

Un **prédicat inductif** définit une relation via des **règles d'inférence**. C'est le moyen de définir des propriétés ou des relations non calculables directement.

**Exemple fondamental du cours** :

```coq
Inductive E : Z -> Z -> Prop :=
  | ZZ   : E 0 0
  | UN   (x y : Z) : E x y -> E (x-1) (y+1)
  | DEUX (x y : Z) : E x y -> E (x+2) (y-2).
```

On peut prouver `E 3 (-3)` en appliquant les règles comme des constructeurs :

```coq
Lemma Eex1 : E 3 (-3).
Proof.
  apply (DEUX 1 (-1)).
  apply (DEUX (-1) 1).
  apply (UN 0 0).
  exact ZZ.
Qed.
```

### 18.2 Induction sur un prédicat

Quand on définit un prédicat avec `Inductive`, Rocq génère un principe d'induction. On peut faire `induction h` sur une preuve `h` d'un prédicat inductif, comme sur `nat` ou `list`.

---

## 19. Semaine 10 — `bool` versus `Prop`, réflexion booléenne

### 19.1 Deux façons d'exprimer « n ≤ m »

```coq
(* Version Prop : inductive, preuvable, raisonnement *)
Inductive le (n : nat) : nat -> Prop :=
  | le_n : le n n
  | le_S : forall m, le n m -> le n (S m).
Notation "n <= m" := (le n m).

(* Version bool : calculable, décidable *)
Fixpoint leb n m :=
  match n, m with
  | 0,    _    => true
  | S _,  0    => false
  | S n', S m' => leb n' m'
  end.
Notation "n <=? m" := (leb n m).
```

### 19.2 Réflexion : faire le pont

```coq
(* Les deux approches sont équivalentes *)
Lemma le_leb  (n m : nat) : n <= m      -> n <=? m = true.
Lemma leb_le  (n m : nat) : n <=? m = true -> n <= m.
```

La **réflexion booléenne** permet d'utiliser le calcul (`Compute`, `Fixpoint`) pour décider des questions logiques, puis de ramener la décision dans `Prop`.

### 19.3 La tactique `lia`

`lia` (**L**inear **I**nteger **A**rithmetic) résout automatiquement les buts arithmétiques linéaires sur `nat` et `Z` :

```coq
Lemma ex (n m : nat) : n + m = m + n.
Proof. lia. Qed.   (* prouvé automatiquement ! *)
```

---

## 20. Semaine 11 — `apply`/`rewrite` avancés, listes triées

### 20.1 `apply` dans les deux sens

```coq
(* Vers l'arrière (défaut) : unifie le but avec la conclusion de h *)
apply h.           (* si h : A -> B et but = B, le but devient A *)

(* Vers l'avant : applique h à une hypothèse *)
apply h in h1.     (* si h : A -> B et h1 : A, remplace h1 par h h1 : B *)
apply h in h1 as h2.  (* version conservative : crée h2 sans détruire h1 *)
```

### 20.2 `rewrite` avancé

```coq
rewrite H.         (* remplace gauche de H par droite dans le but *)
rewrite <- H.      (* sens inverse *)
rewrite H in h2.   (* réécrit dans l'hypothèse h2 *)
replace e1 with e2.         (* remplace e1 par e2, crée un sous-but e1 = e2 *)
replace e1 with e2 by tac.  (* résout le sous-but avec tac *)
```

### 20.3 Le prédicat `sorted`

```coq
Inductive sorted : list nat -> Prop :=
  | sorted_nil  : sorted []
  | sorted_one  : forall n, sorted [n]
  | sorted_cons : forall n m l,
      n <= m -> sorted (m :: l) -> sorted (n :: m :: l).
```

---

## 21. Semaine 12 — Fonctions d'ordre supérieur en Rocq

### 21.1 `map` en Rocq

```coq
Fixpoint map {A B : Type} (f : A -> B) (l : list A) :=
  match l with
  | []     => []
  | h :: t => (f h) :: map f t
  end.
(* Type : (?A -> ?B) -> list ?A -> list ?B *)
```

### 21.2 `filter` en Rocq

```coq
Fixpoint filter {A : Type} (p : A -> bool) (l : list A) :=
  match l with
  | []     => []
  | h :: t => if p h then h :: filter p t else filter p t
  end.
```

### 21.3 `fold_right` et `fold_left`

```ocaml
(* OCaml *)
let rec fold_right f l accu =    (* ('a -> 'b -> 'b) -> 'a list -> 'b -> 'b *)
  match l with
  | []     -> accu
  | a :: l -> f a (fold_right f l accu)

let rec fold_left f accu l =     (* ('b -> 'a -> 'b) -> 'b -> 'a list -> 'b *)
  match l with
  | []     -> accu
  | a :: l -> fold_left f (f accu a) l
```

**Différence** :
```
fold_right (+) [10; 42; 3] 0  =  10 + (42 + (3 + 0))  =  55
fold_left  (+) 0 [10; 42; 3]  =  ((0 + 10) + 42) + 3  =  55
```

`fold_right` associe à **droite**, `fold_left` associe à **gauche** (et est souvent plus efficace grâce à la récursion terminale).

---

## 22. Récapitulatif de toutes les tactiques Rocq

### Tactiques de base

| Tactique | Usage |
|----------|-------|
| `exact t` | Fournit le terme de preuve directement. |
| `reflexivity` | Prouve `X = X`. |
| `simpl` | Réduit le but par calcul. |
| `simpl in h` | Réduit dans l'hypothèse `h`. |
| `destruct b` | Preuve par cas sur `b`. |
| `destruct b as [...]` | Preuve par cas avec nommage. |
| `rewrite H` | Réécrit gauche→droite dans le but. |
| `rewrite <- H` | Réécrit droite→gauche. |
| `rewrite H in h2` | Réécrit dans l'hypothèse `h2`. |

### Tactiques logiques

| Tactique | Connecteur | Direction |
|----------|-----------|-----------|
| `intros h` | `→`, `∀` | Introduction |
| `apply h` | `→` | Élimination (vers l'arrière) |
| `apply h in h1` | `→` | Élimination (vers l'avant) |
| `split` | `∧` | Introduction |
| `destruct h as [hA hB]` | `∧` | Élimination |
| `left` | `∨` | Introduction (gauche) |
| `right` | `∨` | Introduction (droite) |
| `destruct h as [hA \| hB]` | `∨` | Élimination |
| `exfalso` | `⊥` | Change le but en `False` |
| `unfold not` | `¬` | Déplie la négation |
| `exists t` | `∃` | Introduction (choisit le témoin) |
| `destruct h as [x hx]` | `∃` | Élimination |
| `specialize H` | `∀` | Instanciation |
| `assumption` | — | Cherche dans le contexte |

### Tactiques avancées

| Tactique | Usage |
|----------|-------|
| `induction l as [...]` | Preuve par induction structurelle. |
| `discriminate H` | Prouve `False` à partir d'une égalité impossible entre constructeurs distincts. |
| `injection H` | Extrait les égalités d'arguments à partir d'une égalité entre constructeurs identiques. |
| `injection H as H1 H2` | Comme `injection` avec nommage des nouvelles hypothèses. |
| `replace e1 with e2` | Remplace `e1` par `e2` dans le but (crée sous-but). |
| `replace e1 with e2 by tac` | Idem mais résout le sous-but avec `tac`. |
| `lia` | Arithmétique linéaire automatique. |
| `ring` | Égalités dans un anneau commutatif. |

---

## 23. Ce qui tombe aux examens

### En PF1

**Exercices typiques** :
- Donner le type d'une fonction OCaml et évaluer des applications
- Définir des fonctions récursives (sur entiers, listes, arbres)
- Écrire des preuves par récurrence/induction sur papier
- Utiliser `map`/`filter` sur des types concrets
- Implémenter le tri fusion ou des algorithmes sur les listes

### En PF2 — Partiel 1 (3h, sur papier)

**Exercice 1 — Preuves de logique propositionnelle** : pour un lemme donné, fournir les 3 choses suivantes :
1. Un terme de preuve direct (avec `exact (match ...)` ou `exact (fun ...)`)
2. Une preuve avec tactiques
3. Un arbre de dérivation en déduction naturelle

*Exemple tombé* : `Lemma and_assoc (h : A /\ (B /\ C)) : (A /\ B) /\ C.`

**Exercice 2 — Typage OCaml** : donner le type d'une fonction, évaluer des applications partielles.

*Exemple tombé* : `let dup f x = f x x` — type ? valeur de `dup (+) 3` ?

**Exercice 3 — Preuves par induction** : définir des fonctions récursives, prouver par induction avec réécritures explicites et écrire des preuves papier détaillées.

### En PF2 — Interrogation 1

Focus sur les **arbres binaires** :
- Représentation graphique d'un arbre Rocq
- Fonctions récursives sur les arbres
- Calcul pas à pas
- Preuve papier par induction

### Points essentiels à maîtriser (PF1 + PF2)

**PF1 — OCaml**
- ✅ Typage fort : différences `int`/`float`, opérateurs distincts
- ✅ `let` vs `let ... in`, portée des variables
- ✅ Fonctions récursives (`let rec`), penser la récursion
- ✅ Pattern matching exhaustif, motifs imbriqués, gardes `when`
- ✅ Types variants avec données, enregistrements
- ✅ Fonctions d'ordre supérieur : `map`, `filter`, application partielle
- ✅ Listes : `::`, `[]`, fonctions récursives
- ✅ Arbres : définition, parcours (préfixe/infixe/suffixe), ABR
- ✅ Preuves par induction structurelle sur papier

**PF2 — Rocq**
- ✅ Correspondance preuves/programmes (Curry-Howard)
- ✅ Termes de preuve directs : `exact (fun ...)`, `exact (match ...)`
- ✅ Tactiques : `intros`, `destruct`, `split`, `left/right`, `apply`, `simpl`, `reflexivity`, `rewrite`
- ✅ Induction avec `induction ... as [...]` et hypothèse d'induction
- ✅ Preuves papier très détaillées (justifier chaque étape par un lemme)
- ✅ `injection` et `discriminate`
- ✅ Différence `bool`/`Prop`, réflexion booléenne, `lia`

---

> **Fichiers les plus utiles pour réviser** (dans les ZIPs) :
>
> *PF1* : `cm03-pattern.ml`, `cm05-liste.ml`, `cm06-HOliste.ml`, `cm07-arbre.ml` — tout le code des CMs  
> *PF2* : `résumé-mi-parcours-2026.pdf`, `partiels/p1/2025-2026/p1-25-26_corr.pdf`, `interros/interro01_corr.pdf`, fichiers `TP0X_corr.v`
