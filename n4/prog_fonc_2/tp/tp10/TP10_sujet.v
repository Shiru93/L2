Set Asymmetric Patterns.
Set Structural Injection.
From Corelib Require Import ssreflect.
(* From Coq Require Import ssreflect. *)
From Stdlib Require Import List PeanoNat BinInt Lia String.
(* From Coq Require Import List PeanoNat BinInt Lia String. *)
Import Nat ListNotations.
Open Scope list_scope.
Open Scope bool_scope.

(** * TP10 : Vers les arbres binaires de recherche *)

(** ** Rappels sur les arbres binaires *)

Inductive btree (A : Type) :=
  | emptyTree
  | node (left : btree A) (key : A) (right : btree A).

Arguments emptyTree {A}.
Arguments node {A}.

Open Scope string_scope.

(** Voici quelques exemples d'arbres binaires dont les étiquettes sont des
    chaînes de caractères : *)

Definition exple2 := node emptyTree "foo" (node emptyTree "baz" emptyTree).
Definition exple3 := node (node emptyTree "baz" emptyTree) "foo" emptyTree.

(** [btree] étant un type inductif, on a comme d'habitude le fait que deux
    constructeurs différents ne peuvent être égaux : *)

Lemma exple2_ne_exple3 : exple2 <> exple3.
Proof.
  unfold exple2, exple3.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Pour raccourcir les petits exemples, on définit la fonction [leaf]
    qui associe à une valeur [k] de type [A] un arbre réduit à une seule feuille
    d'étiquette k. *)

(** Remplacer [emptyTree] par une définition convenable : *)
Definition leaf {A : Type} (k : A) :=
  emptyTree.

(** Votre définition devrait passer les tests ci-dessous : *)

Lemma leaf_test1 : leaf 42 = node emptyTree 42 emptyTree.
Proof. reflexivity. Qed.
Lemma leaf_test2 : leaf "foo" = node emptyTree "foo" emptyTree.
Proof. reflexivity. Qed.
Lemma leaf_test3 : exple2 = node emptyTree "foo" (leaf "baz").
Proof. reflexivity. Qed.

(** Utiliser l'injectivité des constructeurs pour prouver : *)
Lemma exple_inj l k r :
  node (leaf 42) 2 r = node l k (leaf 1) ->
  l = leaf 42 /\ k = 2 /\ r = leaf 1.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Définir récursivement la fonction max sur nat (remplacer 0 par votre
    définition : *)

Fixpoint max (n m : nat) :=
  0.

(** Votre fonction devrait passer les tests suivants : *)

Lemma max_test1 : max 42 12 = 42. Proof. reflexivity. Qed.
Lemma max_test2 : max 35 93 = 93. Proof. reflexivity. Qed.
Lemma max_test3 : max 10 10 = 10. Proof. reflexivity. Qed.
Lemma max_test4 : max 0 10 = 10. Proof. reflexivity. Qed.
Lemma max_test5 : max 10 0 = 10. Proof. reflexivity. Qed.

(** Histoire de réviser, une petite propriété assez simple à prouver : *)

Lemma max_diag n : max n n = n.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Maintenant, rappeler la définition de la fonction hauteur. *)

Fixpoint height {A : Type} (t : btree A) :=
  0.

(** Votre fonction doit passer les tests suivants : *)

Lemma height_test1 : height exple2 = 2.
Proof. reflexivity. Qed.
Lemma height_test2 {A : Type} : height (@emptyTree A) = 0.
Proof. reflexivity. Qed.
Lemma height_test3 : height exple3 = 2.
Proof. reflexivity. Qed.
Lemma height_test4 : let eT := emptyTree in
  height (node eT 1 (node eT 1 (node eT 1 (node eT 1 (leaf 1))))) = 5.
Proof. reflexivity. Qed.

(** Ci-dessous, un arbre parfait de hauteur n, d'étiquette k est l'arbre de
    hauteur n dont tous les niveaux sont remplis et tous les sommets sont
    d'étiquette a.
    Remplacer emptyTree par votre définition : *)
Fixpoint perfect {A : Type} (n : nat) (a : A) :=
  emptyTree.

(** Votre fonction doit passer les tests suivants : *)
Lemma perfect_test1 : perfect 0 42 = emptyTree. Proof. reflexivity. Qed.
Lemma perfect_test2 : perfect 2 "foo" =
  node (leaf "foo") "foo" (leaf "foo").
Proof. reflexivity. Qed.
Lemma perfect_test3 : let foo2 := node (leaf "foo") "foo" (leaf "foo") in
  perfect 3 "foo" = node foo2 "foo" foo2.
