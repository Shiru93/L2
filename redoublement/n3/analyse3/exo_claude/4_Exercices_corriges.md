# Analyse 3 — Exercices corrigés

> Méthode conseillée : cache la correction, cherche 10–15 min, puis compare **la rédaction** autant que le résultat.
> Niveau : ⭐ application directe · ⭐⭐ classique de partiel · ⭐⭐⭐ plus difficile

---

# PARTIE A — Chapitre 1 (ensembles, ℝ, ℂ, cardinaux)

## A1 ⭐ Borne sup d'un ensemble de type $1-\frac1n$

Soit $A=\left\{1-\frac1n : n\in\mathbb N^*\right\}$. Déterminer $\sup A$, $\inf A$, et s'ils sont atteints.

<details><summary><b>Correction</b></summary>

**Inf.** Pour tout $n\ge1$, $\frac1n\le1$ donc $1-\frac1n\ge0$ : $0$ est un minorant. De plus $0=1-\frac11\in A$. Donc $0=\min A=\inf A$.

**Sup.** Pour tout $n$, $1-\frac1n<1$ : $1$ est un majorant.
Soit $\varepsilon>0$. Par Archimède, il existe $n\in\mathbb N^*$ avec $n>\frac1\varepsilon$, i.e. $\frac1n<\varepsilon$. Alors $1-\frac1n>1-\varepsilon$ : $1-\varepsilon$ n'est pas un majorant. Donc $\sup A=1$.
Comme $1-\frac1n=1\iff\frac1n=0$, impossible, $1\notin A$ : **$A$ n'a pas de plus grand élément**.
</details>

## A2 ⭐ (Exemple 2.5 du cours)

$A=\{x\in\mathbb N : x^2<111\}$. Plus grand et plus petit élément ?

<details><summary><b>Correction</b></summary>

$10^2=100<111$ et $11^2=121\ge111$. Si $x\ge11$, $x^2\ge121$ donc $x\notin A$. Ainsi $A=\{0,1,\dots,10\}$ : $\max A=10$, $\min A=0$.
</details>

## A3 ⭐⭐ Sup/inf avec deux paramètres

$F=\left\{\frac1n+\frac1m : n,m\in\mathbb N^*\right\}$. Déterminer $\sup F$, $\inf F$.

<details><summary><b>Correction</b></summary>

**Sup.** $\frac1n\le1$ et $\frac1m\le1$ donc tout élément est $\le2$, et $2=\frac11+\frac11\in F$. Donc $\max F=\sup F=2$.

**Inf.** Tout élément est $>0$ : $0$ est un minorant. Soit $\varepsilon>0$ ; on prend $n=m>\frac2\varepsilon$ (Archimède). Alors $\frac1n+\frac1m=\frac2n<\varepsilon=0+\varepsilon$. Donc $\inf F=0$. Comme tous les éléments sont $>0$, $0\notin F$ : pas de min.
</details>

## A4 ⭐⭐ $\sqrt3$ est irrationnel

<details><summary><b>Correction</b></summary>

Par l'absurde, $\sqrt3=\frac ab$ avec $a,b\in\mathbb N^*$ premiers entre eux. Alors $a^2=3b^2$, donc $3\mid a^2$. Comme $3$ est premier, $3\mid a$ (lemme d'Euclide) : $a=3a'$. Alors $9a'^2=3b^2$, soit $b^2=3a'^2$, donc $3\mid b^2$ et $3\mid b$. Ainsi $3$ divise $a$ et $b$ : contradiction.

*Variante sans lemme d'Euclide* : si $3\nmid a$, $a=3k\pm1$, $a^2=9k^2\pm6k+1\equiv1\pmod 3$.
</details>

## A5 ⭐ Partie entière

1. Montrer que $\lfloor x+k\rfloor=\lfloor x\rfloor+k$ pour $x\in\mathbb R$, $k\in\mathbb Z$.
2. A-t-on $\lfloor2x\rfloor=2\lfloor x\rfloor$ ?
3. Calculer $\lfloor-2{,}3\rfloor$, $\lfloor\pi\rfloor$, $\lfloor-\pi\rfloor$.

