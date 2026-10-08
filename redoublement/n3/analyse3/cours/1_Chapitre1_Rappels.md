# Analyse 3 — Chapitre 1 : Rappels (cours expliqué)

> L2 Informatique — USPN. Ce fichier reprend **tout** le chapitre 1, avec des explications, des intuitions, des preuves commentées et des exemples supplémentaires.
> Légende : 🎯 = à savoir par cœur · ⚠️ = piège classique · 💡 = intuition · ✍️ = preuve à savoir refaire

---

## Sommaire

1. Entiers et rationnels (structures algébriques)
2. Relations d'ordre, majorants, borne supérieure
3. Le corps des réels ℝ (Archimède, partie entière, droite achevée, intervalles)
4. Les nombres complexes ℂ
5. Cardinal d'un ensemble (dénombrabilité, Cantor)

---

## 1. Entiers et rationnels

On a $\mathbb N \subset \mathbb Z \subset \mathbb Q$, avec $+$ et $\times$ :

| Propriété | ℕ | ℤ | ℚ |
|---|---|---|---|
| $+$ et $\times$ associatives, commutatives | ✅ | ✅ | ✅ |
| neutres $0$ et $1$ | ✅ | ✅ | ✅ |
| distributivité | ✅ | ✅ | ✅ |
| opposé $-a$ pour tout $a$ | ❌ ($1$ n'a pas d'opposé) | ✅ | ✅ |
| inverse $1/a$ pour tout $a\neq 0$ | ❌ | ❌ ($2$ n'a pas d'inverse) | ✅ |

### Vocabulaire (à revoir, ça tombe en question de cours)

- **Groupe** $(G,*)$ : loi associative, élément neutre, tout élément a un symétrique. **Abélien** = commutatif.
- **Anneau** $(A,+,\times)$ : $(A,+)$ groupe abélien, $\times$ associative avec neutre, distributive sur $+$.
- **Corps** : anneau commutatif où tout élément **non nul** est inversible.

🎯 Conclusion : $(\mathbb Z,+)$ et $(\mathbb Q,+)$ sont des groupes abéliens ; $(\mathbb Z,+,\times)$ est un anneau commutatif (pas un corps) ; $(\mathbb Q,+,\times)$ est un corps commutatif.

💡 **Construction** : ℕ = 0, 1, 1+1, … (lié à la **récurrence**) ; ℤ = on ajoute les opposés ; ℚ = on ajoute les inverses, avec l'identification $\frac ab = \frac cd \iff ad = bc$.

---

## 2. Relations d'ordre et borne supérieure

### 2.1 Relation d'ordre 🎯

Une relation binaire $\le$ sur $E$ est une **relation d'ordre** si elle est :
- **réflexive** : $\forall x,\ x\le x$
- **antisymétrique** : $x\le y$ et $y\le x \Rightarrow x=y$
- **transitive** : $x\le y$ et $y\le z \Rightarrow x\le z$

Elle est **totale** si deux éléments sont toujours comparables : $\forall x,y,\ x\le y$ ou $y\le x$.

**Exemples**
- $\le$ usuel sur ℕ, ℤ, ℚ, ℝ : ordre **total**.
- L'inclusion $\subset$ sur $\mathcal P(E)$ : ordre **partiel** dès que $E$ a ≥ 2 éléments. Avec $E=\{1,2\}$ : ni $\{1\}\subset\{2\}$ ni $\{2\}\subset\{1\}$.
- La divisibilité $\mid$ sur ℕ : ordre partiel ($2\nmid 3$ et $3\nmid 2$). ⚠️ Sur ℤ ce n'est **pas** un ordre : $2\mid -2$ et $-2\mid 2$ mais $2\neq -2$ (antisymétrie fausse).

### 2.2 Majorants, minorants, max, min 🎯

Soit $F\subset E$.
- $y\in E$ est un **majorant** de $F$ si $\forall x\in F,\ x\le y$. (Il n'a **pas** besoin d'être dans $F$.)
- Un majorant **qui appartient à $F$** est le **plus grand élément** (max) de $F$.
- Idem pour minorant / plus petit élément (min).