Proof. reflexivity. Qed.

(** Maintenant on prouve : *)
Lemma height_perfect {A : Type} (n : nat) (a : A) :
  height (perfect n a) = n.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Maintenant, rappeler la définition de la fonction "nombre de sommets". *)
Fixpoint numNodes {A : Type} (t : btree A) :=
  0.

(** Votre fonction devrait passer les tests suivants : *)
Lemma numNodes_test1 {A : Type} : numNodes (@emptyTree A) = 0.
Proof. reflexivity. Qed.
Lemma numNodes_test2 : numNodes exple2 = 2.
Proof. reflexivity. Qed.
Lemma numNodes_test3 : numNodes (perfect 3 "foo") = 7.
Proof. reflexivity. Qed.
Lemma numNodes_test4 : numNodes (node (leaf 3) 42 (node (leaf 2) 31 (leaf 93))) = 5.
Proof. reflexivity. Qed.

(** Pour prouver le lemme suivant, on a besoin de la fonction qui à un naturel
    n associe 2 puissance n.
    Remplacer 0 par votre définition : *)

Fixpoint twoPow n :=
  0.

(** Votre fonction devrait passer les tests suivants : *)
Lemma twoPow_test1 : twoPow 0 = 1. Proof. reflexivity. Qed.
Lemma twoPow_test2 : twoPow 3 = 8. Proof. reflexivity. Qed.
Lemma twoPow_test3 : twoPow 8 = 256. Proof. reflexivity. Qed.

(** Maintenant prouver le lemme suivant en utilisant les deux méthodes suivantes :
    - vite fait bien fait avec [lia].
    - sans [lia], utiliser les réécritures habituelles [add_succ_l], ... *)
Lemma numNodes_perfect (n k : nat) : S (numNodes (perfect n k)) = twoPow n.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** ** "est dans" un arbre binaire de [nat] *)

(** On veut définir une fonction booléenne qui dit
    [true] si un entier naturel apparaît dans un arbre binaire d'entiers
    [false] sinon.

    Pour ça, on ne peut pas utiliser l'égalité usuelle [=], car celle-ci ne
    calcule pas.

    On a besoin d'une égalité booléenne sur nat. *)

(** *** Égalité booléenne sur [nat] : *)

Module NatEqb.

(** Définir ci-dessous la fonction [eqb] qui décide si deux entiers naturels
    sont égaux, ou non. Remplacer [true] par votre définition. *)

Fixpoint eqb (n m : nat) :=
  true.

(** On se donne la notation suivante : *)
Notation "x =? y" := (eqb x y).

(** Votre fonction devrait passer les tests suivants : *)

Lemma eqb_test1 : (4 =? 4) = true. Proof. reflexivity. Qed.
Lemma eqb_test2 : (42 =? 93) = false. Proof. reflexivity. Qed.
Lemma eqb_test3 : (0 =? 93) = false. Proof. reflexivity. Qed.
Lemma eqb_test4 : (93 =? 0) = false. Proof. reflexivity. Qed.
Lemma eqb_test5 : (0 =? 0) = true. Proof. reflexivity. Qed.

End NatEqb.
Open Scope nat_scope.
(** On va montrer la réflexion de [=] dans ce [=?] *)

(** On a besoin de montrer que [eqb] est bien réflexif, vu que c'est la
    définition de [=]. *)

Lemma eqb_refl (n : nat) : n =? n = true.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma eq_eqb (n m : nat) : n = m -> n =? m = true.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Pour l'autre sens, c'est une récurrence, la plus générale possible : *)
Lemma eqb_eq (n m : nat) : n =? m = true -> n = m.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Tant qu'à faire, allons voir les versions négatives : *)

(** Ici, penser à [destruct] le booléen [n =? m] en gardant sa valeur dans
    une équation et prouver que le cas [(n =? m) = true] est impossible *)
Lemma neq_neqb (n m : nat) : n <> m -> n =? m = false.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma neqb_neq (n m : nat) : n =? m = false -> n <> m.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Pour finir sur ces révisions, tout prédicat (dans Prop) qui se réfléchit
    dans une fonction (dans [bool]) est décidable. On le revoit dans le cas
    particulier de l'égalité sur [nat] : *)

(** Indice : raisonner par cas sur la valeur de [n =? m] en gardant sa valeur
    dans une équation : *)
Lemma eq_dec (n m : nat) : n = m \/ n <> m.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Il est aussi intéressant de prouver la symétrie de [eqb].
    Ceci se fait par induction avec une hypothèse d'induction la plus générale
    possible : *)
