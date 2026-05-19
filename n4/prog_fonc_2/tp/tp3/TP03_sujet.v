(** * TP3 : [False] et la négation *)

(** [False] *)

(** La proposition [False] est définie comme un type inductif vide (sans
    constructeur) : *)

Print False.

(** Par conséquent, l'existence d'un terme de type [False] est impossible,
    contradictoire, cela met fin à toute preuve : *)

Lemma exfalso_quod_libet (A : Prop) : False -> A.
Proof.
  intros h.
  destruct h.
Qed.

(** On peut même utiliser un intro pattern (vide) pour terminer la preuve : *)
Lemma exfalso_quod_libet' (A : Prop) : False -> A.
Proof.
  intros [].
Qed.

(** À vous, juste pour rigoler... *)

Lemma foo1 (A B : Prop) : False -> A -> B.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma foo2 (A B : Prop) : A -> False -> B -> (A -> A) -> B /\ A.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Un peu plus difficile, utiliser les hypothèses pour créer un terme de type
    [False] à détruire : *)
Lemma foo3 (A B : Prop) : A -> (A -> False) -> B.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Comme le faux entraîne n'importe quoi, on peut toujours choisir (mais c'est
    un choix très important !) d'appliquer le lemme [exfalso_quod_libet]
    pour prouver n'importe quel but.

    Pour l'exemple précédent, ça donne : *)
Lemma exemple_exfalso1 (A B : Prop) : A -> (A -> False) -> B.
Proof.
  intros hA hnA.
  apply (exfalso_quod_libet B).
  apply hnA.
  exact hA.
Qed.

(** Mais c'est un peu long à taper, alors il y a une tactique qui fait justement
    ça : remplacer le but par [False] *)
Lemma exemple_exfalso2 (A B : Prop) : A -> (A -> False) -> B.
Proof.
  intros hA hnA.
  exfalso.
  apply hnA.
  exact hA.
Qed.

(** Comme toujours, lorsqu'on vient de rencontrer une nouvelle tactique, prendre
    des notes. *)

(** À vous pour les suivants : *)
Lemma exo_exfalso1 (A B C : Prop) : A -> (A -> B -> False) -> B -> C.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** À vous pour les suivants : *)
Lemma exo_exfalso2 (A B C : Prop) : A \/ B -> (A -> False) -> (B -> False) -> C.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)

(** ** La négation *)

(** En Rocq, mais aussi en logique intuitionniste, la négation d'une proposition
    [A] est la proposition [A -> False] (A entraîne une contradiction).
    En Rocq, elle est notée [~A]. *)

Locate "~".
Print not.
Print Notation "~ _". (* at level 75, donc plus prioritaire que /\ et \/ *)

(** On peut vouloir "déplier" une notation ou une définition, c'est-à-dire
    la remplacer par sa définition : on peut le faire avec [unfold] : *)

Lemma exemple_not_1 (A B : Prop) : ~ A -> A -> B.
Proof.
  unfold not.
  intros hnA hA; exfalso; apply hnA; exact hA.
Qed.

(** Même chose avec unfold "~" : *)
Lemma exemple_not_2 (A B : Prop) : ~ A -> A -> B.
Proof.
  unfold "~ _".
  intros hnA hA; exfalso; apply hnA; exact hA.
Qed.

(** Mais en vrai, on n'est pas du tout obligé de déplier si c'est clair dans
    notre tête que [~A] est [A -> False]. *)
Lemma exemple_not_3 (A B : Prop) : ~ A -> A -> B.
Proof.
  intros hnA hA; exfalso; apply hnA; exact hA.
Qed.

(** C'est parti pour une myriade d'exercices, à faire avec [unfold] ou non,
    [exfalso] ou non, ... comme vous préférez. *)

Lemma not_ex1 (A : Prop) : ~ (A /\ ~ A).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma not_ex2 (A B : Prop) : A \/ B -> ~ A -> B.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma not_ex3 (A B : Prop) : (A -> B) -> (~ B -> ~ A).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma DeMorgan1 (A B : Prop) : ~ (A \/ B) -> ~ A /\ ~ B.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma DeMorgan2 (A B : Prop) : ~ A /\ ~ B -> ~ (A \/ B).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma DeMorgan3 (A B : Prop) : ~ A \/ ~ B -> ~ (A /\ B).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** ** Un éliminateur pour False *)

