(** * TP4 : [forall] *)

Set Asymmetric Patterns. (* Rocq, ne nous force pas à mettre des _ qui ne
                            servent à rien pour les paramètres dans les match *)

(** ** Exemples de [forall] *)

(** On commence par des exemples sur les booléens *)

(** On rappelle les définitions du type [bool] et des opérations usuelles sur
    [bool]. *)

Open Scope bool_scope.

Print bool.
Print negb.
Print andb.
Print orb.

(** Pour tout booléen (mais bon, il n'y en a que deux...) [b],
    (negb (negb b)) = b. *)

Lemma negb_negb : forall (b : bool), negb (negb b) = b.
Proof.
  (* On commence la preuve par "Soit b un booléen." *)
  intros b.
  (* Ensuite, comme dans le premier TP, on calcule après avoir fait
     une disjonction de cas. *)
  destruct b as [|]. (* ou juste [destruct b] vu qu'il n'y a rien à nommer *)
  - simpl. reflexivity.
  - simpl. reflexivity.
Qed.

(** Donc finalement, pas de différence avec la flèche [->], si ce n'est
    que derrière un [forall], le type peut dépendre de la variable liée par
    [forall]. *)

(** À vous pour les suivants : *)
Lemma andb_true_l : forall b, true && b = b.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma andb_comm : forall b, forall b', b && b' = b' && b.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma orb_comm : forall b, forall b', b || b' = b' || b.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Comme toujours, avec intros, on peut destruct au moment du intros.
    On n'hésite pas non plus (surtout avec les booléens) à utiliser
    la composition des tactiques. *)

(** Par exemple, le premier exemple peut devenir : *)

Lemma negb_negb' : forall (b : bool), negb (negb b) = b.
Proof.
  intros [|]; simpl; reflexivity.
Qed.

(** Exercice : prouver andb_true et andb_comm en une seule ligne *)

Lemma andb_true_l' : forall b, true && b = b.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma andb_comm' : forall b, forall b', b && b' = b' && b.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Bon, une fois qu'on a vu ça, les preuves sur les booléens ne sont pas très
    intéressantes... *)

(** Voyons simplement comment utiliser un [forall] avec specialize *)

Lemma exemple_idiot_forall : forall foo, foo && true = foo.
Proof.
  intros foo.
  (** On peut évidemment [destruct foo] et conclure par calcul.
      Ici on va utiliser [andb_comm] et [andb_true_l]. *)
  (** On commence par rappeler [andb_comm] et appeler notre copie locale [h]. *)
  specialize andb_comm as h.
  (** On veut utiliser [h] avec notre [foo] et [true] : *)
  specialize (h foo true).
  (** Bien, maintenant on utilise l'égalité [h] pour changer
      [foo && true] en [true && foo] dans le but : *)
  rewrite h.
  (** Toujours pour illustrer l'utilisation des proposition universellement
      quantifiées, allons chercher  [andb_true_l], mais cette fois directement
      avec le bon argument : *)
  specialize (andb_true_l foo) as h'.
  exact h'.
Qed.

(** À vous, sans utiliser [destruct] ni d'intro pattern, prouver avec
    [specialize] et [rewrite] le lemme suivant.
    Remarque : le && est associatif à gauche, donc lorsque Rocq affiche
    [b && true && b'], il faut comprendre [(b && true) && b']. *)
Lemma exo_specialize : forall (b b' : bool), (b && true) && b' = b' && b.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** ** Exemples de "il existe" *)

(** Passons au quantificateur existentiel, en Rocq, il est noté "exists". *)

(** Ceci est bien une proposition *)
Check (exists (b : bool), forall b', b && b' = b').

(** Cette proposition est bien prouvable : *)
Lemma exemple_exists : exists (b : bool), forall b', b && b' = b'.
Proof.
  (** Là il faut trouver soi-même le bon témoin (par quoi remplacer [b]
      pour rendre ce qui est derrière "il existe b" vrai).
      Une intuition géniale me fait penser à [true]. *)
  exists true.
  (** Pour prouver un "il existe", on propose un témoin avec exists.
      Après il faut prouver que ce témoin convient. *)
  exact andb_true_l.
Qed.

(** À vous : *)

Lemma exo_exists : exists (b : bool), forall b', b && b' = false.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma exo_exists2 : exists (b : bool), forall b', b || b' = b'.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Derrière exists, on peut avoir n'importe quel terme, y compris une
    fonction. Vous pouvez ensuite faire une preuve par cas avec [destruct].  *)

Lemma exo_exists3 : exists (f : bool -> bool), forall b, b || f b = true.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Voici maintenant un exemple d'utilisation de [exists] *)

Lemma exemple_utilise_exists :
  exists (f : bool -> bool), forall b, f b || b = true.
Proof.
  (** On peut évidemment le prouver comme exo_exists3, mais voyons
      comment on peut le déduire de cet exercice et de la commutativité
      de [||]. *)
  (** [exo_exists3] est du type "exists truc, P truc".
      Lorsqu'on le [destruct], on obtient deux choses :
      - truc et
      - une preuve de P truc. *)
  destruct exo_exists3 as [f Hf].
  exists f.
  intros mon_petit_booléen.
  specialize (Hf mon_petit_booléen).
  specialize (orb_comm (f mon_petit_booléen) mon_petit_booléen) as h.
  rewrite h.
  exact Hf.
Qed.

(** À vous, sans preuve directe, mais en utilisant les lemmes déjà prouvés
    [exo_exists] et [exo_exists2]. *)

Check exo_exists.
Lemma exo_exists' : exists b, forall b', b' && b = false.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Check exo_exists2.
Lemma exo_exists2' : exists b, forall b', b' || b = b'.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** ** Calcul des prédicats *)

