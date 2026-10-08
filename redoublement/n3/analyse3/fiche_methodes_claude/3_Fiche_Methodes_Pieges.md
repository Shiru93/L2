# Analyse 3 — Fiche de révision : définitions, méthodes, pièges

> La fiche à relire la veille et le matin du partiel. Tout tient ici.

---

## 🧠 1. Définitions à réciter mot pour mot

| Notion | Définition |
|---|---|
| Relation d'ordre | réflexive + antisymétrique + transitive ; **totale** si tout couple est comparable |
| Majorant de $F$ | $y$ tel que $\forall x\in F,\ x\le y$ |
| Max de $F$ | majorant **appartenant à $F$** |
| $\sup F$ | plus petit des majorants |
| Prop. borne sup | toute partie **non vide majorée** a une borne sup |
| ℝ | corps commutatif totalement ordonné contenant ℚ avec la prop. de la borne sup |
| Archimède | $\forall a,b>0,\ \exists n\in\mathbb N,\ na>b$ |
| $\lfloor x\rfloor$ | unique $n\in\mathbb Z$ avec $n\le x<n+1$ |
| $\mathrm{card}\,E=\mathrm{card}\,F$ | ∃ bijection $E\to F$ |
| $\mathrm{card}\,E\le\mathrm{card}\,F$ | ∃ injection $E\to F$ |
| Dénombrable | $\mathrm{card}\,E=\mathrm{card}\,\mathbb N$ |
| Suite extraite | $(u_{\varphi(n)})$ avec $\varphi:\mathbb N\to\mathbb N$ **strictement croissante** |
| $u_n\to\ell$ | $\forall\varepsilon>0,\exists N,\forall n\ge N,\ \lvert u_n-\ell\rvert<\varepsilon$ |
| $u_n\to+\infty$ | $\forall A,\exists N,\forall n\ge N,\ u_n\ge A$ |
| Bornée | $\exists C>0,\forall n,\ \lvert u_n\rvert\le C$ |
| $u_n=o(v_n)$ | $\forall\varepsilon>0,\exists N,\forall n\ge N,\ \lvert u_n\rvert\le\varepsilon\lvert v_n\rvert$ |
| $u_n\sim v_n$ | $u_n-v_n=o(v_n)$ |
| $u_n=O(v_n)$ | $\exists N,\exists C>0,\forall n\ge N,\ \lvert u_n\rvert\le C\lvert v_n\rvert$ |
| $u_n=\Omega(v_n)$ | $\exists N,\exists c>0,\forall n\ge N,\ \lvert u_n\rvert\ge c\lvert v_n\rvert$ |
| $u_n=\Theta(v_n)$ | $\exists N,\exists c,C>0,\forall n\ge N,\ c\lvert v_n\rvert\le\lvert u_n\rvert\le C\lvert v_n\rvert$ |
| Adjacentes | $u_n\le v_n$, $u\nearrow$, $v\searrow$, $v_n-u_n\to0$ |
| $\limsup u_n$ | $\lim_n\sup_{k\ge n}u_k$ |

## 🏛️ 2. Théorèmes à énoncer (avec hypothèses !)