(** Il est sans doute trop tôt pour écrire des termes de preuves qui utilisent
    un terme de type [False] (cela nécessite une connaissance fine de [match]).
    Mais on peut admettre l'existence d'une fonction appelée [False_ind],
    qui a précisément le type : [forall (P : Prop), False -> P], autrement dit,
    si [P : Prop] et [h : False], alors [False_ind P h : P].
    On peut s'en servir pour écrire des termes de preuve à la main. *)

Check False_ind.
(** Pour les plus curieux, [False_ind] est défini comme toujours avec un
    (certes étrange) pattern matching (voir partie bonus ou, peut-être, plus
    tard dans le cours). *)
Print False_ind.

(** Mais pour l'instant, son type est tout ce qui nous importe. *)

Lemma exemple_False_ind1 (A B : Prop) : A -> ~ A -> B.
Proof.
  exact (fun hA hnA => False_ind B (hnA hA)).
Qed.

(** Exercice : prendre une feuille de papier et noter les types de [hA], [hnA],
    [(hnA hA)], pour vérifier que le terme écrit est bien du bon type. *)

(** Maintenant prouver avec uniquement exact (et en admettant [False_ind]) : *)

Lemma False_ind_ex1 (A B : Prop) : (A /\ ~ A) -> B.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


Lemma False_ind_ex2 (A B : Prop) : A \/ B -> ~ A -> B.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** ** Logique classique *)

(** Il ne vous aura peut-être pas échappé qu'on a prouvé que 3 lois de De
    Morgan. La dernière n'est pas prouvable dans la logique de Rocq sans
    axiome supplémentaire. *)

Lemma DeMorgan4 (A B : Prop) : ~ (A /\ B) -> ~ A \/ ~ B.
Proof.
  intros H.
  (* et ?? left ? right ? aucun moyen d'avancer... *)
Abort.

(** On dit qu'une proposition [A] satisfait "le principe du tiers exclu" (en
    anglais "law of excluded middle") lorsqu'on a [A \/ ~ A]. *)
(** Là vous vous dîtes : mais qu'est-ce qu'on me raconte, évidemment qu'on
    a toujours A \/ ~ A...
    Pourquoi pas, d'ailleurs, on peut l'ajouter comme axiome dans Rocq sans
    introduire d'incohérence. Mais par ailleurs, on y perd une propriété
    importante : les preuves ne sont plus toutes des programmes complets,
    certaines utilisent le programme "magique" qui prouve que pour toute
    proposition [A], [A \/ ~ A].

    Ceci dit, pour de nombreuses propositions, on peut prouver (sans axiome)
    qu'elles vérifient le tiers exclu. *)

(** On appelle lem A la propriété du tiers exclu pour A : *)
Definition lem A := A \/ ~ A.

(** On va voir que pour prouver la dernière loi de De Morgan, on a juste besoin
    d'une preuve de lem A. *)
Lemma DeMorgan4 (A B : Prop) : lem A -> ~ (A /\ B) -> ~ A \/ ~ B.
Proof.
  unfold lem.
  intros hA hAB.
  destruct hA as [hA | hnA].
  - (* Si A est vrai, B doit être faux : *)
    right.
    intros hB.
    apply hAB. split.
    + exact hA.
    + exact hB.
  - left. exact hnA.
Qed.

(** À vous pour, sans regarder la preuve précédente, vous convaincre que tout
    marche aussi si on suppose qu'on a [lem B] : *)

Lemma DeMorgan4' (A B : Prop) : lem B -> ~ (A /\ B) -> ~ A \/ ~ B.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Une autre propriété à laquelle on est habituée est l'élimination de la
    double-négation, qu'on appellera dne (double negation elimination) : *)

Definition dne A := ~~A -> A.

(** Eh bien c'est une conséquence du tiers exclus : *)

Lemma lem_impl_dne (A : Prop) : lem A -> dne A.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Ici, on va voir que "l'implication classique" comme vue en cours de
    mathématiques est valable lorsque sa prémisse satisfait lem : *)

Lemma lem_impl_classical_imp (A B : Prop) : lem A -> (A -> B) -> (B \/ ~ A).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** C'est aussi vrai si la conclusion satisfait lem : *)
Lemma lem_impl_classical_imp' (A B : Prop) : lem B -> (A -> B) -> (B \/ ~ A).
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)


(** Le tiers exclu est aussi une conséquence de dne mais pas pour la
    même proposition : *)

(** Pour le montrer, c'est plus agréable de connaître la tactique [apply ... in]
    dont voici des exemples : *)
Lemma exemple_apply_in (A B : Prop) : ~ (A \/ B) -> ~ A.
Proof.
  intros h.
  (* [h] a pour type ~ (A \/ B)
     (DeMorgan1 A B) a pour type [~ (A \/ B) -> ~ A /\ ~ B] *)
  Check (DeMorgan1 A B).
  (* Donc [DeMorgan1 A B h] a pour type ~ A /\ ~ B, on va appliquer
     [DeMorgan1 A B] à l'hypothèse [h] pour en déduire que [~ A /\ ~ B]. *)
  apply (DeMorgan1 A B) in h as h'.
  destruct h' as [hnA _]; exact hnA.
Qed.

(** En vous servant du lemme précédent comme indice, prouver : *)

Lemma dne_impl_lem (A : Prop) : dne (lem A) -> lem A.
Proof.
  (* Remplir la preuve ici *)
Admitted. (* Remplacer cette ligne par Qed. *)

