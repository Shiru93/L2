Set Asymmetric Patterns.
Set Structural Injection.
From Corelib Require Import ssreflect.
(* From Coq Require Import ssreflect. *)
From Stdlib Require Import List PeanoNat BinInt Lia.
(* From Coq Require Import List PeanoNat BinInt Lia. *)
Import Nat ListNotations.
Open Scope list_scope.
Open Scope bool_scope.

(** * TP8 : Prop "vraiment" inductives *)

Module ExerciceSerguei.

Open Scope nat_scope.

(** On continue à explorer les exercices de programmation fonctionnelle 1
    avec le prédicat F sur [nat] : *)

Inductive F : nat -> Prop :=
  | F1 : F 1
  | F2 : F 2
  | FP3 (x : nat) (h : F x) : F (x + 3).

(** Exercice sur papier :
    Pouvez-vous écrire les constructeurs sous forme de règles d'inférence ? *)

Lemma e1q21 : F 1.
Proof.
  exact F1.
Qed.

Lemma e1q22 : F 2.
Proof.
  exact F2.
Qed.

(** Ici, raisonner vers l'arrière en fournissant explicitement argument x
    de FP3 : *)
Lemma e1q24 : F 4.
Proof.
  apply (FP3 1).
  exact F1.
Qed.

(** Si on ne veut pas fournir explicitement cet argument, on peut faire
    plusieurs choses différentes : *)
(** D'abord raisonner vers l'avant : *)
Lemma e1q25 : F 8.
Proof.
  (** On part de (F 2) : *)
  specialize F2 as H.
  (** On applique le constructeur FP3 à H :
      pas le choix pour x, ça doit être 2, pas la peine de le fournir
      explicitement. *)
  apply FP3 in H.
  (** Si on veut on peut réduire, dans H : *)
  simpl in H.
  (** On applique de nouveau le constructeur FP3 à notre nouveau H : *)
  apply FP3 in H.
  simpl in H.
  exact H.
Qed.

(** À vous, en raisonnant vers l'avant, prouvez : *)
Lemma e1q26 : F 7.
Proof.
  specialize F1 as H. (* On sait que F 1. *)
  apply FP3 in H. (* Donc d'après FP3, F (3 + 1) *)
  apply FP3 in H. (* Donc encore d'après FP3, F (3 + (3 + 1)) *)
  exact H.
Qed.

(** L'autre possibilité consiste à [replace] dans le but pour faire apparaître
    le motif (x + 3) : *)
Lemma e1q25' : F 8.
Proof.
  (* Je remplace 8 par (5 + 3) : *)
  replace 8 with (5 + 3).
  - (* preuve du but initial avec remplacement : *)
    apply FP3.
    replace 5 with (2 + 3).
    + (* preuve de (F (2 + 3)) : *)
      apply FP3.
      exact F2.
    + (* preuve que 2 + 3 = 5 : *)
      reflexivity.
  - (* preuve que 5 + 3 = 8 *)
    reflexivity.
Qed.

(** C'est embêtant d'ouvrir des sous-buts en général et là, juste pour
    reflexivity...
    Si la preuve de l'égalité est tactic, on peut simplement :
    replace term1 with term2 by tactic.
    ou si c'est une petite série de tactiques (tac1; tac2; ...) :
    replace term1 with term2 by (tac1; tac2; ...).
*)
Lemma e1q25'' : F 8.
Proof.
  replace 8 with (5 + 3) by reflexivity.
  apply FP3.
  replace 5 with (2 + 3) by reflexivity.
  apply FP3.
  exact F2.
Qed.

(** À vous, avec une preuve vers l'arrière utilisant replace, sans instancier
    à la main les apply, prouver de nouveau : *)

Lemma e1q24' : F 4.
Proof.
  replace 4 with (1 + 3) by reflexivity.
  apply FP3. exact F1.
Qed.

Lemma e1q26' : F 7.
Proof.
  replace 7 with (4 + 3) by reflexivity.
  apply FP3.
  replace 4 with (1 + 3) by reflexivity.
  apply FP3.
  exact F1.
Qed.

(** On va continuer avec F, mais d'abord Un petit rappel sur "il existe" :
    c'est une proposition à un seul constructeur : *)
Print ex.
(** Le constructeur se nomme "ex_intro" et prend comme argument un élément
    x de A et une preuve de P x.
    En général, on utilise la tactique "exists" suivi du témoin qu'on fournit. *)

Lemma exists_exple1 : exists x, x * x = x.
Proof.
  exists 0. (* Je choisis la témoin 0. *)
  (* Il faut prouver qu'il satisfait la propriété maintenant : *)
  (* Preuve de 0 * 0 = 0 : *)
  reflexivity.
Qed.

(** 0 n'était pas la seule solution, pouvez-vous en trouver une autre ? *)
Lemma exists_exple1' : exists x, x * x = x.
Proof.
  exists 1.
  reflexivity.
Qed.

(** Comme une preuve de "il existe" est un élément et une propriété satisfaite
    par cet élément, on peut la [destruct] pour obtenir ces deux choses : *)
Lemma exists_exple2 (n : nat) : (exists k, n = 2 * k) -> exists q, n = q + q.
Proof.
  intros H.
  destruct H as [k Hk]. (* H fournit un nat k tel que n = 2 * k *)
  (* Pour q, je choisis... k *)
  exists k.
  (* là c'est résolu par lia : *)
  lia.
Qed.

(** Rappel : on aurait pu à la place de
    intros H. destruct H as [k Hk].
    écrire directement :
    intros [k Hk].
*)

(* À vous pour le suivant : *)
Lemma multiple4_multiple2 (n : nat) :
  (exists k, n = 4 * k) -> exists q, n = 2 * q.
Proof.
  intros [k Hk].
  exists (2 * k).
  lia.
Qed.

(** Maintenant on retourne au prédicat inductif [F]. *)

(** Écrire la preuve suivante en raisonnant directement par induction sur la
    preuve de (F x).
    Pour les égalités ou inégalités "évidentes" sur nat ou Z, on peut utiliser
    lia dans ce TP.
*)
Lemma e2q2 (x : nat) : F x -> exists k, x = 3 * k + 1 \/ x = 3 * k + 2.
Proof.
  intros H.
  induction H as [| | x h IH].
  - exists 0; left; reflexivity.
  - exists 0; right; reflexivity.
  - destruct IH as [k [Hk | Hk]].
    + rewrite Hk; exists (S k); left. lia.
    + rewrite Hk; exists (S k); right. lia.
Qed.

(** Quid de la réciproque ? Indice : penser à [replace]. *)

Lemma e2q2' (k : nat) : F (3 * k + 1) /\ F (3 * k + 2).
Proof.
  induction k as [| k' IH].
  - split; [exact F1 | exact F2].
  - destruct IH as [IH1 IH2]; split.
    + replace (3 * S k' + 1) with (((3 * k') + 1) + 3) by lia.
      apply FP3. exact IH1.
    + replace (3 * S k' + 2) with (((3 * k') + 2) + 3) by lia.
      apply FP3. exact IH2.
Qed.
End ExerciceSerguei.
