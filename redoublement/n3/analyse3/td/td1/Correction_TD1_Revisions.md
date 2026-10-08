# Analyse 3 — Correction détaillée du TD 1 : Révisions

> L2 Informatique — USPN, 2026-27.
> Pour chaque exercice : 🧭 **Méthode** (ce qu'il faut reconnaître), ✍️ **Rédaction** (ce qu'on écrit sur la copie), 💡 **À retenir**.
> Les renvois « cours » désignent le polycopié (Chapitre 1 : Rappels, Chapitre 2 : Suites).

---

## Partie entière et valeur absolue

### Exercice 1 — Partie entière

**Rappel (Déf. 3.5 du cours).** $\lfloor x\rfloor$ est l'**unique** entier $n$ tel que $n\le x<n+1$.

🧭 **Méthode** : pour calculer $\lfloor x\rfloor$, on **encadre** $x$ entre deux entiers consécutifs. Pour démontrer une formule, on utilise l'**unicité** : on exhibe un entier $m$ qui vérifie $m\le y<m+1$, et on conclut $\lfloor y\rfloor=m$.

#### (a) Calculs

| $x$ | Encadrement | $\lfloor x\rfloor$ |
|---|---|---|
| $3$ | $3\le3<4$ | $3$ |
| $-3$ | $-3\le-3<-2$ | $-3$ |
| $3{,}1$ | $3\le3{,}1<4$ | $3$ |
| $-3{,}1$ | $-4\le-3{,}1<-3$ | $\mathbf{-4}$ ⚠️ |
| $\sqrt{237}$ | voir ci-dessous | $15$ |

Pour $\sqrt{237}$ : $15^2=225$ et $16^2=256$, donc $225\le237<256$. La fonction racine carrée est strictement croissante sur $\mathbb R^+$, donc $15\le\sqrt{237}<16$, d'où $\lfloor\sqrt{237}\rfloor=15$.

