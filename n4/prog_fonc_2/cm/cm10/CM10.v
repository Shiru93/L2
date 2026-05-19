Set Asymmetric Patterns.
Set Structural Injection.
From Corelib Require Import ssreflect.
From Stdlib Require Import List PeanoNat BinInt Lia.
Import Nat ListNotations.
Open Scope list_scope.
Open Scope bool_scope.

Section Rappels.

Open Scope Z_scope.
Inductive E : Z -> Z -> Prop :=
| ZZ : E 0 0
| UN (x y : Z) : E x y -> E (x - 1) (y + 1)
| DEUX (x y : Z) : E x y -> E (x + 2) (y - 2).

Lemma Eex1 : E 3 (-3).
Proof.
  apply (DEUX 1 (-1)).
  apply (DEUX (-1) 1).
  apply (UN 0 0).
  exact ZZ.
Qed.

Lemma Eex2 (x y : Z) : E x y -> E (x + 1) (y - 1).
Proof.
  intros H.
  replace (x + 1) with ((x + 2) - 1) by lia.
  replace (y - 1) with ((y - 2) + 1) by lia.
  apply UN.
  apply DEUX.
  exact H.
Qed.

Print E_ind.
Check E_ind.

End Rappels.

Section PeanoLe.
Print Peano.le.
About Peano.le.

Lemma le_exple1 : 2 <= 5.
Proof.
  apply le_S. (* 2 <= 4 *)
  apply le_S. (* 2 <= 3 *)
  apply le_S.
  exact (le_n 2).
Qed.

Lemma le_refl (n : nat) : n <= n.
Proof. exact (le_n n). Qed.

Lemma le_0_l (n : nat) : 0 <= n.
Proof.
  induction n as [| p IH].
  - exact (le_n 0).
  - apply le_S. exact IH.
Qed.

Lemma le_le_succ_succ (n m : nat) : n <= m -> S n <= S m.
Proof.
  intros H.
  induction H as [| p H' IH].
  - (* H = le_n n *)
    exact (le_n _).
  - apply le_S. exact IH.
Qed.

Print leb.

Lemma leb_refl (n : nat) : n <=? n = true.
Proof.
  induction n as [| p IH].
  - reflexivity.
  - simpl; rewrite IH; reflexivity.
Qed.

Lemma leb_leb_succ_r (n m : nat) : n <=? m = true -> n <=? S m = true.
Proof.
  induction n as [| p IH] in m |- *.
  - intros _; reflexivity.
  - intros H. destruct m as [| m'].
    + discriminate H.
    + simpl. apply IH.
      exact H.
Qed.

Lemma le_leb (n m : nat) : n <= m -> n <=? m = true.
Proof.
  intros H.
  induction H as [| m H IHle].
  - exact (leb_refl _).
  - apply leb_leb_succ_r. exact IHle.
Qed.

Lemma leb_le (n m : nat) : n <=? m = true -> n <= m.
Proof.
  induction n as [| p IH] in m |- *.
  - intros _. exact (le_0_l m).
  - intros H. destruct m as [| m'].
    * discriminate H.
    * simpl in H.
      apply le_le_succ_succ.
      apply IH.
      exact H.
Qed.

Lemma exple_le_leb : 100 <= 200.
Proof.
  apply leb_le.
  simpl.
  reflexivity.
Qed.

Lemma le_decidable (n m : nat) : n <= m \/ (~ n <= m).
Proof.
  destruct (n <=? m) eqn:E.
  - left.
    apply leb_le. exact E.
  - right.
    intros H.
    apply le_leb in H.
    rewrite E in H.
    discriminate H.
Qed.
End PeanoLe.
