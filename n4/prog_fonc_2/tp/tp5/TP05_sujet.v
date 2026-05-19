(** * TP5 : récursivité et induction *)

From Corelib Require Import ssreflect.
(* From Coq Require Import ssreflect. *)

(** ** Le jeu des entiers naturels *)

(** Les entiers naturels sont déjà définis dans le prélude de Rocq : *)

Print nat.

Import Init.Nat. (* On veut des noms courts et les notations usuelles : *)

(** L'addition et les notations décimales aussi : *)

Print add.

Check 42.
Compute 20 + 42.

(** Avec la définition de add, on obtient tout de suite : *)
Lemma add_0_l (n : nat) : 0 + n = n.
Proof. simpl. reflexivity. Qed.

Lemma add_succ_l (n m : nat) : (S n) + m = S (n + m).
Proof. simpl. reflexivity. Qed.

(** Mais pour [add_0_r], comme vu en cours et en TD, il faut une preuve par
    induction : *)

Lemma add_0_r (n : nat) : n + 0 = n.
Proof.
  induction n as [| p IH].
  - simpl. reflexivity.
  - simpl. rewrite IH. reflexivity.
Qed.

Lemma add_succ_r (n m : nat) : n + (S m) = S (n + m).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Dans la preuve du lemme suivant, il est possible que vous ayez besoin
    de calculer (réduire) dans l'hypothèse de récurrence.
    Pour cela, on peut utiliser [simpl in IH] (si votre hypothèse de récurrence
    se nomme IH). *)
Lemma add_succ_comm (n m : nat) : S n + m = n + (S m).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** On peut utiliser les lemmes déjà prouvés avec [rewrite] pour transformer
    le but. *)

Lemma rewriteExemple1 (n : nat) : (0 + (n + 0)) + 0 = n.
Proof.
  rewrite add_0_r.
  rewrite add_0_r.
  rewrite add_0_l.
  reflexivity.
Qed.

(** De plus, utiliser [rewrite] avec des règles de réécritures peut être une
    alternative à [simpl] (ou toute autre tactique qui fait des réductions)
    lorsque [simpl] en fait trop (voir plus loin, avec la multiplication. *)

Lemma add_comm (n m : nat) : n + m = m + n.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma add_assoc (n m p : nat) : n + (m + p) = (n + m) + p.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Maintenant, on ajoute la multiplication dans la théorie : *)

(** On a déjà [mul] dans le prélude. *)

Print mul.
Locate "_ * _".
Print Notation "_ * _".

(** On a directement : *)

Lemma mul_0_l (n : nat) : 0 * n = 0.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Et presque directement : *)

(** Penser à utiliser [add_comm] ici : *)

