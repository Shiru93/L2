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
  induction n as [| p IH].
  - simpl. reflexivity.
  - simpl. rewrite IH. reflexivity.
Qed.

(** Dans la preuve du lemme suivant, il est possible que vous ayez besoin
    de calculer (réduire) dans l'hypothèse de récurrence.
    Pour cela, on peut utiliser [simpl in IH] (si votre hypothèse de récurrence
    se nomme IH). *)
Lemma add_succ_comm (n m : nat) : S n + m = n + (S m).
Proof.
  induction n as [| p IH].
  - simpl. reflexivity.
  - simpl in IH.
    simpl.
    rewrite IH.
    reflexivity.
Qed.

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
  induction n as [| p IH].
  - rewrite add_0_l.
    rewrite add_0_r.
    reflexivity.
  - rewrite add_succ_l.
    rewrite IH.
    rewrite add_succ_r.
    reflexivity.
Qed.

Lemma add_assoc (n m p : nat) : n + (m + p) = (n + m) + p.
Proof.
  induction n as [| k IH].
  - simpl. reflexivity.
  - simpl. rewrite IH. reflexivity.
Qed.

(** Maintenant, on ajoute la multiplication dans la théorie : *)

(** On a déjà [mul] dans le prélude. *)

Print mul.
Locate "_ * _".
Print Notation "_ * _".

(** On a directement : *)

Lemma mul_0_l (n : nat) : 0 * n = 0.
Proof.
  simpl.
  reflexivity.
Qed.

(** Et presque directement : *)

(** Penser à utiliser [add_comm] ici : *)

Lemma mul_succ_l (n m : nat) : (S n) * m = n * m + m.
Proof.
  simpl.
  rewrite add_comm.
  reflexivity.
Qed.

