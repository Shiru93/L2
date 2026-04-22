(** * TP1 : booléens, match destruct *)

(** ** Booléens *)

(** On se place dans un module pour "ranger" toutes les définitions sur les
    booléens sous un même espace de nom.
    On verra les modules plus en détail plus tard. *)

Module Bool.

(** Les booléens de Rocq ne sont pas primitifs. Ils sont définis comme un type
    à deux élements (nécessairement distincts) : true et false. *)
Inductive bool := true | false.

(** On définit le et logique entre deux booléens par filtrage par motifs
    (pattern matching) sur le premier argument. *)
Definition andb (b1 b2 : bool) : bool :=
  match b1 with
  | true => b2 (* andb_true_l *)
  | false => false (* andb_false_l *)
  end.

(** Cette définition est un programme, qui permet de calculer : *)
Compute (andb true (andb false true)).

(** On utilise la notation infixe [&&] pour [andb]. *)
Notation "b1 && b2" := (andb b1 b2) : bool_scope.
(** Pour utiliser les notations de bool_scope, comme &&, on doit utiliser
    la commande suivante : *)
Open Scope bool_scope.

(** Il n'est pas nécessaire de maîtriser le système de notations de Rocq dans
    ce cours.
    Cependant, il y a deux choses importantes pour les opérateurs binaires :
    le niveau (pour la priorité des opérateurs) et l'associativité.
    Pour [&&], c'est déjà fixé : *)
Print Notation "_ && _".

(** Ici, l'associativité est à gauche, cela signifie que
    b1 && b2 && b3 est une notation pour (andb (andb b1 b2) b3) : *)
Set Printing All.
Check (true && false && true).
Unset Printing All.

(** On va déjà prouver quelques lemmes simples sur [andb] : *)

Lemma andb_true_l (b : bool) : true && b = b.
Proof.
  simpl. (* on calcule tant qu'on peut *)
  reflexivity. (* b = b, la preuve est terminée *)
Qed.

(** À vous pour la preuve aussi très simple de : *)
Lemma andb_false_l (b : bool) : false && b = false.
Proof.
  (* Remplir la preuve ici *)
  simpl. (* on calcule tant qu'on peut *)
  reflexivity. (* peu importe b, le résultat sera false *)
Qed. (* Remplacer cette ligne par Qed. *)


(** On veut maintenant prouver : *)
Lemma andb_true_r (b : bool) : b && true = b.
Proof.
  (* On tente de calculer : *)
  simpl.
  (* Aïe, on n'arrive à rien par calcul. *)
  (* On doit faire une preuve par cas. *)
  destruct b.
  - (* b = true *)
    simpl.
    reflexivity.
  - (* b = false *)
    simpl.
    reflexivity.
Qed.

(** À vous maintenant pour : *)
Lemma andb_false_r (b : bool) : b && false = false.
Proof.
  (* Remplir la preuve ici *)
  simpl.
  destruct b.
  - (* b = true *)
  simpl.
  reflexivity.
  - (* b = false *)
  simpl.
  reflexivity.
Qed. (* Remplacer cette ligne par Qed. *)


(** On définit maintenant la négation booléenne : *)
Definition negb (b : bool) : bool :=
  match b with
  | true => false (* negb_false *)
  | false => true (* negb_true *)
  end.

Notation "! b" := (negb b) (at level 35) : bool_scope.
(** Remarque : la notation [! b] au niveau 35 est plus prioritaire que
    [b1 && b2] (au niveau 40).
    Donc, [!true && false] signifie [(!true) && false]. *)
Compute !(true && true) && (!false && true).

(** Prouvons immédiatement : *)
Lemma negb_true : !true = false.
Proof.
  (* Remplir la preuve ici *)
  simpl.
  reflexivity.
Qed. (* Remplacer cette ligne par Qed. *)


Lemma negb_false : !false = true.
Proof.
  (* Remplir la preuve ici *)
  simpl.
  reflexivity.
Qed. (* Remplacer cette ligne par Qed. *)


Lemma negb_negb (b : bool) : negb (negb b) = b.
Proof.
  (* Remplir la preuve ici *)
  simpl.
  destruct b.
  - (* b = true *)
  simpl.
  reflexivity.
  - (* b = false *)
  simpl.
  reflexivity.
Qed. (* Remplacer cette ligne par Qed. *)


Lemma andb_assoc (b1 b2 b3 : bool) :
  b1 && (b2 && b3) = (b1 && b2) && b3.
Proof.
  (* Remplir la preuve ici *)
  destruct b1.
  - (* b1 = true *)
  simpl.
  reflexivity.
  - (* b1 = false *)
  simpl.
  reflexivity.
Qed. (* Remplacer cette ligne par Qed. *)


(** Passons à la commutativité. Avec juste ce qu'on a montré précédemment, c'est
    un peu long pour une propriété si simple... *)
Lemma andb_comm (b1 b2 : bool) :
  b1 && b2 = b2 && b1.
Proof.
  destruct b1.
  - (* Cas 1 : b1 = true *)
    destruct b2.
    + (* Cas 1.1 : b2 = true *)
      simpl.
      reflexivity.
    + (* Cas 1.2 : b2 = false *)
      simpl.
      reflexivity.
  - (* Cas 2 : b1 = false *)
    destruct b2.
    + (* Cas 2.1 : b2 = true *)
      simpl.
      reflexivity.
    + (* Cas 2.2 : b2 = false *)
      simpl.
      reflexivity.
Qed.

(** C'est pas génial... on répète beaucoup trop de choses.
    On va voir deux façons de faire mieux. *)

Lemma andb_comm' (b1 b2 : bool) :
  b1 && b2 = b2 && b1.
Proof.
  (* D'abord, on peut demander à Rocq de détruire b1 puis b2 dans un seul
     [destruct]. *)
  destruct b1, b2.
  (* On a maintenant 4 cas. *)
  - simpl. reflexivity.
  - simpl. reflexivity.
  - simpl. reflexivity.
  - simpl. reflexivity.
Qed.

(** Mais il reste encore beaucoup trop de duplication.
    Dans pareil cas, on utilise l'opérateur de composition entre tactiques
    [;].
    Dans une preuve, [tac1; tac2.] applique la tactique [tac2] à chaque
    sous-but engendré par tac1. *)
Lemma andb_comm'' (b1 b2 : bool) :
  b1 && b2 = b2 && b1.
Proof.
  destruct b1, b2; simpl.
  (* On a utilisé [simpl] dans les 4 sous-buts *)
  - reflexivity.
  - reflexivity.
  - reflexivity.
  - reflexivity.
Qed.

(** C'est déjà mieux, mais on peut enchaîner les compositions de tactiques : *)
Lemma andb_comm''' (b1 b2 : bool) :
  b1 && b2 = b2 && b1.
Proof.
  destruct b1, b2; simpl; reflexivity.
Qed.

(** Exercice : simplifiez certaines de vos preuves précédentes en utilisant
    la composition de tactiques. *)

(** La brutalité de [destruct b1, b2; simpl; reflexivity] a ses bons côtés.
    Mais on verra à la fin de ce sujet que pour des types plus compliqués, ou
    plus de variables, ce n'est pas tenable en terme de complexité. *)

(** On peut utiliser des résultats déjà prouvés. Pour le moment, voyons
    [rewrite] pour changer un terme en un autre dans le but. *)

Lemma andb_comm_encore (b1 b2 : bool) :
  b1 && b2 = b2 && b1.
Proof.
  destruct b1.
  - simpl.
    (* J'ai déjà un lemme qui dit que [b2 && true = b2] : *)
    Check andb_true_r.
    (* Je peux le spécialiser en b2, il aura le type : *)
    Check (andb_true_r b2).
    (* Je regarde l'égalité de gauche à droite.
       Je remplace tous les termes du but qui correspondent à la partie gauche
       par la partie droite : *)
    rewrite (andb_true_r b2).
    reflexivity.
  - simpl.
    (** Ici on va se servir de : *)
    Check andb_false_r.
    (** À vous de terminer la preuve en utilisant [rewrite]. *)
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Pour vous entraîner, prouvez de nouveau andb_assoc, mais sans utiliser
    [simpl], uniquement [rewrite].
    Pour se faire on peut utiliser : *)

Check andb_true_l.
Check andb_true_r.
Check andb_false_l.
Check andb_false_r.

Lemma andb_assoc' (b1 b2 b3 : bool) : b1 && (b2 && b3) = (b1 && b2) && b3.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Encore une fois, mais avec [negb_negb] en utilisant [rewrite] avec : *)

Check negb_true.
Check negb_false.

Lemma negb_negb' (b : bool) : negb (negb b) = b.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** On revient (une dernière fois) sur [andb_assoc].
    Il est très utile et important de savoir spécialiser les lemmes d'égalités
    pour les utiliser avec [rewrite].
    Cependant ça peut être assez long de taper tous les termes, alors que la
    plupart du temps, il n'y a que peu d'endroits où la règle s'applique,
    et Rocq peut le deviner. *)

Lemma andb_assoc'' (b1 b2 b3 : bool) : b1 && (b2 && b3) = (b1 && b2) && b3.
Proof.
  destruct b1.
  - (** On veut utiliser andb_true_l dont le type est : *)
    Check andb_true_l.
    (** Ici, le membre gauche de l'égalité est [true && _], où _ sera remplacé
        par l'argument donné au lemme [andb_true_l].
        Que se passe-t-il si on demande à Rocq de deviner lui-même ce trou ? *)
    rewrite (andb_true_l _).
    (** Rocq a choisi le premier endroit (de gauche à droite) où il pouvait
        appliquer cette règle, donc ici a utilisé l'égalité
        [andb_true_l (b2 && b3)]. *)
    (** On peut même omettre les [_] pour ces [rewrite] :*)
    rewrite andb_true_l. (* Ici pas le choix, de toute façon. *)
    reflexivity.
  - (* Terminer la preuve avec des [rewrite], en laissant Rocq unifier *)
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** On considère maintenant le lemme (idiot) suivant.
    Avec une preuve brutale qui examine tous les cas, combien y a-t-il de cas ?
    Écrire cette preuve en une ligne.
    Puis écrire la commande [Time] juste avant pour voir le temps pris par
    Rocq pour terminer cette preuve, comme dans
    [Time foo; bar; baz.]

    Faire de même avec une preuve immédiate qui utilise rewrite et l'unification
    de Rocq. On rappelle que les parenthèses cachées sont à gauche pour [&&].
*)
Lemma foo1 (b1 b2 b3 b4 b5 b6 b7 b8 : bool) :
  b1 && b2 && b3 && b4 && b5 && b6 && b7 && b8 && false = false.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** À vous maintenant de définir [orb] : remplacez [true] par votre définition.
*)
Definition orb (b1 b2 : bool) :=
  true.

(** Comme précédemment, on se donne une notation infixe usuelle. *)
Notation "b1 || b2" := (orb b1 b2) : bool_scope.
(** Elle est aussi associative à gauche et est moins prioritaire que [&&] *)
Print Notation "_ || _".

(** Prouvez les résultats suivants, par études de cas sur [b1].
    Vous pouvez utiliser [negb_negb]. *)
Lemma not_andb_not_not (b1 b2 : bool) :
  !(!b1 && !b2) = b1 || b2.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma andb_orb_distr_l (b1 b2 b3 : bool) :
  b1 && (b2 || b3) = (b1 && b2) || (b1 && b3).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma orb_andb_distr_l (b1 b2 b3 : bool) :
  b1 || (b2 && b3) = (b1 || b2) && (b1 || b3).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Définir [xorb] (ou exclusif booléen) en remplaçant [true] par votre
    définition. *)
Definition xorb (b1 b2 : bool) :=
  true

(** A-t-on besoin d'une preuve par cas ici ? *)
Lemma xorb_false_l (b : bool) :
  xorb false b = b.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Et là ? *)
Lemma xorb_false_r (b : bool) :
  xorb b false = b.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Définir [eqb], l'égalité booléenne entre deux booléens, en remplaçant [true]
    par votre définition. *)
Definition eqb (b1 b2 : bool) :=
  true

(** Définir [implb], l'implication booléenne entre deux booléens, en remplaçant
    [true] par votre définition. *)
Definition implb (b1 b2 : bool) :=
  true

(** Terminer l'énoncé du lemme en remplaçant [true] par [op b1 b2], où
    [op] est l'un des opérateurs booléens définis dans ce sujet,
    puis prouver ce lemme. *)
Lemma implb_andb_implb (b1 b2 : bool) :
  (implb b1 b2) && (implb b2 b1) =
  true.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)

End Bool.

Module Ternary.
(** Dans ce module, on s'intéresse à la logique à trois états :
    - [truet] pour vrai
    - [falset] pour faux
    - [unknownt] pour inconnu *)
Declare Scope ternary_scope.
Delimit Scope ternary_scope with ternary.
Open Scope ternary_scope.

Inductive ternary := truet | falset | unknownt.

(** À vous de définir convenablement la négation, le et logique et le ou logique
    pour ce nouveau type. *)
Definition negt (t1 t2 : ternary) :=
  truet.

Definition andt (t1 t2 : ternary) :=
  truet.

Definition ort (t1 t2 : ternary) :=
  truet.

(** On peut, en Rocq réutiliser une notation dans un autre "scope" (une portée,
    en français). *)
Notation "t1 && t2" := (andt t1 t2) : ternary_scope.
Notation "t1 || t2" := (ort t1 t2) : ternary_scope.
Notation "! t" := (negt t) (at level 35) : ternary_scope.

(** Prouvez les résultats suivants avec des preuves par cas, mais en essayant
    de ne pas trop multiplier les cas et d'utiliser (avec [rewrite]) des
    énoncé déjà prouvés. *)
Lemma andt_truet_l (t : ternary) :
  truet && t = t.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma andt_truet_r (t : ternary) :
  t && truet = t.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma andt_falset_l (t : ternary) :
  falset && t = falset.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma andt_falset_r (t : ternary) :
  t && falset = falset.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma andt_assoc (t1 t2 t3 : ternary) :
  t1 && (t2 && t3) = (t1 && t2) && t3.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma andt_comm (t1 t2 : ternary) :
  t1 && t2 = t2 && t1.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** On considère maintenant le lemme idiot suivant.
    Avec une preuve brutale qui examine tous les cas, combien y a-t-il de cas ?
    Écrire cette preuve brutale en une ligne et la chronométrer.

    Faire de même avec une preuve immédiate qui utilise rewrite.
*)
Lemma foo (t1 t2 t3 t4 t5 t6 t7 t8 t9 : ternary) :
  t1 && t2 && t3 && t4 && t5 && t6 && t7 && t8 && falset = falset.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)

End Ternary.