Section Predicats.

(** On quitte le monde tout de même assez réduit des booléens, pour celui
    des prédicats en général. *)

(** Dans toute cette partie, on considère un type quelconque A. *)

Context (A : Type).

(** On suppose donnés deux prédicats sur A, c'est-à-dire deux fonctions
    de A vers [Prop]. *)

Context (P : A -> Prop) (Q : A -> Prop).

(** On s'intéresse aux tautologies (propriétés toujours vraies) du calcul
    des prédicats, qui ne dépendent donc ni du type A, ni des prédicats
    P et Q. *)

(** À vous de les prouver. On en donne toujours deux versions.
    La première est à prouver avec toutes les tactiques vues jusqu'à présent
    (intros, destruct, split, exists, exact, assumption, ...).
    La deuxième, si le coeur vous en dit, est à prouver avec un seul exact.
    En vrai, vous pouvez tricher et faire
    [Print forall_and_and_forall.] après, par exemple, la preuve du lemme
    suivant, mais c'est mieux si vous avez déjà cherché.
    De plus, les termes de preuve écrits à la main sont souvent plus clairs
    et plus petits que ceux écrits avec des tactiques. *)

Lemma forall_and_and_forall :
  (forall x, P x /\ Q x) -> (forall x, P x) /\ (forall x, Q x).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma forall_and_and_forall' :
  (forall x, P x /\ Q x) -> (forall x, P x) /\ (forall x, Q x).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma and_forall_forall_and :
  (forall x, P x) /\ (forall x, Q x) -> forall x, P x /\ Q x.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma and_forall_forall_and' :
  (forall x, P x) /\ (forall x, Q x) -> forall x, P x /\ Q x.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma or_forall_forall_or :
  (forall x, P x) \/ (forall x, Q x) -> (forall x, P x \/ Q x).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma or_forall_forall_or' :
  (forall x, P x) \/ (forall x, Q x) -> (forall x, P x \/ Q x).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma or_exists_exists_or :
  (exists x, P x) \/ (exists x, Q x) -> exists x, P x \/ Q x.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Pour écrire à la main un terme de preuve pour prouver "il existe", il faut
    commencer par s'intéresser à ce qu'il recouvre. *)

Locate "exists".

(** [exists] est une notation derrière laquelle il y a la proposition inductive
    [ex] : *)

Print ex.

(** On voit que [ex] a deux paramètres, le premier est un type et le deuxième
    un prédicat.
    Il y a un seul constructeur qui s'appelle [ex_intro]. *)

About ex_intro.

(** L'argument A (dans [Type]) est implicite, déduit à partir de P. *)

Check (ex_intro P).

(** Pour prouver (ex_intro P), il faut fournir un élément x de A et une preuve
    de (P x). *)

(** Ce qui est un peu plus dur ici, c'est d'écrire soi-même le prédicat
    dans [ex_intro].
    Ici, ce sera (fun x => P x \/ Q x).
    Pour utiliser une preuve donnée par [ex_intro], c'est plus simple,
    directement dans le pattern matching. *)
Lemma or_exists_exists_or' :
  (exists x, P x) \/ (exists x, Q x) -> exists x, P x \/ Q x.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma exists_or_or_exists :
  (exists x, P x \/ Q x) -> (exists x, P x) \/ (exists x, Q x).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Un peu moins dur mais pas si évident, ne pas hésiter non plus à le passer
    en première lecture. *)
Lemma exists_or_or_exists' :
  (exists x, P x \/ Q x) -> (exists x, P x) \/ (exists x, Q x).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)