1. **ℚ n'a pas la prop. de la borne sup** ($\{x\in\mathbb Q^+ : x^2<2\}$) ; **$\sqrt2\notin\mathbb Q$**.
2. **Archimède**.
3. **Cantor–Bernstein** : injection $E\to F$ + injection $F\to E$ ⇒ bijection.
4. **ℕ plus petit infini** : $E$ infini ⇒ $\mathrm{card}\,\mathbb N\le\mathrm{card}\,E$.
5. **ℤ, ℕ², ℚ, ℕᵏ dénombrables.**
6. **Cantor** : pas de surjection $E\to\mathcal P(E)$ ; donc $\mathrm{card}\,E<\mathrm{card}\,\mathcal P(E)$.
7. $\mathrm{card}\,\mathbb R=\mathrm{card}\,\mathcal P(\mathbb N)$ ; ℝ non dénombrable.
8. **d'Alembert** : polynôme de degré $n\ge1$ ⇒ $n$ racines complexes avec multiplicité.
9. Unicité de la limite ; convergente ⇒ bornée ; extraite d'une convergente converge vers la même limite.
10. **Gendarmes** ; comparaison ($u_n\le v_n$, $u_n\to+\infty$ ⇒ $v_n\to+\infty$).
11. **Limite monotone** ; **suites adjacentes**.
12. **Croissances comparées** $n^k=o(q^n)$, $q>1$.
13. $\liminf=\limsup$ ⟺ la suite a une limite dans $\overline{\mathbb R}$.

---

## 🛠️ 3. Boîte à méthodes

### M1 — Trouver/prouver $\sup$, $\inf$, $\max$, $\min$ d'un ensemble
1. Calculer quelques éléments, **conjecturer** (souvent : séparer $n$ pair / impair).
2. Montrer que $m$ est un majorant ($\forall x\in F,\ x\le m$).
3. Montrer : $\forall\varepsilon>0,\ \exists x\in F,\ x>m-\varepsilon$ (souvent via Archimède : prendre $n>1/\varepsilon$). **Ou** montrer $m\in F$ ⇒ c'est un max.
4. Si $m\notin F$ ⇒ pas de max (le dire !).

### M2 — Montrer qu'un nombre est irrationnel
Par l'absurde : $\frac ab$ irréductible, élever au carré, divisibilité ⇒ $a$ et $b$ ont un facteur commun. (Pour $\sqrt3$ : si $3\mid a^2$ alors $3\mid a$ car 3 premier.)

### M3 — Montrer qu'un ensemble est dénombrable
- Construire une **bijection** explicite avec ℕ (ou une partie infinie de ℕ) ; **ou**
- Montrer qu'il est **infini** + construire une **injection** vers ℕ, ℕ², ℤ×ℕ… (Cantor–Bernstein) ; **ou**
- Montrer que c'est une partie infinie d'un dénombrable, ou un produit fini de dénombrables.

### M4 — Montrer que deux ensembles ont même cardinal
Bijection explicite (fonction affine, $\tan$, $x\mapsto\frac1{1-x}-\frac1x$…) ou deux injections + Cantor–Bernstein.