<details><summary><b>Correction</b></summary>

1. $n=\lfloor x\rfloor$ vérifie $n\le x<n+1$, donc $n+k\le x+k<n+k+1$ avec $n+k\in\mathbb Z$. Par **unicité** de la partie entière, $\lfloor x+k\rfloor=n+k$.
2. Non : $x=0{,}5$ donne $\lfloor1\rfloor=1\ne0=2\lfloor0{,}5\rfloor$.
3. $-3$, $3$, $-4$.
</details>

## A6 ⭐ Calculs complexes

1. Module, inverse et forme exponentielle de $z=1+i$.
2. Calculer $(1+i)^8$.
3. Linéariser $\cos^3\theta$.

<details><summary><b>Correction</b></summary>

1. $\lvert z\rvert=\sqrt2$, $\frac1z=\frac{1-i}{2}$, $z=\sqrt2\left(\frac{\sqrt2}2+i\frac{\sqrt2}2\right)=\sqrt2e^{i\pi/4}$.
2. $(1+i)^8=(\sqrt2)^8e^{8i\pi/4}=16e^{2i\pi}=16$.
3. $\cos^3\theta=\left(\frac{e^{i\theta}+e^{-i\theta}}2\right)^3=\frac18\left(e^{3i\theta}+3e^{i\theta}+3e^{-i\theta}+e^{-3i\theta}\right)=\frac{2\cos3\theta+6\cos\theta}{8}=\frac{\cos3\theta+3\cos\theta}{4}$.
</details>

## A7 ⭐⭐ Trinôme à coefficients complexes

Résoudre $z^2-(1+i)z+i=0$.

<details><summary><b>Correction</b></summary>

$\Delta=(1+i)^2-4i=2i-4i=-2i$. On cherche $\omega=a+ib$ avec $\omega^2=-2i$ :
$a^2-b^2=0$, $2ab=-2$, d'où $a=1,b=-1$ : $\omega=1-i$ (vérif. $(1-i)^2=1-2i-1=-2i$ ✅).
$$z=\frac{(1+i)\pm(1-i)}{2}\quad\Rightarrow\quad z_1=1,\ z_2=i.$$
Vérification : somme $1+i$, produit $i$ ✅.
</details>

## A8 ⭐ Racines $n$-ièmes

Résoudre $z^6=1$ et placer les solutions.

<details><summary><b>Correction</b></summary>

$z_k=e^{2ik\pi/6}=e^{ik\pi/3}$, $k=0,\dots,5$ : $1,\ \frac12+i\frac{\sqrt3}2,\ -\frac12+i\frac{\sqrt3}2,\ -1,\ -\frac12-i\frac{\sqrt3}2,\ \frac12-i\frac{\sqrt3}2$. Ce sont les sommets d'un **hexagone régulier** inscrit dans le cercle unité.
</details>

## A9 ⭐ Ordre non total

Montrer que $\subset$ est une relation d'ordre sur $\mathcal P(\{1,2\})$, non totale.

<details><summary><b>Correction</b></summary>

Réflexive ($A\subset A$), antisymétrique ($A\subset B$ et $B\subset A\Rightarrow A=B$, double inclusion), transitive. Non totale : $\{1\}\not\subset\{2\}$ et $\{2\}\not\subset\{1\}$.
</details>

## A10 ⭐⭐ Dénombrabilité

1. Montrer que $2\mathbb N$ (entiers pairs) est dénombrable de deux façons.
2. Montrer que $\mathbb N^3$ est dénombrable.
3. Montrer que $\mathbb Z\times\mathbb Z$ est dénombrable.

<details><summary><b>Correction</b></summary>

