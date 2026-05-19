From Coq Require Import Reals BinInt.

(* Premier exemple : bool avec deux constructeurs constants : *)
Inductive bool := true | false.

Definition negb (b : bool) : bool :=
  match b with
  | true => false
  | false => true
  end.

(* Cette définition permet à Rocq de calculer *)
Compute (negb true).
Compute (negb false).

Lemma negb_negb (b : bool) : negb (negb b) = b.
Proof.
  destruct b.
  - (* 1er cas : b = true *)
    simpl.
    reflexivity.
  - (* 2ème cas : b = false *)
    simpl.
    reflexivity.
Qed.

(* Pour les booléens on a aussi la notation if/then/else *)
Definition andb (b1 b2 : bool) :=
  if b1 then b2 else false.

(* Mais c'est vraiment juste une notation, comme on le voit ici : *)
Set Printing All.
Print andb.
Unset Printing All.

Lemma andb_true_r (b : bool) : andb b true = b.
Proof.
  destruct b.
  - (* b = true *)
    simpl. reflexivity.
  - (* b = false *)
    simpl. reflexivity.
Qed.

Inductive unit := tt.
(* Rien de plus à en dire... *)

Inductive number :=
  | Real (r : R)
  | Int (i : Z)
  | Error.

(* On peut définir des fonctions par cas avec match : *)
Definition is_real (n : number) : bool :=
  match n with
  | Real r =>  true
  | Int i => false
  | Error => false
  end.

(* On peut regrouper des cas et ignorer des arguments avec _ : *)
Definition is_real' (n : number) : bool :=
  match n with
  | Int _ | Error => false
  | Real r => true
  end.

(* Ici la solution la plus courte est d'ignorer tous les cas autres
   que Real : *)
Definition is_real'' (n : number) : bool :=
  match n with Real _ => true | _ => false end.

(* On peut aussi définir un type point à un seul constructeur qui prend deux
   arguments *)
Inductive point := Point (x y : R).

(* On peut définir des fonctions sur point avec match : *)
Definition symmetric (p : point) : point :=
  match p with
  | Point x y => Point (- x) (- y)
  end.

(* Mais aussi avec un motif irréfutable : *)
Definition symmetric_irrefutable '(Point x y) :=
  Point (- x) (- y).

Definition fst (p : point) :=
  match p with
  | Point x _ => x
  end.

Definition snd '(Point _ y) := y.

(* Ici, destruct a un seul cas, mais deux variables *)
Lemma symmetric_symmetric (p : point) :
  symmetric (symmetric p) = p.
Proof.
  destruct p as [x y].
  simpl.
  rewrite !Ropp_involutive. (* plus sur rewrite plus tard *)
  reflexivity.
Qed.
