# Correction — PF2 Partiel 2
> Programmation Fonctionnelle 2 — mai 2026 — Pierre Rousselin  
> Université Sorbonne Paris Nord

---

## Exercice 1 — Preuves de logique des propositions (12 pts)

> Pour chaque lemme : terme de preuve direct (`exact`), preuve avec tactiques, arbre de dérivation.

---

### 1. `Lemma ex1_1 : A /\ (B \/ C) -> (A /\ B) \/ (A /\ C)` *(4 pts)*

**Terme de preuve :**
```coq
exact (fun h =>
  match h with conj hA hBC =>
    match hBC with
    | or_introl hB => or_introl (conj hA hB)
    | or_intror hC => or_intror (conj hA hC)
    end
  end).
```

**Avec tactiques :**
```coq
Proof.
  intros [hA [hB | hC]].
  - left.  split. exact hA. exact hB.
  - right. split. exact hA. exact hC.
Qed.
```

**Arbre de dérivation :**
```
[hA:A] [hB:B]                    [hA:A] [hC:C]
────────────── (∧I)              ────────────── (∧I)
   ⊢ A ∧ B                          ⊢ A ∧ C
──────────────────── (∨I-g)     ──────────────────── (∨I-d)
⊢ (A∧B) ∨ (A∧C)                ⊢ (A∧B) ∨ (A∧C)
─────────────────────────────────────────────────── (∨E sur hBC : B∨C)
         hA:A, hBC:B∨C ⊢ (A∧B) ∨ (A∧C)
         ────────────────────────────── (∧E sur h)
         h : A∧(B∨C) ⊢ (A∧B) ∨ (A∧C)
         ────────────────────────────── (→I)
         ⊢ A∧(B∨C) → (A∧B) ∨ (A∧C)
```

---

### 2. `Lemma ex1_2 : (A /\ B -> C) -> A -> B -> C` *(4 pts)*

**Terme de preuve :**
```coq
exact (fun h hA hB => h (conj hA hB)).
```

**Avec tactiques :**
```coq
Proof.
  intros h hA hB.
  apply h.
  split. exact hA. exact hB.
Qed.
```

**Arbre de dérivation :**
```
[hA:A]  [hB:B]
────────────── (∧I)    [h : A∧B → C]
    ⊢ A ∧ B
──────────────────────────────────── (→E)
                ⊢ C
────────────────────────────────────── (→I ×3)
⊢ (A∧B → C) → A → B → C
```

---

### 3. `Lemma ex1_3 : A \/ B -> ~ A -> B` *(4 pts)*

> On utilise `False_ind : forall (P : Prop), False -> P`

**Terme de preuve :**
```coq
exact (fun h hna =>
  match h with
  | or_introl hA => False_ind B (hna hA)
  | or_intror hB => hB
  end).
```

**Avec tactiques :**
```coq
Proof.
  intros [hA | hB] hna.
  - exfalso. apply hna. exact hA.
  - exact hB.
Qed.
```

**Arbre de dérivation :**
```
[hA:A]  [hna:¬A]                    [hB:B]
──────────────── (→E)               ────── (Ax)
  ⊢ False                             ⊢ B
──────────────── (exfalso)
  ⊢ B
──────────────────────────────────────────── (∨E sur h : A∨B)
      h:A∨B, hna:¬A ⊢ B
      ──────────────────────── (→I ×2)
      ⊢ A∨B → ¬A → B
```

---

## Exercice 2 — Arbres binaires non vides `nebtree` (13 pts)

Type utilisé dans tout l'exercice :
```coq
Inductive nebtree (A : Type) :=
  | leaf  (key : A)
  | unode (key : A) (child : nebtree A)
  | bnode (left : nebtree A) (key : A) (right : nebtree A).
Arguments leaf {A}. Arguments unode {A}. Arguments bnode {A}.
```

---

### 1. Définition de `exple_1` *(1 pt)*

L'arbre donné (étiquettes dans `nat`) :
```
        42
       /   \
      12    1
      |    / \
      10  2   3
      |
      20
```

```coq
Definition exple_1 :=
  bnode
    (unode 12 (unode 10 (leaf 20)))
    42
    (bnode (leaf 2) 1 (leaf 3)).
```