1. (a) $n\mapsto2n$ est une bijection $\mathbb N\to2\mathbb N$. (b) $2\mathbb N$ est une partie infinie de ℕ ⇒ dénombrable (Prop. 5.9).
2. Avec $\varphi:\mathbb N^2\to\mathbb N$ bijective (Cantor), $\Phi(a,b,c)=\varphi(\varphi(a,b),c)$ est bijective (composée de bijections : $(a,b,c)\mapsto(\varphi(a,b),c)$ est bijective $\mathbb N^3\to\mathbb N^2$, puis $\varphi$).
3. Avec $f:\mathbb Z\to\mathbb N$ bijective, $(x,y)\mapsto(f(x),f(y))$ est une bijection $\mathbb Z^2\to\mathbb N^2$, et $\mathbb N^2$ est dénombrable.
</details>

## A11 ⭐⭐ Bijections entre intervalles

1. Bijection de $]0,1[$ sur $]2,5[$.
2. Bijection de $]0,1[$ sur $]1,+\infty[$.
3. En déduire que $]2,5[$ a la puissance du continu.

<details><summary><b>Correction</b></summary>

1. $x\mapsto2+3x$ (affine strictement croissante, réciproque $y\mapsto\frac{y-2}{3}$).
2. $x\mapsto\frac1x$ : réciproque $y\mapsto\frac1y$, qui envoie bien $]1,+\infty[$ dans $]0,1[$.
3. $\mathrm{card}\,]2,5[\,=\mathrm{card}\,]0,1[\,=\mathrm{card}\,\mathbb R$ (Théorème 5.12 ; composer les bijections).
</details>

## A12 ⭐⭐ Cantor sur un exemple concret

$E=\{1,2,3\}$, $\psi(1)=\{1,2\}$, $\psi(2)=\emptyset$, $\psi(3)=\{1\}$. Calculer $D=\{x\in E:x\notin\psi(x)\}$ et vérifier qu'il n'a pas d'antécédent.

<details><summary><b>Correction</b></summary>

$1\in\psi(1)$ ⇒ $1\notin D$ ; $2\notin\emptyset$ ⇒ $2\in D$ ; $3\notin\{1\}$ ⇒ $3\in D$. Donc $D=\{2,3\}$, qui n'est ni $\{1,2\}$, ni $\emptyset$, ni $\{1\}$. $D$ diffère de $\psi(x)$ sur l'élément $x$ : c'est exactement l'argument diagonal.
</details>

## A13 ⭐⭐⭐ $\{0,1\}^{\mathbb N}$ n'est pas dénombrable (argument diagonal direct)

<details><summary><b>Correction</b></summary>

Supposons $n\mapsto s^{(n)}$ une surjection de ℕ sur $\{0,1\}^{\mathbb N}$, où $s^{(n)}=(s^{(n)}_0,s^{(n)}_1,\dots)$. Définissons $t_k=1-s^{(k)}_k$. La suite $t$ diffère de chaque $s^{(n)}$ en position $n$ ($t_n\ne s^{(n)}_n$) : elle n'est l'image d'aucun $n$. Contradiction.
(C'est le théorème de Cantor via la bijection $\mathcal P(\mathbb N)\leftrightarrow\{0,1\}^{\mathbb N}$.)
</details>

## A14 ⭐⭐ Cantor–Bernstein

Montrer que $\mathrm{card}\,[0,1]=\mathrm{card}\,]0,1[$ et que $\mathrm{card}\,\mathbb R^2\ge\mathrm{card}\,\mathbb R$.

<details><summary><b>Correction</b></summary>

- Inclusion $]0,1[\hookrightarrow[0,1]$ et $x\mapsto\frac14+\frac x2$ de $[0,1]$ dans $]0,1[$ : injections ⇒ Cantor–Bernstein.
- $x\mapsto(x,0)$ est une injection $\mathbb R\to\mathbb R^2$.
</details>

---

# PARTIE B — Chapitre 2 (suites)

## B1 ⭐ Limite par la définition

Montrer avec la définition que $u_n=\frac{2n+1}{n+3}\to2$, puis que $v_n=n^2+1\to+\infty$.

<details><summary><b>Correction</b></summary>

$\lvert u_n-2\rvert=\left\lvert\frac{2n+1-2n-6}{n+3}\right\rvert=\frac5{n+3}$.
Soit $\varepsilon>0$. Par Archimède, soit $N\in\mathbb N$ avec $N>\frac5\varepsilon$. Pour $n\ge N$ : $\frac5{n+3}<\frac5N<\varepsilon$. Donc $u_n\to2$.

Soit $A\in\mathbb R$. Prenons $N\in\mathbb N$ avec $N\ge\lvert A\rvert$. Pour $n\ge N$ : $n^2+1\ge n\ge N\ge A$ (car $n^2\ge n$ pour $n\in\mathbb N$). Donc $v_n\to+\infty$.
</details>

## B2 ⭐ Divergences

Montrer que $((-1)^n)$ et $(\cos\frac{n\pi}{2})$ divergent.

<details><summary><b>Correction</b></summary>

$u_{2n}=1\to1$, $u_{2n+1}=-1\to-1$ : deux suites extraites de limites différentes ⇒ divergence (une suite convergente a toutes ses extraites de même limite).
$\cos\frac{n\pi}{2}$ : pour $n=4k$ vaut $1$, pour $n=4k+2$ vaut $-1$ ⇒ divergente (c'est d'ailleurs une suite périodique non constante).
</details>

## B3 ⭐⭐ Calculs de limites

Déterminer :
a) $\dfrac{3n^2-n+1}{2n^2+5}$ b) $n^3-2^n$ c) $\sqrt{n+1}-\sqrt n$ d) $\dfrac{\sin n}{n}$
e) $\dfrac{n!}{n^n}$ f) $\dfrac{2^n+3^n}{3^n+1}$ g) $\dfrac{n^2}{2^n}$ h) $\dfrac{2^n}{n!}$

