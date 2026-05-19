(** * TP2 : Prop *)

(** ** La sorte [Prop] *)

(** On rappelle que les sortes en Rocq sont les types qui servent à typer les
    types *)

Check true. (* : bool, qui est un type *)
Check bool. (* : Set, c'est une sorte *)
Check Set.  (* : Type, c'est une sorte *)

(** Parmi ces sortes, il y en a une en particulier qui sert à faire de la
    logique : le type Prop *)
Check true = false.
Check 2 + 2 = 4.
Check 2 + 2 = 5 -> true = false.

(** Les types qui sont dans Prop sont à interpréter intuitivement comme des
    propositions et les termes de ces types sont des preuves de ces
    propositions. *)

(** Par exemple, si on regarde la proposition True. *)

Print True.

(** C'est un type inductif qui vit dans Prop, ayant un seul constructeur qui
    s'appelle I. *)
Check True. (* : Prop *)
Check I. (* : True *)

(** Comme I est un habitant de [True], c'est une preuve de [True]. *)

Lemma True_True : True.
Proof.
  exact I.
Qed.

(** ** La conjonction *)

(** Le type inductif [and] a deux paramètres de sorte Prop et un constructeur
    qui prend deux arguments : une preuve pour chacun de ses paramètres. *)

Print and.

(** La notation "_ /\ _" est utilisée pour la conjonction. *)
Locate "_ /\ _".
(** Elle est associative à droite et de niveau assez haut 80 (priorité assez
    basse donc) *)
Print Notation "_ /\ _".

(** *** Prouver une conjonction directement *)
(** Ayant connaissance de ce constructeur, on peut écrire directement les
    termes de preuves de "A et B". *)

Lemma exemple_conj (A B : Prop) (hA : A) (hB : B) : A /\ B.
Proof. exact (conj hA hB). Qed.

(** À vous de jouer pour les suivants : *)

Lemma prove_and_exact1 (A B : Prop) (hA : A) (hB : B) : B /\ A.
Proof.
  exact (conj hB hA).
Qed.

(** On se souvient que "_ /\ _" est associatif à droite *)
Lemma prove_and_exact2 (A B : Prop) (hA : A) (hB : B) : A /\ (B /\ (A /\ B)).
Proof.
  exact (conj hA (conj hB (conj hA hB))).
Qed.

(** *** Prouver une conjonction avec [split] *)

(** Lorsque le but est un type inductif à un seul constructeur, la tactique
    [split] applique ce constructeur et crée autant de sous-buts qu'il y a
    d'arguments à ce constructeurs (deux ici).
    Cela évite d'apprendre les noms des constructeurs et permet une vision de
    plus haut niveau, plus proche de la logique usuelle. *)

Lemma exemple_split (A B : Prop) (hA : A) (hB : B) : A /\ B.
Proof.
  split.
  - exact hA.
  - exact hB.
Qed.

Lemma prove_and_split1 (A B : Prop) (hA : A) (hB : B) : B /\ A.
Proof.
  split.
  - exact hB.
  - exact hA.
Qed.

(** Pour les "bullets" qui organisent la preuve en sous-preuve,
    sous-sous-preuve, etc, on peut utiliser + ou * ou ++ lorsqu'on a besoin
    de sous-sous-preuve, etc
    Par exemple :
    - foo.
      + bar.
        * baz.
        * foo.
      + bar.
    - baz.
    L'indentation n'est pas obligatoire mais vivement conseillée.split
*)

Lemma prove_and_split2 (A B : Prop) (hA : A) (hB : B) : A /\ (B /\ (A /\ B)).
Proof.
  split.
  - exact hA.
  - split.
    + exact hB.
    + split.
      * exact hA.
      * exact hB.
Qed.

(** *** Utiliser un "et" avec [match] *)

(** On commence par un exemple. *)
Lemma exemple_and_match (A B : Prop) (h : A /\ B) : B.
Proof.
  exact (
    match h with
    | conj ha hb => hb
    end
  ).
Qed.
(** Quelques variantes tant qu'on y est.
    Si un des arguments du constructeur n'est pas utiliser, c'est une bonne
    pratique de l'indiquer en le défaussant avec _. *)
Lemma exemple_and_match' (A B : Prop) (h : A /\ B) : B.
Proof.
  exact (
    match h with
    | conj _ hb => hb
    end
  ).
Qed.
(** Dans le cas d'un inductif à un seul constructeur, on peut aussi utiliser
    un motif irréfutable (avec let) de cette façon : *)
Lemma exemple_and_match'' (A B : Prop) (h : A /\ B) : B.
Proof.
  exact (let 'conj _ hb := h in hb).
Qed.
(** ou même carrément avec la liste des variables entre parenthèses, séparées
    par des virgules, sans mentionner le constructeur : *)
Lemma exemple_and_match''' (A B : Prop) (h : A /\ B) : B.
Proof.
  exact (let (_, hb) := h in hb).
Qed.

(** Bien sûr, tout ça n'est que du sucre syntaxique, ces termes
    sont bien les mêmes et au bout il y a toujours [match] *)
Set Printing All.
Print exemple_and_match.
Print exemple_and_match'.
Print exemple_and_match''.
Print exemple_and_match'''.
Unset Printing All.

(** Il serait bon de s'exercer à manipuler ces différentes syntaxes dans les
    exercices suivants : *)

Lemma use_and_match1 (A B : Prop) (h : A /\ B) : A.
Proof.
  exact (let (ha, _) := h in ha).
Qed.

Lemma use_and_match2 (A B : Prop) (h : A /\ B) : B /\ A.
Proof.
  exact (let (ha, hb) := h in conj hb ha).
Qed.

Lemma use_and_match3 (A B C : Prop) (h : A /\ (B /\ C)) : (A /\ B) /\ C.
Proof.
  exact (let 'conj ha (conj hb hc) := h in conj (conj ha hb) hc).
Qed.

(** *** Utiliser un "et" avec destruct *)

(** On commence par un exemple. *)
Lemma exemple_and_destruct (A B : Prop) (h : A /\ B) : B.
Proof.
  destruct h as [ha hb].
  exact hb.
Qed.

(** Tant qu'on y est, rappelons que c'est une bonne pratique de défausser les
    arguments non utilisés dans destruct : *)
Lemma exemple_and_destruct' (A B : Prop) (h : A /\ B) : B.
Proof.
  destruct h as [_ hb].
  exact hb.
Qed.

(** Et aussi qu'on peut utiliser des [destruct] imbriqués : *)
Lemma exemple_and_destruct_nested (A B C : Prop) (h : A /\ (B /\ C)) : A.
Proof.
  destruct h as [ha [hb hc]].
  exact ha.
Qed.

(** À vous, cette fois avec destruct : *)
Lemma use_and_destruct1 (A B : Prop) (h : A /\ B) : A.
Proof.
  destruct h as [ha _]. exact ha.
Qed.

Lemma use_and_destruct2 (A B : Prop) (h : A /\ B) : B /\ A.
Proof.
  destruct h as [ha hb]. split.
  - exact hb.
  - exact ha.
Qed.

Lemma use_and_destruct3 (A B C : Prop) (h : A /\ (B /\ C)) : (A /\ B) /\ C.
Proof.
  destruct h as [ha [hb hc]]. split.
  - split.
    + exact ha.
    + exact hb.
  - exact hc.
Qed.

(** ** La disjonction *)

(** Le type inductif [or] a deux paramètres A et B de sorte Prop et
    deux constructeurs :
    le premier, [or_introl] prenant en argument une preuve de A
    le second, [or_intror] prenant en argument une preuve B. *)

Print or.

(** La notation "_ \/ _" est utilisée pour la disjonction. *)
Locate "_ \/ _".
(** Elle est associative à droite et de niveau haut 85 (priorité plus basse que
  le "et". *)
Print Notation "_ \/ _".

(** *** Prouver une disjonction directement *)
(** Ayant connaissance de ces constructeur, on peut écrire directement les
    termes de preuves de "A ou B". *)

Lemma exemple_disj (A B : Prop) (hB : B)  : A \/ B.
Proof. exact (or_intror hB). Qed.

(** À vous de jouer pour les suivants : *)

Lemma prove_or_exact1 (A B : Prop) (hA : A) : A \/ B.
Proof.
  exact (or_introl hA).
Qed.

(** On se souvient que "_ \/ _" est associatif à droite *)
Lemma prove_or_exact2 (A B : Prop) (hA : A) : B \/ (A \/ B).
Proof.
  exact (or_intror (or_introl hA)).
Qed.

(** *** Prouver une conjonction avec [left] ou [right] *)

(** Lorsque le but est un type inductif à deux constructeurs, utiliser la
    tactique [left] (respectivement [right]) revient à dire à Rocq qu'on
    veut construire le terme en utilisant le premier (respectivement le second)
    constructeur.
    Rocq nous demande ensuite de construire les éventuels arguments de ce
    constructeur.

    Vu autrement, pour une preuve de "ou", [left] (respectivement [right])
    déclare qu'on va prouver le "ou" en prouvant l'opérande de gauche
    (respectivement l'opérande de droite).
*)

Lemma exemple_disj_left_right (A B : Prop) (hB : B)  : A \/ B.
Proof. right. exact hB. Qed.

(** À vous de jouer pour les suivants : *)

Lemma prove_or_left_right1 (A B : Prop) (hA : A) : A \/ B.
Proof.
  left. exact hA.
Qed.

(** On se souvient que "_ \/ _" est associatif à droite *)
Lemma prove_or_left_right2 (A B : Prop) (hA : A) : B \/ (A \/ B).
Proof.
  right. left. exact hA.
Qed.

(** *** Utiliser un "ou" avec [match] *)

(** On commence par un exemple. *)
Lemma exemple_or_match (A B : Prop) (h : A \/ A) : A.
Proof.
  exact (
    match h with
    | or_introl h => h
    | or_intror h' => h'
    end
  ).
Qed.

Lemma use_or_match1 (A B : Prop) (h : A \/ B) : B \/ A.
Proof.
  exact (
    match h with
    | or_introl ha => or_intror ha
    | or_intror hb => or_introl hb
    end).
Qed.

Lemma use_or_match2 (A B C : Prop) (h : A \/ (B \/ C)) : (A \/ B) \/ C.
Proof.
  exact (
    match h with
    | or_introl ha => or_introl (or_introl ha)
    | or_intror (or_introl hb) => or_introl (or_intror hb)
    | or_intror (or_intror hc) => or_intror hc
    end).
Qed.

(** *** Utiliser un "ou" avec destruct *)

(** On commence par un exemple. *)
Lemma exemple_or_destruct (A B : Prop) (h : A \/ A) : A.
Proof.
  destruct h as [ha | ha].
  - exact ha.
  - exact ha.
Qed.

(** À vous pour : *)

Lemma use_or_destruct1 (A B : Prop) (h : A \/ B) : B \/ A.
Proof.
  destruct h as [ha | hb].
  - right. exact ha.
  - left. exact hb.
Qed.

(** Pour gagner du temps ici, utilisez un destruct imbriqué.
    En fin de sujet, on vous montre comment prouver ce lemme en une ligne. *)
Lemma use_or_destruct2 (A B C : Prop) (h : A \/ (B \/ C)) : (A \/ B) \/ C.
Proof.
  destruct h as [ha | [hb | hc]].
  - left. left. exact ha.
  - left. right. exact hb.
  - right. exact hc.
Qed.

(** ** Implication (ou fonction) *)

(** *** Utiliser une implication vue comme fonction *)

(** Les implications peuvent être vues comme des fonctions.
    On commence par un exemple. *)

Lemma impl_fun1 (A B : Prop) (ha : A) (h : A -> B) : B.
Proof.
  (* h est de type A -> B *)
  (* ha est de type A *)
  (* donc (h ha) est de type B *)
  exact (h ha).
Qed.

(** À vous pour la suite : *)

Lemma impl_fun2 (A B C : Prop) (ha : A) (hab : A -> B) (hbc : B -> C) : C.
Proof.
  exact (hbc (hab ha)).
Qed.

Lemma impl_fun3 (A B C : Prop) (hb : B) (hbc : B -> C) (hac : A -> C) : C.
Proof.
  exact (hbc hb).
Qed.

(** *** Utiliser une implication avec [apply] *)

(** La tactique [apply f] avec [f : A -> B] commence par :
    - vérifier que le but est bien B
    - remplace le but par A *)

Lemma impl_apply1 (A B : Prop) (ha : A) (h : A -> B) : B.
Proof.
  (* Comme A -> B (d'après h), il suffit de prouver A : *)
  apply h.
  exact ha.
Qed.

(** À vous pour la suite : *)

Lemma impl_apply2 (A B C : Prop) (ha : A) (hab : A -> B) (hbc : B -> C) : C.
Proof.
  apply hbc.
  apply hab.
  exact ha.
Qed.

Lemma impl_apply3 (A B C : Prop) (hb : B) (hbc : B -> C) (hac : A -> C) : C.
Proof.
  apply hbc.
  exact hb.
Qed.

(** *** Prouver une implication directement en définissant une fonction *)

(** Le type A -> B étant le type des fonctions de A vers B, il suffit pour
    prouver A -> B de donner la définition d'une telle fonction. *)
Lemma impl_def1 (A : Prop) : A -> A.
Proof.
  exact (fun (h : A) => h : A).
Qed.

(** On peut se passer des types, ils sont inférés. *)
Lemma impl_def1' (A : Prop) : A -> A.
Proof.
  exact (fun h => h).
Qed.

(** Bien sûr, le nom de la variable n'a aucune importance : *)
Lemma impl_def1'' (A : Prop) : A -> A.
Proof.
  exact (fun foo => foo).
Qed.

(** À vous maintenant, avec seulement un exact : *)
Lemma impl_def2 (A B C : Prop) (hab : A -> B) (hbc : B -> C) : A -> C.
Proof.
  exact (fun h => (hbc (hab h))).
Qed.

Lemma impl_def3 (A B C : Prop) (hab : A -> B) (hac : A -> C) : A -> B /\ C.
Proof.
  exact (fun h => conj (hab h) (hac h)).
Qed.

(** *** Prouver une implication en introduisant une hypothèse *)

(** La tactique [intros] permet d'introduire une nouvelle hypothèse (déclarer
    une variable) dans le contexte de l'état de preuve courant et "mange"
    le début du but. *)

Lemma imp_intros1 (A : Prop) : A -> A.
Proof.
  intros h. (* On suppose (hypothèse h) A) *)
  exact h.
Qed.

(** En fait, après [intros], on est exactement dans la position précédente
    où l'on définissait une fonction, mais à droite de la flèche [=>], et on
    écrit le corps de la fonction en mode tactiques. *)

(** À vous maintenant, en utilisant [intros], [apply] et [exact]. *)
Lemma impl_intros2 (A B C : Prop) (hab : A -> B) (hbc : B -> C) : A -> C.
Proof.
  intros hA.
  apply hbc.
  apply hab.
  exact hA.
Qed.

(** Ici, utiliser la tactique appropriée pour prouver un "et" *)
Lemma impl_intros3 (A B C : Prop) (hab : A -> B) (hac : A -> C) : A -> B /\ C.
Proof.
  intros h. split.
  - apply hab. exact h.
  - apply hac. exact h.
Qed.

(** ** Exercices supplémentaires sur ou, et, implique *)

(** Pour ces exercices, vous êtes libres de travailler en mode "termes" (avec
    exact) ou en mode "tactiques", voire de panacher ou d'alterner les deux. *)

Lemma or_ind (A B C : Prop) (hpr : A -> C) (hqr : B -> C) : A \/ B -> C.
Proof.
  intros [ha | hb].
  - apply hpr. exact ha.
  - apply hqr. exact hb.
Qed.

Lemma weak_peirce (A B : Prop) : ((((A -> B) -> A) -> A) -> B) -> B.
Proof.
  intros h.
  apply h.
  intros h'.
  apply h'.
  intros ha.
  apply h.
  intros _.
  exact ha.
Qed.

(** Quelques remarques pour le lemme suivant :
    - l'associativité de l'opérateur -> est à droite, donc
      A -> B -> C (sans parenthèses) est en fait A -> (B -> C)
    - On peut intros plusieurs hypothèses d'un coup, par exemple avec
      [intros hab hac hbcd.]
*)

Lemma diamond (A B C D : Prop) :
  (A -> B) -> (A -> C) -> (B -> C -> D) -> A -> D.
Proof.
  intros h1 h2 h3 ha.
  apply h3.
  - apply h1. exact ha.
  - apply h2. exact ha.
Qed.

(** ** Les bons tuyaux du TP2 *)

(** *** Utiliser la composition en uniformisant les noms. *)

(** Considérons le lemme (très très ch...enapan) suivant : *)

Lemma chenapan (A : Prop) : A \/ A \/ A \/ A \/ A \/ A -> A.
Proof.
  (* Avec une preuve sans réfléchir, on aboutit à : *)
  intros h.
  destruct h as [h1 | h2].
  - exact h1.
  - destruct h2 as [h3 | h4].
    + exact h3.
    + destruct h4 as [h5 | h6].
      * exact h5.
        (* Je veux mourir... *)
      * destruct h6 as [h6 | h7].
        -- exact h6.
        -- destruct h7 as [h8 | h9].
           ++ exact h8.
           ++ exact h9.
Qed.
(** C'est beaucoup de travail pour quelque chose de si bête.
    On peut faire mieux.
    Pour commencer on va imbriquer les destruct en un seul : *)

Lemma chenapan' (A : Prop) : A \/ A \/ A \/ A \/ A \/ A -> A.
Proof.
  intros h.
  destruct h as [h1 | [h2 | [h3 | [h4 | [h5 | h6]]]]].
  (* Déjà tout est détruit, donc c'est plus rapide.
     Surtout, tout est maintenant au même niveau (ouf !) *)
  - exact h1.
  - exact h2.
  - exact h3.
  - exact h4.
  - exact h5.
  - exact h6.
Qed.

(* Mais tout de même, les 5 lignes de exact...
   Si on y réfléchit :
   - le premier h est destruct (donc n'apparaît plus), on peut s'en servir
     à la place de h1, ça donne :
     [destruct h as [h | [...]].
   - dans la partie après |, il n'y a pas de h non plus car c'est un | !
   - on peut donc utiliser h partout
*)

Lemma chenapan'' (A : Prop) : A \/ A \/ A \/ A \/ A \/ A -> A.
Proof.
  intros h.
  destruct h as [h | [h | [h | [h | [h | h]]]]].
  - exact h.
  - exact h.
  - exact h.
  - exact h.
  - exact h.
  - exact h.
Qed.

(** Maintenant, (exercice) :
    - si ce n'est pas déjà fait, faire la partie du TP1 sur la composition
    - réduire à 1 le nombre de [exact] de la preuve suivante : *)

Lemma chenapan''' (A : Prop) : A \/ A \/ A \/ A \/ A \/ A -> A.
Proof.
  intros h.
  destruct h as [h | [h | [h | [h | [h | h]]]]]; exact h.
Qed.

(** *** Les intro patterns : destruct en même temps qu'intros *)

(** La plupart du temps, on veut utiliser [destruct] immédiatement sur une
    hypothèse.
    Au lieu de :
    intros h. destruct h as [ha hb].
    On peut écrire directement :
    intros [ha hb].
    Idem pour un type à deux constructeurs, etc.
    De plus, ces intro patterns peuvent être imbriqués.
*)

(** Voici un exemple : *)
Lemma exemple_intro_patt (A B C : Prop) : A /\ (B \/ C) -> (A /\ B) \/ (A /\ C).
Proof.
  intros [ha [h | h]].
  - left. split.
    + exact ha.
    + exact h.
  - right. split.
    + exact ha.
    + exact h.
Qed.

(** En utilisant un intro pattern, prouver : *)
Lemma exo_intro_patt1 (A B C : Prop) : A \/ (B /\ C) -> (A \/ B) /\ (A \/ C).
Proof.
  intros [h | [hb hc]]; split.
  - left. exact h.
  - left. exact h.
  - right.
    exact hb.
  - right.
    exact hc.
Qed.

(** *** Application locale de tactiques *)

(** On a vu (et revu ici) la composition des tactiques.
    Parfois on voudrait juste appliquer une petite tactique au premier sous-but
    et une autre au deuxième, etc. Bref, on a des preuves qui se ressemblent
    mais pas totalement.
    Pour traiter ce cas on a l'application locale de tactiques, qui permet
    de sélectionner certains des sous-buts générés pour y appliquer une ou
    plusieurs tactiques.
    Un exemple : *)

Lemma exemple_intro_patt' (A B C : Prop) : A /\ (B \/ C) -> (A /\ B) \/ (A /\ C).
Proof.
  intros [ha [h | h]]; (* j'ai un sous-but ou j'ai A et B et l'autre A et C *)
    [left | right]; (* dans le premier sous-but, left, dans le second, right *)
        split; (* dans les deux split, chaque sous-but se sépare en deux *)
  (* À ce stade j'ai 4 sous-buts, le premier et le troisième sont prouvés par
     ha : *)
        [exact ha | (* vide pour ne rien faire *) | exact ha | (* vide *)].
  - exact h.
  - exact h.
Qed.

(** Reprendre la preuve précédente en enlevant les commentaire et en la
   raccourcissant. Essayer de la faire tenir sur une seule ligne ou presque. *)
Lemma exemple_intro_patt'' (A B C : Prop) : A /\ (B \/ C) -> (A /\ B) \/ (A /\ C).
Proof.
intros [ha [h | h]]; [left | right]; split; [exact ha | exact h | exact ha | exact h].
Qed.

(** Reprenez certaines des preuves un peu longues de ce sujet pour les
    raccourcir avec les intro patterns et l'application locale. *)

(** *** La tactique Assumption *)

(** Souvent, les sous-buts ne diffèrent que par le [exact] final.
    La tactique [assumption] cherche dans le contexte un terme dont le type
    est le but. Si elle le trouve, c'est fini pour ce but. *)

(** Reprenons notre fidèle exemple : *)
Lemma exemple_intro_patt''' (A B C : Prop) : A /\ (B \/ C) -> (A /\ B) \/ (A /\ C).
Proof.
  intros [ha [h | h]]; [left | right]; split.
  - assumption. (* trouve ha *)
  - assumption. (* trouve h *)
  - assumption. (* trouve ha *)
  - assumption. (* trouve h *)
Qed.

(** assumption est une forme très légère d'automatisation *)
(** Maintenant toutes les preuves, ou presque, de ce TP sont faisables en une
    seule ligne.
    Exercice : chercher à raccourcir les preuves écrites en mode "tactiques" de
    ce TP. *)
