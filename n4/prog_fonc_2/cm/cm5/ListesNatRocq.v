Print list.
(*
Inductive list (A : Type) : Type :=
   nil : list A | cons : A -> list A -> list A.
*)

Check list. (* list : Type -> Type *)
Check list bool. (* list bool : Set *)

About nil.
(* nil : forall {A : Type}, list A *)
(* les accolades dans {A} montrent que c'est un argument implicite *)
Check nil. (* list ?A, car l'argument de type est implicite *)
Check @nil.
Check @nil bool. (* list bool *)

About cons.
Check cons. (* ?A -> list ?A -> list ?A, pour la même raison *)
Check @cons bool.

Check (cons 42 (cons 10 (nil))).
(* 42 :: 10 :: nil : list nat *)
Check (cons 42 (cons 10 (cons 25 nil))).
Locate "::".
Print Notation "_ :: _".

Open Scope list_scope.
Check (42 :: 10 :: 25 :: nil).

From Coq Require Import List.
Import ListNotations.

About "[ ]".
Print Notation "[ ]".

Locate "[ x ; y ; .. ; z ]".
Print Notation "[ x ; y ; .. ; z ]".

Check [42; 10; 25].

Definition is_empty {A : Type} (l : list A) :=
match l with
| nil => true
| _ => false
end.

Section ExempleNil.
  Eval simpl in (is_empty nil).
  Eval simpl in (is_empty (true :: false :: nil)).
  Context (l : list nat).
  Eval simpl in (is_empty (42 :: l)).
  Eval simpl in (is_empty l).
  Check [[2; 3]; [4; 5]].
End ExempleNil.
Eval simpl in (is_empty []). (* true *)
Eval simpl in (is_empty [32; 10]). (* false *)

Fixpoint app {A : Type} (l0 l1 : list A) :=
 match l0 with
 | [] => l1
 | h :: q => h :: (app q l1)
 end.

Eval simpl in (app [32; 10] [1; 2; 3]).
(* = [32; 10; 1; 2; 3] : list nat *)

Section ExpleAppend.
  Context (A : Type) (l1 l2 : list A) (a b : A).
  Eval simpl in (app (cons a (cons b l1)) l2).
  Eval simpl in (app l1 []).
End ExpleAppend.

Lemma app_nil_l {A : Type} : forall (l : list A), app [] l = l.
Proof.
 intros l.
 simpl. (* par calcul, (app [] l) se réduit en l *)
 reflexivity. (* l = l, fin de la preuve *)
Qed.

Lemma app_nil_r {A : Type} : forall (l : list A), app l [] = l.
Proof.
 (* C'est certainement vrai, allons-y. *)
 intros l.
 simpl. (* arg, rien ne se passe *)
 (* essayons par cas *)
 destruct l as [| h q]. (* nil ou h :: q *)
 - simpl. (* par calcul, app [] [] se réduit en [] *)
   reflexivity. (* ok, [] = [] *)
 - simpl. (* par calcul, app (h :: q) [] = h :: (app q []) *)
   (* Hmm... ne suffit pas... *)
   (* On a besoin de la preuve que (app q [] = q) *)
Abort. (* On recommence avec une preuve par induction. *)

Lemma app_nil_r {A : Type} : forall (l : list A), app l [] = l.
Proof.
 intros l.
 induction l as [| h q IH].
 - (* cas l = [] *)
   simpl.
   reflexivity.
 - (* cas l = h :: q
      avec l'hypothèse d'induction :
      IH : app q [] = q *)
   simpl.
   rewrite IH. (* changer (app q []) en q dans le but *)
   reflexivity. (* h :: q = h :: q *)
Qed.

Print nat.

Check 4.

Set Printing All.
Check 4.
Unset Printing All.
Check S (S (S (S (S (S O))))).
Print Nat.add.
Eval simpl in (2 + 2).

Section AddExple.
  Context (n m : nat).
  Eval simpl in (0 + m). (* m *)
  Eval simpl in (2 + m). (* S (S m) *)
  Eval simpl in (S (S n) + m). (* S (S (n + m)) *)
  Eval simpl in (n + 0). (* n + 0 *)
  Eval simpl in (n + 1). (* n + 1 *)
End AddExple.

Lemma add_0_l : forall (n : nat), 0 + n = n.
Proof.
 intros n. (* Soit (n : nat). *)
 simpl. (* On réduit 0 + n en n *)
 reflexivity. (* n = n, ok *)
Qed.

Lemma add_0_r : forall (n : nat), n + 0 = n.
Proof.
 intros n. induction n as [| p IH].
 - simpl. (* 0 + 0 se réduit en 0 *)
   reflexivity. (* 0 = 0 ok *)
 - (* n = S p où p satisfait
      IH : p + 0 = p *)
   simpl. (* S p + 0 se réduit en S (p + 0) *)
   rewrite IH. (* On utilise IH pour changer
                  p + 0 en p dans le but *)
   reflexivity. (* S p = S p, ok *)
Qed.

Fixpoint length [A : Type] (l : list A) :=
 match l with
 | [] => 0
 | _ :: q => S (length q)
 end.

Lemma length_app {A : Type} (l l' : list A) :
length (app l l') = length l + length l'.
Proof.
 induction l as [| h q IH].
 - simpl.
   reflexivity.
 - simpl.
   rewrite IH.
   reflexivity.
Qed.

Lemma app_assoc {A : Type} (l1 l2 l3 : list A) :
  app (app l1 l2) l3 = app l1 (app l2 l3).
Proof.
  induction l1 as [| h q Hl1].
  - simpl.
    reflexivity.
  - simpl.
    rewrite Hl1.
    reflexivity.
Qed.

Lemma app_cons_l {A : Type} (h : A) (q l : list A) :
 app (h :: q) l = h :: (app q l).
Proof. simpl. reflexivity. Qed.
Lemma length_nil {A : Type} : length (@nil A) = 0.
Proof. simpl. reflexivity. Qed.
Lemma length_cons {A : Type} (h : A) (q : list A) :
 length (h :: q) = S (length q).
Proof. simpl. reflexivity. Qed.

Lemma app_assoc' {A : Type} (l1 l2 l3 : list A) :
 app (app l1 l2) l3 = app l1 (app l2 l3).
Proof.
 induction l1 as [| h q IH].
 - rewrite app_nil_l. (* but : app l2 l3 = app [] (app l2 l3) *)
   rewrite app_nil_l. (* but : app l2 l3 = app l2 l3 *)
   reflexivity.
 - rewrite app_cons_l.
   (* but : app (h :: app (q l2) l3 = app (h :: q) (app l2 l3) *)
   rewrite app_cons_l.
   (* but : h :: app (app (q l2)) l3 = app (h :: q) (app l2 l3) *)
   rewrite app_cons_l.
   (* but : h :: app (app (q l2)) l3 = h :: app q (app l2 l3) *)
   rewrite IH.
   (* but : h :: app q (app l2 l3) = h :: app q (app l2 l3) *)
   reflexivity.
Qed.

About nat_ind.
(* forall (P : nat -> Prop), P 0 -> (forall n, P n -> P (S n))
     -> forall n, P n *)
About list_ind.

Fixpoint my_nat_ind (P : nat -> Prop) (h0 : P 0)
 (hnSn : forall n, P n -> P (S n)) n : P n :=
 match n with
 | 0 => h0
 | S p => hnSn p (my_nat_ind P h0 hnSn p)
 end.

Print nat_ind.
Print add_0_r.
Print eq_ind.
Lemma add_0_r' : forall (n : nat), n + 0 = n.
Proof.
 exact (fun n => nat_ind (fun x => x + 0 = x) eq_refl
 (fun p IH => eq_ind_r (fun m => S m = S p) eq_refl IH)
 n).
Qed.

Fixpoint my_list_ind {A : Type} (P : list A -> Prop) (hnil : P [])
 (hcons : forall a l, P l -> P (a :: l)) l : P l :=
 match l with
 | [] => hnil
 | h :: q => hcons h q (my_list_ind P hnil hcons q)
 end.