<details><summary><b>Correction</b></summary>

a) $=\frac{n^2(3-\frac1n+\frac1{n^2})}{n^2(2+\frac5{n^2})}\to\frac32$.
b) $=-2^n\left(1-\frac{n^3}{2^n}\right)$ ; $\frac{n^3}{2^n}\to0$ (croissances comparées) ⇒ $\to-\infty$.
c) $=\frac{(n+1)-n}{\sqrt{n+1}+\sqrt n}=\frac1{\sqrt{n+1}+\sqrt n}\to0$.
d) $(\sin n)$ bornée par 1, $\frac1n\to0$ ⇒ $\to0$ (bornée × →0). Ou gendarmes : $-\frac1n\le\frac{\sin n}n\le\frac1n$.
e) $\frac{n!}{n^n}=\frac1n\cdot\frac2n\cdots\frac nn\le\frac1n$ (chaque facteur $\le1$), et $\ge0$ ⇒ gendarmes ⇒ $0$.
f) $=\frac{3^n\left((\frac23)^n+1\right)}{3^n(1+3^{-n})}\to\frac{0+1}{1+0}=1$.
g) $n^2=o(2^n)$ ⇒ $0$.
h) Rapport $\frac{u_{n+1}}{u_n}=\frac{2}{n+1}\le\frac12$ pour $n\ge3$, donc $0<u_n\le u_3\left(\frac12\right)^{n-3}\to0$ ⇒ $0$.
</details>

## B4 ⭐⭐ Équivalents et conjuguée

a) Limite de $\sqrt{n^2+n}-n$. b) Équivalent simple de $\frac1n-\frac1{n+1}$. c) Limite de $\frac{(n^2+3n)(2n+1)}{n^3-5}$.

<details><summary><b>Correction</b></summary>

