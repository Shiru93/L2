Set Asymmetric Patterns.
Set Structural Injection.
From Corelib Require Import ssreflect.
(* From Coq Require Import ssreflect. *)
From Stdlib Require Import List PeanoNat.
(* From Coq Require Import List PeanoNat. *)
Import Nat ListNotations.
Open Scope list_scope.
Open Scope bool_scope.

(** * TP6 : égalité entre constructeurs *)

(** ** La tactique injection *)

(** La tactique injection permet de simplifier les égalités faisant intervenir
    un même constructeur à gauche et à droite. *)
Lemma succ_inj (n m : nat) : S n = S m -> n = m.
Proof.
  intros H.
  injection H.
  exact H.
Qed.

(** Voici un autre exemple avec des listes : *)
Lemma cons_inj {A : Type} (h1 h2 : A) (t1 t2 : list A) :
  h1 :: t1 = h2 :: t2 -> h1 = h2 /\ t1 = t2.
Proof.
  intros H.
  (* Ici on nomme les deux égalités : *)
  injection H as Hh Ht.
  split; assumption.
Qed.

(** À vous maintenant : *)
Lemma succ_eq_1 (n : nat) : S n = 1 -> n = 0.
Proof.
  intros H.
  injection H.
  exact H.
Qed.

(** La tactique injection peut simplifier plusieurs fois d'un coup : *)
Lemma succ_succ_inj (n m : nat) : S (S n) = S (S m) -> n = m.
Proof.
  intros H. injection H. exact H.
Qed.

(** Et même s'appliquer récursivement : *)
Lemma cons_succ_succ_inj (n m : nat) (l1 l2 : list nat) :
  S (S n) :: l1 = S (S m) :: l2 -> n = m /\ l1 = l2.
Proof.
  intros H.
  injection H as Hnm Hl1l2.
  split; assumption.
Qed.

(** Voici maintenant une application moins évidente.
    Prouver par induction : *)
Lemma add_eq_reg_l (n m p : nat) : n + m = n + p -> m = p.
Proof.
  intros H.
  induction n as [| n IH].
  - simpl. exact H.
  - apply IH.
    injection H.
    exact H.
Qed.

(** Idem avec des listes.
    Rappel : pour réduire les termes (en utilisant les définitions) dans une
    hypothèse H, on peut utiliser [simpl in H.] *)
Lemma app_eq_reg_l {A : Type} (l1 l2 l3 : list A) :
  l1 ++ l2 = l1 ++ l3 -> l2 = l3.
Proof.
  intros H.
  induction l1 as [| h t IH].
  - exact H.
  - apply IH. injection H. exact H.
Qed.

(** ** La tactique discriminate *)

(** Lorsqu'on a (après réduction et simplifications éventuelles) une égalité
    entre constructeurs différents, on peut terminer la preuve avec la tactique
    [dicriminate].

    [discriminate] est indispensable pour évacuer les cas impossibles. *)

Lemma exemple_discriminate1 (n : nat) : S (S n) <> 0.
Proof.
  intros H.
  discriminate H. (* boum ! *)
Qed.

(** C'est aussi une bonne occasion de montrer que de [False], on peut prouver
    n'importe quoi : *)
Lemma exemple_discriminate2 (n : nat) : S (S n) = 1 -> 2 + 2 = 5.
Proof.
  intros H.
  discriminate H. (* boum ! *)
Qed.

(** À vous pour quelques exercices simples d'abord.
    À chaque fois, demandez-vous comment Rocq parvient à prouver [False]. *)
Lemma exo_discriminate1 (n m : nat) : S n + m <> 0.
Proof.
  intros H.
  discriminate H.
Qed.

Lemma exo_discriminate2 (n m : nat) (l1 l2 : list nat) : S n :: l1 <> 0 :: l2.
Proof.
  intros H.
  discriminate H.
Qed.

(** Là, il faut d'abord se convaincre que [discriminate] ne peut pas avancer.
    Utiliser [add_comm] pour aider [discriminate].
    Pour l'utiliser dans une hypothèse H,
    [rewrite add_comm in H.] *)
Lemma exo_discriminate3 (n m : nat) : n + S m <> 0.
Proof.
  intros H.
  Fail discriminate H.
  rewrite add_comm in H.
  discriminate H.
Qed.

(** Maintenant, prouver avec une preuve par cas : *)
Lemma add_eq_0_l (n m : nat) : n + m = 0 -> n = 0.
Proof.
  intros H.
  destruct n as [| p].
  - reflexivity.
  - discriminate H.
Qed.

Lemma add_eq_0_r (n m : nat) : n + m = 0 -> m = 0.
Proof.
  intros H.
  destruct m as [| p].
  - reflexivity.
  - rewrite add_comm in H. discriminate H.
Qed.

(** Par contre, [discriminate] ne sait pas sans aide prouver que [S n <> n.]
    Raisonner par induction et se rappeler que [injection] existe. *)
Lemma neq_succ_diag_l (n : nat) : S n <> n.
Proof.
  intros H.
  induction n as [| p IH].
  - discriminate H.
  - apply IH.
    injection H.
    exact H.
Qed.

(** Même chose avec les listes *)
Lemma neq_cons_diag_l {A : Type} (l : list A) (a : A) : a :: l <> l.
Proof.
  intros H.
  induction l as [| h t IH].
  - discriminate H.
  - apply IH.
    injection H as Ha Hnimp.
    rewrite Ha.
    exact Hnimp.
Qed.

(** En utilisant [add_eq_reg_l] et [add_comm], montrer le lemme suivant : *)
(** Rappel : pour utiliser [add_comm] avec comme arguments m et n, on utilise
    [rewrite (add_comm m n).] *)
Lemma add_eq_reg_r (n m p : nat) : m + n = p + n -> m = p.
Proof.
  rewrite (add_comm m n) (add_comm p n).
  exact (add_eq_reg_l n m p).
Qed.

(** On va en déduire le résultat suivant. *)
Lemma add_eq_id_l (n m : nat) : n + m = n -> m = 0.
Proof.
  intros H.
  (* Ce rewrite permet de changer n en n + 0 dans le membre de droite (RHS, pour
     "right hand side") de l'égalité : *)
  rewrite -[RHS](add_0_r n) in H.
  (* On a utilisé le symbole - ici pour signifier qu'on utilise l'égalité
     n + 0 = n de droite à gauche. *)
  (* Maintenant, on a :
     H : n + m = n + 0
     add_eq_reg_l : forall n m p, n + m = n + p -> m = p
  *)
  apply add_eq_reg_l in H.
  exact H.
Qed.

(** Un tel résultat est certainement encore valable sur les listes.
    Pour une première preuve, on peut passer par la longueur. *)
Lemma length_0_nil {A : Type} (l : list A) : length l = 0 -> l = [].
Proof.
  intros H. destruct l as [| h t].
  - reflexivity.
  - discriminate H.
Qed.

Lemma length_app {A : Type} (l1 l2 : list A) :
  length (l1 ++ l2) = length l1 + length l2.
Proof.
  induction l1 as [| h t IH].
  - reflexivity.
  - simpl. rewrite IH. reflexivity.
Qed.

Lemma app_eq_id_l {A : Type} (l1 l2 : list A) : l1 ++ l2 = l2 -> l1 = [].
Proof.
  intros H.
  apply length_0_nil.
  apply (add_eq_id_l (length l2)).
  rewrite add_comm.
  rewrite -length_app.
  rewrite H.
  reflexivity.
Qed.

(** Mais il y a certainement quelque chose de plus direct et plus propre aux
    listes. *)

Lemma app_cons_r {A : Type} (l1 l2 : list A) (a : A) :
  l1 ++ (a :: l2) = (l1 ++ [a]) ++ l2.
Proof.
  induction l1 as [| h t IH].
  - reflexivity.
  - simpl. rewrite IH. reflexivity.
Qed.

(** Sans résultats ou opérations supplémentaires, la preuve suivante est assez
    longue (et peu parlante).
    On raisonne par induction sur l1 puis par cas sur l2.
    Il faut parfois un raisonnement par cas dans le raisonnement par cas...
    Injection et disciminate sont beaucoup utilisés. *)

Lemma app_eq_reg_r_subproof {A : Type} (l1 l2 : list A) (h : A) :
  l1 ++ [h] = l2 ++ [h] -> l1 = l2.
Proof.
  (* On a besoin d'une induction la plus générale possible, donc on précise
     ici (avec cette syntaxe pas très jolie) qu'on généralise sur l2. *)
  induction l1 as [| h1 t1 IH] in l2 |- *.
  - destruct l2 as [| h2 t2].
    + intros _; reflexivity.
    + destruct t2 as [| h3 t3].
      * intros H; discriminate H.
      * intros H; discriminate H.
  - destruct l2 as [| h2 t2].
    + destruct t1 as [| h1' t1'].
      * intros H; discriminate H.
      * intros H; discriminate H.
    + intros H; injection H as H1 H2. rewrite H1.
      specialize (IH t2 H2). rewrite IH. reflexivity.
Qed.

Lemma app_eq_reg_r {A : Type} (l1 l2 l3 : list A) :
  l2 ++ l1 = l3 ++ l1 -> l2 = l3.
Proof.
  induction l1 as [| h t IH] in l2, l3 |- *.
  - intros H. rewrite 2!app_nil_r in H. exact H.
  - intros H.
    rewrite 2!(app_cons_r _ t) in H.
    apply IH in H.
    apply app_eq_reg_r_subproof in H.
    exact H.
Qed.

(** Comme promis (et si vous êtes arrivés là, bravo), on a maintenant une
    deuxième preuve de [app_eq_id_l] : *)

Lemma app_eq_id_l' {A : Type} (l1 l2 : list A) : l1 ++ l2 = l2 -> l1 = [].
Proof.
  rewrite -[RHS](app_nil_l l2).
  intros H.
  apply (app_eq_reg_r l2).
  exact H.
Qed.
