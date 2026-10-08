# Analyse 3 — Partiel blanc (2h, sans document, sans calculatrice)

> Barème indicatif sur 20. Fais-le **en conditions réelles** (chrono 2h), puis corrige-toi avec la correction détaillée plus bas. Soigne la rédaction : elle compte.

---

## Exercice 1 — Questions de cours (4 pts)

1. (1 pt) Donner la définition de la borne supérieure d'une partie $F$ d'un ensemble ordonné. Énoncer la propriété de la borne supérieure. ℚ la possède-t-il ?
2. (1,5 pt) Énoncer et démontrer le théorème de Cantor.
3. (1 pt) Énoncer le théorème de la limite monotone pour une suite croissante.
4. (0,5 pt) Donner la définition de $u_n=O(v_n)$ et de $u_n=\Theta(v_n)$.

## Exercice 2 — Ensembles et cardinaux (4 pts)

On considère $A=\left\{(-1)^n+\frac1n : n\in\mathbb N^*\right\}$.

1. (0,5 pt) Calculer les éléments obtenus pour $n=1,2,3,4$.
2. (2 pts) Déterminer, en justifiant, $\sup A$ et $\inf A$. Préciser si $A$ a un plus grand / un plus petit élément.
3. (1,5 pt) Montrer que $\mathbb N\times\mathbb Z$ est dénombrable. L'ensemble $\mathcal P(\mathbb Z)$ est-il dénombrable ? Justifier.

## Exercice 3 — Nombres complexes (3 pts)

1. (1,5 pt) Déterminer les racines quatrièmes de $-4$, sous forme exponentielle puis algébrique.
2. (1,5 pt) En déduire une factorisation de $X^4+4$ en produit de deux polynômes de degré 2 à coefficients réels.

## Exercice 4 — Limites (4 pts)

1. (1 pt) Montrer **à l'aide de la définition** que $\dfrac{n-1}{n+1}\to1$.
2. (3 pts) Déterminer les limites suivantes en justifiant :
   a) $\dfrac{n^2+(-1)^nn}{3n^2+1}$  b) $\dfrac{2^n+n^5}{3^n-n}$  c) $\sqrt{n^2+3n}-n$

## Exercice 5 — Vrai ou faux (2 pts)

Justifier brièvement (preuve ou contre-exemple).
1. Si $u_n\sim v_n$, alors $u_n-v_n\to0$.
2. $n^{100}=O(1{,}01^n)$.
3. $2^{2n}=\Theta(2^n)$.
4. Si $u_n=o(v_n)$ et $v_n=o(w_n)$, alors $u_n=o(w_n)$.

## Exercice 6 — Suite récurrente (3 pts)

Soit $u_0=1$ et $u_{n+1}=\dfrac{u_n}{1+u_n}$.
1. (0,5 pt) Montrer que $u_n>0$ pour tout $n$.
2. (1 pt) Montrer que $(u_n)$ est décroissante, puis qu'elle converge ; déterminer sa limite.
3. (1 pt) Montrer que $w_n=\frac1{u_n}$ est arithmétique. En déduire $u_n$ explicitement.
4. (0,5 pt) Donner un équivalent simple de $u_n$.

## Bonus (+1)

Déterminer $\limsup$ et $\liminf$ de $x_n=\left(1+\frac{(-1)^n}{2}\right)^n$.

---
---

# ✅ CORRECTION DÉTAILLÉE

## Exercice 1

**1.** $m\in E$ est la borne supérieure de $F$ si $m$ est un majorant de $F$ et si $m\le M$ pour tout majorant $M$ de $F$ (le plus petit des majorants). $(E,\le)$ a la propriété de la borne supérieure si toute partie **non vide et majorée** de $E$ admet une borne supérieure. **ℚ ne la possède pas** : $\{x\in\mathbb Q: x\ge0,\ x^2<2\}$ est non vide, majoré, sans borne sup dans ℚ.

**2.** *Énoncé* : pour tout ensemble $E$, il n'existe pas de surjection de $E$ dans $\mathcal P(E)$.
*Preuve* : supposons $\psi:E\to\mathcal P(E)$ surjective. Soit $D=\{x\in E: x\notin\psi(x)\}\in\mathcal P(E)$. Il existe $d$ avec $\psi(d)=D$. Alors $d\in D\iff d\notin\psi(d)\iff d\notin D$ : contradiction. ∎