a) $\sqrt{n^2+n}-n=\frac{n}{\sqrt{n^2+n}+n}=\frac{1}{\sqrt{1+\frac1n}+1}\to\frac12$.
b) $\frac1n-\frac1{n+1}=\frac{1}{n(n+1)}\sim\frac1{n^2}$ (car $n(n+1)\sim n^2$, et on peut passer à l'inverse).
⚠️ On ne pouvait pas écrire $\frac1n\sim\frac1{n+1}$ puis « soustraire » !
c) Numérateur $\sim n^2\cdot2n=2n^3$ (produit d'équivalents), dénominateur $\sim n^3$ ⇒ quotient $\sim2$ ⇒ limite $2$.
</details>

## B5 ⭐⭐ Vrai ou faux (notations de Landau)

1. $3n^2+5n=\Theta(n^2)$ 2. $n^3=O(n^2)$ 3. $2^{n+1}=\Theta(2^n)$ 4. $4^n=O(2^n)$
5. $n^{100}=o(1{,}01^n)$ 6. $\log_2n=\Theta(\ln n)$ 7. $n+\sin n\sim n$ 8. $n\sim n+\sqrt n$

<details><summary><b>Correction</b></summary>

1. **V** : $\frac{3n^2+5n}{n^2}\to3\in]0,\infty[$ ; concrètement $3n^2\le3n^2+5n\le8n^2$.
2. **F** : $\frac{n^3}{n^2}=n$ non bornée.
3. **V** : $2^{n+1}=2\cdot2^n$.
4. **F** : $\frac{4^n}{2^n}=2^n$ non bornée. ⚠️ piège classique.
5. **V** : croissances comparées (Prop. 2.15 avec $q=1{,}01$).
6. **V** : $\log_2n=\frac{\ln n}{\ln2}$ (la base d'un log ne change qu'une constante : on écrit $O(\log n)$ sans préciser).
7. **V** : $\frac{n+\sin n}{n}=1+\frac{\sin n}n\to1$.
8. **V** : $\frac{n+\sqrt n}{n}=1+\frac1{\sqrt n}\to1$.
</details>

## B6 ⭐⭐ Suite récurrente

$u_0=0$, $u_{n+1}=\sqrt{2+u_n}$. Montrer que $(u_n)$ converge et donner sa limite.

<details><summary><b>Correction</b></summary>

Soit $f(x)=\sqrt{2+x}$, croissante sur $[0,2]$.
**Stabilité** : si $x\in[0,2]$, $2+x\in[2,4]$ donc $f(x)\in[\sqrt2,2]\subset[0,2]$. Par récurrence, $u_n\in[0,2]$ pour tout $n$.
**Monotonie** : récurrence sur $P(n)$ : « $u_n\le u_{n+1}$ ». $P(0)$ : $0\le\sqrt2$ ✅. Si $u_n\le u_{n+1}$, $f$ croissante donne $f(u_n)\le f(u_{n+1})$, i.e. $u_{n+1}\le u_{n+2}$ ✅. Donc $(u_n)$ croissante.
**Convergence** : croissante et majorée par $2$ ⇒ converge vers $\ell\in[0,2]$.
**Limite** : $f$ continue, $\ell=\sqrt{2+\ell}$ ⇒ $\ell^2-\ell-2=0$ ⇒ $\ell\in\{2,-1\}$. Comme $\ell\ge0$ : $\ell=2$.
</details>

## B7 ⭐ Arithmético-géométrique

$u_0=0$, $u_{n+1}=\frac{u_n}{2}+3$. Expression de $u_n$ et limite.

<details><summary><b>Correction</b></summary>

Point fixe : $\ell=\frac\ell2+3\Rightarrow\ell=6$. $v_n=u_n-6$ : $v_{n+1}=\frac{u_n}2+3-6=\frac{u_n-6}{2}=\frac{v_n}2$ : géométrique de raison $\frac12$, $v_0=-6$.
Donc $u_n=6-\frac{6}{2^n}\to6$.
</details>

## B8 ⭐⭐⭐ Suites adjacentes et le nombre $e$

$u_n=\sum_{k=0}^{n}\frac1{k!}$ et $v_n=u_n+\frac1{n\cdot n!}$ pour $n\ge1$.
1. Montrer qu'elles sont adjacentes. 2. (Bonus) En déduire que leur limite $e$ est irrationnelle.

<details><summary><b>Correction</b></summary>

1. - $u_{n+1}-u_n=\frac1{(n+1)!}>0$ : $(u_n)$ strictement croissante.
   - $v_{n+1}-v_n=\frac1{(n+1)!}+\frac{1}{(n+1)(n+1)!}-\frac1{n\cdot n!}$. Au dénominateur commun $n(n+1)(n+1)!$ (avec $\frac1{n\cdot n!}=\frac{(n+1)^2}{n(n+1)(n+1)!}$) :
   $$v_{n+1}-v_n=\frac{n(n+1)+n-(n+1)^2}{n(n+1)(n+1)!}=\frac{-1}{n(n+1)(n+1)!}<0.$$
   $(v_n)$ strictement décroissante.
   - $v_n-u_n=\frac{1}{n\cdot n!}>0$ et $\to0$.
   Donc adjacentes ⇒ même limite $e$, avec $u_n<e<v_n$ (strict car monotonies strictes).
2. Si $e=\frac pq$ ($p,q\in\mathbb N^*$) : $u_q<\frac pq<u_q+\frac1{q\cdot q!}$. On multiplie par $q\cdot q!$ : $A<p\cdot q!<A+1$ où $A=q\cdot q!\,u_q=q\sum_{k=0}^q\frac{q!}{k!}\in\mathbb N$. Un entier strictement entre deux entiers consécutifs : absurde.
</details>

## B9 ⭐⭐ Limites sup et inf

a) $u_n=(-1)^n\left(1+\frac1n\right)$, $n\ge1$. b) $w_n=\cos\frac{2n\pi}{3}$. c) $x_n=n^{(-1)^n}$.