---

### 2. Représentation graphique de `exple2` *(1 pt)*

```coq
Definition exple2 :=
  bnode (bnode (leaf "rofl") "lol" (leaf "xD"))
        "foo"
        (unode "bar" (leaf "baz")).
```

```
           "foo"
          /      \
       "lol"     "bar"
       /   \        \
  "rofl"  "xD"    "baz"
```

---

### 3. Évaluation de `numBinaryNodes exple2` *(1 pt)*

```coq
Fixpoint numBinaryNodes {A} (t : nebtree A) :=
  match t with
  | leaf _      => 0           (* nBl *)
  | unode _ c   => numBinaryNodes c          (* nBu *)
  | bnode l _ r => S (numBinaryNodes l + numBinaryNodes r)  (* nBb *)
  end.
```

Posons `L = bnode (leaf "rofl") "lol" (leaf "xD")` et `R = unode "bar" (leaf "baz")` :

```
numBinaryNodes exple2
  = S(numBinaryNodes L + numBinaryNodes R)            [nBb]
  = S(S(numBinaryNodes(leaf "rofl")
        + numBinaryNodes(leaf "xD"))
      + numBinaryNodes (leaf "baz"))                  [nBb sur L, nBu sur R]
  = S(S(0 + 0) + 0)                                  [nBl ×3]
  = S(S 0 + 0)
  = S(1 + 0)
  = S 1
  = 2
```

**Résultat : `2`**

---

### 4. Preuve papier de `mirror_involutive` *(3 pts)*

```coq
Fixpoint mirror {A} (t : nebtree A) :=
  match t with
  | leaf a      => leaf a                          (* ml *)
  | unode a c   => unode a (mirror c)              (* mu *)
  | bnode l a r => bnode (mirror r) a (mirror l)   (* mb *)
  end.
```

**Lemme :** `∀ t : nebtree A, mirror (mirror t) = t`

**Preuve par induction structurelle sur `t` :**

**Cas `leaf a` :**
```
mirror (mirror (leaf a))
  = mirror (leaf a)    [ml]
  = leaf a             [ml]
  = t                  ✓
```

**Cas `unode a c`, IH : `mirror (mirror c) = c` :**
```
mirror (mirror (unode a c))
  = mirror (unode a (mirror c))         [mu]
  = unode a (mirror (mirror c))         [mu]
  = unode a c                           [IH]
  = t                                   ✓
```

**Cas `bnode l a r`, IHl : `mirror(mirror l) = l`, IHr : `mirror(mirror r) = r` :**
```
mirror (mirror (bnode l a r))
  = mirror (bnode (mirror r) a (mirror l))              [mb]
  = bnode (mirror(mirror l)) a (mirror(mirror r))       [mb]
  = bnode l a r                                         [IHl, IHr]
  = t                                                   ✓
```

---

### 5. Preuve papier de `iter_numBinaryNodes` *(3 pts)*

```coq
Fixpoint iter {A B : Type}
    (fl : A -> B) (f1 : A -> B -> B) (f2 : B -> A -> B -> B) (t : nebtree A) :=
  match t with
  | leaf a      => fl a
  | unode a c   => f1 a (iter fl f1 f2 c)
  | bnode l a r => f2 (iter fl f1 f2 l) a (iter fl f1 f2 r)
  end.
```

**Lemme :**
```
iter (fun _ => 0) (fun _ z => z) (fun x _ z => S(x + z)) t = numBinaryNodes t
```

**Preuve par induction sur `t` :**

**Cas `leaf a` :**
```
iter ... (leaf a)
  = (fun _ => 0) a      [définition iter, cas leaf]
  = 0
  = numBinaryNodes (leaf a)   [nBl]  ✓
```

**Cas `unode a c`, IH :**
```
iter ... (unode a c)
  = (fun _ z => z) a (iter ... c)    [cas unode]
  = iter ... c
  = numBinaryNodes c                 [IH]
  = numBinaryNodes (unode a c)       [nBu]  ✓
```

