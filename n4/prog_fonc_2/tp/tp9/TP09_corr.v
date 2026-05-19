Set Asymmetric Patterns.
Set Structural Injection.
From Corelib Require Import ssreflect.
(* From Coq Require Import ssreflect. *)
From Stdlib Require Import List PeanoNat BinInt Lia.
(* From Coq Require Import List PeanoNat BinInt Lia. *)
Import Nat ListNotations.
Open Scope list_scope.
Open Scope bool_scope.

(** * TP9 : Propositions et réflexion *)

Open Scope nat_scope.

(** On commence par rappeler la définition de <= sur nat : *)
Print Peano.le.

(** C'est un prédicat inductif à deux constructeurs : *)
Check le_n.
Check le_S.

(** En utilisant ces deux constructeurs, prouver (sans lia) : *)

Lemma dix_treize : 10 <= 13.
Proof.
  apply le_S, le_S, le_S.
  exact (le_n _).
Qed.

(** On prouve maintenant que 0 est minimal dans nat.
    C'est fait dans le dernier CM, mais vous devriez y arriver
    sans aide, par induction sur n. *)
Lemma le_0_l (n : nat) : 0 <= n.
Proof.
  induction n as [| p IH].
  - exact (le_n 0).
  - apply le_S. exact IH.
Qed.

(** Pour la propriété suivante, il faut raisonner par induction
    sur la preuve de [n <= m] elle-même.
*)

Lemma le_le_succ_succ (n m : nat) : n <= m -> S n <= S m.
Proof.
  intros H. induction H as [| p H' IH].
  - (* H = le_n n *)
    exact (le_n _).
  - apply le_S. exact IH.
Qed.

(** Le lemme suivant devrait être simple... le problème est
    que raisonner par cas (avec destruct) sur une preuve de
    [n <= 0] a tendance à détruire trop de choses.
    Pour cette raison, on va ici utiliser [remember] pour garder
    en tête que le membre de droite de [<=] est 0. *)
Lemma le_0_r (n : nat) : n <= 0 -> n = 0.
Proof.
  intros H. remember 0 as m eqn:def_m.
  (* regarder l'effet de la tactique [remember] *)
  destruct H as [| p H'].
  - reflexivity.
  - discriminate def_m.
Qed.

Lemma nle_succ_0 (n : nat) : ~ (S n <= 0).
Proof.
  intros H.
  apply le_0_r in H.
  discriminate H.
Qed.

(** On va relier [le] à [leb] maintenant. *)
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

(** Définir la fonction insert qui insère un élément dans une
    liste juste avant le premier élément qui lui supérieur ou égal
    (remplacer la liste vide par votre définition).
    Utiliser [<=?] (qui calcule, contrairement à [<=]. *)

Fixpoint insert x l :=
  match l with
  | [] => [x]
  | h :: t => if (x <=? h) then x :: h :: t else h :: (insert x t)
  end.

(** Les tests suivants devraient passer : *)

Lemma insert_test1 : insert 3 [1; 2; 4; 5] = [1; 2; 3; 4; 5].
Proof. reflexivity. Qed.
Lemma insert_test2 : insert 0 [1; 2; 4; 5] = [0; 1; 2; 4; 5].
Proof. reflexivity. Qed.
Lemma insert_test3 : insert 0 [] = [0].
Proof. reflexivity. Qed.

(** S'en servir pour définir le tri par insertion. *)

Fixpoint insertion_sort l :=
  match l with
  | [] => []
  | h :: t => insert h (insertion_sort t)
  end.

(** Les tests suivants devraient passer : *)

Lemma insertion_sort_test1 : insertion_sort [5; 42; 93; 1] = [1; 5; 42; 93].
Proof. reflexivity. Qed.
Lemma insertion_sort_test2 : insertion_sort [] = [].
Proof. reflexivity. Qed.
Lemma insertion_sort_test3 : insertion_sort [1; 2; 3; 4] = [1; 2; 3; 4].
Proof. reflexivity. Qed.
Lemma insertion_sort_test4 : insertion_sort [4; 3; 2; 1] = [1; 2; 3; 4].
Proof. reflexivity. Qed.

(** On définit le fait d'être trié pour une liste de nat de la façon suivante.
*)
Inductive sorted : list nat -> Prop :=
  | nil_sorted : sorted []
  | one_sorted (x : nat) : sorted [x]
  | cons_sorted (h1 h2 : nat) (t : list nat) :
      sorted (h2 :: t) -> h1 <= h2 -> sorted (h1 :: h2 :: t).

(** En utilisant les constructeurs (et, par exemple, [lia] pour prouver les
    inégalités évidents), prouver : *)
Lemma sorted_example1 :
  sorted [1; 2; 3; 4].
Proof.
  apply cons_sorted; [| lia].
  apply cons_sorted; [| lia].
  apply cons_sorted; [| lia].
  exact (one_sorted _).
Qed.

(** Suite au prochain numéro...*)

(** Avant d'écrire des preuves sur [insertion_sort], on va prouver que [le] et
   [leb] sont bien des relations d'ordre. *)

(** Pour prouver le résultat suivant, on peut raisonner directement par cas : *)
Lemma leb_0_r (n : nat) : n <=? 0 = true -> n = 0.
Proof.
  intros H; destruct n.
  - reflexivity.
  - discriminate H.
Qed.

(** Ou bien passer par la réflexion ([leb_le]) et le résultat équivalent
    ([le_0_r]) pour [le] : *)

Lemma leb_0_r' (n : nat) : n <=? 0 = true -> n = 0.
Proof.
  intros H. apply leb_le in H.
  apply le_0_r. exact H.
Qed.

(** On prouve l'antisymétrie par induction sur n : *)
Lemma leb_antisymm (n m : nat) : n <=? m = true -> m <=? n = true -> n = m.
Proof.
  induction n as [| p IH] in m |- *.
  - intros _ H; rewrite (leb_0_r _ H). reflexivity.
  - destruct m as [| q].
    + intros H; discriminate H.
    + simpl; intros H1 H2.
      rewrite (IH q); [assumption.. | reflexivity].
Qed.

(** Maintenant prouver l'équivalent dans [le] par réflexion : *)
Lemma le_antisymm (n m : nat) : n <= m -> m <= n -> n = m.
Proof.
  intros H1 H2.
  apply le_leb in H1, H2.
  apply leb_antisymm; assumption.
Qed.

Lemma le_succ_l (n m : nat) : S n <= m -> n <= m.
Proof.
  induction 1.
  - apply le_S; exact (le_n _).
  - apply le_S; exact IHle.
Qed.

(** Passons à la transitivité. *)
Lemma le_trans (n m p : nat) : n <= m -> m <= p -> n <= p.
Proof.
  intros H. induction H as [| q H' IH].
  - intros H2. exact H2.
  - intros H3. apply le_succ_l in H3.
    apply IH.
    exact H3.
Qed.

(** Pour [leb], autant passer par la réflexion : *)
Lemma leb_trans (n m p : nat) :
  n <=? m = true -> m <=? p = true -> n <=? p = true.
Proof.
  intros H1 H2.
  apply leb_le in H1, H2.
  apply le_leb, (le_trans _ m); assumption.
Qed.

(** On relie (assez facilement) la propriété
    [(x <=? y) = false] avec la négation de [(x <= y)].
    On pourra, par exemple, utiliser
    destruct (x <=? y) eqn:E
    pour raisonner par cas sur (x <=? y) avec une équation E pour se souvenir
    de sa valeur. *)
Lemma nleb_nle : forall x y : nat, (x <=? y) = false -> ~ x <= y.
Proof.
  intros x y H1 H2.
  destruct (x <=? y) eqn:E.
  - discriminate H1.
  - apply le_leb in H2.
    rewrite E in H2; discriminate H2.
Qed.

Lemma nle_nleb : forall x y : nat, ~ x <= y -> (x <=? y) = false.
Proof.
  intros x y H1.
  destruct (x <=? y) eqn:E.
  - apply leb_le in E.
    exfalso; apply H1; exact E.
  - reflexivity.
Qed.

(** On repasse au tri par insertion.
    Les trois lemmes suivants sont des conséquences immédiates de la définition
    d'insert. *)

Lemma insert_nil (x : nat) : insert x [] = [x].
Proof.
  reflexivity.
Qed.

Lemma insert_leb (x h : nat) (t : list nat) :
  x <=? h = true -> insert x (h :: t) = x :: h :: t.
Proof.
  intros H; simpl; rewrite H; reflexivity.
Qed.

Lemma insert_nleb (x h : nat) (t : list nat) :
  x <=? h = false -> insert x (h :: t) = h :: (insert x t).
Proof.
  intros H; simpl; rewrite H; reflexivity.
Qed.

(** Celui-là est un assez gros morceau, mais est très satisfaisant.
    Penser à raisonner par cas sur la valeur (h <=? x).
    Pour les inégalités évidentes, on peut aussi revenir à [<=] par réflexion
    et utiliser [lia]. *)
Lemma sorted_sorted_insert (t : list nat) (h : nat) :
  sorted t -> sorted (insert h t).
Proof.
  intros H. induction H as [| x | h1 h2 t H IH Hineq].
  - simpl. exact (one_sorted _).
  - simpl.
    destruct (h <=? x) eqn:E.
    + apply leb_le in E; apply cons_sorted; [exact (one_sorted _) | lia].
    + apply nleb_nle in E; apply cons_sorted; [exact (one_sorted _) | lia].
  - simpl.
    destruct (h <=? h1) eqn:E.
    + apply leb_le in E.
      apply cons_sorted; [apply cons_sorted |]; [assumption | lia..].
    + apply nleb_nle in E.
      destruct (h <=? h2) eqn:E2.
      * rewrite insert_leb in IH; [| apply cons_sorted]; [assumption.. | lia].
      * simpl in IH; rewrite E2 in IH; apply cons_sorted; [exact IH | lia].
Qed.

(** On en déduit que le tri par insertion produit bien une liste triée : *)
Lemma sorted_insertion_sort (l : list nat) : sorted (insertion_sort l).
Proof.
  induction l as [| h t IH].
  - simpl. exact nil_sorted.
  - destruct t as [| h' t'].
    + exact (one_sorted _).
    + simpl. simpl in IH.
      apply sorted_sorted_insert.
      exact IH.
Qed.

(** Malheureusement, cela ne suffit pas à prouver que le tri est correct : il
    faut aussi s'assurer que la liste obtenue est bien une permutation de
    la liste de départ.

    On définit la relation "est une permutation de" de la façon suivante : *)
Inductive Permutation {A : Type} : list A -> list A -> Prop :=
  | perm_nil : Permutation [] []
  | perm_skip (x : A) (l l' : list A) :
      Permutation l l' -> Permutation (x :: l) (x :: l')
  | perm_swap (x y : A) (l : list A) :
      Permutation (y :: x :: l) (x :: y :: l)
  | perm_trans (l l' l'' : list A) :
      Permutation l l' -> Permutation l' l'' -> Permutation l l''.

(** Il n'est pas clair qu'une telle définition est correcte...
    On va montrer un premier exemple de preuve à la main : *)

Lemma Permutation_exple1 :
  Permutation [42; 93; 2] [42; 2; 93].
Proof.
  apply perm_skip.
  exact (perm_swap _ _ _).
Qed.

(** À vous pour le suivant : *)
Lemma Permutation_exple2 : Permutation [93; 42] [93; 42].
Proof.
  apply perm_skip, perm_skip.
  exact perm_nil.
Qed.

(** Un autre exemple, plus délicat, utilisant la transitivité : *)
Lemma Permutation_exple3 : Permutation [93; 42; 1; 2] [42; 93; 2; 1].
Proof.
  (* marche pas : [1; 2] et [2; 1] ne sont pas la même liste : *)
  Fail apply perm_swap.
  (* On va passer par la liste intermédiaire [93; 42; 2; 1] avec la
     transitivité :
     [perm_trans] prend 3 arguments : l, l' et l''
     [apply perm_trans] devine, par unification que
     l = [93; 42; 1; 2]
     et
     l'' = [42; 93; 2; 1]
     mais ne peut pas deviner la liste entre les deux, on va lui donner : *)
  apply (perm_trans _ [93; 42; 2; 1]).
  - (* preuve de Permutation [93; 42; 1; 2] [93; 42; 2; 1] : *)
    apply perm_skip, perm_skip. exact (perm_swap _ _ _).
  - (* preuve de Permutation [93; 42; 2; 1] [42; 93; 2; 1] : *)
    exact (perm_swap _ _ _).
Qed.

(** À vous pour le suivant : *)
Lemma Permutation_exple4 :
  Permutation [2; 42; 93; 1; 2] [2; 93; 42; 2; 1].
Proof.
  apply perm_skip.
  apply (perm_trans _ [42; 93; 2; 1]).
  - apply perm_skip, perm_skip. exact (perm_swap _ _ _).
  - exact (perm_swap _ _ _).
Qed.

(** On peut maintenant prouver que la relation "être une permutation de" est
    réflexive : *)
Lemma Permutation_refl {A : Type} (l : list A) : Permutation l l.
Proof.
  induction l as [| h t IH].
  - exact perm_nil.
  - apply perm_skip; exact IH.
Qed.

(** On revient à notre tri par insertion : *)
Lemma insert_perm (x : nat) (l : list nat) :
  Permutation (x :: l) (insert x l).
Proof.
  induction l as [| h t IH].
  - simpl. apply perm_skip. exact perm_nil.
  - destruct (x <=? h) eqn:E.
    + simpl. rewrite E. exact (Permutation_refl _).
    + simpl. rewrite E.
      apply (perm_trans _ (h :: x :: t)).
      * exact (perm_swap _ _ _).
      * apply perm_skip. exact IH.
Qed.

(** Notre tri par insertion est bien correct : *)
Lemma insertion_sort_perm (l : list nat) :
  Permutation l (insertion_sort l).
Proof.
  induction l as [| h t IH].
  - simpl. exact perm_nil.
  - simpl.
    apply (perm_trans _ (h :: insertion_sort t)).
    + apply perm_skip. exact IH.
    + exact (insert_perm _ _).
Qed.
