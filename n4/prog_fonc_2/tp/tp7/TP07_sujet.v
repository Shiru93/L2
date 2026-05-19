Set Asymmetric Patterns.
Set Structural Injection.
From Corelib Require Import ssreflect.
(* From Coq Require Import ssreflect. *)
From Stdlib Require Import List PeanoNat BinNat String Lia.
(* From Coq Require Import List PeanoNat BinNat String Lia. *)
Import Nat ListNotations.
Open Scope list_scope.
Open Scope bool_scope.

(** * TP7 : types inductifs à plusieurs constructeurs ou arguments inductifs *)

(** ** Entiers en binaire *)

Module Positive.

(** Le type [positive] de la bibliothèque standard modélise les entiers naturels
    non nuls en binaire *)

Print positive.

(** C'est un type à trois constructeurs : *)

Check xI. (* représente l'ajout à la fin d'un "un" dans l'entier en binaire *)
Check xO. (* représente l'ajout à la fin d'un "zéro" dans l'entier en binaire *)
Check xH. (* représente l'entier 1 *)

(** On importe le module BinPos pour pouvoir utiliser des notations plus
    habituelles : *)

Import BinPos.
Open Scope positive.

Check xI (xO (xI xH)). (* 13%positive *)
Check xO (xO (xO (xO xH))). (* 16%positive *)

(** On a, de plus, les notations pratiques suivantes : *)
Check 1. (* 1 pour xH *)
Check 1~1~0~1. (* p~1 pour (xI p) et p~0 pour (xO p) *)
Check 1~0~0~0~0.

(** On définit la fonction successeur sur ces entiers de la façon suivante : *)

Fixpoint succ (p : positive) :=
  match p with
  | 1 => 1~0
  | q~0 => q~1
  | q~1 => (succ q)~0
  end.

Compute (succ 1~1~1~1).
Compute (succ 1~0~1~1).
Compute (succ 1~0~1~0).

Lemma succ_1 : succ 1 = 1~0. Proof. reflexivity. Qed.
Lemma succ_xO (p : positive) : succ p~0 = p~1. Proof. reflexivity. Qed.
Lemma succ_xI (p : positive) : succ p~1 = (succ p)~0. Proof. reflexivity. Qed.

(** À vous maintenant de montrer le résultat suivant.
    Rappelez-vous que [a <> b] est une notation pour [a = b -> False].
    (Vous pouvez utiliser [unfold "<>"] si vous voulez.)
    Vous devrez [destruct p] pour que [succ] puisse faire une étape de calcul.
*)

Lemma neq_succ_diag_l (p : positive) : succ p <> p.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Définir la fonction [of_nat] ci-dessous (remplacer "1" par votre
    définition)
    Pour "0%nat", pas vraiment de bon choix, prendre arbitrairement 1. *)

Fixpoint of_nat (n : nat) :=
  match n with
  | 0%nat => 1
  | 1%nat => 1
  | S p => 1
  end.

(** Les "tests" suivants devraient réussir : *)

Lemma assert_of_nat1 : of_nat (42%nat) = 42. Proof. reflexivity. Qed.
Lemma assert_of_nat2 : of_nat (2%nat) = 2. Proof. reflexivity. Qed.
Lemma assert_of_nat3 : of_nat (1000%nat) = 1000. Proof. reflexivity. Qed.

Lemma of_nat_1 : of_nat 1%nat = 1. Proof. reflexivity. Qed.

(** Quelques commentaires sur les ouvertures locales de portée.
    On a utilisé précédemment %nat pour préciser "avec les notations habituelles
    de nat" car l'ouverture de la portée "positive_scope" avec la commande
    Open Scope positive_scope.
    a relégué au second plan les notations de [nat].
    Il suffit d'ouvrir localement la portée de nat pour pouvoir utiliser les
    notations habituelles avec le type [nat] : *)

Compute (4 + 38)%nat.
Compute (2 * 45 + 3)%nat.

(** Définir la fonction [to_nat] ci-dessous (remplacer "0%nat" par votre
    définition). *)
Fixpoint to_nat (p : positive) :=
  0%nat.

(** Les "tests" suivants devraient réussir : *)

Lemma assert_to_nat1 : to_nat 42 = 42%nat. Proof. reflexivity. Qed.
Lemma assert_to_nat2 : to_nat 2 = 2%nat. Proof. reflexivity. Qed.
Lemma assert_to_nat3 : to_nat 1000 = 1000%nat. Proof. reflexivity. Qed.

(** Voici un exemple d'induction sur une variable de type [positive]. *)
Lemma to_nat_ne_0 (p : positive) : to_nat p <> 0%nat.
Proof.
  induction p as [p' IH | p' IH |].
  - simpl. lia.
  - simpl. lia.
  - simpl. lia.
Qed.

Lemma of_nat_succ (n : nat) : n <> 0%nat -> of_nat (S n) = succ (of_nat n).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Voici la définition de [add] vue en cours : *)

Fixpoint add (p q : positive) :=
  match p with
  | xH => succ q
  | xO p' => match q with
          | xH => xI p'
          | xO q' => xO (add p' q')
          | xI q' => xI (add p' q')
          end
  | xI p' => match q with
          | xH => xO (succ p')
          | xO q' => xI (add p' q')
          | xI q' => xO (succ (add p' q'))
          end
  end.

Notation "x + y" := (add x y) : positive_scope.

(** À vous pour les lemmes suivants : *)

Lemma add_1_r (p : positive) : p + 1 = succ p.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma add_1_l (p : positive) : 1 + p = succ p.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma add_diag (p : positive) : p + p = p~0.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma add_succ_l (p q : positive) : (succ p) + q = succ (p + q).
Proof.
  (* Ici, on a besoin de l'hypothèse d'induction la plus générale possible : *)
  induction p as [p' IH | p' IH |] in q |- *.
  (* À vous de compléter la preuve : *)
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma add_succ_r (p q : positive) : p + succ q = succ (p + q).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Nos lemmes masquent ceux des [nat], pour utiliser par exemple add_succ_r
    sur nat, utiliser la syntaxe Nat.add_succ_r *)

Lemma of_nat_add (n m : nat) : n <> 0%nat -> m <> 0%nat ->
  of_nat (n + m)%nat = of_nat n + of_nat m.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma of_nat_to_nat (p : positive) : of_nat (to_nat p) = p.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** On va maintenant pouvoir prouver l'associativité de l'addition par transfert
    de celle de [nat], grâce à tout le travail précédent. *)
Lemma add_assoc (p q r : positive) : p + (q + r) = (p + q) + r.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** ** Arbre de syntaxe abstrait *)

(** Par exemple en programmation *)

Module ExprBool.

(** On considère les expressions booléennes : *)

Inductive ExprBool :=
  | ETrue
  | EFalse
  | EAnd (left : ExprBool) (right : ExprBool)
  | EOr (left : ExprBool) (right : ExprBool)
  | ENot (e : ExprBool).

(** Définir la fonction [eval] qui retourne un booléen à partir d'une telle
    expression (remplacer [true] par la définition) : *)

Fixpoint eval (e : ExprBool) :=
  true.

(** Les "tests" suivants devraient réussir : *)

Lemma assert_eval1 : eval (ENot (ENot (EAnd ETrue (EOr EFalse ETrue)))) = true.
Proof. reflexivity. Qed.
Lemma assert_eval2 : eval (EOr (ENot ETrue) EFalse) = false.
Proof. reflexivity. Qed.

(** La fonction suivante élimine les doubles négations dans une expression
    booléenne, la lire attentivement : *)
Fixpoint eliminateDoubleNegation (e : ExprBool) :=
  match e with
  | ENot f => let g := (eliminateDoubleNegation f) in
              match g with
              | ENot h => h
              | _ => ENot g
              end
  | ETrue | EFalse => e
  | EAnd l r => EAnd (eliminateDoubleNegation l) (eliminateDoubleNegation r)
  | EOr l r => EOr (eliminateDoubleNegation l) (eliminateDoubleNegation r)
  end.

Compute (eliminateDoubleNegation
  (ENot (ENot (EAnd (ENot (ENot ETrue)) (EOr EFalse ETrue))))).

(** A-t-on changé la valeur de l'expression avec cette "optimisation" ? : *)
Lemma eliminateDoubleNegation_correct (e : ExprBool) :
  eval (eliminateDoubleNegation e) = eval e.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)

End ExprBool.