**Cas `bnode l a r`, IHl, IHr :**
```
iter ... (bnode l a r)
  = (fun x _ z => S(x+z)) (iter ... l) a (iter ... r)   [cas bnode]
  = S(iter ... l + iter ... r)
  = S(numBinaryNodes l + numBinaryNodes r)               [IHl, IHr]
  = numBinaryNodes (bnode l a r)                         [nBb]  ✓
```

---

### 6. Définitions avec `iter` *(4 pts)*

```coq
(* a) Nombre de nœuds à un seul enfant (unode) *)
Definition numUnaryNodes {A} (t : nebtree A) : nat :=
  iter (fun _ => 0)
       (fun _ z => S z)
       (fun x _ z => x + z)
       t.

(* b) Somme des étiquettes (pour nebtree nat) *)
Definition sum (t : nebtree nat) : nat :=
  iter (fun n => n)
       (fun n z => n + z)
       (fun x n z => x + n + z)
       t.

(* c) Tous les sommets vérifient le prédicat p *)
Definition all {A} (p : A -> bool) (t : nebtree A) : bool :=
  iter p
       (fun a z => p a && z)
       (fun x a z => x && p a && z)
       t.

(* d) Nombre de sommets dont l'étiquette vérifie p *)
Definition count {A} (p : A -> bool) (t : nebtree A) : nat :=
  iter (fun a => if p a then 1 else 0)
       (fun a z => (if p a then 1 else 0) + z)
       (fun x a z => x + (if p a then 1 else 0) + z)
       t.
```

---

## Exercice 3 — Prédicat inductif `mystere` (14 pts)

```coq
Inductive mystere : nat -> nat -> Prop :=
  | mn    (n : nat)   : mystere n n
  | mSS   (n m : nat) : mystere n m -> mystere n (S (S m))
  | msymm (n m : nat) : mystere n m -> mystere m n.
```

---

### 1. Règles d'inférence *(1 pt)*

```
                                  Γ ⊢ mystere n m           Γ ⊢ mystere n m
─────────────── (mn)          ──────────────────── (mSS)  ──────────────────── (msymm)
mystere n n                   mystere n (S (S m))          mystere m n
```

---

### 2. Preuves de `mystere 0 6` et `mystere 5 3` *(4 pts)*

#### a) `mystere 0 6`

**Arbre de dérivation :**
```
────────── (mn)
mystere 0 0
────────── (mSS)
mystere 0 2
────────── (mSS)
mystere 0 4
────────── (mSS)
mystere 0 6
```

**En Rocq :**
```coq
Lemma mystere06 : mystere 0 6.
Proof.
  apply mSS. apply mSS. apply mSS. apply mn.
Qed.
(* Terme direct : exact (mSS 0 4 (mSS 0 2 (mSS 0 0 (mn 0)))). *)
```

#### b) `mystere 5 3`

**Arbre de dérivation :**
```
────────── (mn)
mystere 3 3
────────── (mSS)
mystere 3 5
────────── (msymm)
mystere 5 3
```

**En Rocq :**
```coq
Lemma mystere53 : mystere 5 3.
Proof.
  apply msymm. apply mSS. apply mn.
Qed.
```

---

### 3. `meme_par_mystere` — preuve par induction sur `k` *(3 pts)*

```coq
Lemma meme_par_mystere (n m k : nat) : m = n + 2 * k -> mystere n m.
Proof.
  induction k as [| k IH] in m |-.
  - (* k = 0 : m = n *)
    intros H.
    assert (m = n) by lia. subst. apply mn.
  - (* k = S k' : on raisonne deux fois par cas sur m *)
    destruct m as [| [| m']].
    + intros H. exfalso. lia.     (* m = 0 : impossible car n + 2*(S k) ≥ 2 *)
    + intros H. exfalso. lia.     (* m = 1 : impossible *)
    + intros H.                   (* m = S(S m') *)
      apply mSS. apply IH. lia.   (* m' = n + 2*k *)
Qed.
```

> **Explication du cas récursif :** `m = S(S m')` avec `H : S(S m') = n + 2*(S k)`.
> Donc `m' = n + 2*k`. On applique `mSS` (qui réduit le but de `mystere n (S(S m'))` à `mystere n m'`),
> puis `IH` avec le fait `m' = n + 2*k` prouvé par `lia`.