Lemma eqb_sym n m : (n =? m) = (m =? n).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** *** Retour sur "est dans" *)

(** Définir la fonction isIn ci-dessous qui répond [true] si son premier
    argument (un nat) est une étiquette de son deuxième argument
    (un arbre binaire de nat). Remplacer [true] par votre définition. *)

Fixpoint isIn (needle : nat) (hayStack : btree nat) :=
  true.

(** Votre fonction devrait passer les tests suivants : *)

Lemma isIn_test1 :
  isIn 42 (node (node (leaf 12) 2 (leaf 23)) 12 (node (leaf 42) 1 (leaf 93)))
  = true.
Proof. reflexivity. Qed.
Lemma isIn_test2 :
  isIn 43 (node (node (leaf 12) 2 (leaf 23)) 12 (node (leaf 42) 1 (leaf 93)))
  = false.
Proof. reflexivity. Qed.
Lemma isIn_test3 :
  isIn 2 (perfect 20 2) = true.
Proof. reflexivity. Qed.

(** Mais il y a un petit problème... : *)
Lemma isIn_test4 :
  isIn 2 (perfect 20 1) = false.
Proof. Time reflexivity. Qed.

(** Pour l'instant, nos arbres n'ont aucune structure, ce qui fait qu'un
    calcul bête et méchant comme isIn 2 (perfect 20 1) doit parcourir les
    2^{20} - 1 sommets de l'arbre avant de conclure que non, 2 n'y figure pas.

    On va apporter davantage de structure avec les arbres binaires de recherche.

    Mais d'abord, on aura besoin de terminer l'histoire des ordres sur [nat]
    avec l'ordre strict [<] : *)

(** ** Ordre strict [<] *)

Open Scope nat_scope.

(** On va avoir besoin de l'ordre strict [<] sur [nat].
    Au passage, ça nous fera pas mal de révisions. *)
Print Peano.lt.

(** On a aussi la notation usuelle [<] : *)
About "_ < _".

(** Comme on le voit, [n < m] est synonyme de [S n <= m]. *)

Lemma exple_lt1 : 2 < 3.
Proof.
  unfold "<".
  (** En utilisant les constructeurs le_n et le_S, prouver : *)
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma exple_lt2 : 2 < 6.
Proof.
  unfold "<".
  (** En utilisant les constructeurs le_n et le_S, prouver : *)
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** La fonction booléenne correspondante s'appelle [ltb] et est notée [<?] : *)
Print ltb.
About "<?".

(** Là aussi, [n <? m] est synonyme de [S n <=? m]. *)
Lemma exple_ltb1 : 2 <? 6 = true.
Proof.
  unfold "<?".
  (** Ce qui calcule évidemment, comme pour [leb] : *)
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** L'avantage de ces définitions est qu'on va pouvoir déduire les propriétés
    importantes à partir de celles déjà prouvées sur [le] et [leb]. *)

(** *** Rappels sur [le] et [leb] : *)

(** On se souvient qu'on a les lemmes suivants sur [le] et [leb].
    Si vous ne vous en souvenez plus, c'est le bon moment pour les prouver de
    nouveau, sinon vous pouvez les admettre (ou recopier vos preuves du TP09) *)

Lemma le_le_succ_succ (n m : nat) : n <= m -> S n <= S m.
Proof.
  intros H. induction H as [| p H' IH].
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma leb_refl (n : nat) : n <=? n = true.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma leb_leb_succ_r (n m : nat) : n <=? m = true -> n <=? S m = true.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma le_leb (n m : nat) : n <= m -> n <=? m = true.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma leb_le (n m : nat) : n <=? m = true -> n <= m.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma nleb_nle : forall x y : nat, (x <=? y) = false -> ~ x <= y.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma nle_nleb : forall x y : nat, ~ x <= y -> (x <=? y) = false.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** *** Retour sur [lt] et [ltb] : *)

Lemma ltb_lt (n m : nat) : n <? m = true -> n < m.
Proof.
  unfold "<?", "<".
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma lt_ltb (n m : nat) : n < m -> n <? m = true.
Proof.
  unfold "<?", "<".
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Remarque : pour aller plus vite, on peut utiliser [apply] avec le bon lemme
    directement, sans [intros] ni presque rien.
    C'est un bon exercice (sur papier) d'écrire à la main quelles variables
    seront unifiées par [apply]. *)
Lemma nltb_nlt (n m : nat) : n <? m = false -> ~(n < m).
Proof.
  unfold "<?", "<".
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Vous pouvez aussi commenter la ligne "unfold", et constater que Rocq n'en a
    vraiment pas besoin (mais souvent, les humains, si). *)