<details><summary><b>Correction</b></summary>

a) **Avec $S_n$, $I_n$** : pour $k$ pair $u_k=1+\frac1k$ (décroît avec $k$), pour $k$ impair $u_k=-1-\frac1k$ (croît avec $k$). Donc $S_n=1+\frac1{p_n}$ où $p_n$ = plus petit pair $\ge n$, et $I_n=-1-\frac1{i_n}$ où $i_n$ = plus petit impair $\ge n$. Comme $p_n,i_n\to\infty$ : $\limsup=1$, $\liminf=-1$. La suite diverge.
**Avec les sous-suites** : $u_{2n}\to1$, $u_{2n+1}\to-1$ ; elles recouvrent ℕ ⇒ même résultat.
b) $n\equiv0\ [3]$ : $1$ ; $n\equiv1$ ou $2\ [3]$ : $-\frac12$. Donc $\limsup=1$, $\liminf=-\frac12$.
c) $n$ pair : $x_n=n\to+\infty$ ; $n$ impair : $x_n=\frac1n\to0$. $\limsup=+\infty$, $\liminf=0$.
</details>

## B10 ⭐⭐ Propriétés générales

1. Si $u_n\to\ell$, montrer $\lvert u_n\rvert\to\lvert\ell\rvert$. Réciproque ?
2. $(u_n)$ bornée et $v_n\to0$ ⇒ $u_nv_n\to0$ (Exercice 1.24).
3. Si $u_{2n}\to\ell$ et $u_{2n+1}\to\ell$, alors $u_n\to\ell$.

<details><summary><b>Correction</b></summary>

1. $\big\lvert\lvert u_n\rvert-\lvert\ell\rvert\big\rvert\le\lvert u_n-\ell\rvert\to0$ ⇒ gendarmes. Réciproque fausse : $u_n=(-1)^n$.
2. Voir cours (choisir $N$ tel que $\lvert v_n\rvert<\varepsilon/C$).
3. Soit $\varepsilon>0$. $\exists N_1,\ \forall k\ge N_1,\ \lvert u_{2k}-\ell\rvert<\varepsilon$ ; $\exists N_2,\ \forall k\ge N_2,\ \lvert u_{2k+1}-\ell\rvert<\varepsilon$. Pour $n\ge N=\max(2N_1,2N_2+1)$ : si $n=2k$ alors $k\ge N_1$ ; si $n=2k+1$ alors $k\ge N_2$. Dans les deux cas $\lvert u_n-\ell\rvert<\varepsilon$.
</details>