---

### 4. `meme_par_mystere'` — preuve courte *(2 pts)*

```coq
Lemma meme_par_mystere' (n m k : nat) : n = m + 2 * k -> mystere n m.
Proof.
  intros H.
  apply msymm.
  apply (meme_par_mystere m n k).
  lia.
Qed.
```

> **Idée :** `n = m + 2*k` est exactement la prémisse de `meme_par_mystere` avec les rôles de `n` et `m` échangés. On applique `msymm` pour retourner la relation puis on invoque le lemme précédent.

---

### 5. `mystere_exists` — les trois cas *(4 pts)*

```coq
Lemma mystere_exists (n m : nat) :
  mystere n m -> (exists k, m = n + 2*k) \/ (exists k, n = m + 2*k).
Proof.
  intros H.
  induction H as [p | p q Hpq IHpq | p q Hpq IHpq].
  - (* mn : mystere p p *)
    left. exists 0. lia.

  - (* mSS : mystere p q -> mystere p (S(S q)) *)
    destruct IHpq as [[k Hk] | [k Hk]].
    + left.  exists (k + 1). lia.
    + destruct k as [| k'].
      * left.  exists 1.   lia.
      * right. exists k'.  lia.

  - (* msymm : mystere p q -> mystere q p *)
    destruct IHpq as [IHl | IHr].
    + right. exact IHl.
    + left.  exact IHr.
Qed.
```

---

## Exercice 4 — `positive`, `eqb`, réflexion (20 pts)

```coq
Inductive positive : Set :=
  | xI (p : positive) | xO (p : positive) | xH.
Notation "1"     := xH.
Notation "p ~ 1" := (xI p).
Notation "p ~ 0" := (xO p).
```

---

### 1. Valeur décimale de `1~0~0~1~0` *(1 pt)*

On lit les bits de gauche à droite (bit de poids fort en tête) :

```
xH              = 1
1~0   = xO xH   = 2×1       = 2
1~0~0           = 2×2       = 4
1~0~0~1         = 2×4 + 1   = 9
1~0~0~1~0       = 2×9       = 18
```

**Réponse : 18**

---

### 2. Représentation sans notation *(1 pt)*

`1~0~0~1~0` = **`xO (xI (xO (xO xH)))`**

---

### 3. Évaluation de `1~1~0~1 =? 1~0~0~1` *(1 pt)*

```coq
Fixpoint eqb (x y : positive) : bool :=
  match x with
  | xH   => match y with xH => true | _ => false end
  | xI p => match y with xI q => eqb p q | _ => false end
  | xO p => match y with xO q => eqb p q | _ => false end
  end.
```

Évaluation :
```
eqb (1~1~0~1) (1~0~0~1)
  = eqb (xI(xO(xI xH))) (xI(xO(xO xH)))
  = eqb (xO(xI xH)) (xO(xO xH))          [cas xI p, xI q]
  = eqb (xI xH) (xO xH)                   [cas xO p, xO q]
  = false                                  [cas xI p, xO _ → false]
```

**Résultat : `false`**

---

### 4. Preuve de `eqb_refl` *(3 pts)*

```coq
Lemma eqb_refl (x : positive) : x =? x = true.
Proof.
  induction x as [p IH | p IH | ].
  - simpl. exact IH.    (* x = xI p : eqb (xI p)(xI p) = eqb p p = true par IH *)
  - simpl. exact IH.    (* x = xO p : idem *)
  - simpl. reflexivity. (* x = xH   : eqb xH xH = true *)
Qed.
```

---

### 5. Déduire `eq_eqb` *(1 pt)*

```coq
Lemma eq_eqb (x y : positive) : x = y -> x =? y = true.
Proof.
  intros H. rewrite H. apply eqb_refl.
Qed.
```

---

### 6. Premier et troisième cas de `eqb_eq` *(3 pts)*

```coq
Lemma eqb_eq (x y : positive) : x =? y = true -> x = y.
Proof.
  induction x as [p IH | p IH | ] in y |-.
```