Lemma nlt_nltb (n m : nat) : ~(n < m) -> n <? m = false.
Proof.
  unfold "<?", "<".
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** ** Les BST (Binary Search Tree) *)

(** Pour simplifier, on considère des arbres dont les étiquettes sont des
    entiers naturels, et c'est tout, donc pas d'association clé-valeur, juste
    des clés.

    Certaines idées de cette partie, viennent de :
    "Verified Functional Programming", d'Andrew W. Appel
*)

(** Intuitivement, pour nous, un arbre binaire de recherche est :
    - un arbre binaire dont les étiquettes sont dans [nat] tel que :
    - toutes les étiquettes du sous-arbre gauche sont <= à la racine
    - toutes les étiquettes du sous-arbre droit sont >= à la racine
    - le sous-arbre droit et le sous-arbre gauche sont aussi des BST

    et l'arbre vide est un BST.

    Pour formaliser cette définition, on a besoin d'un prédicat "pour tous"
    sur les étiquettes d'un arbre : *)

Inductive ForallT (P : nat -> Prop) : btree nat -> Prop :=
  | ForallET : ForallT P emptyTree
  | ForallN : forall (l : btree nat) (k : nat) (r : btree nat),
      (ForallT P l) -> P k -> (ForallT P r) -> ForallT P (node l k r).

(** Cette propriété est beaucoup moins compliquée qu'elle n'en a l'air :
    - si l'arbre est vide, toute propriété sur ses étiquettes est vraie
    - si la propriété est vérifiée sur l'étiquette de la racine, sur toutes les
      étiquettes de l'arbre gauche et sur toutes les étiquettes de l'arbre droit,
      alors elle est vérifiée pour l'arbre entier *)

(** Quelques exemples pour pratiquer.
    Pour les inégalités ou égalités évidentes (et "linéaires"), utiliser [lia]. *)

(** Ici, utiliser les constructeurs "à la main", on pourra ensuite dans un
    second temps essayer de réduire la preuve (qui n'est certes pas très
    intéressante).

    Pour ceux qui aiment faire du golf sur ce genre de choses :
    la tacticielle "repeat" permet de répéter une tactique "tant qu'elle
    progresse", par exemple, [repeat apply le_S] appliquera le_S tant que
    possible. Il y a aussi la tacticielle [try] qui permet à une tactique de
    ne pas échouer donc de ne s'appliquer qu'à certains sous-buts.
    N'hésitez pas à consulter la documentation officielle ou à questionner votre
    chargé de TP. *)
Lemma ForallT_exple1 :
  ForallT (fun k => k < 10) (node (leaf 9) 3 (node (leaf 2) 8 (leaf 2))).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Et pour gagner du temps : *)
Lemma ForallT_leaf (P : nat -> Prop) (n : nat) :
  P n -> ForallT P (leaf n).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Autre exemple, plus intéressant : *)
Lemma perfectAllEqual (n k : nat) : ForallT (fun x => x = k) (perfect n k).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Encore plus intéressant : *)
Lemma isIn_Forall (P : nat -> Prop) (x : nat) (t : btree nat) :
  ForallT P t -> isIn x t = true -> P x.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Enfin, un lemme bien utile sur l'affaiblissement de la condition : *)
Lemma ForallWeaken (P Q : nat -> Prop) t :
  (forall x, P x -> Q x) -> ForallT P t -> ForallT Q t.
Proof.
  intros HPQ HF. induction HF as [| l k r Hl IHl H Hr IHr].
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Avant de se lancer dans la suite, n'oubliez pas que [lia] est vraiment
    très forte... Voir avec : *)
Lemma lt_total (n m : nat) : n < m \/ n = m \/ m < n.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Allez, on va spécifier les BST maintenant, ici on choisit de donner une
    définition proche de notre définition informelle de tout à l'heure : *)

Inductive BST : btree nat -> Prop :=
  | BSTET : BST emptyTree
  | BSTN (l : btree nat) (k : nat) (r : btree nat) :
      BST l -> BST r ->
      ForallT (fun x => x <= k) l -> ForallT (fun x => k <= x) r ->
      BST (node l k r).

(** Exercice cerveau/papier : se convaincre que cette définition correspond
    à celle donnée informellement au début de cette partie. *)

(** Des exemples : *)