**3.** Une suite réelle croissante et majorée converge (vers $\sup\{u_n:n\in\mathbb N\}$) ; une suite croissante non majorée tend vers $+\infty$.

**4.** $u_n=O(v_n)$ : $\exists N\in\mathbb N,\ \exists C>0,\ \forall n\ge N,\ \lvert u_n\rvert\le C\lvert v_n\rvert$.
$u_n=\Theta(v_n)$ : $\exists N,\ \exists c,C>0,\ \forall n\ge N,\ c\lvert v_n\rvert\le\lvert u_n\rvert\le C\lvert v_n\rvert$.

## Exercice 2

**1.** $n=1$ : $0$ ; $n=2$ : $\frac32$ ; $n=3$ : $-\frac23$ ; $n=4$ : $\frac54$.

**2.** On sépare :
- $n$ pair : $a_n=1+\frac1n\in\left]1,\frac32\right]$, maximal pour $n=2$.
- $n$ impair : $a_n=-1+\frac1n\in\left]-1,0\right]$.

**Sup** : tout élément est $\le\frac32$ (les pairs sont $\le\frac32$, les impairs $\le0$) et $\frac32\in A$ ($n=2$). Donc $\sup A=\max A=\frac32$.

**Inf** : tout élément est $>-1$ (car $\frac1n>0$) : $-1$ est un minorant.
Soit $\varepsilon>0$. Par Archimède, il existe un entier $k$ avec $2k+1>\frac1\varepsilon$ ; pour $n=2k+1$ (impair), $a_n=-1+\frac1n<-1+\varepsilon$. Donc aucun $-1+\varepsilon$ n'est minorant : $\inf A=-1$.
Comme $a_n>-1$ pour tout $n$, $-1\notin A$ : **$A$ n'a pas de plus petit élément**.

**3.** ℤ est dénombrable : il existe une bijection $f:\mathbb Z\to\mathbb N$ (ex. $f(x)=2x-1$ si $x>0$, $-2x$ si $x\le0$). Alors $(n,x)\mapsto(n,f(x))$ est une bijection $\mathbb N\times\mathbb Z\to\mathbb N^2$, et $\mathbb N^2$ est dénombrable (bijection de Cantor $\varphi(a,b)=\frac{(a+b)(a+b+1)}2+b$). Par composition, $\mathbb N\times\mathbb Z$ est dénombrable.
$\mathcal P(\mathbb Z)$ : comme $\mathbb Z$ et $\mathbb N$ sont en bijection, $\mathcal P(\mathbb Z)$ et $\mathcal P(\mathbb N)$ aussi ($A\mapsto f(A)$). Par Cantor, $\mathrm{card}\,\mathbb N<\mathrm{card}\,\mathcal P(\mathbb N)$ : **$\mathcal P(\mathbb Z)$ n'est pas dénombrable**.

## Exercice 3

**1.** $-4=4e^{i\pi}$. Les racines quatrièmes sont $z_k=4^{1/4}e^{i\frac{\pi+2k\pi}{4}}=\sqrt2\,e^{i(\frac\pi4+\frac{k\pi}2)}$, $k=0,1,2,3$ :
$$z_0=\sqrt2e^{i\pi/4}=1+i,\quad z_1=\sqrt2e^{3i\pi/4}=-1+i,\quad z_2=-1-i,\quad z_3=1-i.$$
(Vérif : $(1+i)^2=2i$, $(2i)^2=-4$ ✅.)

**2.** $X^4+4=\prod_k(X-z_k)$. On regroupe les racines conjuguées :
$(X-(1+i))(X-(1-i))=X^2-2X+2$ et $(X-(-1+i))(X-(-1-i))=X^2+2X+2$. Donc
$$X^4+4=(X^2-2X+2)(X^2+2X+2).$$
(Vérif : $(X^2+2)^2-(2X)^2=X^4+4X^2+4-4X^2$ ✅.)

## Exercice 4

**1.** $\left\lvert\frac{n-1}{n+1}-1\right\rvert=\frac{2}{n+1}<\frac2n$ pour $n\ge1$. Soit $\varepsilon>0$, et $N\in\mathbb N^*$ tel que $N>\frac2\varepsilon$ (Archimède). Pour $n\ge N$ : $\left\lvert\frac{n-1}{n+1}-1\right\rvert<\frac2n\le\frac2N<\varepsilon$. ∎