Lemma mul_succ_l (n m : nat) : (S n) * m = n * m + m.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Enfin, on sait multiplier par 1 à gauche (mais en utilisant une propriété de
    l'addition, pas juste par calcul) *)
Lemma mul_1_l (n : nat) : 1 * n = n.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Maintenant, place à l'induction... *)
Lemma mul_0_r (n : nat) : n * 0 = 0.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Ici, il faut utiliser des propriétés de l'addition encore. *)

Lemma mul_succ_r (n m : nat) : n * S m = n * m + n.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma mul_comm (n m : nat) : n * m = m * n.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma mul_1_r (n : nat) : n * 1 = n.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


From Coq Require Import PeanoNat.

(** Parfois, on a besoin d'être précis sur les rewrite pour dire où on veut
    que les règles soient appliquées.
    Une possibilité est d'instancier les lemmes soi-même : *)

Lemma rewriteExemple2 (n m : nat) : (n + m) + n + m = m + (n + m) + n.
Proof.
  (* Par exemple, je veux échanger le premier n avec le premier m : *)
  rewrite (add_comm n m).
  (* Ici je précise que le deuxième argument est [m] pour mettre le m juste
   * avant le = tout à gauche *)
  rewrite (add_comm _ m).
  rewrite add_assoc.
  reflexivity.
Qed.

(** À vous pour celui-ci (embêtant sur les rewrite).
    Prendre une feuille de papier et faire apparaître les parenthèses cachées.
    On peut aussi le passer en première lecture.
*)
Lemma mul_add_distr_r (n m p : nat) : (n + m) * p = n * p + m * p.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma mul_add_distr_l (n m p : nat) : n * (m + p) = n * m + n * p.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma mul_assoc (n m p : nat) : n * (m * p) = (n * m) * p.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


From Coq Require Import List.
Import ListNotations.

(** Changer la définition de la fonction [length] pour qu'elle corresponde à la
    longueur d'une liste. *)
Fixpoint length {A : Type} (l : list A) :=
  0.

(** Maintenant décommenter les tests suivants. *)
(* Lemma length_test1 : length [2; 5; 1] = 3. *)
(* Proof. reflexivity. Qed. *)
(* Lemma length_test2 {A : Type} : length (@nil A) = 0. *)
(* Proof. reflexivity. Qed. *)
(* Lemma length_test3 : length [true] = 1. *)
(* Proof. reflexivity. Qed. *)

(** Changer la définition de la fonction [repeat] pour qu'elle crée une liste de
   longueur [n] avec n fois l'élément [a]. *)
Fixpoint repeat {A : Type} (n : nat) (a : A) : list A :=
  [].

(** Maintenant décommenter les tests suivants. *)
(* Lemma repeat_test1 : repeat 5 true = [true; true; true; true; true]. *)
(* Proof. reflexivity. Qed. *)
(* Lemma repeat_test2 : repeat 0 42 = []. *)
(* Proof. reflexivity. Qed. *)
(* Lemma repeat_test3 : repeat 3 (repeat 2 true) = *)
(*   [[true; true]; [true; true]; [true; true]]. *)
(* Proof. reflexivity. Qed. *)

(** Prouver maintenant : *)
Lemma length_repeat {A : Type} (n : nat) (a : A) :
  length (repeat n a) = n.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Remplacer la définition de la fonction [map] pour obtenir une fonction
    qui applique la fonction f à chaque élément d'une liste. *)
Fixpoint map {A B : Type} (f : A -> B) (l : list A) : list B :=
  [].

(** Maintenant décommenter les tests suivants. *)
Lemma map_test1 : map S [1; 2; 3] = [2; 3; 4].
Proof. reflexivity. Qed.
Lemma map_test2 : map negb [true; false; true] = [false; true; false].
Proof. reflexivity. Qed.
Lemma map_test3 : map negb [] = [].
Proof. reflexivity. Qed.

(** Prouver le lemme suivant : *)
Lemma length_map {A B : Type} (f : A -> B) (l : list A) :
  length (map f l) = length l.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Remplacer la définition de la fonction [flatten] pour obtenir une fonction
    qui transforme une liste de liste en une liste (voir les tests suivants).
    Penser à utiliser [app]. *)
Fixpoint flatten {A : Type} (l : list (list A)) : list A :=
  [].

(* Lemma flatten_test1 : flatten [[1; 2; 3]; []; [4; 5]] = [1; 2; 3; 4; 5]. *)
(* Proof. reflexivity. Qed. *)
(* Lemma flatten_test2 : flatten [[true]; [false; true]; []] = [true; false; true]. *)
(* Proof. reflexivity. Qed. *)

(** Sur append, prouver les lemmes suivants.
    Dans quel cas faut-il raisonner par induction ? *)

Lemma app_nil_l {A : Type} (l : list A) : [] ++ l = l.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma app_nil_r {A : Type} (l : list A) : l ++ [] = l.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma app_assoc {A : Type} (l1 l2 l3 : list A) :
  l1 ++ (l2 ++ l3) = (l1 ++ l2) ++ l3.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma map_app {A B : Type} (f : A -> B) (l1 l2 : list A) :
  map f (l1 ++ l2) = (map f l1) ++ (map f l2).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Module Cailloux.

(** Maintenant, on oublie les entiers naturels [nat].
    On va définir les entiers comme des listes de cailloux. *)

Inductive caillou := Caillou.
Notation "🪨" := Caillou.
Definition entier := list caillou.

Definition zero : entier := [].
Definition un : entier := [🪨].
Definition deux : entier := [🪨; 🪨].
Definition trois : entier := [🪨; 🪨; 🪨].
Definition quatre : entier := [🪨; 🪨; 🪨; 🪨].

(** L'addition est la concaténation des listes : *)
Definition add (n m : entier) := app n m.

(** En utilisant les propriétés de [app], prouver : *)
Lemma add_0_l (n : entier) : add zero n = n.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma add_0_r (n : entier) : add n zero = n.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma add_assoc (n m p : entier) : add n (add m p) = add (add n m) p.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** On redéfinit [repeat] avec nos entiers à base de cailloux (remplacer la
    définition par une définition convenable utilisant [map] : *)
Definition repeat {A : Type} (n : entier) (a : A) : list A :=
  [].

Lemma repeat_zero {A : Type} (a : A) : repeat zero a = [].
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Décommenter les tests suivants : *)
(* Lemma repeat_test1 : repeat quatre false = [false; false; false; false]. *)
(* Proof. reflexivity. Qed. *)
(* Lemma repeat_test2 : repeat zero false = []. *)
(* Proof. reflexivity. Qed. *)
(* Lemma repeat_test3 : repeat quatre 🪨 = quatre. *)
(* Proof. reflexivity. Qed. *)

(** length (à valeur dans entier à base de cailloux) peut être défini avec
    map *)
Definition length {A : Type} : list A -> entier :=
  0.

(** Décommenter les tests suivants : *)
(* Lemma length_test1 : length [false; true; false] = trois. *)
(* Proof. reflexivity. Qed. *)
(* Lemma length_test2 {A : Type} : length (@nil A) = zero. *)
(* Proof. reflexivity. Qed. *)
(* Lemma length_test4 : length [trois; un] = deux. *)
(* Proof. reflexivity. Qed. *)

(** Prouver le lemme suivant sans induction, en utilisant des propriétés
    déjà prouvées. *)
Lemma length_app {A : Type} (l1 l2 : list A) :
  length (l1 ++ l2) = add (length l1) (length l2).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Maintenant pour la multiplication des cailloux, utiliser map, repeat,
    flatten, ... *)

Definition mul (n m : entier) :=
  [].

(** Décommenter les tests suivants : *)
(* Lemma mul_test1 : mul deux trois = [🪨; 🪨; 🪨; 🪨; 🪨; 🪨]. *)
(* Proof. reflexivity. Qed. *)
(* Lemma mul_test2 : mul trois zero = zero. *)
(* Proof. reflexivity. Qed. *)

End Cailloux.