⚠️ Un ensemble majoré peut ne pas avoir de max. Exemple fondamental :
$$B = \{x\in\mathbb Q : 0\le x<2\}$$
$2$ majore $B$ mais $2\notin B$. Et $B$ n'a **pas** de max.

✍️ **Preuve (technique du milieu)** : si $m$ était le max, $0\le m<2$, donc $m<\frac{m+2}{2}<2$. Le milieu $\frac{m+2}{2}$ est rationnel, dans $B$, et $>m$ : contradiction.

💡 Cette astuce « prendre le milieu entre $m$ et la borne » sert très souvent.

### 2.3 Propriétés de ℕ et ℤ (à connaître)

- (a) Toute partie **non vide** de ℕ a un plus petit élément (c'est le principe du **bon ordre**, équivalent à la récurrence).
- (b) Toute partie non vide **majorée** de ℤ a un plus grand élément.
- (c) Toute partie non vide **minorée** de ℤ a un plus petit élément.

⚠️ Tout cela est **faux dans ℚ** (cf. $B$).

### 2.4 Borne supérieure / inférieure 🎯

**Définition.** $m$ est la **borne supérieure** de $F$ si $m$ est un majorant de $F$ et si $m\le M$ pour tout autre majorant $M$. Autrement dit :
$$\sup F = \text{le plus petit des majorants.}$$
De même $\inf F$ = le plus grand des minorants.

**Liens avec max/min :**
- Si $F$ a un max, alors $\sup F = \max F$.
- $\sup F$ existe sans forcément être dans $F$. Si $\sup F\in F$, c'est le max.

#### 🎯 Caractérisation pratique (LA méthode d'exercice)

Pour $F\subset\mathbb R$ non vide, $m=\sup F$ si et seulement si :
1. $\forall x\in F,\ x\le m$ ($m$ est un majorant) ;
2. $\forall\varepsilon>0,\ \exists x\in F,\ x>m-\varepsilon$ (rien de plus petit que $m$ ne majore $F$).

De même $m=\inf F$ ssi : (1) $\forall x\in F,\ m\le x$ ; (2) $\forall\varepsilon>0,\ \exists x\in F,\ x<m+\varepsilon$.

💡 Le point 2 dit : « je peux m'approcher de $m$ par des éléments de $F$ aussi près que je veux ».

**Exemple :** $\sup B=2$ (preuve du cours) : $2$ majore $B$ ; si $M<2$ était un majorant, $\frac{M+2}{2}$ serait dans $B$ (si $M\ge0$) et $>M$ : contradiction.

### 2.5 Propriété de la borne supérieure

$(E,\le)$ a la **propriété de la borne supérieure** si **toute partie non vide et majorée** admet une borne supérieure (dans $E$).

🎯 **ℚ ne l'a pas.** L'ensemble
$$C=\{x\in\mathbb Q: x\ge0 \text{ et } x^2<2\}$$
est non vide ($1\in C$), majoré (par $2$), mais n'a pas de borne sup dans ℚ (sa « vraie » borne sup serait $\sqrt2\notin\mathbb Q$).

✍️ **Structure de la preuve** (à savoir expliquer) :
1. Supposons $m=\sup C\in\mathbb Q$. On a $m\ge1$.
2. Si $m^2<2$ : on trouve $\varepsilon>0$ rationnel petit tel que $(m+\varepsilon)^2<2$, donc $m+\varepsilon\in C$ et $m+\varepsilon>m$ : $m$ n'est pas majorant. Contradiction. (Choix : $\varepsilon<\min\left(1,\frac{2-m^2}{4m}\right)$ ; alors $2m\varepsilon+\varepsilon^2<2-m^2$.)
3. Si $m^2>2$ : $m-\varepsilon$ est encore un majorant pour $\varepsilon$ petit, plus petit que $m$. Contradiction.
4. Donc $m^2=2$, impossible avec $m$ rationnel :

✍️ **$\sqrt2\notin\mathbb Q$** 🎯 : si $m=a/b$ avec $a,b$ premiers entre eux, $a^2=2b^2$ donc $a^2$ pair, donc $a$ pair ($a=2a'$), donc $2b^2=4a'^2$, $b^2=2a'^2$ pair, $b$ pair. $a$ et $b$ pairs : contradiction.

(Pour « $a^2$ pair ⇒ $a$ pair » : par contraposée, si $a=2k+1$ alors $a^2=4k^2+4k+1$ impair.)

---

## 3. Le corps des réels

### 3.1 Définition axiomatique 🎯

**Théorème (admis).** Il existe un corps commutatif **totalement ordonné**, contenant ℚ, ayant la **propriété de la borne supérieure**. C'est **ℝ** (unique à isomorphisme près).

💡 ℝ = ℚ « sans trous ». Tout ce qui fait la puissance de l'analyse (limites monotones, suites adjacentes…) vient de la propriété de la borne sup.

### 3.2 Propriété d'Archimède 🎯

**Théorème.** $\forall a>0,\ \forall b>0,\ \exists n\in\mathbb N,\ na>b$.

💡 « En ajoutant assez de fois un petit nombre, on dépasse n'importe quel grand nombre. » Conséquence : ℕ n'est pas majoré dans ℝ ; pour tout $\varepsilon>0$ il existe $n$ avec $1/n<\varepsilon$ (utilisé sans arrêt dans les preuves en $\varepsilon$).

✍️ **Preuve** : sinon $A=\{n\in\mathbb N: na\le b\}=\mathbb N$ serait majoré, de borne sup $m$. $m-1$ n'est pas majorant, donc il existe $k>m-1$, d'où $k+1>m$ avec $k+1\in\mathbb N$ : contradiction.

### 3.3 Partie entière 🎯

$E(x)=\lfloor x\rfloor$ = l'unique entier $n$ tel que $n\le x<n+1$.

- ⚠️ $\lfloor -0{,}5\rfloor=-1$ (et pas $0$ !). $\lfloor -3\rfloor=-3$, $\lfloor \pi\rfloor = 3$.
- Inégalités utiles : $x-1<\lfloor x\rfloor\le x$.
- Partie entière supérieure : $\lceil x\rceil$ = unique entier avec $x\le\lceil x\rceil<x+1$.

✍️ **Unicité** (exercice du cours) : si $n\le x<n+1$ et $n'\le x<n'+1$, alors $n\le x<n'+1$ donc $n<n'+1$, i.e. $n\le n'$ (entiers). Symétriquement $n'\le n$. Donc $n=n'$.

### 3.4 Droite réelle achevée

$\overline{\mathbb R}=\mathbb R\cup\{-\infty,+\infty\}$ avec $-\infty<x<+\infty$ pour tout réel $x$.
Dans $\overline{\mathbb R}$, **toute partie non vide** a un sup et un inf ($\sup=+\infty$ si non majorée).

### 3.5 Intervalles

$[a,b]$ (fermé, = **segment**), $]a,b[$ (ouvert), $]a,b]$, $[a,b[$ (semi-ouverts), plus $]a,+\infty[$, etc. Notation anglaise : $(a,b)$, $(a,b]$, $[a,b)$.

---

## 4. Les nombres complexes

### 4.1 Définition

$\mathbb C=\mathbb R^2$ avec $(x,y)+(x',y')=(x+x',y+y')$ et $(x,y)(x',y')=(xx'-yy',\ xy'+x'y)$.
On pose $i=(0,1)$ : $i^2=-1$, et on écrit $z=x+iy$, $\mathrm{Re}\,z=x$, $\mathrm{Im}\,z=y$.
ℝ s'identifie à $\{(x,0)\}$ via un **morphisme injectif de corps** (plongement).

### 4.2 Formules 🎯

| Objet | Formule |
|---|---|
| Conjugué | $\bar z=x-iy$ |
| Partie réelle / imaginaire | $\mathrm{Re}\,z=\dfrac{z+\bar z}{2}$, $\mathrm{Im}\,z=\dfrac{z-\bar z}{2i}$ |
| Module | $\lvert z\rvert=\sqrt{x^2+y^2}$, $\lvert z\rvert^2=z\bar z$ |
| Inverse ($z\ne0$) | $\dfrac1z=\dfrac{\bar z}{\lvert z\rvert^2}=\dfrac{x-iy}{x^2+y^2}$ |
| Inégalité triangulaire | $\lvert z+z'\rvert\le\lvert z\rvert+\lvert z'\rvert$ |
| Inég. triangulaire inverse | $\big\lvert\,\lvert z\rvert-\lvert z'\rvert\,\big\rvert\le\lvert z-z'\rvert$ |

**Exemple :** $\dfrac{1}{3+4i}=\dfrac{3-4i}{25}$ ; $\lvert 3+4i\rvert=5$.

### 4.3 Géométrie

- $z=x+iy$ ↔ point $M_z(x,y)$ ; $z$ = **affixe** de $M_z$.
- $\lvert z-z'\rvert$ = **distance** entre $M_z$ et $M_{z'}$.
- $\lvert z\rvert=1$ ⟺ $z=\cos\theta+i\sin\theta$ ⟺ $M_z$ sur le cercle trigonométrique.

### 4.4 Exponentielle complexe 🎯

$$e^{x+iy}=e^x(\cos y+i\sin y),\qquad e^{i\theta}=\cos\theta+i\sin\theta\ \text{(Euler)}$$

- $e^{z_1+z_2}=e^{z_1}e^{z_2}$, $(e^z)^n=e^{nz}$
- $\lvert e^z\rvert=e^{\mathrm{Re}\,z}>0$ : **l'exponentielle ne s'annule jamais**.
- Forme polaire : $z=\rho e^{i\theta}$, $\rho=\lvert z\rvert$.
- $e^{z_1}=e^{z_2}\iff z_1-z_2\in 2i\pi\mathbb Z$.
- Formules d'Euler : $\cos\theta=\dfrac{e^{i\theta}+e^{-i\theta}}{2}$, $\sin\theta=\dfrac{e^{i\theta}-e^{-i\theta}}{2i}$.

**Retrouver la trigo** : $\cos(a+b)=\mathrm{Re}(e^{ia}e^{ib})=\cos a\cos b-\sin a\sin b$ et $\sin(a+b)=\mathrm{Im}(\ldots)=\sin a\cos b+\cos a\sin b$.

#### Racines $n$-ièmes 🎯

Les racines $n$-ièmes de $\rho e^{i\theta}$ ($\rho>0$) sont les $n$ nombres
$$\rho^{1/n}\,e^{i\frac{\theta+2k\pi}{n}},\qquad k=0,\dots,n-1.$$
💡 Géométriquement : $n$ points régulièrement espacés sur le cercle de rayon $\rho^{1/n}$ (polygone régulier).

**Exemple : racines cubiques de $8i$.** $8i=8e^{i\pi/2}$, donc $z_k=2e^{i(\pi/6+2k\pi/3)}$ :
$z_0=2e^{i\pi/6}=\sqrt3+i$, $z_1=2e^{i5\pi/6}=-\sqrt3+i$, $z_2=2e^{i3\pi/2}=-2i$.
Vérification : $(-2i)^3=-8i^3=8i$ ✅.

**Racines de l'unité** : $e^{2ik\pi/n}$. Pour $n=3$ : $1,\ j=e^{2i\pi/3}=-\frac12+i\frac{\sqrt3}{2},\ j^2=\bar j$, et $1+j+j^2=0$.

### 4.5 Théorème de d'Alembert(-Gauss) (admis) 🎯

Tout polynôme complexe de degré $n\ge1$ a **exactement $n$ racines comptées avec multiplicité** :
$P(X)=a_n\prod_j (X-\alpha_j)^{\mu_j}$ avec $\sum\mu_j=n$.

**Trinôme** $aX^2+bX+c$ : $\Delta=b^2-4ac$, on cherche $\omega$ avec $\omega^2=\Delta$, et
$$r_\pm=\frac{-b\pm\omega}{2a}.$$
Racine double ⟺ $\Delta=0$.

**Exemple :** $z^2-2z+5=0$ : $\Delta=-16=(4i)^2$, racines $1\pm2i$.

⚠️ **Pas d'ordre sur ℂ** : on n'écrit **jamais** $z<z'$ entre complexes, ni d'intervalle complexe. On compare des **modules** (réels).

---

## 5. Cardinal d'un ensemble

### 5.1 Cas fini (Prop. 5.1)

Pour $A,B$ finis non vides, équivalence entre :
(a) $\mathrm{card}\,A\ge\mathrm{card}\,B$ ; (b) ∃ injection $B\to A$ ; (c) ∃ surjection $A\to B$.
Et $\mathrm{card}\,A=\mathrm{card}\,B$ ⟺ ∃ bijection.

💡 Idée de Cantor : on **définit** la taille des ensembles infinis par ces caractérisations.

### 5.2 Définitions générales 🎯

- $\mathrm{card}\,E=\mathrm{card}\,F$ ⟺ il existe une **bijection** $E\to F$.
- $\mathrm{card}\,E\le\mathrm{card}\,F$ ⟺ il existe une **injection** $E\to F$.
- Si $A\neq\emptyset$ : $\mathrm{card}\,A\le\mathrm{card}\,B$ ⟺ il existe une **surjection** $B\to A$ (Prop. 5.5 ; le sens ⇐ utilise l'axiome du choix).

⚠️ Sens des flèches : injection **de $E$ vers $F$** = « $E$ est plus petit ». Surjection **de $B$ vers $A$** = « $A$ est plus petit ».

✍️ **Prop. 5.5, sens ⇒** : avec $\varphi:A\to B$ injective et $a\in A$ fixé, on pose $\psi(y)=x$ si $y=\varphi(x)$ (unique par injectivité), $\psi(y)=a$ sinon. $\psi$ est surjective car $\psi(\varphi(x))=x$.

### 5.3 Cantor–Bernstein (admis) 🎯

S'il existe une injection $E\to F$ **et** une injection $F\to E$, alors il existe une bijection $E\to F$.

💡 **Outil n°1** pour montrer que deux ensembles ont même cardinal : on n'a pas besoin de construire la bijection, juste deux injections (souvent faciles).

**Exemple :** $[0,1]$ et $]0,1[$. Injection $]0,1[\to[0,1]$ : l'inclusion. Injection $[0,1]\to]0,1[$ : $x\mapsto\frac14+\frac x2$ (image $[\frac14,\frac34]$). Donc même cardinal.

### 5.4 Dénombrabilité 🎯

- **Prop. 5.7** : si $E$ est infini, $\mathrm{card}\,\mathbb N\le\mathrm{card}\,E$. **ℕ est le plus petit infini.** (On construit $\varphi(0),\varphi(1),\ldots$ par récurrence en choisissant à chaque fois un élément pas encore pris.)
- $E$ **dénombrable** ⟺ $\mathrm{card}\,E=\mathrm{card}\,\mathbb N$ (on peut numéroter ses éléments $e_0,e_1,e_2,\ldots$ sans en oublier).
- **Au plus dénombrable** = fini ou dénombrable.
- **Prop. 5.9** : toute partie **infinie** de ℕ est dénombrable (Cantor–Bernstein : inclusion + Prop. 5.7).

#### Les grands exemples 🎯

**ℤ est dénombrable.** On numérote $0,1,-1,2,-2,\ldots$ :
$$f(x)=\begin{cases}2x-1 & x>0\\ -2x & x\le0\end{cases}$$
($1\mapsto1$, $-1\mapsto2$, $2\mapsto3$, $-2\mapsto4$, $0\mapsto0$.) Positifs → impairs, négatifs ou nul → pairs : bijection.

**ℕ² est dénombrable** (bijection de Cantor, par diagonales) :
$$\varphi(a,b)=\frac{(a+b)(a+b+1)}{2}+b$$
On parcourt les diagonales $a+b=0,1,2,\ldots$ : $(0,0),(1,0),(0,1),(2,0),(1,1),(0,2),(3,0),\ldots$
Avant la diagonale $a+b=s$, il y a $1+2+\dots+s=\frac{s(s+1)}{2}$ couples ; $b$ donne la position dans la diagonale.

**ℚ est dénombrable** : $r=\frac ab$ (forme irréductible, $b>0$) $\mapsto(a,b)$ est une injection de ℚ dans $\mathbb Z\times\mathbb N$, qui est dénombrable. Et ℚ est infini ⇒ dénombrable (Cantor–Bernstein).

**Produits finis** : $\mathbb N^k$ dénombrable (ex. $\mathbb N^3$ : $(a,b,c)\mapsto\varphi(\varphi(a,b),c)$ est une bijection).

### 5.5 Théorème de Cantor 🎯✍️ (preuve à connaître PAR CŒUR)

**Théorème.** Pour tout ensemble $E$, il n'existe **pas de surjection** $E\to\mathcal P(E)$.

**Preuve (argument diagonal).** Supposons $\psi:E\to\mathcal P(E)$ surjective. Posons
$$D=\{x\in E : x\notin\psi(x)\}.$$
$D\in\mathcal P(E)$, donc par surjectivité $D=\psi(d)$ pour un $d\in E$. Alors
$$d\in D\iff d\notin\psi(d)\iff d\notin D.$$
Contradiction. ∎

💡 $D$ est construit pour être **différent de chaque $\psi(x)$** : il diffère de $\psi(x)$ au moins sur l'élément $x$.

Comme $x\mapsto\{x\}$ est une injection $E\to\mathcal P(E)$ :
$$\mathrm{card}\,E<\mathrm{card}\,\mathcal P(E).$$
Donc $\mathbb N<\mathcal P(\mathbb N)<\mathcal P(\mathcal P(\mathbb N))<\cdots$ : **une infinité d'infinis différents**.

### 5.6 Le continu

**Théorème (preuve hors programme).** $\mathrm{card}\,]0,1[\,=\mathrm{card}\,\mathbb R=\mathrm{card}\,\mathcal P(\mathbb N)$.

- Bijection $]0,1[\to\mathbb R$ : $x\mapsto\frac{1}{1-x}-\frac1x$ (strictement croissante, continue, limites $-\infty$ en $0$ et $+\infty$ en $1$). Autre : $x\mapsto\tan(\pi(x-\frac12))$.
- $\mathcal P(\mathbb N)\leftrightarrow\{0,1\}^{\mathbb N}$ : $A\mapsto$ la suite indicatrice ($a_n=1$ si $n\in A$).
- $]0,1[\to\{0,1\}^{\mathbb N}$ : développement binaire (injection).

🎯 **Donc ℝ n'est pas dénombrable.** On appelle $\mathrm{card}\,\mathbb R$ la **puissance du continu**. Ont aussi cette puissance : $\mathcal P(\mathbb N)$, $\{0,1\}^{\mathbb N}$, $\mathbb R^k$, ℂ, tout intervalle non réduit à un point.

**Hypothèse du continu** : existe-t-il $E$ avec $\mathrm{card}\,\mathbb N<\mathrm{card}\,E<\mathrm{card}\,\mathbb R$ ? **Indécidable** (Gödel 1938, Cohen 1963) dans la théorie des ensembles usuelle.

---

## ✅ À retenir (selon le prof)

- Notions de **cardinal** et d'ensemble **dénombrable**.
- **ℕᵏ et ℚ sont dénombrables.**
- $\mathrm{card}\,E<\mathrm{card}\,\mathcal P(E)$ (Cantor) et $\mathrm{card}\,\mathcal P(\mathbb N)=\mathrm{card}\,\mathbb R$.

Plus, pour les exercices : la **caractérisation ε de sup/inf**, la preuve de **$\sqrt2\notin\mathbb Q$**, **Archimède**, la **partie entière**, les **racines $n$-ièmes** et la résolution des **trinômes dans ℂ**.