## B11 ⭐⭐⭐ Lemme de Cesàro (classique de TD)

Si $u_n\to\ell\in\mathbb R$, montrer que $\frac{u_1+\cdots+u_n}{n}\to\ell$. La réciproque est-elle vraie ?

<details><summary><b>Correction</b></summary>

Quitte à remplacer $u_n$ par $u_n-\ell$, on suppose $\ell=0$. Soit $\varepsilon>0$ et $N$ tel que $\lvert u_k\rvert<\frac\varepsilon2$ pour $k\ge N$. Posons $C=\lvert u_1+\cdots+u_{N-1}\rvert$ (constante). Pour $n\ge N$ :
$$\left\lvert\frac{u_1+\cdots+u_n}{n}\right\rvert\le\frac Cn+\frac{n-N+1}{n}\cdot\frac\varepsilon2\le\frac Cn+\frac\varepsilon2.$$
Pour $n\ge N'$ avec $N'>\frac{2C}{\varepsilon}$, $\frac Cn<\frac\varepsilon2$. Donc pour $n\ge\max(N,N')$, la moyenne est $<\varepsilon$ en valeur absolue.
Réciproque fausse : $u_n=(-1)^n$ diverge mais ses moyennes valent $0$ ou $-\frac1n$, donc $\to0$.
</details>

## B12 ⭐⭐ Somme harmonique (Exercice 2.23)

Montrer que $H_n=\sum_{k=1}^n\frac1k\to+\infty$.

<details><summary><b>Correction</b></summary>

$(H_n)$ est croissante. Pour $j\ge0$ : $\sum_{k=2^j+1}^{2^{j+1}}\frac1k\ge2^j\cdot\frac1{2^{j+1}}=\frac12$ ($2^j$ termes, chacun $\ge\frac1{2^{j+1}}$).
Donc $H_{2^n}=1+\sum_{j=0}^{n-1}\sum_{k=2^j+1}^{2^{j+1}}\frac1k\ge1+\frac n2$. La sous-suite $(H_{2^n})$ n'est pas majorée, donc $(H_n)$ croissante non majorée ⇒ $H_n\to+\infty$ (Rem. 2.21).
(💡 On montre en fait $H_n\sim\ln n$.)
</details>

## B13 ⭐⭐ Dichotomie et suites adjacentes

Soit $f(x)=x^2-2$ sur $[1,2]$. On pose $a_0=1$, $b_0=2$, $m_n=\frac{a_n+b_n}2$ ; si $f(m_n)\le0$ : $(a_{n+1},b_{n+1})=(m_n,b_n)$, sinon $(a_n,m_n)$. Montrer que $(a_n)$, $(b_n)$ sont adjacentes, de limite $\sqrt2$, et donner $n$ pour avoir $\sqrt2$ à $10^{-3}$ près.

<details><summary><b>Correction</b></summary>

Par construction $a_n\le a_{n+1}\le b_{n+1}\le b_n$ et $b_n-a_n=\frac{1}{2^n}\to0$ : adjacentes, limite $\ell$. Par récurrence $f(a_n)\le0<f(b_n)$, i.e. $a_n^2\le2<b_n^2$ ; en passant à la limite, $\ell^2\le2\le\ell^2$ donc $\ell^2=2$, $\ell=\sqrt2$ ($\ell\ge1$).
Erreur $\le b_n-a_n=2^{-n}\le10^{-3}$ dès $n\ge10$ ($2^{10}=1024$). C'est la **recherche dichotomique** : coût $\Theta(\log\frac1{\text{précision}})$.
</details>