(** Celui-ci fera gagner du temps : *)
Lemma BST_leaf n : BST (leaf n).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma BST_exple1 :
  BST (node (node (leaf 4) 6 (leaf 7)) 8 (node (leaf 41) 42 (leaf 43))).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Bien sûr, c'est long et fastidieux et il y a bien des moyens d'automatiser
    ce genre de raisonnement. Mais pour un premier cours en L2, on n'abordera
    pas ces techniques. Assurez-vous plutôt d'avoir bien compris le rôle de
    [apply] dans votre preuve. *)

(** Voici un exemple pas très intéressant de BST, mais bon, ça fait toujours
    pratiquer...

    Au passage, pour ceux qui seraient passés à côtés, voici comment on
    prouve un résultat intermédiaire dans une preuve : *)

Lemma BST_perfect (n k : nat) : BST (perfect n k).
Proof.
  assert (forall q, ForallT (fun x => x <= k) (perfect q k)) as Hperf. {
  (* Remplacer admit. par votre preuve de ce fait. *)
  admit.
  }
  (** Maintenant, remarquez qu'on a ce nouveau fait Hperf dans le contexte
      local. *)
  (** Allez, idem dans l'autre sens (un copier-coller, faute de mieux, fait
      l'affaire...) *)
  assert (forall q, ForallT (fun x => k <= x) (perfect q k)) as Hperf2. {
  (* Remplacer admit. par votre preuve de ce fait *)
  admit.
  }
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Maintenant, on passe à la recherche dans un BST.
    En supposant que l'arbre binaire donné est un BST, définir la fonction
    isInBST qui dit "rapidement" si un élément donné est dans un arbre binaire
    supposé être un BST.

    Remplacer [true] par votre définition, qui utilisera des opérations
    booléennes sur [nat]. *)

Fixpoint isInBST (needle : nat) (hayStack : btree nat) :=
  true.

Lemma isInBST_test1 :
  isInBST 41 (node (node (leaf 4) 6 (leaf 7)) 8 (node (leaf 41) 42 (leaf 43)))
  = true.
Proof. reflexivity. Qed.

(** Votre fonction devrait passer les tests suivants : *)

Lemma isInBST_test2 :
  isInBST 44 (node (node (leaf 4) 6 (leaf 7)) 8 (node (leaf 41) 42 (leaf 43)))
  = false.
Proof. reflexivity. Qed.

Lemma isInBST_test3 :
  isInBST 2 (perfect 10 2) = true.
Proof. reflexivity. Qed.

(** Alors, alors, moment de vérité : *)
Lemma isInBST_test4 :
  isInBST 2 (perfect 20 1) = false.
Proof. Time reflexivity. Qed.

(** On a gagné ? Pas vraiment encore... Rien ne nous dit que notre fonction
    isInBST donne la même réponse que isIn dans le cas des BST.
    Va-t-on y arriver ? Pas sûr... *)

(** On découpe le gros morceau en petits morceaux plus digestes.
    N'hésitez pas par la suite à :
   - assert des propriétés intermédiaires
   - utiliser la réflexion et lia pour prouver égalités, inégalités et
     diségalités "évidentes".
*)

Lemma isInBST_isInBSTl x l k r :
  BST (node l k r) -> x < k -> isInBST x (node l k r) = isInBST x l.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma isInBST_isInBSTr x l k r :
  BST (node l k r) -> k < x -> isInBST x (node l k r) = isInBST x r.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma orb_true_r (b : bool) : b || true = true.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma orb_false_r (b : bool) : b || false = b.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma BST_isIn_isInl x l k r :
  BST (node l k r) -> x < k -> isIn x (node l k r) = isIn x l.
Proof.
  (** Pour des raisons techniques, on doit se souvenir de la valeur de l'arbre
      [node l k r] avant de détruire l'hypothèse que c'est un BST. *)
  intros H Hxy. remember (node l k r) as t eqn:Et.
  destruct (H) as [| ? ? ? BSTl BSTr Hl Hr].
  - discriminate Et.
  - injection Et.
    (* La tactique suivante utilise toutes les hypothèse de types
       <var> = <terme> ou <terme> = <var> pour remplacer les <var> par les
       <terme>s correspondant partout et supprime ces hypothèses.
       Cela simplifie énormément le contexte local *)
    subst.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma BST_isIn_isInr x l k r :
  BST (node l k r) -> k < x -> isIn x (node l k r) = isIn x r.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma isInBST_correct needle hayStack : BST hayStack ->
  isInBST needle hayStack = isIn needle hayStack.
Proof.
  (** Ici, on met (H) entre parenthèses, pour se souvenir que l'arbre est un
      BST, ça permet de ne pas enlever H du contexte. *)
  intros H. induction (H) as [| l k r BSTl IHl BSTr IHr FAl FAr].
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)