**2.a)** $\dfrac{n^2+(-1)^nn}{3n^2+1}=\dfrac{1+\frac{(-1)^n}{n}}{3+\frac1{n^2}}$. Or $\frac{(-1)^n}{n}\to0$ (bornée × →0). Limite : $\frac13$.

**b)** $\dfrac{2^n+n^5}{3^n-n}=\left(\frac23\right)^n\cdot\dfrac{1+\frac{n^5}{2^n}}{1-\frac{n}{3^n}}$. Par croissances comparées, $\frac{n^5}{2^n}\to0$ et $\frac n{3^n}\to0$ ; et $\left(\frac23\right)^n\to0$ car $0<\frac23<1$. Limite : $0\times1=0$.

**c)** $\sqrt{n^2+3n}-n=\dfrac{3n}{\sqrt{n^2+3n}+n}=\dfrac{3}{\sqrt{1+\frac3n}+1}\to\dfrac32$.

## Exercice 5

1. **Faux** : $u_n=n^2+n\sim n^2=v_n$ mais $u_n-v_n=n\to+\infty$. (Un équivalent contrôle le **rapport**, pas la différence.)
2. **Vrai** : par croissances comparées ($q=1{,}01>1$), $n^{100}=o(1{,}01^n)$, et $o\Rightarrow O$.
3. **Faux** : $\frac{2^{2n}}{2^n}=2^n$ n'est pas borné, donc $2^{2n}\ne O(2^n)$.
4. **Vrai** : si $v_n,w_n\ne0$ à partir d'un rang, $\frac{u_n}{w_n}=\frac{u_n}{v_n}\cdot\frac{v_n}{w_n}\to0\cdot0=0$. Dans le cas général : soit $\varepsilon>0$, pour $n$ grand $\lvert u_n\rvert\le\sqrt\varepsilon\lvert v_n\rvert$ et $\lvert v_n\rvert\le\sqrt\varepsilon\lvert w_n\rvert$, d'où $\lvert u_n\rvert\le\varepsilon\lvert w_n\rvert$.

## Exercice 6

**1.** Récurrence : $u_0=1>0$ ; si $u_n>0$ alors $1+u_n>0$ et $u_{n+1}=\frac{u_n}{1+u_n}>0$.

**2.** $u_{n+1}-u_n=\frac{u_n-u_n(1+u_n)}{1+u_n}=\frac{-u_n^2}{1+u_n}<0$ : $(u_n)$ strictement décroissante. Décroissante et minorée par $0$ ⇒ converge vers $\ell\ge0$. Comme $x\mapsto\frac{x}{1+x}$ est continue sur $\mathbb R^+$, en passant à la limite : $\ell=\frac{\ell}{1+\ell}$, soit $\ell(1+\ell)=\ell$, $\ell^2=0$, **$\ell=0$**.

**3.** $w_{n+1}=\frac{1+u_n}{u_n}=\frac1{u_n}+1=w_n+1$ : arithmétique de raison $1$, $w_0=1$. Donc $w_n=n+1$ et
$$u_n=\frac{1}{n+1}.$$

**4.** $u_n=\frac1{n+1}\sim\frac1n$ (rapport $\frac{n}{n+1}\to1$).

## Bonus

$n$ pair : $x_n=\left(\frac32\right)^n\to+\infty$ (car $\frac32>1$). $n$ impair : $x_n=\left(\frac12\right)^n\to0$.
Les deux sous-suites recouvrent ℕ : $\limsup x_n=+\infty$, $\liminf x_n=0$.

---

## 📊 Auto-évaluation

| Score | Diagnostic |
|---|---|
| < 10 | Reprendre les fichiers de cours 1 et 2, surtout les définitions et preuves ✍️ |
| 10–14 | Bases OK : travailler la **rédaction** (quantificateurs, hypothèses des théorèmes) et les pièges de la fiche |
| 15–17 | Bon niveau : refaire les exercices ⭐⭐⭐ et chronométrer |
| ≥ 18 | Prêt·e. Relire la fiche la veille. |

**Erreurs les plus fréquentes sur ce sujet** : oublier de dire que $-1$ n'est pas atteint (Ex. 2) ; écrire $\frac{4^n}{2^n}$ borné ; sommer des équivalents dans l'Ex. 4b ; ne pas justifier $\ell\ge0$ pour choisir la bonne racine (Ex. 6).