**Cas `x = xI p`, sous-cas `y = xI q` (premier cas) :**
```coq
  - destruct y as [q | q | ].
    + (* y = xI q *)
      simpl. intros H.
      rewrite (IH q H). reflexivity.  (* p = q donc xI p = xI q *)
    + simpl. intros H. discriminate H.  (* cas xI/xO : impossible *)
    + simpl. intros H. discriminate H.  (* cas xI/xH : impossible *)
```

**Cas `x = xH` (troisième cas) :**
```coq
  - destruct y as [q | q | ].
    + simpl. intros H. discriminate H.
    + simpl. intros H. discriminate H.
    + simpl. intros _. reflexivity.    (* xH = xH *)
Qed.
```

---

### 7. Déduire `eq_dec` *(2 pts)*

```coq
Lemma eq_dec (x y : positive) : x = y \/ x <> y.
Proof.
  destruct (x =? y) eqn:E.
  - left.  apply eqb_eq. exact E.
  - right. intros H. apply eq_eqb in H. rewrite H in E. discriminate E.
Qed.
```

---

### 8a. Évaluation de `mem 1~1 [1; 1~0; 1~1; 1~1~0]` *(1 pt)*

```coq
Fixpoint mem (x : positive) (l : list positive) : bool :=
  match l with
  | []      => false
  | h :: t  => (h =? x) || mem x t
  end.
```

(`1~1` = 3, liste = [1; 2; 3; 6])

```
mem 1~1 [1; 1~0; 1~1; 1~1~0]
  = (1 =? 1~1)   || mem 1~1 [1~0; 1~1; 1~1~0]
  = false        || mem 1~1 [1~0; 1~1; 1~1~0]
  = (1~0 =? 1~1) || mem 1~1 [1~1; 1~1~0]
  = false        || mem 1~1 [1~1; 1~1~0]
  = (1~1 =? 1~1) || mem 1~1 [1~1~0]
  = true         || mem 1~1 [1~1~0]
  = true
```

**Résultat : `true`**

---

### 8b. Preuve de `isIn 1~1 [1; 1~0; 1~1; 1~1~0]` *(1 pt)*

```coq
Inductive isIn (e : positive) : list positive -> Set :=
  | isInHead (h : positive) (t : list positive) : h = e -> isIn e (h :: t)
  | isInTail (h : positive) (t : list positive) : isIn e t -> isIn e (h :: t).
```

```coq
(* On passe les deux premiers éléments avec isInTail,
   puis on conclut avec isInHead *)
apply isInTail.   (* passe 1 *)
apply isInTail.   (* passe 1~0 *)
apply isInHead.   (* tête = 1~1 = e *)
reflexivity.
```

---

### 9. Preuve de `mem_isIn` *(3 pts)*

```coq
Lemma mem_isIn (e : positive) (l : list positive) :
  mem e l = true -> isIn e l.
Proof.
  induction l as [| h t IH].
  - simpl. intros H. discriminate H.   (* liste vide : mem = false *)
  - simpl. intros H.
    destruct (h =? e) eqn:E.
    + apply isInHead. apply eqb_eq. exact E.   (* h = e *)
    + simpl in H.
      apply isInTail. apply IH. exact H.       (* h ≠ e, on continue *)
Qed.
```

---

### 10. Preuve de `isIn_mem` *(3 pts)*

**Règles de calcul supplémentaires nécessaires (« évidentes ») :**

```coq
Lemma mem_head (e : positive) (t : list positive) :
  mem e (e :: t) = true.
Proof. simpl. rewrite eqb_refl. simpl. reflexivity. Qed.

Lemma mem_tail_true (e h : positive) (t : list positive) :
  mem e t = true -> mem e (h :: t) = true.
Proof.
  simpl. intros H.
  destruct (h =? e) eqn:E; simpl; [reflexivity | exact H].
Qed.
```

**Preuve du lemme par induction sur la preuve `isIn` :**

```coq
Lemma isIn_mem (e : positive) (l : list positive) :
  isIn e l -> mem e l = true.
Proof.
  intros H.
  induction H as [h t Hhe | h t _ IH].
  - (* isInHead : h = e *)
    rewrite <- Hhe. apply mem_head.
  - (* isInTail : e ∈ t donc mem e t = true, on remonte *)
    apply mem_tail_true. exact IH.
Qed.
```