### M5 — Montrer qu'un ensemble n'est pas dénombrable
Il contient (ou s'injecte) un non dénombrable : $\mathcal P(\mathbb N)$, $\{0,1\}^{\mathbb N}$, un intervalle de ℝ ; ou argument diagonal à la Cantor.

### M6 — Racines $n$-ièmes / équations dans ℂ
Forme exponentielle $\rho e^{i\theta}$ ⇒ $\rho^{1/n}e^{i(\theta+2k\pi)/n}$, $k=0..n-1$. Trinôme : $\Delta$, chercher $\omega$ avec $\omega^2=\Delta$.
Si $\Delta<0$ réel : $\omega=i\sqrt{-\Delta}$. Si $\Delta$ complexe : écrire $\omega=a+ib$, résoudre $a^2-b^2=\mathrm{Re}\,\Delta$, $2ab=\mathrm{Im}\,\Delta$, $a^2+b^2=\lvert\Delta\rvert$.

### M7 — Prouver une limite par la définition
Majorer $\lvert u_n-\ell\rvert\le\frac{C}{n}$ (simplifier en minorant le dénominateur / majorant le numérateur), puis choisir $N>C/\varepsilon$.

### M8 — Calculer une limite (ordre d'attaque)
1. Limites usuelles + opérations : est-ce une FI ?
2. FI avec polynômes/exponentielles : **factoriser par le terme dominant**.
3. Racines : **quantité conjuguée**.
4. Termes oscillants ($\sin n$, $(-1)^n$) : **bornée × →0** ou **gendarmes**.
5. Équivalents : remplacer par l'équivalent dans **produits/quotients** uniquement.
6. Factorielles / puissances : **rapport $\frac{u_{n+1}}{u_n}$**.

### M9 — Montrer une divergence
Deux suites extraites de limites différentes ; ou suite non bornée (si on veut montrer non convergente) ; ou $\liminf\ne\limsup$.

### M10 — Comparer asymptotiquement ($o$, $O$, $\Theta$, $\sim$)
Calculer $\frac{u_n}{v_n}$ : $\to0$ ⇒ $o$ ; $\to1$ ⇒ $\sim$ ; $\to L\ne0$ fini ⇒ $\Theta$ ; bornée ⇒ $O$ ; $\to\infty$ ⇒ ni $O$ (mais $\Omega$ et $v_n=o(u_n)$).

### M11 — Suite récurrente $u_{n+1}=f(u_n)$
Intervalle stable → monotonie (signe de $f(x)-x$ ou $f$ croissante) → bornée → converge → $\ell=f(\ell)$.

### M12 — Arithmético-géométrique $u_{n+1}=au_n+b$
Point fixe $\ell=\frac{b}{1-a}$, $v_n=u_n-\ell$ géométrique de raison $a$.

### M13 — Suites adjacentes
Vérifier les 4 points : signe de $u_{n+1}-u_n$, de $v_{n+1}-v_n$, de $v_n-u_n$, limite de $v_n-u_n$.

### M14 — $\limsup$ / $\liminf$
Découper en sous-suites qui recouvrent ℕ, calculer leurs limites : $\limsup$ = max, $\liminf$ = min. Ou calculer directement $S_n$ et $I_n$.

---

## 📈 4. Hiérarchie des croissances

$$1\ \ll\ \ln n\ \ll\ \sqrt n\ \ll\ n\ \ll\ n\ln n\ \ll\ n^2\ \ll\ n^{k}\ \ll\ 2^n\ \ll\ 3^n\ \ll\ n!\ \ll\ n^n$$

| Complexité (lien info) | Exemple d'algo |
|---|---|
| $\Theta(1)$ | accès tableau |
| $\Theta(\log n)$ | recherche dichotomique |
| $\Theta(n)$ | parcours |
| $\Theta(n\log n)$ | tri fusion |
| $\Theta(n^2)$ | tri par insertion (pire cas) |
| $\Theta(2^n)$ | sous-ensembles (force brute) |
| $\Theta(n!)$ | permutations |

## 📌 5. Limites et formules usuelles

- $\frac1{n^\alpha}\to0$ ($\alpha>0$) ; $q^n\to0$ si $\lvert q\rvert<1$ ; $\to+\infty$ si $q>1$ ; diverge si $q\le-1$.
- $\sum_{k=0}^nq^k=\frac{1-q^{n+1}}{1-q}$ ; $\sum_{k=1}^nk=\frac{n(n+1)}2$ ; $\sum_{k=1}^nk^2=\frac{n(n+1)(2n+1)}6$.
- Bernoulli : $(1+x)^n\ge1+nx$ pour $x\ge-1$.
- $\lvert\lvert a\rvert-\lvert b\rvert\rvert\le\lvert a-b\rvert$ ; $\lvert a+b\rvert\le\lvert a\rvert+\lvert b\rvert$.
- $\lfloor x\rfloor\le x<\lfloor x\rfloor+1$ et $x-1<\lfloor x\rfloor$.
- $e^{i\theta}=\cos\theta+i\sin\theta$ ; $\cos\theta=\frac{e^{i\theta}+e^{-i\theta}}2$ ; $\sin\theta=\frac{e^{i\theta}-e^{-i\theta}}{2i}$.
- $\frac1z=\frac{\bar z}{\lvert z\rvert^2}$ ; $\lvert z\rvert^2=z\bar z$.
- Équivalents de fonctions (L1, utiles) : si $x_n\to0$ : $\sin x_n\sim x_n$, $\ln(1+x_n)\sim x_n$, $e^{x_n}-1\sim x_n$, $(1+x_n)^\alpha-1\sim\alpha x_n$.

---

## ⚠️ 6. LES PIÈGES (ceux qui coûtent des points)

1. **Majorant ≠ max** : un max doit appartenir à l'ensemble. Toujours dire si sup est atteint ou non.
2. **$\lfloor-0{,}5\rfloor=-1$**, pas $0$.
3. **Pas d'inégalité entre complexes**. On compare des modules.
4. **Injection $E\to F$** = $E$ plus petit. Ne pas inverser le sens.
5. **ℚ est dénombrable** (même s'il est « dense ») ; **ℝ ne l'est pas**.
6. **Inégalité stricte → large** au passage à la limite.
7. **Bornée ⇏ convergente** ; **$\lvert u_n\rvert$ converge ⇏ $u_n$ converge** (sauf vers 0).
8. **Non majorée ⇏ $\to+\infty$**.
9. **Ne JAMAIS sommer des équivalents**, ne jamais écrire $u_n\sim0$.
10. **$\Theta\not\Rightarrow\sim$** ($n$ vs $2n$).
11. **Le « $=$ » de $O$/$o$ n'est pas symétrique** : $n=O(n^2)$ mais pas $n^2=O(n)$.
12. **$2^{2n}\ne\Theta(2^n)$** (rapport $2^n\to\infty$), mais $2^{n+1}=\Theta(2^n)$.
13. **Le théorème de la limite monotone ne donne pas la valeur** : il faut $\ell=f(\ell)$ et sélectionner la bonne solution.
14. **Dans une preuve ε, $N$ dépend de ε** : on écrit « Soit ε > 0 » **en premier**.
15. **Dans $\varepsilon$-$N$, ne pas « résoudre » une inégalité dans le mauvais sens** : on a besoin de « $n\ge N\Rightarrow\lvert u_n-\ell\rvert<\varepsilon$ », donc on **majore**.
16. **FI** : $\infty-\infty$, $0\times\infty$, $\frac\infty\infty$, $\frac00$, $1^\infty$. Ex. $(1+\frac1n)^n\to e$, pas $1$ !
17. **$\limsup$ / $\liminf$ uniquement pour les suites réelles.**
18. **Suite extraite** : $\varphi$ strictement croissante obligatoire ($u_{\lfloor n/2\rfloor}$ n'est pas une suite extraite).

---

## 🗓️ 7. Plan de révision conseillé

| Jour | Contenu |
|---|---|
| J-7 | Relire `1_Chapitre1_Rappels.md`, refaire les preuves ✍️ (√2, Archimède, Cantor) |
| J-6 | Exercices corrigés partie A (ensembles, sup/inf, complexes, cardinaux) |
| J-5 | Relire `2_Chapitre2_Suites.md` §1–4, s'entraîner aux preuves ε-N |
| J-4 | §5–9 + exercices corrigés partie B |
| J-3 | Refaire **sans regarder** les preuves ✍️ du chapitre 2 |
| J-2 | **Partiel blanc** en 2h chrono, puis correction |
| J-1 | Cette fiche + pièges + refaire les exos ratés |
| Jour J | Relire les sections 1, 2, 6 de cette fiche |

**Conseils de rédaction en partiel**
- Annoncer la méthode (« par l'absurde », « par récurrence », « par le théorème des gendarmes »).
- Citer le théorème utilisé **et vérifier ses hypothèses** (ex. « $(u_n)$ est croissante **et** majorée, donc converge »).
- Récurrence : initialisation, hérédité, conclusion — les trois écrits.
- Quantificateurs dans le bon ordre : $\forall\varepsilon\ \exists N$ (pas l'inverse).
