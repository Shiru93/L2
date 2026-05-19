(** * Le type [Prop] *)

(** ** Vers le type [Prop] : les sortes *)

Check true. (* true : bool *)
Check bool. (* bool : Set *)
Check Set. (* Set : Type *)
Check nat -> bool.
Check Type. (* Type : Type ... ??? *)
(* En fait, Type : Type entraîne une incohérence... *)

Set Printing Universes.
Check Type.
Unset Printing Universes.

Check 2 = 2. (* 2 = 2 : Prop *)
Check true = false. (* true = false : Prop *)
Check Prop. (* Prop : Type *)

(** ** Donner un terme de preuve directement avec exact *)

Lemma foo (A : Prop) (h : A) : A.
Proof. exact h. Qed.

Print True. (* Inductive True : Prop :=  I. *)
Lemma bar : True.
Proof. exact I. Qed.

About True.

Lemma foo' (A : Prop) : A -> A.
Proof. exact (fun (h : A) => h). Qed.

(** ** La conjonction *)

(** *** Définition de la conjonction : *)

Print "_ /\ _".
About and.
Print and.

(** *** Prouver un "et" à la main avec exact et le constructeur : *)

Lemma useConj (A B : Prop) (hA : A) (hB : B) : A /\ B.
Proof.
  exact (conj hA hB).
Qed.

Lemma useConj2 (A : Prop) (hA : A) : A /\ A.
Proof.
  exact (conj hA hA).
Qed.

Lemma useConj3 (A B : Prop) (hA : A) (hB : B) : (A /\ B) /\ A.
Proof.
  exact (conj (conj hA hB) hA).
Qed.

(** *** Prouver un "et" avec la tactique split : *)

Lemma plop (A B : Prop) (h : A) (h' : B) : A /\ B.
Proof.
  split.
  - (* preuve de A *)
    exact h.
  - (* preuve de B *)
    exact h'.
Qed.

Inductive and3 (A B C : Prop) :=
  conj3 (hA : A) (hB : B) (hC : C).

Lemma foo3 (A : Prop) (hA : A) : and3 A A A.
Proof.
  split; exact hA.
Qed.

(** Utiliser un "et" à la main avec exact et match *)

Lemma proj1 (A B : Prop) (h : A /\ B) : A.
Proof.
  exact (
    match h with
    | conj ha _ => ha
    end
  ).
Qed.


Lemma and_comm (A B : Prop) (h : A /\ B) : B /\ A.
Proof.
  exact (
    match h with
    | conj hA hB => conj hB hA
    end).
Qed.

(** *** Utiliser un "et" avec destruct : *)

Lemma proj1'' (A B : Prop) (h : A /\ B) : A.
Proof.
  destruct h as [hA hB].
  exact hA.
Qed.

Lemma and_assoc (A B C : Prop) (h : A /\ (B /\ C)) :
  (A /\ B) /\ C.
Proof.
  destruct h as [hA hBC].
  destruct hBC as [hB hC].
  (* exact (conj (conj hA hB) hC). *)
  split.
  - split.
    + exact hA.
    + exact hB.
  - exact hC.
Qed.

Lemma and_assoc' (A B C : Prop) (h : A /\ (B /\ C)) : (A /\ B) /\ C.
Proof.
  destruct h as [hA [hB hC]].
  exact (conj (conj hA hB) hC).
Qed.

(** ** Le ou de Prop *)

Print "_ \/ _".
About or.
Print or.

Check or_introl.

(** *** Prouver un "ou" à la main avec les constructeurs *)

Lemma foo1 (A B : Prop) (hA : A) : A \/ B.
Proof. exact (or_introl hA). Qed.
Lemma foo2 (A B : Prop) (hB : B) : A \/ B.
Proof. exact (or_intror hB). Qed.
Lemma foo4 (A B : Prop) (h : A /\ B) : A \/ B.
Proof. exact (let '(conj _ hB) := h in or_intror hB). Qed.

(** *** Prouver un "ou" avec left ou right *)

Lemma foo1' (A B : Prop) (hA : A) : A \/ B.
Proof. left. exact hA. Qed.
Lemma foo2' (A B : Prop) (hB : B) : A \/ B.
Proof. right. exact hB. Qed.
Lemma foo4' (A B : Prop) (h : A /\ B) : A \/ B.
Proof. destruct h as [hA _]. left. exact hA. Qed.

(** *** Utiliser un "ou" directement avec match *)

Lemma bar1 (A : Prop) (H : A \/ A) : A.
Proof.
  exact (match H with or_introl ha => ha | or_intror ha => ha end).
Qed.

Lemma bar2 (A B : Prop) (H : A \/ B) : B \/ A.
Proof.
  exact (
    match H with
    | or_introl hA => or_intror hA
    | or_intror hB => or_introl hB
    end).
Qed.

(** *** Utiliser un ou avec destruct *)

Lemma bar1' (A : Prop) (H : A \/ A) : A.
Proof.
  destruct H as [hA | hA].
  - exact hA.
  - exact hA.
Qed.

Lemma bar1'' (A : Prop) (H : A \/ A) : A.
Proof.
  destruct H as [hA | hA]; exact hA.
Qed.

Lemma bar2' (A B : Prop) (H : A \/ B) : B \/ A.
Proof.
  destruct H as [hA | hB].
  - right. exact hA.
  - left. exact hB.
Qed.

Lemma bar2'' (A B : Prop) (H : A \/ B) : B \/ A.
Proof.
  destruct H as [h | h]; [right | left]; exact h.
Qed.

(** ** L'implication *)


(** ** Utilisation directe comme une fonction *)
Lemma modus_ponens (A B : Prop) (hA : A) (h : A -> B) : B.
Proof.
  exact (h hA).
Qed.

Lemma impl_trans1 (A B C : Prop) (h1 : A -> B) (h2 : B -> C)
  (hA : A) : C.
Proof.
  exact (h2 (h1 hA)).
Qed.

(** ** Utilisation avec apply *)

Lemma modus_ponens' (A B : Prop) (hA : A) (h : A -> B) : B.
Proof.
  apply h. (* le but devient A *)
  exact hA.
Qed.

Lemma impl_trans1' (A B C : Prop) (h1 : A -> B) (h2 : B -> C)
  (hA : A) : C.
Proof.
  apply h2. (* le but devient B *)
  apply h1. (* le but devient A *)
  exact hA.
Qed.

(** ** Preuve directe en écrivant directement la fonction *)

Lemma impl_refl (A : Prop) : A -> A.
Proof.
  exact (fun h => h).
Qed.

Lemma impl_trans (A B C : Prop) (h1 : A -> B) (h2 : B -> C) :
  A -> C.
Proof.
  exact (fun hA => (h2 (h1 hA))).
Qed.

(** ** Preuve en ajoutant des variables dans le contexte avec intros *)

Lemma impl_refl' (A : Prop) : A -> A.
Proof.
  intros h. (* le but devient A
               et on a h : A dans le contexte *)
  exact h.
Qed.

Lemma impl_trans' (A B C : Prop) (h1 : A -> B) (h2 : B -> C) :
  A -> C.
Proof.
  intros hA. (* le but devient C
                et on a hA : C dans le contexte *)
  apply h2.
  apply h1.
  exact hA.
Qed.