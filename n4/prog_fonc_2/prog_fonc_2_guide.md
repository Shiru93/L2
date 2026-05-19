# Guide complet — Programmation Fonctionnelle 2
> Cours de Pierre Rousselin — L2 Informatique, Université Sorbonne Paris Nord (Paris 13)  
> Année 2025–2026

---

## Table des matières

1. [C'est quoi ce cours ?](#1-cest-quoi-ce-cours-)
2. [Structure des fichiers du ZIP](#2-structure-des-fichiers-du-zip)
3. [Les outils : OCaml et Rocq](#3-les-outils--ocaml-et-rocq)
4. [Semaine 1 — Variants et `match`](#4-semaine-1--variants-et-match)
5. [Semaine 2 — La sorte `Prop`](#5-semaine-2--la-sorte-prop)
6. [Semaine 3 — Tuples, curryfication, `False`](#6-semaine-3--tuples-curryfication-false)
7. [Semaine 4 — `forall` et types dépendants](#7-semaine-4--forall-et-types-dépendants)
8. [Semaine 5 — Types récursifs, `nat`, listes, induction](#8-semaine-5--types-récursifs-nat-listes-induction)
9. [Semaine 6 — Réécriture et égalité](#9-semaine-6--réécriture-et-égalité)
10. [Semaine 8 — Arbres binaires et entiers en binaire](#10-semaine-8--arbres-binaires-et-entiers-en-binaire)
11. [Semaine 9 — `positive`, propositions inductives](#11-semaine-9--positive-propositions-inductives)
12. [Semaine 10 — `bool` versus `Prop`, réflexion booléenne](#12-semaine-10--bool-versus-prop-réflexion-booléenne)
13. [Semaine 11 — `apply` et `rewrite` avancés, listes triées](#13-semaine-11--apply-et-rewrite-avancés-listes-triées)
14. [Semaine 12 — Fonctions d'ordre supérieur](#14-semaine-12--fonctions-dordre-supérieur)
15. [Récapitulatif de toutes les tactiques Rocq](#15-récapitulatif-de-toutes-les-tactiques-rocq)
16. [Ce qui tombe aux examens](#16-ce-qui-tombe-aux-examens)

---

## 1. C'est quoi ce cours ?

Ce cours s'appelle **Programmation Fonctionnelle 2** (PF2). Il a un double objectif :

- Approfondir la **programmation fonctionnelle** avec le langage **OCaml**.
- Apprendre à **prouver formellement des propriétés de programmes** avec l'assistant de preuve **Rocq** (anciennement appelé Coq).

Le mot-clé central du cours est : **"preuves et programmes, c'est la même chose"**. Une preuve mathématique d'un énoncé, c'est exactement un programme qui produit un terme du type correspondant à cet énoncé. C'est ce qu'on appelle la **correspondance de Curry-Howard**.

---

## 2. Structure des fichiers du ZIP

```
prog_fonc_2/
├── résumé-mi-parcours-2026.pdf    ← Résumé des 6 premières semaines (très utile !)
├── TP01_sujet.v                   ← Copie du TP1 (à la racine, probablement le sujet distribué en cours)
│
├── cm/                            ← Cours Magistraux (slides PDF + fichiers .v de démo)
│   ├── cm1/   cm01.pdf + ExemplesInductives.v
│   ├── cm2/   cm02.pdf + DemoCM2.v
│   ├── cm3/   cm03.pdf
│   ├── cm4/   cm04.pdf
│   ├── cm5/   cm05.pdf + ListesNatRocq.v
│   ├── cm6/   cm06.pdf
│   ├── cm8/   cm08.pdf
│   ├── cm9/   cm09.pdf
│   ├── cm10/  cm10.pdf + CM10.v
│   ├── cm11/  cm11.pdf
│   └── cm12/  cm12.pdf
│
├── td/                            ← Travaux Dirigés (sujet + correction PDF)
│   ├── td1/ à td11/
│
├── tp/                            ← Travaux Pratiques (fichiers Rocq .v, sujet + correction)
│   ├── tp1/ à tp10/
│
├── partiels/
│   └── p1/2025-2026/              ← Partiel 1 (sujet + correction PDF)
│
└── interros/
    └── interro01_corr.pdf         ← Interrogation n°1 avec correction
```

> **Note :** Il n'y a pas de CM7 dans le ZIP (la semaine 7 n'a pas de CM spécifique, les TD/TP font suite au CM6).

---

## 3. Les outils : OCaml et Rocq

### OCaml

OCaml est un langage de programmation fonctionnel. Dans ce cours, on l'utilise principalement pour **comprendre les concepts** (types, fonctions, pattern matching) avant de les formaliser en Rocq.

Caractéristiques importantes :
- Typage statique fort (le compilateur vérifie les types avant l'exécution).
- Les fonctions sont des valeurs comme les autres.
- Pas de boucles (on utilise la récursion à la place).
- Les constructeurs de types commencent par une **majuscule**.

### Rocq (ex-Coq)

Rocq est à la fois :
- Un **langage de programmation fonctionnel** (appelé Gallina).
- Un **assistant de preuve** : il vérifie que vos preuves mathématiques sont correctes.

La grande différence avec OCaml : **les types sont des termes comme les autres**. On peut donc exprimer des énoncés logiques comme des types, et prouver ces énoncés en écrivant des programmes.

#### Vocabulaire Rocq de base

| Terme | Signification |
|-------|---------------|
| **Vernaculaire** | Commandes qui modifient l'environnement global (commencent par une majuscule, finissent par `.`) : `Inductive`, `Definition`, `Lemma`, `Check`, `Compute`... |
| **Gallina** | Le langage des termes (expressions) : `fun`, `match`, `let`... |
| **Sorte** | Le type d'un type. `Set` contient `bool`, `nat`... `Prop` contient les propositions logiques. `Type` contient tout. |
| **Tactique** | Commande pour construire une preuve de façon interactive : `exact`, `simpl`, `destruct`... |

---

## 4. Semaine 1 — Variants et `match`

### 4.1 Les types variants en OCaml

Un **type variant** (ou type somme) est un type qui peut prendre plusieurs formes. Chaque forme est introduite par un **constructeur**.

```ocaml
(* Type à 3 constructeurs *)
type number = Float of float | Int of int | Error

let n1 = Float 2.3    (* constructeur Float appliqué à 2.3 *)
let n2 = Int 0        (* constructeur Int appliqué à 0 *)
let n3 = Error        (* constructeur sans argument *)

(* Type à 1 constructeur *)
type point = Point of float * float
```

### 4.2 Le pattern matching (`match`)

Le `match` permet de **raisonner par cas** sur un type variant. Il fait deux choses en même temps :
1. Il distingue les différents constructeurs possibles.
2. Il **lie les arguments** du constructeur à des variables locales.

```ocaml
let is_float n =
  match n with
  | Float _ -> true   (* le _ signifie "peu importe la valeur" *)
  | _       -> false  (* cas par défaut *)

let symm p =
  match p with
  | Point (x, y) -> Point (-. x, -. y)
```

**Motif irréfutable** : quand le type n'a qu'un seul constructeur, on peut faire le pattern matching directement dans l'argument de la fonction :

```ocaml
let fst (Point (x, y)) = x
let snd p = let Point (x, y) = p in y
```

### 4.3 Les booléens (premier exemple important)

```ocaml
(* OCaml : true et false sont prédéfinis *)
let negb b = match b with true -> false | false -> true
let andb b1 b2 = match b1 with true -> b2 | false -> false
```

### 4.4 Les mêmes concepts en Rocq

En Rocq, on utilise `Inductive` pour définir des types variants :

```coq
(* Définition des booléens (déjà dans le prélude de Rocq) *)
Inductive bool := true | false.

(* Définition d'un type number *)
Inductive number :=
  | Real (r : R)
  | Int  (i : Z)
  | Error.

(* Pattern matching *)
Definition negb (b : bool) : bool :=
  match b with
  | true  => false
  | false => true
  end.
```

La grosse différence syntaxique : `->` en OCaml devient `=>` en Rocq dans les branches du `match`, et il faut un `end` pour fermer le `match`.

### 4.5 Les preuves par cas (`destruct`)

En Rocq, prouver quelque chose sur un type variant, c'est souvent faire une **preuve par cas** avec la tactique `destruct` :

```coq
Lemma negb_negb (b : bool) : negb (negb b) = b.
Proof.
  destruct b.
  - (* cas b = true  *) simpl. reflexivity.
  - (* cas b = false *) simpl. reflexivity.
Qed.
```

#### Tactiques introduites en semaine 1

| Tactique | Ce qu'elle fait |
|----------|----------------|
| `reflexivity` | Termine une preuve si les deux membres sont identiques : `X = X`. |
| `simpl` | Réduit (calcule) autant que possible dans le but. |
| `destruct b` | Fait une preuve par cas sur `b` (crée un sous-but par constructeur). |
| `rewrite règle` | Remplace une expression par une autre dans le but, en utilisant une égalité. |
| `exact terme` | Donne directement le terme de preuve. Termine la preuve si `terme` a le bon type. |

---

## 5. Semaine 2 — La sorte `Prop`

### 5.1 Les sortes de Rocq

```
true   : bool    (un terme)
bool   : Set     (un type → sorte Set)
Set    : Type    (une sorte → sorte Type)
Prop   : Type    (une sorte spéciale pour la logique)
```

**`Prop`** est la sorte des **propositions logiques**. Une proposition est un type dont les habitants sont des **preuves**.

```coq
Check (2 = 2).        (* 2 = 2 : Prop — c'est une proposition *)
Check (true = false). (* true = false : Prop — une proposition fausse *)
```

### 5.2 Prouver `True`

```coq
Print True.
(* Inductive True : Prop := I. *)
(* True est une proposition avec un seul constructeur I (sans argument) *)

Lemma True_est_vrai : True.
Proof. exact I. Qed.
```

### 5.3 La conjonction (« et ») : `A /\ B`

```coq
Inductive and (A B : Prop) : Prop :=
  conj (hA : A) (hB : B).
Notation "A /\ B" := (and A B).
```

**Pour prouver** `A /\ B` : fournir une preuve de `A` ET une preuve de `B`.
- Avec terme : `conj hA hB`
- Avec tactiques : `split` (crée deux sous-buts)

**Pour utiliser** une hypothèse `h : A /\ B` :
- Avec terme : `match h with conj hA hB => ...`
- Avec tactiques : `destruct h as [hA hB]`

```coq
Lemma and_comm (A B : Prop) (h : A /\ B) : B /\ A.
Proof.
  destruct h as [hA hB].  (* on extrait les deux parties *)
  split.
  - exact hB.
  - exact hA.
Qed.
```

### 5.4 La disjonction (« ou ») : `A \/ B`

```coq
Inductive or (A B : Prop) : Prop :=
  or_introl (hA : A) | or_intror (hB : B).
Notation "A \/ B" := (or A B).
```

**Pour prouver** `A \/ B` : choisir un côté.
- `left` : on va prouver `A`
- `right` : on va prouver `B`

**Pour utiliser** une hypothèse `h : A \/ B` :
- `destruct h as [hA | hB]` (crée deux sous-buts : un avec `hA : A`, un avec `hB : B`)

### 5.5 L'implication : `A -> B`

En Rocq, `A -> B` est **le type des fonctions de `A` vers `B`**. Une preuve de `A -> B`, c'est une fonction qui transforme une preuve de `A` en preuve de `B`.

```coq
Lemma modus_ponens (A B : Prop) (h : A -> B) (hA : A) : B.
Proof.
  apply h.  (* le but devient A *)
  exact hA.
Qed.
```

| Tactique | Ce qu'elle fait |
|----------|----------------|
| `intros h` | Introduit une hypothèse `h` (pour prouver `A -> B`, `intros h` met `h : A` dans le contexte et le but devient `B`). |
| `apply h` | Applique `h : A -> B` : si le but est `B`, le nouveau but devient `A`. |
| `split` | Prouve un `A /\ B` : crée deux sous-buts. |
| `left` | Pour prouver `A \/ B` en prouvant `A`. |
| `right` | Pour prouver `A \/ B` en prouvant `B`. |
| `destruct h as [hA hB]` | Utilise une preuve de `A /\ B`. |
| `destruct h as [hA \| hB]` | Utilise une preuve de `A \/ B`. |
| `assumption` | Cherche dans le contexte une hypothèse qui correspond au but. |

### 5.6 Lien avec la déduction naturelle

Chaque tactique correspond à une règle de déduction naturelle :

```
Γ ⊢ A    Γ ⊢ B
──────────────── (∧I)       →  split
    Γ ⊢ A ∧ B

   Γ ⊢ A ∧ B
──────────────── (∧E-g)     →  destruct h as [hA _]
     Γ ⊢ A

   Γ ⊢ A
──────────────── (∨I-g)     →  left
  Γ ⊢ A ∨ B

  Γ, A ⊢ B
──────────────── (→I)       →  intros hA
  Γ ⊢ A → B

Γ ⊢ A → B    Γ ⊢ A
──────────────────── (→E)   →  apply h
       Γ ⊢ B
```

---

## 6. Semaine 3 — Tuples, curryfication, `False`

### 6.1 Tuples vs fonctions curryfiées

En OCaml (et en Rocq), il y a deux façons de faire une fonction "à deux arguments" :

**Version tuple (non curryfiée)** :
```ocaml
let add_tuple (x, y) = x + y
(* type : int * int -> int *)
```

**Version curryfiée** (préférable) :
```ocaml
let add x y = x + y
(* type : int -> int -> int  (i.e. int -> (int -> int)) *)
```

La **curryfication** consiste à transformer une fonction qui prend un tuple en une fonction qui prend ses arguments un par un. `add 3` est alors une fonction valide qui attend encore un entier (application partielle).

```ocaml
let curry   f x y = f (x, y)   (* type : ('a * 'b -> 'c) -> 'a -> 'b -> 'c *)
let uncurry f (x, y) = f x y   (* type : ('a -> 'b -> 'c) -> 'a * 'b -> 'c *)
```

**Règle importante** : Le type `A -> B -> C` doit se lire `A -> (B -> C)`. L'association est **à droite**.

### 6.2 Types produits en Rocq

```coq
(* nat * nat est le type des paires d'entiers *)
Definition add_tuple := fun c => match c with (x, y) => x + y end.
Check add_tuple. (* add_tuple : nat * nat -> nat *)

(* Motif irréfutable avec ' pour les tuples en Rocq *)
Definition add_triple := fun '(x, y, z) => x + y + z.
```

### 6.3 `False` et la négation

`False` est une proposition **sans constructeur** : il est impossible d'en fournir une preuve. Mais si on suppose `False` dans les hypothèses, on peut prouver n'importe quoi (principe d'explosion).

```coq
Print False.
(* Inductive False : Prop := . — pas de constructeur ! *)

Lemma exfalso (A : Prop) : False -> A.
Proof.
  intros h.
  destruct h.  (* pas de cas à traiter ! La preuve est terminée *)
Qed.
```

**La négation** `¬A` (notée `~ A` en Rocq) est définie comme `A -> False` :

```coq
Definition not (A : Prop) := A -> False.
Notation "~ A" := (not A).
```

| Tactique | Ce qu'elle fait |
|----------|----------------|
| `exfalso` | Change le but en `False` (utile si on a une contradiction dans le contexte). |
| `unfold not` ou `unfold "~"` | Déplie la définition de `~` en `... -> False`. |
| `destruct h` sur `h : False` | Clôt la preuve (aucun cas). |

---

## 7. Semaine 4 — `forall` et types dépendants

### 7.1 La quantification universelle

En OCaml, les fonctions polymorphes sont implicitement quantifiées :
```ocaml
let id x = x  (* val id : 'a -> 'a *)
(* i.e. : ∀α, α → α *)
```

En Rocq, cette quantification est **explicite** :
```coq
Definition id (A : Type) : A -> A := fun x => x.
Check id.  (* forall A : Type, A -> A *)
```

`A -> B` est en fait du sucre syntaxique pour `forall _ : A, B` quand `B` ne dépend pas de la valeur de l'argument.

**Pour prouver un `forall`** : on utilise encore `intros` pour nommer le paramètre quantifié.

```coq
Lemma foo : forall (A : Prop), A -> A.
Proof.
  intros A.   (* Soit A une proposition *)
  intros hA.  (* On suppose hA : A *)
  exact hA.
Qed.
```

### 7.2 Types dépendants

Un **type dépendant** est un type dont la valeur dépend d'un terme. Exemple : le type de retour dépend de la valeur d'un booléen.

```coq
Definition false_or_42 (b : bool) :=
  match b return (if b then bool else nat) with
  | true  => false
  | false => 42
  end.
Check false_or_42.  (* forall b : bool, if b then bool else nat *)
```

### 7.3 Types sommes et produits dans `Type`

```coq
(* Produit (paire) dans Type — analogue de /\ dans Prop *)
Inductive prod (A B : Type) := pair (a : A) (b : B).
Check prod.  (* Type -> Type -> Type *)

(* Somme (union) dans Type — analogue de \/ dans Prop *)
Inductive sum (A B : Type) := inl (a : A) | inr (b : B).
Check sum.   (* Type -> Type -> Type *)
```

### 7.4 Le quantificateur existentiel (`∃`)

```coq
(* exists x, P x  signifie  ∃x, P(x) *)
Lemma ex_example : exists n : nat, n + 1 = 2.
Proof.
  exists 1.  (* on choisit le témoin n = 1 *)
  simpl. reflexivity.
Qed.
```

**Pour utiliser** `h : exists x, P x` : `destruct h as [x hx]` donne le témoin `x` et la preuve `hx : P x`.

| Tactique | Ce qu'elle fait |
|----------|----------------|
| `specialize H` | Instancie une hypothèse (ou un lemme) avec des arguments. |
| `exists t` | Prouve `∃x, P x` en choisissant le témoin `t`. |
| `destruct h as [x hx]` | Utilise une preuve de `∃x, P x`. |

---

## 8. Semaine 5 — Types récursifs, `nat`, listes, induction

### 8.1 Les entiers naturels de Peano

```coq
Inductive nat : Set :=
  | O : nat        (* zéro *)
  | S : nat -> nat (* successeur *)
```

`0` est `O`, `1` est `S O`, `2` est `S (S O)`, etc. Rocq fournit les notations décimales habituelles.

**Fonctions récursives** avec `Fixpoint` :

```coq
Fixpoint add (n m : nat) :=
  match n with
  | O   => m
  | S p => S (add p m)  (* add (S p) m = S (add p m) *)
  end.
```

Règle d'or pour les fonctions récursives : se demander comment obtenir le résultat pour `S p` si on le connaît pour `p`.

### 8.2 Les listes

```coq
Inductive list (A : Type) : Type :=
  | nil  : list A                    (* liste vide *)
  | cons : A -> list A -> list A.    (* tête :: queue *)

(* Notations *)
Check [].             (* liste vide *)
Check 1 :: 2 :: [].  (* [1; 2] *)
Check [4; 3; 2; 1].  (* liste de 4 entiers *)
```

**Exemple de fonction récursive sur les listes** :

```coq
Fixpoint app {A : Type} (l1 l2 : list A) :=
  match l1 with
  | []      => l2
  | h :: q  => h :: (app q l2)
  end.
Notation "l1 ++ l2" := (app l1 l2).

Fixpoint length {A : Type} (l : list A) :=
  match l with
  | []     => 0
  | _ :: q => S (length q)
  end.
```

### 8.3 La preuve par induction

Une **preuve par induction** sur un type récursif, c'est une preuve par cas où, pour le cas récursif, on dispose d'une **hypothèse d'induction** (l'énoncé vrai pour le sous-terme récursif).

```coq
Lemma app_nil_r {A : Type} : forall (l : list A), l ++ [] = l.
Proof.
  intros l.
  induction l as [| h q IH].  (* IH : q ++ [] = q *)
  - (* cas l = [] *)
    simpl. reflexivity.
  - (* cas l = h :: q *)
    simpl.
    rewrite IH.   (* on utilise l'hypothèse d'induction *)
    reflexivity.
Qed.
```

**Syntaxe** : `induction l as [| h q IH]`
- Branche `[]` : pas de variable à nommer.
- Branche `h :: q` : `h` est la tête, `q` la queue, `IH` l'hypothèse d'induction.

Sur `nat` : `induction n as [| p IH]` (cas `O`, cas `S p` avec `IH : P p`).

### 8.4 L'induction vue comme une fonction récursive

```coq
(* La preuve par induction SUR nat EST une fonction récursive *)
Fixpoint nat_ind (P : nat -> Prop)
    (h0 : P 0)
    (hered : forall k, P k -> P (S k))
    (n : nat) :=
  match n with
  | 0   => h0
  | S p => hered p (nat_ind P h0 hered p)
  end.
```

Cela illustre la correspondance preuves/programmes : une preuve par induction est un programme récursif.

| Tactique | Ce qu'elle fait |
|----------|----------------|
| `induction l as [...]` | Preuve par induction. Nommer les variables et l'hypothèse d'induction. |
| `rewrite IH` | Réécrire en utilisant l'hypothèse d'induction (de gauche à droite). |
| `rewrite <- IH` | Réécrire de droite à gauche. |

---

## 9. Semaine 6 — Réécriture et égalité

### 9.1 Règles de réécriture de base

Pour éviter de dépendre de ce que `simpl` fait exactement (ce qui est opaque), on définit et utilise des **lemmes de réécriture élémentaires** correspondant aux cas du `match`.

```coq
(* Pour app *)
Lemma app_nil_l {A : Type} (l : list A) : [] ++ l = l.
Proof. simpl. reflexivity. Qed.

Lemma app_cons_l {A : Type} (h : A) (q l : list A) :
  (h :: q) ++ l = h :: (q ++ l).
Proof. simpl. reflexivity. Qed.

(* Pour length *)
Lemma length_nil {A : Type} : length (@nil A) = 0.
Proof. simpl. reflexivity. Qed.

Lemma length_cons {A : Type} (h : A) (q : list A) :
  length (h :: q) = S (length q).
Proof. simpl. reflexivity. Qed.

(* Pour add *)
Lemma add_0_l (n : nat) : 0 + n = n.
Proof. simpl. reflexivity. Qed.

Lemma add_succ_l (n m : nat) : (S n) + m = S (n + m).
Proof. simpl. reflexivity. Qed.
```

### 9.2 Preuves "papier très détaillées"

Le cours insiste sur la capacité à écrire des preuves lisibles sur papier, en justifiant chaque étape par un lemme ou une règle de calcul. Exemple :

```
Lemma length_app (l l' : list A) : length (l ++ l') = length l + length l'.
Preuve par induction sur l.
  Cas l = [] :
    length ([] ++ l')  = length l'          [par app_nil_l]
                       = 0 + length l'      [par add_0_l]
                       = length [] + length l' [par length_nil]

  Cas l = h :: q, avec IH : length (q ++ l') = length q + length l' :
    length ((h :: q) ++ l')  = length (h :: (q ++ l'))   [par app_cons_l]
                              = S (length (q ++ l'))      [par length_cons]
                              = S (length q + length l')  [par IH]
                              = S (length q) + length l'  [par add_succ_l]
                              = length (h :: q) + length l' [par length_cons]
□
```

### 9.3 Égalité entre constructeurs

**Injectivité** : si `S n = S m` alors `n = m`. La tactique `injection` extrait cette information.

```coq
Lemma ex (n m : nat) : S (S n) = S m -> S n = m.
Proof.
  intros H.
  injection H as H'.  (* H' : S n = m *)
  exact H'.
Qed.
```

**Discrimination** : `true ≠ false`, `S n ≠ O`, etc. La tactique `discriminate` prouve des égalités impossibles entre constructeurs distincts.

```coq
Lemma zero_neq_one : 0 <> 1.
Proof.
  intros H.
  discriminate H.  (* impossible : O = S O *)
Qed.
```

---

## 10. Semaine 8 — Arbres binaires et entiers en binaire

### 10.1 Arbres binaires en OCaml

```ocaml
(* Arbre binaire strict : pas d'arbre vide *)
type 'a sbtree = Leaf of 'a | Node of 'a sbtree * 'a * 'a sbtree

(* Arbre binaire non strict : l'arbre vide est autorisé *)
type 'a btree = EmptyTree | Node of 'a btree * 'a * 'a btree
```

### 10.2 Arbres binaires en Rocq

```coq
(* Arbre strict *)
Inductive sbtree (A : Type) :=
  | leaf (key : A)
  | node (l : sbtree A) (key : A) (r : sbtree A).
Arguments leaf {A}.
Arguments node {A}.  (* A devient implicite *)

(* Arbre non strict (utilisé plus souvent dans les TD/TP) *)
Inductive btree (A : Type) :=
  | emptyTree
  | node (left : btree A) (key : A) (right : btree A).
Arguments emptyTree {A}.
Arguments node {A}.
```

**Fonctions usuelles sur les arbres** :

```coq
Fixpoint height {A : Type} (t : btree A) : nat :=
  match t with
  | emptyTree    => 0
  | node l _ r  => S (max (height l) (height r))
  end.

Fixpoint numNodes {A : Type} (t : btree A) : nat :=
  match t with
  | emptyTree    => 0
  | node l _ r  => 1 + numNodes l + numNodes r
  end.

Fixpoint mirror {A : Type} (t : btree A) :=
  match t with
  | emptyTree    => emptyTree
  | node l k r  => node (mirror r) k (mirror l)
  end.

(* Parcours préfixe (racine, gauche, droite) *)
Fixpoint prefixDFS {A : Type} (t : btree A) : list A :=
  match t with
  | emptyTree    => []
  | node l k r  => [k] ++ prefixDFS l ++ prefixDFS r
  end.
```

### 10.3 Entiers en binaire : le type `positive`

```coq
(* Entiers strictement positifs en binaire *)
Inductive positive : Set :=
  | xI : positive -> positive  (* rajoute un bit 1 à droite : p -> 2p+1 *)
  | xO : positive -> positive  (* rajoute un bit 0 à droite : p -> 2p   *)
  | xH : positive.             (* représente 1 *)

(* Notations *)
Notation "1"     := xH.
Notation "p ~ 1" := (xI p).  (* 1 en bit de poids faible *)
Notation "p ~ 0" := (xO p).  (* 0 en bit de poids faible *)
```

**Exemples de lecture** (attention : les bits se lisent de droite à gauche) :
- `xH` = `1` (en décimal : 1)
- `xO xH` = `1~0` (bits : 10 en binaire = 2 en décimal)
- `xI xH` = `1~1` (bits : 11 en binaire = 3 en décimal)
- `xO (xI xH)` = `1~1~0` (bits : 110 en binaire = 6 en décimal)

**Le successeur** (exemple de fonction récursive non triviale) :
```coq
Fixpoint succ (p : positive) :=
  match p with
  | 1     => 1~0      (* 1 → 2 *)
  | q~0   => q~1      (* 2k → 2k+1 *)
  | q~1   => (succ q)~0  (* 2k+1 → 2(k+1) avec retenue *)
  end.
```

---

## 11. Semaine 9 — `positive`, propositions inductives

### 11.1 Les autres types d'entiers

| Type | Représente | Défini à partir de |
|------|------------|-------------------|
| `positive` | Entiers > 0 | Constructeurs `xH`, `xI`, `xO` |
| `N` | Entiers ≥ 0 | `N0` (zéro) et `Npos p` |
| `Z` | Entiers relatifs | `Z0`, `Zpos p`, `Zneg p` |

### 11.2 Propositions inductives (prédicats inductifs)

Un **prédicat inductif** définit une relation entre termes via des **règles d'inférence**. C'est une proposition dont les preuves sont construites par des règles.

**Exemple célèbre du cours** : le prédicat `E` sur `Z × Z`.

```coq
Inductive E : Z -> Z -> Prop :=
  | ZZ : E 0 0                               (* règle de base *)
  | UN   (x y : Z) : E x y -> E (x-1) (y+1) (* règle UN   *)
  | DEUX (x y : Z) : E x y -> E (x+2) (y-2) (* règle DEUX *)
```

Cela définit la plus petite relation satisfaisant les trois règles. Pour prouver `E 3 (-3)` :

```coq
Lemma Eex1 : E 3 (-3).
Proof.
  apply (DEUX 1 (-1)).   (* E 1 (-1) -> E 3 (-3) *)
  apply (DEUX (-1) 1).   (* E (-1) 1 -> E 1 (-1) *)
  apply (UN 0 0).        (* E 0 0 -> E (-1) 1 *)
  exact ZZ.
Qed.
```

### 11.3 Le principe d'induction sur un prédicat inductif

Quand on définit un prédicat inductif, Rocq génère automatiquement un **principe d'induction** pour raisonner sur ses preuves. On peut utiliser `induction` sur une preuve d'un prédicat inductif comme sur `nat` ou `list`.

---

## 12. Semaine 10 — `bool` versus `Prop`, réflexion booléenne

### 12.1 Deux façons de parler d'une propriété

Pour une propriété comme "n ≤ m", il y a deux approches en Rocq :

**Approche `Prop`** : prédicat inductif, "prouvable" mais pas directement calculable.
```coq
Inductive le (n : nat) : nat -> Prop :=
  | le_n : le n n                             (* n ≤ n *)
  | le_S : forall m, le n m -> le n (S m).    (* si n ≤ m alors n ≤ S m *)
Notation "n <= m" := (le n m).
```

**Approche `bool`** : fonction calculable, retourne `true` ou `false`.
```coq
Fixpoint leb n m :=
  match n, m with
  | 0,    _    => true
  | S _,  0    => false
  | S n', S m' => leb n' m'
  end.
Notation "n <=? m" := (leb n m).
```

### 12.2 La réflexion booléenne

La **réflexion** consiste à faire le lien entre les deux approches : prouver que `n <=? m = true` si et seulement si `n <= m`.

```coq
Lemma le_leb (n m : nat) : n <= m -> n <=? m = true.
Lemma leb_le (n m : nat) : n <=? m = true -> n <= m.
```

Ceci permet d'utiliser le **calcul booléen** (rapide, automatique) pour décider des questions logiques.

**Avantages de chaque approche** :
- `Prop` : permet de raisonner, d'utiliser `destruct`, `induction`, plus expressif.
- `bool` : calculable avec `Compute`, peut s'utiliser dans des programmes, décidable.

**La tactique `lia`** : automatise les preuves arithmétiques sur les entiers. Très utile pour les cas triviaux.

```coq
Lemma example (n : nat) : n + 0 = n.
Proof. lia. Qed.  (* lia trouve la preuve toute seule *)
```

---

## 13. Semaine 11 — `apply` et `rewrite` avancés, listes triées

### 13.1 `apply` vers l'avant et vers l'arrière

**Vers l'arrière** (le plus courant) : `apply h` quand `h : A -> B` et le but est `B`. Le but devient `A`.

**Vers l'avant** : `apply h in h1` quand `h : A -> B` et `h1 : A`. `h1` est remplacé par `h h1 : B`.

```coq
(* Version conservatrice : crée une nouvelle hypothèse sans modifier h1 *)
apply h in h1 as h2.  (* h2 : B, h1 inchangé *)
```

### 13.2 `rewrite` avancé

```coq
rewrite H.       (* remplace le membre gauche de H par le droit dans le but *)
rewrite <- H.    (* sens inverse : remplace le membre droit par le gauche *)
rewrite H in h2. (* réécrit dans l'hypothèse h2 plutôt que dans le but *)
```

**La tactique `replace`** : remplace une expression par une autre en créant un sous-but d'égalité.
```coq
replace (x + 1) with (1 + x) by ring.
```

### 13.3 Le prédicat `sorted` (listes triées)

```coq
Inductive sorted : list nat -> Prop :=
  | sorted_nil  : sorted []
  | sorted_one  : forall n, sorted [n]
  | sorted_cons : forall n m l,
      n <= m -> sorted (m :: l) -> sorted (n :: m :: l).
```

Une liste est triée si elle est vide, ou singleton, ou si sa tête est ≤ au deuxième élément et le reste est trié.

### 13.4 Le prédicat `Permutation`

`Permutation l1 l2` exprime que `l2` est une permutation de `l1` (même éléments, ordre potentiellement différent). Défini dans la bibliothèque standard de Rocq.

---

## 14. Semaine 12 — Fonctions d'ordre supérieur

### 14.1 `map`

`map` applique une fonction à chaque élément d'une liste.

```ocaml
(* OCaml *)
let rec map f l =
  match l with
  | []     -> []
  | h :: t -> f h :: map f t
(* Type : ('a -> 'b) -> 'a list -> 'b list *)
```

```coq
(* Rocq *)
Fixpoint map {A B : Type} (f : A -> B) (l : list A) :=
  match l with
  | []     => []
  | h :: t => (f h) :: (map f t)
  end.
```

### 14.2 `filter`

`filter` garde uniquement les éléments satisfaisant un prédicat booléen.

```ocaml
let rec filter p l =
  match l with
  | []     -> []
  | h :: t -> if p h then h :: filter p t else filter p t
(* Type : ('a -> bool) -> 'a list -> 'a list *)
```

### 14.3 `fold_right` et `fold_left`

Les fonctions `fold` sont les fonctions d'ordre supérieur les plus puissantes : elles permettent de **réduire** une liste à une valeur en appliquant une fonction accumulatrice.

```ocaml
let rec fold_right f l accu =
  match l with
  | []     -> accu
  | a :: l -> f a (fold_right f l accu)
(* Type : ('a -> 'b -> 'b) -> 'a list -> 'b -> 'b *)

let rec fold_left f accu l =
  match l with
  | []     -> accu
  | a :: l -> fold_left f (f accu a) l
(* Type : ('b -> 'a -> 'b) -> 'b -> 'a list -> 'b *)
```

**Différence** :
- `fold_right f [a; b; c] init` = `f a (f b (f c init))` — associe à droite
- `fold_left  f init [a; b; c]` = `f (f (f init a) b) c` — associe à gauche

**Exemple** :
```ocaml
fold_right ( + ) [10; 42; 3] 0  (* = 10 + (42 + (3 + 0)) = 55 *)
fold_left  ( + ) 0 [10; 42; 3]  (* = ((0 + 10) + 42) + 3 = 55 *)
```

### 14.4 Composition de fonctions

```ocaml
let compose f g = fun x -> f (g x)
(* Type : ('b -> 'c) -> ('a -> 'b) -> 'a -> 'c *)
(* Correspond à f ∘ g en mathématiques *)
```

---

## 15. Récapitulatif de toutes les tactiques Rocq

### Tactiques de base (semaines 1–2)

| Tactique | Usage |
|----------|-------|
| `exact t` | Termine la preuve en donnant directement le terme `t`. |
| `reflexivity` | Prouve `X = X` (égalité réflexive). |
| `simpl` | Réduit (évalue) le but autant que possible. |
| `simpl in h` | Réduit dans l'hypothèse `h`. |
| `destruct b` | Preuve par cas sur `b` (crée un sous-but par constructeur). |
| `destruct b as [...]` | Preuve par cas avec nommage des composantes. |
| `rewrite H` | Réécrit dans le but en utilisant l'égalité `H`. |
| `rewrite <- H` | Réécrit dans le sens inverse. |
| `rewrite H in h2` | Réécrit dans l'hypothèse `h2`. |

### Tactiques logiques (semaines 2–4)

| Tactique | Connecteur | Direction |
|----------|-----------|-----------|
| `intros h` | `→`, `∀` | Introduction (prouver une implication) |
| `apply h` | `→` | Élimination vers l'arrière |
| `apply h in h1` | `→` | Élimination vers l'avant |
| `split` | `∧` | Introduction (prouve un "et") |
| `destruct h as [hA hB]` | `∧` | Élimination |
| `left` | `∨` | Introduction (gauche) |
| `right` | `∨` | Introduction (droite) |
| `destruct h as [hA \| hB]` | `∨` | Élimination |
| `exfalso` | `⊥` | Change le but en `False` |
| `unfold not` | `¬` | Déplie la négation |
| `exists t` | `∃` | Introduction (choisir le témoin) |
| `destruct h as [x hx]` | `∃` | Élimination |
| `specialize H` | `∀` | Instanciation d'un quantificateur universel |
| `assumption` | — | Cherche dans le contexte |

### Tactiques avancées (semaines 5–11)

| Tactique | Usage |
|----------|-------|
| `induction l as [...]` | Preuve par induction structurelle. |
| `discriminate H` | Prouve `False` à partir d'une égalité impossible entre constructeurs. |
| `injection H` | Extrait les égalités des arguments à partir d'une égalité entre constructeurs. |
| `injection H as H1 H2...` | Comme `injection` mais nomme les nouvelles hypothèses. |
| `replace e1 with e2` | Remplace `e1` par `e2` dans le but (crée un sous-but `e1 = e2`). |
| `replace e1 with e2 by tac` | Comme ci-dessus mais résout le sous-but avec `tac`. |
| `lia` | Résout automatiquement les buts arithmétiques linéaires. |
| `ring` | Résout les égalités dans un anneau commutatif. |

---

## 16. Ce qui tombe aux examens

D'après le partiel 1 et l'interrogation 1 présents dans le ZIP :

### Partiel 1 (3h, sur papier)

Trois types d'exercices :

**1. Preuves de logique propositionnelle** — Pour un lemme donné, fournir :
- Un terme de preuve direct (avec `exact (match ...)` ou `exact (fun ...)`)
- Une preuve avec tactiques
- Un arbre de dérivation en déduction naturelle

Exemple tombé : `Lemma and_assoc (h : A /\ (B /\ C)) : (A /\ B) /\ C.`

**2. Typage de fonctions OCaml** — Donner le type d'une fonction, évaluer des applications partielles.

Exemple tombé : `let dup f x = f x x` — donner son type, évaluer `dup (+) 3`.

**3. Preuves par induction** — Définir des fonctions récursives, prouver des lemmes par induction avec réécritures explicites, écrire des preuves papier détaillées.

### Interrogation 1

Focus sur les **arbres binaires** :
- Représenter graphiquement un arbre donné en Rocq.
- Définir des fonctions récursives sur les arbres.
- Calculer pas à pas l'évaluation d'une fonction.
- Preuve papier par induction.

### Points essentiels à maîtriser

- ✅ Pattern matching en OCaml et en Rocq
- ✅ Types variants (Inductive) avec un ou plusieurs constructeurs
- ✅ Curryfication et application partielle
- ✅ Termes de preuve (match, fun, conj, or_introl...)
- ✅ Tactiques : `intros`, `destruct`, `split`, `left/right`, `apply`, `exact`, `simpl`, `reflexivity`, `rewrite`
- ✅ Induction sur `nat` et `list`, avec hypothèse d'induction
- ✅ Preuves papier très détaillées (justifier chaque étape avec un lemme nommé)
- ✅ Arbres binaires en OCaml et Rocq
- ✅ Injection et discrimination entre constructeurs
- ✅ Différence `bool` / `Prop`, réflexion booléenne

---

> **Fichiers les plus utiles pour réviser** :
> - `résumé-mi-parcours-2026.pdf` — résumé exhaustif des 6 premières semaines avec tout le code
> - `partiels/p1/2025-2026/p1-25-26_corr.pdf` — correction du partiel 1
> - `interros/interro01_corr.pdf` — correction de l'interrogation 1
> - Les fichiers `TP0X_corr.v` — corrections complètes de tous les TPs