⚠️ **Piège** : $\lfloor-3{,}1\rfloor=-4$ et non $-3$. La partie entière arrondit **vers $-\infty$**, pas vers $0$ (ce n'est pas la troncature `(int)` du C !).

#### (b) Expression de $\lfloor-x\rfloor$

Posons $n=\lfloor x\rfloor$ : $n\le x<n+1$. En multipliant par $-1$ (on renverse les inégalités) :
$$-n-1<-x\le-n.$$

**Cas 1 : $x\in\mathbb Z$.** Alors $x=n$, donc $-x=-n$ est un entier et $\lfloor-x\rfloor=-n=-\lfloor x\rfloor$.

**Cas 2 : $x\notin\mathbb Z$.** Alors $x\ne n$, donc $n<x$ et l'inégalité de droite devient stricte : $-n-1<-x<-n$. En particulier $-n-1\le-x<(-n-1)+1$. Par unicité de la partie entière, $\lfloor-x\rfloor=-n-1$.

$$\boxed{\lfloor-x\rfloor=\begin{cases}-\lfloor x\rfloor & \text{si } x\in\mathbb Z\\[2pt] -\lfloor x\rfloor-1 & \text{si } x\notin\mathbb Z\end{cases}}$$

Vérification : $\lfloor-3{,}1\rfloor=-\lfloor3{,}1\rfloor-1=-4$ ✅.

💡 En informatique, ceci donne la partie entière supérieure : $\lceil x\rceil=-\lfloor-x\rfloor$.

---

### Exercice 2 — max et min

🧭 **Méthode** : une valeur absolue $\lvert a\rvert$ se traite **par disjonction de cas** sur le signe de $a$.

✍️ Soient $x,y\in\mathbb R$.

**Cas $x\ge y$** : $\lvert x-y\rvert=x-y$ et $\max(x,y)=x$, $\min(x,y)=y$.
$$\frac{x+y+\lvert x-y\rvert}{2}=\frac{x+y+x-y}{2}=x=\max(x,y),\qquad\frac{x+y-\lvert x-y\rvert}{2}=\frac{2y}{2}=y=\min(x,y).$$

**Cas $x<y$** : $\lvert x-y\rvert=y-x$, $\max(x,y)=y$, $\min(x,y)=x$.
$$\frac{x+y+(y-x)}{2}=y=\max(x,y),\qquad\frac{x+y-(y-x)}{2}=x=\min(x,y).$$

Les deux formules sont vraies dans tous les cas. ∎

💡 Interprétation : $\frac{x+y}2$ est le **milieu** de $x$ et $y$, $\frac{\lvert x-y\rvert}2$ la **demi-distance**. Le max est le milieu plus la demi-distance. Corollaires utiles : $\max+\min=x+y$, $\max-\min=\lvert x-y\rvert$.

---

### Exercice 3 — Racine carrée entière par dichotomie

🧭 **Méthode** : c'est une **recherche dichotomique** (cours, §2.5 « suites adjacentes » et dichotomie). On travaille avec un **invariant de boucle**, prouvé par récurrence, puis un argument de **terminaison** (une quantité entière positive qui décroît strictement).

Notations : $a_0=0$, $b_0=N+1$, $m_n=\left\lfloor\frac{a_n+b_n}{2}\right\rfloor$ ; si $m_n^2\le N$ alors $(a_{n+1},b_{n+1})=(m_n,b_n)$, sinon $(a_{n+1},b_{n+1})=(a_n,m_n)$.

#### (a) Invariant : $a_n,b_n\in\mathbb N$ et $a_n^2\le N<b_n^2$

✍️ Récurrence sur $n$, avec $P(n)$ : « $a_n,b_n\in\mathbb N$ et $a_n^2\le N<b_n^2$ ».

- **Initialisation** : $a_0=0$, $b_0=N+1$ sont des entiers naturels ; $a_0^2=0\le N$ (car $N\ge1$) et $N<N+1\le(N+1)^2$. Donc $P(0)$.
- **Hérédité** : supposons $P(n)$. $a_n+b_n\ge0$ donc $m_n=\lfloor\frac{a_n+b_n}2\rfloor\in\mathbb N$.
  - Si $m_n^2\le N$ : $a_{n+1}=m_n\in\mathbb N$ vérifie $a_{n+1}^2\le N$, et $b_{n+1}=b_n$ vérifie $N<b_{n+1}^2$ par hypothèse.
  - Sinon $m_n^2>N$ : $b_{n+1}=m_n\in\mathbb N$ vérifie $N<b_{n+1}^2$, et $a_{n+1}=a_n$ vérifie $a_{n+1}^2\le N$.
  
  Dans les deux cas, $P(n+1)$ est vraie.
- **Conclusion** : $P(n)$ est vraie pour tout $n\in\mathbb N$. ∎

#### (b) Les suites sont stationnaires

Posons $d_n=b_n-a_n$.

**Étape 1 : $d_n\ge1$.** D'après (a), $a_n^2\le N<b_n^2$, donc $a_n^2<b_n^2$ ; comme $a_n,b_n\ge0$, cela donne $a_n<b_n$, et comme ce sont des entiers, $d_n\ge1$.

**Étape 2 : si $d_n\ge2$, alors $a_n<m_n<b_n$.**
- $\frac{a_n+b_n}{2}=a_n+\frac{d_n}2\ge a_n+1$, et $a_n+1$ est entier, donc $m_n\ge a_n+1>a_n$.
- $m_n\le\frac{a_n+b_n}{2}<b_n$ (car $a_n<b_n$).

Donc, quelle que soit la branche choisie, l'intervalle est **strictement réduit** : $d_{n+1}<d_n$. (Plus précisément, $d_{n+1}\le\lceil d_n/2\rceil$ : on divise environ par 2.)

**Étape 3 : si $d_n=1$, tout est figé.** Alors $m_n=\lfloor\frac{2a_n+1}{2}\rfloor=\lfloor a_n+\frac12\rfloor=a_n$, et $m_n^2=a_n^2\le N$, donc $a_{n+1}=a_n$ et $b_{n+1}=b_n$. Par récurrence, les suites sont constantes à partir de ce rang.

**Étape 4 : $d_n$ atteint la valeur 1.** Tant que $d_n\ge2$, la suite $(d_n)$ est une suite d'**entiers** strictement décroissante, minorée par 1. Une telle suite ne peut pas décroître strictement indéfiniment (sinon $d_n\le d_0-n<1$ pour $n$ grand, contradiction). Il existe donc un rang $k$ tel que $d_k=1$, et d'après l'étape 3 les suites sont constantes à partir de $k$. ∎

💡 Comme $d$ est (environ) divisé par 2 à chaque étape, $k\approx\log_2(N+1)$ : **complexité $\Theta(\log N)$**, bien meilleure qu'un parcours $1,2,3,\dots$ en $\Theta(\sqrt N)$.

#### (c) Le résultat est $\lfloor\sqrt N\rfloor$

Pour $n\ge k$ : $d_n=1$, donc $b_n=a_n+1$. L'invariant donne
$$a_n^2\le N<(a_n+1)^2\quad\Longrightarrow\quad a_n\le\sqrt N<a_n+1$$
(racine carrée croissante, tout est positif). Par **unicité** de la partie entière : $a_n=\lfloor\sqrt N\rfloor$. ∎

#### (d) Programme et test sur $N=237$

```python
def isqrt(N: int) -> int:
    """Racine carrée entière par dichotomie (sans sqrt)."""
    a, b = 0, N + 1            # invariant : a*a <= N < b*b
    while b - a > 1:
        m = (a + b) // 2       # // = partie entière pour des entiers positifs
        if m * m <= N:
            a = m
        else:
            b = m
    return a

print(isqrt(237))   # 15
```

Déroulement pour $N=237$ :

| $n$ | $a_n$ | $b_n$ | $m_n$ | $m_n^2\le237$ ? |
|---|---|---|---|---|
| 0 | 0 | 238 | 119 | non ($14161$) |
| 1 | 0 | 119 | 59 | non ($3481$) |
| 2 | 0 | 59 | 29 | non ($841$) |
| 3 | 0 | 29 | 14 | oui ($196$) |
| 4 | 14 | 29 | 21 | non ($441$) |
| 5 | 14 | 21 | 17 | non ($289$) |
| 6 | 14 | 17 | 15 | oui ($225$) |
| 7 | 15 | 17 | 16 | non ($256$) |
| 8 | 15 | 16 | — | arrêt |

Résultat : $15$ en 8 itérations ($\log_2238\approx7{,}9$), cohérent avec l'exercice 1(a). ✅

---

## Raisonnement par récurrence

### Exercice 4 — Sommes classiques

🧭 **Méthode** : récurrence en trois temps (initialisation, hérédité, conclusion). Dans l'hérédité, on **isole le dernier terme** : $\sum_{k=1}^{n+1}=\sum_{k=1}^{n}+(\text{terme }n+1)$.

#### Somme des entiers

$P(n)$ : « $\sum_{k=1}^nk=\frac{n(n+1)}2$ ».
- **Init.** $n=1$ : $\sum_{k=1}^1k=1=\frac{1\cdot2}{2}$ ✅.
- **Hérédité.** Si $P(n)$ :
$$\sum_{k=1}^{n+1}k=\frac{n(n+1)}2+(n+1)=(n+1)\left(\frac n2+1\right)=\frac{(n+1)(n+2)}{2}.$$
C'est $P(n+1)$.
- **Conclusion.** $P(n)$ vraie pour tout $n\ge1$.

💡 Preuve « de Gauss » (sans récurrence) : on écrit la somme à l'endroit et à l'envers, $2S=\sum_{k=1}^n\big(k+(n+1-k)\big)=n(n+1)$.

#### Somme des carrés

$Q(n)$ : « $\sum_{k=1}^nk^2=\frac{n(n+1)(2n+1)}6$ ».
- **Init.** $n=1$ : $1=\frac{1\cdot2\cdot3}{6}$ ✅.
- **Hérédité.** Si $Q(n)$ :
$$\sum_{k=1}^{n+1}k^2=\frac{n(n+1)(2n+1)}6+(n+1)^2=\frac{(n+1)\big[n(2n+1)+6(n+1)\big]}{6}=\frac{(n+1)(2n^2+7n+6)}{6}.$$
Or $(n+2)(2n+3)=2n^2+7n+6$. Donc la somme vaut $\frac{(n+1)(n+2)(2(n+1)+1)}{6}$ : c'est $Q(n+1)$.
- **Conclusion.** $Q(n)$ vraie pour tout $n\ge1$.

💡 **Astuce de rédaction** : dans l'hérédité, on **factorise** par $(n+1)$ dès le début au lieu de tout développer, puis on vise la forme attendue $(n+2)(2n+3)$.
Asymptotiquement (Chapitre 2) : $\sum k\sim\frac{n^2}2$ et $\sum k^2\sim\frac{n^3}{3}$, soit $\Theta(n^2)$ et $\Theta(n^3)$ : ce sont les coûts des doubles et triples boucles imbriquées.

---

## Bornes supérieure et inférieure

### Exercice 5 — Caractérisations de la borne supérieure

🧭 **Méthode** : ce sont **les deux outils** pour manipuler un sup en exercice. Toujours deux parties : (1) majorant, (2) « on ne peut pas faire mieux ».

Soit $A\subset\mathbb R$ non vide et majorée ; $\sup A$ existe (propriété de la borne supérieure de ℝ).

#### (a) Caractérisation séquentielle

> $M=\sup A$ ⟺ $M$ majore $A$ **et** il existe une suite $(a_n)$ d'éléments de $A$ telle que $a_n\to M$.

**(⇒)** Supposons $M=\sup A$. $M$ est un majorant par définition. Soit $n\in\mathbb N$. Comme $M-\frac1{n+1}<M$ et que $M$ est le **plus petit** majorant, $M-\frac1{n+1}$ n'est **pas** un majorant : il existe $a_n\in A$ avec $a_n>M-\frac1{n+1}$. On a ainsi construit une suite vérifiant
$$M-\frac1{n+1}<a_n\le M.$$
Par le **théorème des gendarmes**, $a_n\to M$.

**(⇐)** Supposons $M$ majorant et $a_n\in A$ avec $a_n\to M$. Soit $M'$ un majorant quelconque de $A$. Pour tout $n$, $a_n\le M'$. Par **passage à la limite dans les inégalités larges** (Prop. 2.3) : $M\le M'$. Donc $M$ est un majorant plus petit que tous les majorants : $M=\sup A$. ∎

#### (b) Caractérisation « epsilon »

> $M=\sup A$ ⟺ $M$ majore $A$ **et** $\forall\varepsilon>0,\ \exists x\in A,\ M-\varepsilon<x\le M$.

**(⇒)** Soit $\varepsilon>0$. $M-\varepsilon<M$ n'est pas un majorant (car $M$ est le plus petit), donc il existe $x\in A$ avec $x>M-\varepsilon$ ; et $x\le M$ car $M$ est un majorant.

**(⇐)** $M$ est un majorant. Par l'absurde, soit $M'$ un majorant avec $M'<M$. Posons $\varepsilon=M-M'>0$ : il existe $x\in A$ avec $x>M-\varepsilon=M'$, ce qui contredit le fait que $M'$ majore $A$. Donc tout majorant $M'$ vérifie $M'\ge M$ : $M=\sup A$. ∎

💡 **Quand utiliser laquelle ?** (a) quand on a une suite naturelle ($1-\frac1n$, $2-\frac1n$…) ; (b) quand on veut une preuve directe en ε. Les deux sont équivalentes, choisis la plus rapide.

---

### Exercice 6 — Étude de $A$ et $B$

#### Ensemble $A=[1,2[\,\cap\,\mathbb Q$

**(a) Côté supérieur.**
- **Majoré** : tout $x\in A$ vérifie $x<2$, donc $2$ est un majorant.
- **Pas de plus grand élément** : par l'absurde, soit $m=\max A$. Alors $m\in\mathbb Q$ et $1\le m<2$. Le milieu $m'=\frac{m+2}{2}$ est **rationnel** (somme et quotient de rationnels) et vérifie $m<m'<2$, donc $m'\in A$ et $m'>m$ : contradiction. *(C'est exactement la technique de l'exemple 2.5 du cours.)*
- **$\sup A=2$** (Ex. 5(a)) : $2$ est un majorant, et $a_n=2-\frac1{n+1}$ est rationnel, dans $[1,2[$ pour tout $n\ge0$, et tend vers $2$.

**(b) Côté inférieur.** $1\in A$ et $1\le x$ pour tout $x\in A$ : $1$ est le **plus petit élément**, donc $A$ est minoré et $\inf A=\min A=1$.

#### Ensemble $B=\{x\in\mathbb R : x^2+x<2\}$

🧭 On commence par **décrire $B$ explicitement** : $x^2+x-2=(x-1)(x+2)$. Un trinôme est strictement négatif strictement entre ses racines, donc
$$B=\,]-2,1[\,.$$
(Vérification par tableau de signes : $(x-1)(x+2)<0\iff$ les deux facteurs sont de signes opposés $\iff-2<x<1$.)

**(a) Côté supérieur.** $B$ est majoré par $1$. Il n'a **pas de plus grand élément** : si $m=\max B$, alors $m<1$ et $\frac{m+1}{2}\in\,]m,1[\,\subset B$, contradiction. Enfin $\sup B=1$ : $1$ majore $B$ et $b_n=1-\frac1{n+1}\in B$ (car $0\le b_n<1$), $b_n\to1$.

**(b) Côté inférieur.** $B$ est minoré par $-2$, sans plus petit élément (même argument avec le milieu $\frac{m-2}{2}$), et $\inf B=-2$ via $c_n=-2+\frac1{n+1}\in B$, $c_n\to-2$.

| | majoré | max | sup | minoré | min | inf |
|---|---|---|---|---|---|---|
| $A$ | oui | non | $2$ | oui | $1$ | $1$ |
| $B$ | oui | non | $1$ | oui | non | $-2$ |

---

### Exercice 7 — Borne supérieure et opérations

#### (a) $\sup(A+B)$ et $\sup A+\sup B$

On suppose $A$, $B$ non vides et majorées. Posons $\alpha=\sup A$, $\beta=\sup B$.

**Étape 1 : $\sup(A+B)\le\alpha+\beta$.** Pour $x\in A$, $y\in B$ : $x\le\alpha$, $y\le\beta$, donc $x+y\le\alpha+\beta$. Ainsi $A+B$ est majorée par $\alpha+\beta$, et le sup (plus petit majorant) vérifie $\sup(A+B)\le\alpha+\beta$.

**Étape 2 : $\alpha+\beta$ est le sup** (caractérisation ε). Soit $\varepsilon>0$. Il existe $x\in A$ avec $x>\alpha-\frac\varepsilon2$ et $y\in B$ avec $y>\beta-\frac\varepsilon2$. Alors $x+y\in A+B$ et $x+y>\alpha+\beta-\varepsilon$.

$$\boxed{\sup(A+B)=\sup A+\sup B}$$

💡 L'astuce $\frac\varepsilon2+\frac\varepsilon2=\varepsilon$ est la même que dans la preuve de « limite d'une somme ».
Si l'une des parties n'est pas majorée, $A+B$ non plus et l'égalité reste vraie dans $\overline{\mathbb R}$ ($+\infty=+\infty$).

#### (b) $\sup_{x\in A}f(x)$ et $f(\sup A)$, pour $f$ croissante

**Inégalité toujours vraie.** Pour $x\in A$ : $x\le\sup A$, donc (croissance) $f(x)\le f(\sup A)$. Ainsi $f(\sup A)$ majore $f(A)$ :
$$\sup_{x\in A}f(x)\le f(\sup A).$$

**L'égalité peut être fausse.** Contre-exemple : $f(x)=0$ si $x<0$, $f(x)=1$ si $x\ge0$ (croissante), et $A=\,]-1,0[$. Alors $\sup A=0$, $f(\sup A)=1$, mais $f(A)=\{0\}$, donc $\sup f(A)=0<1$.

**Conditions suffisantes d'égalité.**
1. **$\sup A\in A$** (le sup est un max) : alors $f(\sup A)\in f(A)$ et il majore $f(A)$, c'est donc le max de $f(A)$.
2. **$f$ continue en $\sup A$** (en fait la continuité à gauche suffit). Preuve : par l'exercice 5(a), il existe $a_n\in A$ avec $a_n\to\sup A$. Par continuité, $f(a_n)\to f(\sup A)$. Or $f(a_n)\le\sup f(A)$ pour tout $n$, donc en passant à la limite, $f(\sup A)\le\sup f(A)$. Avec l'inégalité précédente : égalité.

💡 Le contre-exemple « marche d'escalier » est **le** contre-exemple type dès qu'une continuité est en jeu.

---

### Exercice 8 — L'ordre $\subset$ sur $\mathcal P(E)$

**(a) Relation d'ordre.** Pour $X,Y,Z\in\mathcal P(E)$ :
- **réflexive** : $X\subset X$ ;
- **antisymétrique** : $X\subset Y$ et $Y\subset X\Rightarrow X=Y$ (principe de double inclusion) ;
- **transitive** : si $X\subset Y\subset Z$ et $x\in X$, alors $x\in Y$ puis $x\in Z$, donc $X\subset Z$.

**(b) Non totale.** Si $a\ne b$ sont deux éléments de $E$, alors $\{a\}\not\subset\{b\}$ (car $a\notin\{b\}$) et $\{b\}\not\subset\{a\}$ : ces deux parties ne sont pas comparables.

**(c) Minorant et majorant triviaux.** Pour toute famille $\mathcal A=\{A_i,\ i\in I\}$ : $\emptyset\subset A_i\subset E$. Donc **$\emptyset$ est un minorant et $E$ un majorant**.

**(d) Borne supérieure et inférieure.**
$$\sup\mathcal A=\bigcup_{i\in I}A_i,\qquad\inf\mathcal A=\bigcap_{i\in I}A_i.$$

*Preuve pour le sup.* Notons $U=\bigcup_iA_i$.
1. $U$ majore $\mathcal A$ : chaque $A_i\subset U$.
2. $U$ est le plus petit majorant : si $M$ vérifie $A_i\subset M$ pour tout $i$, alors tout $x\in U$ appartient à un certain $A_{i_0}\subset M$, donc $x\in M$ : $U\subset M$.

*Preuve pour l'inf.* Notons $J=\bigcap_iA_i$. $J\subset A_i$ pour tout $i$ (minorant) ; si $m\subset A_i$ pour tout $i$, alors tout $x\in m$ est dans chaque $A_i$, donc dans $J$ : $m\subset J$.

💡 Ici le sup existe **toujours**, même si l'ordre n'est pas total. (Cas limite $I=\emptyset$ : $\sup=\emptyset$, $\inf=E$ avec la convention que l'intersection vide vaut $E$.)

---

## Nombres complexes

### Exercice 9 — Deux inégalités/identités

#### (a) $\big\lvert\lvert z\rvert-\lvert z'\rvert\big\rvert\le\lvert z-z'\rvert$ (inégalité triangulaire inverse)

🧭 **Méthode** : écrire $z=(z-z')+z'$ et appliquer l'inégalité triangulaire.

✍️ $\lvert z\rvert=\lvert(z-z')+z'\rvert\le\lvert z-z'\rvert+\lvert z'\rvert$, donc $\lvert z\rvert-\lvert z'\rvert\le\lvert z-z'\rvert$.
En échangeant les rôles : $\lvert z'\rvert-\lvert z\rvert\le\lvert z'-z\rvert=\lvert z-z'\rvert$.
Un réel $t$ tel que $t\le c$ et $-t\le c$ vérifie $\lvert t\rvert\le c$. D'où le résultat. ∎

💡 Utilisée au Chapitre 2 pour montrer : $u_n\to\ell\Rightarrow\lvert u_n\rvert\to\lvert\ell\rvert$.

#### (b) Identité de la médiane (du parallélogramme)

🧭 **Méthode** : avec des modules au carré, on utilise **$\lvert w\rvert^2=w\bar w$**.

✍️
$$\lvert z+z'\rvert^2=(z+z')(\bar z+\bar z')=\lvert z\rvert^2+\lvert z'\rvert^2+z\bar z'+\bar zz',$$
$$\lvert z-z'\rvert^2=(z-z')(\bar z-\bar z')=\lvert z\rvert^2+\lvert z'\rvert^2-z\bar z'-\bar zz'.$$
En sommant, les termes croisés s'éliminent : $\lvert z+z'\rvert^2+\lvert z-z'\rvert^2=2(\lvert z\rvert^2+\lvert z'\rvert^2)$. ∎

💡 Géométrie : dans le parallélogramme construit sur $0$, $z$, $z'$, $z+z'$, la **somme des carrés des diagonales** égale la **somme des carrés des quatre côtés**.

---

### Exercice 10 — Équations dans ℂ

#### $z^2+z+2=0$

🧭 Trinôme (Exemple 4.4 du cours) : $\Delta=1-8=-7$. On cherche $\omega$ avec $\omega^2=-7$ : $\omega=i\sqrt7$.
$$z_\pm=\frac{-1\pm i\sqrt7}{2}.$$
Vérification : somme $=-1=-\frac ba$ ✅ ; produit $=\frac{1+7}{4}=2=\frac ca$ ✅.

#### $z^5=32i$

🧭 Racines $n$-ièmes : forme exponentielle. $32i=32e^{i\pi/2}$ et $32=2^5$. Les solutions sont
$$z_k=2\,e^{i\left(\frac{\pi}{10}+\frac{2k\pi}{5}\right)},\qquad k\in\{0,1,2,3,4\}.$$
Arguments : $\frac{\pi}{10},\ \frac{\pi}{2},\ \frac{9\pi}{10},\ \frac{13\pi}{10},\ \frac{17\pi}{10}$.
En particulier $z_1=2e^{i\pi/2}=2i$, et $(2i)^5=32\,i^5=32i$ ✅.
💡 Les 5 solutions forment un **pentagone régulier** de rayon 2.

#### $e^{iz^2}=1$

🧭 Propriété du cours : $e^{w_1}=e^{w_2}\iff w_1-w_2\in2i\pi\mathbb Z$. Ici $1=e^0$.
$$e^{iz^2}=1\iff iz^2=2ik\pi\ (k\in\mathbb Z)\iff z^2=2k\pi\ (k\in\mathbb Z).$$
- Si $k\ge0$ : $z^2=2k\pi\ge0$, donc $z=\pm\sqrt{2k\pi}$ (réels).
- Si $k<0$ : $z^2=-2\lvert k\rvert\pi<0$, donc $z=\pm i\sqrt{2\lvert k\rvert\pi}$ (imaginaires purs).

$$\boxed{\mathcal S=\left\{\pm\sqrt{2k\pi},\ \pm i\sqrt{2k\pi}\ :\ k\in\mathbb N\right\}}$$
Vérif : $z=i\sqrt{2\pi}$ donne $z^2=-2\pi$, $iz^2=-2i\pi$, $e^{-2i\pi}=1$ ✅.

⚠️ L'équation $z^2=c$ avec $c<0$ a des solutions **dans ℂ** : ne pas oublier les imaginaires purs.

---

### Exercice 11 — Linéarisation de $\cos^nx$ et $\sin^nx$

🧭 **Méthode** (§4.4 du cours) : **formules d'Euler** + **binôme**, puis regrouper $e^{imx}$ et $e^{-imx}$.

#### $\cos^nx$

$$\cos^nx=\left(\frac{e^{ix}+e^{-ix}}{2}\right)^n=\frac1{2^n}\sum_{k=0}^n\binom nk e^{ikx}e^{-i(n-k)x}=\frac{1}{2^n}\sum_{k=0}^n\binom nk e^{i(2k-n)x}.$$
$\cos^nx$ est réel, donc égal à sa partie réelle :
$$\boxed{\cos^nx=\frac1{2^n}\sum_{k=0}^n\binom nk\cos\big((n-2k)x\big)}$$
(on a utilisé $\cos(-\theta)=\cos\theta$). Les coefficients $\alpha=\lvert n-2k\rvert$ sont bien dans $\{0,\dots,n\}$. En regroupant $k$ et $n-k$ (qui donnent le même cosinus, et $\binom nk=\binom n{n-k}$) :
$$\cos^nx=\frac1{2^{n-1}}\sum_{0\le k<n/2}\binom nk\cos\big((n-2k)x\big)\ \ \Big(+\frac1{2^n}\binom{n}{n/2}\ \text{si } n \text{ pair}\Big).$$

**Exemples :**
- $n=2$ : $\cos^2x=\frac{1+\cos2x}{2}$.
- $n=3$ : $\cos^3x=\frac{\cos3x+3\cos x}{4}$.
- $n=4$ : $\cos^4x=\frac{\cos4x+4\cos2x+3}{8}$.

#### $\sin^nx$

$$\sin^nx=\left(\frac{e^{ix}-e^{-ix}}{2i}\right)^n=\frac{1}{(2i)^n}\sum_{k=0}^n\binom nk(-1)^{n-k}e^{i(2k-n)x}.$$
Il faut distinguer selon la **parité** de $n$, car $i^n$ est réel ou imaginaire pur.

**$n=2p$ pair** : $(2i)^{2p}=(-1)^p4^p$. La somme est réelle (égale à $\sin^nx$ à un facteur réel près), on prend sa partie réelle, et $(-1)^{n-k}=(-1)^k$ :
$$\boxed{\sin^{2p}x=\frac{(-1)^p}{4^p}\sum_{k=0}^{2p}(-1)^k\binom{2p}{k}\cos\big((2p-2k)x\big)}$$

**$n=2p+1$ impair** : $(2i)^{n}=2^n(-1)^p\,i$. La somme doit alors être imaginaire pure ; elle vaut $i\sum_k\binom nk(-1)^{n-k}\sin\big((2k-n)x\big)$, d'où
$$\boxed{\sin^{2p+1}x=\frac{(-1)^p}{2^{2p+1}}\sum_{k=0}^{2p+1}(-1)^{n-k}\binom{2p+1}{k}\sin\big((2k-n)x\big)}$$

**Exemples (à vérifier soi-même, c'est un bon entraînement) :**
- $\sin^2x=\frac{1-\cos2x}{2}$ ($p=1$ : $-\frac14[\cos2x-2+\cos2x]$).
- $\sin^3x=\frac{3\sin x-\sin3x}{4}$ ($p=1$ : $-\frac18[2\sin3x-6\sin x]$).
- $\sin^4x=\frac{\cos4x-4\cos2x+3}{8}$.

💡 En pratique au partiel, on ne retient pas la formule générale : on **refait le calcul** pour un $n$ donné (2, 3 ou 4), en développant avec le triangle de Pascal puis en regroupant les termes conjugués. Utilité : calculer des intégrales comme $\int\cos^4x\,dx$.

---

## 🎯 Bilan du TD 1 : ce qu'il faut savoir refaire

1. Calculer une partie entière en **encadrant**, prouver une formule par **unicité** (Ex. 1).
2. Rédiger une **récurrence** propre (Ex. 3, 4).
3. Les **deux caractérisations du sup** (Ex. 5) : elles servent dans tous les exercices sur les ensembles.
4. **Décrire l'ensemble explicitement**, puis majorant → max ? → sup (Ex. 6).
5. La technique **$\frac\varepsilon2+\frac\varepsilon2$** (Ex. 7) et le contre-exemple **marche d'escalier**.
6. Modules : **$\lvert w\rvert^2=w\bar w$** ; racines $n$-ièmes en **forme exponentielle** ; $e^{w}=1\iff w\in2i\pi\mathbb Z$.
7. **Linéarisation** par Euler + binôme.