(** Enfin, on sait multiplier par 1 à gauche (mais en utilisant une propriété de
    l'addition, pas juste par calcul) *)
Lemma mul_1_l (n : nat) : 1 * n = n.
Proof.
  simpl.
  rewrite add_0_r.
  reflexivity.
Qed.

(** Maintenant, place à l'induction... *)
Lemma mul_0_r (n : nat) : n * 0 = 0.
Proof.
  induction n as [| p IH].
  - simpl. reflexivity.
  - simpl. rewrite IH. reflexivity.
Qed.

(** Ici, il faut utiliser des propriétés de l'addition encore. *)

Lemma mul_succ_r (n m : nat) : n * S m = n * m + n.
Proof.
  induction n as [| p IH].
  - simpl. reflexivity.
  - simpl. rewrite IH add_succ_r add_assoc add_comm.
    reflexivity.
Qed.

Lemma mul_comm (n m : nat) : n * m = m * n.
Proof.
  induction n as [| p IH].
  - simpl. rewrite mul_0_r. reflexivity.
  - simpl. rewrite IH mul_succ_r add_comm.
    reflexivity.
Qed.

Lemma mul_1_r (n : nat) : n * 1 = n.
Proof.
  rewrite mul_comm.
  simpl.
  rewrite add_0_r.
  reflexivity.
Qed.

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
  induction n as [| k IH].
  - simpl. reflexivity.
  - rewrite add_succ_l 2!mul_succ_l IH -add_assoc (add_comm _ p) add_assoc.
    reflexivity.
Qed.

Lemma mul_add_distr_l (n m p : nat) : n * (m + p) = n * m + n * p.
Proof.
  rewrite 3!(mul_comm n). exact (mul_add_distr_r m p n).
Qed.

Lemma mul_assoc (n m p : nat) : n * (m * p) = (n * m) * p.
Proof.
  induction n as [| k IH].
  - simpl. reflexivity.
  - simpl. rewrite IH.
    rewrite mul_add_distr_r.
    reflexivity.
Qed.

From Coq Require Import List.
Import ListNotations.

(** Changer la définition de la fonction [length] pour qu'elle corresponde à la
    longueur d'une liste. *)
Fixpoint length {A : Type} (l : list A) :=
  match l with
  | [] => 0
  | _ :: q => S (length q)
  end.

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
  match n with
  | 0 => []
  | S p => cons a (repeat p a)
  end.

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
  induction n as [| k IH].
  - reflexivity.
  - simpl. rewrite IH. reflexivity.
Qed.

(** Remplacer la définition de la fonction [map] pour obtenir une fonction
    qui applique la fonction f à chaque élément d'une liste. *)
Fixpoint map {A B : Type} (f : A -> B) (l : list A) : list B :=
  match l with
  | [] => []
  | h :: t => (f h) :: map f t
  end.

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
  induction l as [| h t IH].
  - reflexivity.
  - simpl. rewrite IH. reflexivity.
Qed.

(** Remplacer la définition de la fonction [flatten] pour obtenir une fonction
    qui transforme une liste de liste en une liste (voir les tests suivants).
    Penser à utiliser [app]. *)
Fixpoint flatten {A : Type} (l : list (list A)) : list A :=
  match l with
  | [] => []
  | h :: q => app h (flatten q)
  end.

(* Lemma flatten_test1 : flatten [[1; 2; 3]; []; [4; 5]] = [1; 2; 3; 4; 5]. *)
(* Proof. reflexivity. Qed. *)
(* Lemma flatten_test2 : flatten [[true]; [false; true]; []] = [true; false; true]. *)
(* Proof. reflexivity. Qed. *)

(** Sur append, prouver les lemmes suivants.
    Dans quel cas faut-il raisonner par induction ? *)

Lemma app_nil_l {A : Type} (l : list A) : [] ++ l = l.
Proof.
  reflexivity.
Qed.

Lemma app_nil_r {A : Type} (l : list A) : l ++ [] = l.
Proof.
  induction l as [| h t IH].
  - reflexivity.
  - simpl. rewrite IH. reflexivity.
Qed.

Lemma app_assoc {A : Type} (l1 l2 l3 : list A) :
  l1 ++ (l2 ++ l3) = (l1 ++ l2) ++ l3.
Proof.
  induction l1 as [| h t IH].
  - reflexivity.
  - simpl. rewrite IH. reflexivity.
Qed.

Lemma map_app {A B : Type} (f : A -> B) (l1 l2 : list A) :
  map f (l1 ++ l2) = (map f l1) ++ (map f l2).
Proof.
  induction l1 as [| h t IH].
  - reflexivity.
  - simpl. rewrite IH. reflexivity.
Qed.

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
  exact (app_nil_l _).
Qed.

Lemma add_0_r (n : entier) : add n zero = n.
Proof.
  exact (app_nil_r _).
Qed.

Lemma add_assoc (n m p : entier) : add n (add m p) = add (add n m) p.
Proof.
  exact (app_assoc _ _ _).
Qed.

(** On redéfinit [repeat] avec nos entiers à base de cailloux (remplacer la
    définition par une définition convenable utilisant [map] : *)
Definition repeat {A : Type} (n : entier) (a : A) : list A :=
  map (fun _ => a) n.

Lemma repeat_zero {A : Type} (a : A) : repeat zero a = [].
Proof.
  reflexivity.
Qed.

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
  map (fun _ => 🪨).

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
  unfold length.
  rewrite map_app.
  reflexivity.
Qed.

(** Maintenant pour la multiplication des cailloux, utiliser map, repeat,
    flatten, ... *)

Definition mul (n m : entier) :=
  flatten (map (repeat n) m).

(** Décommenter les tests suivants : *)
(* Lemma mul_test1 : mul deux trois = [🪨; 🪨; 🪨; 🪨; 🪨; 🪨]. *)
(* Proof. reflexivity. Qed. *)
(* Lemma mul_test2 : mul trois zero = zero. *)
(* Proof. reflexivity. Qed. *)

End Cailloux.
