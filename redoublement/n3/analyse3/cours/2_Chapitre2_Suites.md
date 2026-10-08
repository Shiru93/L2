# Analyse 3 — Chapitre 2 : Suites (cours expliqué)

> Légende : 🎯 = à savoir par cœur · ⚠️ = piège classique · 💡 = intuition · ✍️ = preuve à savoir refaire

---

## Sommaire

1. Définitions : suites, suites extraites, types de suites
2. Limite d'une suite (définition ε, unicité, opérations)
3. Suites bornées
4. Comparaison asymptotique : $o$, $\sim$, $O$, $\Omega$, $\Theta$
5. Suites réelles : limites infinies, inégalités, gendarmes
6. Formes indéterminées et croissances comparées
7. Suites monotones
8. Suites adjacentes
9. Limites supérieure et inférieure

---

## 1. Définitions

### 1.1 Suite

Une **suite** de $E$ est une application $\mathbb N\to E$ (ou d'une partie infinie $I\subset\mathbb N$). On note $(u_n)_{n\in\mathbb N}$ ou $(u_n)_n$.

Exemples : $((-1)^n)$ dans ℤ ; $(e^{in})$ dans ℂ ; $(\{0,\dots,n\})$ dans $\mathcal P(\mathbb N)$.
$\mathbb R^{\mathbb N}\subset\mathbb C^{\mathbb N}$ : on travaille souvent dans ℂ sans perte de généralité.

### 1.2 Suite extraite (sous-suite) 🎯

$(v_n)$ est **extraite** de $(u_n)$ s'il existe $\varphi:\mathbb N\to\mathbb N$ **strictement croissante** telle que $v_n=u_{\varphi(n)}$.

Exemples : $(u_{2n})$ (rangs pairs), $(u_{2n+1})$ (rangs impairs), $(u_{n+p})$, $(u_{2^n})$, $(u_{n^2})$.

🎯 **Lemme clé** : si $\varphi$ est strictement croissante de ℕ dans ℕ, alors $\varphi(n)\ge n$ pour tout $n$.
✍️ Récurrence : $\varphi(0)\ge0$ ; si $\varphi(n)\ge n$ alors $\varphi(n+1)>\varphi(n)\ge n$, donc $\varphi(n+1)\ge n+1$ (entiers).

### 1.3 Types de suites

- **Constante** : $u_n=u_0$ pour tout $n$.
- **Stationnaire** : constante à partir d'un rang : $\exists n_0,\ \forall n\ge n_0,\ u_n=u_{n_0}$.
- **Périodique** de période $N\ge1$ : $u_{n+N}=u_n$ pour tout $n$.

Exemples : $((-1)^n)$ période 2 ; $(i^n)$ période 4 ; $\left(\lfloor 100/n\rfloor-5\right)_{n\ge1}$ stationnaire (vaut $-5$ dès $n\ge101$).

### 1.4 Suites arithmétiques et géométriques 🎯

| | Récurrence | Terme général | Somme |
|---|---|---|---|
| Arithmétique (raison $a$) | $u_{n+1}=u_n+a$ | $u_n=u_0+na$ | $\sum_{k=0}^{n}u_k=(n+1)\frac{u_0+u_n}{2}$ |
| Géométrique (raison $q$) | $u_{n+1}=qu_n$ | $u_n=u_0q^n$ | $\sum_{k=0}^{n}q^k=\frac{1-q^{n+1}}{1-q}$ ($q\ne1$) |

**Exercice 1.10 / 1.23 (réponses)** pour $u_n=u_0q^n$ :
- **périodique** ⟺ $u_0=0$ ou $q$ est une **racine de l'unité** ($q^N=1$ pour un $N\ge1$) ;
- **bornée** ⟺ $u_0=0$ ou $\lvert q\rvert\le1$ (car $\lvert u_n\rvert=\lvert u_0\rvert\lvert q\rvert^n$).

**Arithmético-géométrique** $u_{n+1}=au_n+b$ ($a\ne1$) : on cherche le **point fixe** $\ell=\frac{b}{1-a}$ ($\ell=a\ell+b$). Alors $v_n=u_n-\ell$ est géométrique de raison $a$ : $u_n=\ell+a^n(u_0-\ell)$.

---

## 2. Limite d'une suite

### 2.1 Définition 🎯 (à écrire parfaitement)

$(u_n)\in\mathbb C^{\mathbb N}$ **converge vers** $\ell\in\mathbb C$ si
$$\forall\varepsilon>0,\ \exists N\in\mathbb N,\ \forall n\ge N,\ \lvert u_n-\ell\rvert<\varepsilon.$$

💡 « À partir d'un certain rang (qui dépend de ε), tous les termes sont dans le disque de centre ℓ et de rayon ε. »

- C'est la même définition dans ℝ et ℂ ($\lvert\cdot\rvert$ = valeur absolue ou module).
- $u_n\to\ell\iff\lvert u_n-\ell\rvert\to0$.

**Négation** (pour montrer qu'une suite ne converge pas vers ℓ) :
$$\exists\varepsilon>0,\ \forall N,\ \exists n\ge N,\ \lvert u_n-\ell\rvert\ge\varepsilon.$$

#### 🎯 Rédaction type d'une preuve « par la définition »

> Soit $\varepsilon>0$. [Calcul : majorer $\lvert u_n-\ell\rvert$ par une expression simple, du type $\frac{C}{n}$.] Choisissons $N$ entier tel que $N>\ldots$ (existe par Archimède). Alors pour tout $n\ge N$, $\lvert u_n-\ell\rvert\le\ldots<\varepsilon$. Donc $u_n\to\ell$.

**Exemple (cours)** : $\frac{i}{n+1}\to0$. Soit $\varepsilon>0$, $N\ge1/\varepsilon$ ; pour $n\ge N$, $\left\lvert\frac{i}{n+1}\right\rvert=\frac1{n+1}<\frac1N\le\varepsilon$.

**Exemple** : $\frac{2n+1}{n+3}\to2$. $\left\lvert\frac{2n+1}{n+3}-2\right\rvert=\frac{5}{n+3}<\frac5n$. Soit $\varepsilon>0$, prenons $N>5/\varepsilon$ : pour $n\ge N$, $\frac5{n+3}<\frac5N<\varepsilon$.

### 2.2 Unicité de la limite ✍️

Si $u_n\to\ell$ et $u_n\to\ell'$ alors $\ell=\ell'$.
Preuve : sinon, $\varepsilon=\frac{\lvert\ell-\ell'\rvert}{3}$ ; pour $n$ assez grand, $\lvert\ell-\ell'\rvert\le\lvert\ell-u_n\rvert+\lvert u_n-\ell'\rvert<2\varepsilon=\frac23\lvert\ell-\ell'\rvert$. Absurde.

### 2.3 Limite et suites extraites 🎯

Si $u_n\to\ell$, **toute** suite extraite tend vers $\ell$ (car $\varphi(n)\ge n$).

💡 **Usage principal : montrer la divergence.** Si deux suites extraites ont des limites différentes, $(u_n)$ diverge.
Ex. $(-1)^n$ : $u_{2n}=1\to1$ et $u_{2n+1}=-1\to-1$ ⇒ divergente.
→ Une suite **périodique non constante** ne converge pas.

Réciproque utile : si $u_{2n}\to\ell$ **et** $u_{2n+1}\to\ell$, alors $u_n\to\ell$.

### 2.4 Opérations 🎯

Si $a_n\to\ell$ et $b_n\to m$ (dans ℂ) : $a_n+b_n\to\ell+m$, $a_nb_n\to\ell m$, et si $m\ne0$ : $\frac{a_n}{b_n}\to\frac\ell m$ (et $b_n\ne0$ à partir d'un certain rang, car $\lvert b_n\rvert>\frac{\lvert m\rvert}{2}$).

Autres : $u_n\to\ell\Rightarrow\lvert u_n\rvert\to\lvert\ell\rvert$ (inégalité triangulaire inverse). ⚠️ Réciproque fausse : $\lvert(-1)^n\rvert\to1$ mais $(-1)^n$ diverge. **Sauf** pour $\ell=0$ : $u_n\to0\iff\lvert u_n\rvert\to0$.

---

## 3. Suites bornées

- $(u_n)$ **bornée** : $\exists C>0,\ \forall n,\ \lvert u_n\rvert\le C$.
- Réelle : **majorée** ($u_n\le A$), **minorée** ($A\le u_n$). Bornée ⟺ majorée et minorée.

🎯 **Une suite convergente est bornée.** ✍️ Pour $n\ge N$, $\lvert u_n\rvert\le\lvert\ell\rvert+1$ ; donc $\lvert u_n\rvert\le\max(\lvert u_0\rvert,\dots,\lvert u_{N-1}\rvert,\lvert\ell\rvert+1)$ pour tout $n$.
⚠️ Réciproque fausse : $(-1)^n$ est bornée et diverge.

🎯 **Exercice 1.24 : bornée × tend vers 0 ⇒ tend vers 0.** ✍️ $\lvert u_n\rvert\le C$, $v_n\to0$. Soit $\varepsilon>0$, il existe $N$ tel que $\lvert v_n\rvert<\varepsilon/C$ pour $n\ge N$, d'où $\lvert u_nv_n\rvert\le C\lvert v_n\rvert<\varepsilon$.
Ex. $\frac{\sin n}{n}\to0$, $\frac{(-1)^n}{\sqrt n}\to0$, $\frac{e^{in}}{n^2}\to0$.

---

## 4. Comparaison asymptotique 🎯🎯 (très important pour un informaticien)

### 4.1 Les définitions

| Notation | Lecture | Définition | Si $v_n\ne0$ |
|---|---|---|---|
| $u_n=o(v_n)$ | $u$ négligeable devant $v$ | $\forall\varepsilon>0,\exists N,\forall n\ge N,\ \lvert u_n\rvert\le\varepsilon\lvert v_n\rvert$ | $\frac{u_n}{v_n}\to0$ |
| $u_n\sim v_n$ | $u$ équivalente à $v$ | $u_n-v_n=o(v_n)$ | $\frac{u_n}{v_n}\to1$ |
| $u_n=O(v_n)$ | $u$ dominée par $v$ | $\exists N,\exists C>0,\forall n\ge N,\ \lvert u_n\rvert\le C\lvert v_n\rvert$ | $\frac{u_n}{v_n}$ bornée |
| $u_n=\Omega(v_n)$ | $u$ minorée par $v$ | $\exists N,\exists c>0,\forall n\ge N,\ \lvert u_n\rvert\ge c\lvert v_n\rvert$ | ⟺ $v_n=O(u_n)$ |
| $u_n=\Theta(v_n)$ ($u_n\asymp v_n$) | même ordre de grandeur | $c\lvert v_n\rvert\le\lvert u_n\rvert\le C\lvert v_n\rvert$ pour $n\ge N$ | ⟺ $O$ et $\Omega$ |

💡 Analogie : $o$ ≈ « $<$ », $O$ ≈ « $\le$ », $\Omega$ ≈ « $\ge$ », $\Theta$ ≈ « $=$ à constante près », $\sim$ ≈ « $=$ avec constante exactement 1 ».

### 4.2 Liens entre les notations

$$u_n=o(v_n)\ \Rightarrow\ u_n=O(v_n),\qquad u_n\sim v_n\ \Rightarrow\ u_n=\Theta(v_n)\ \Rightarrow\ u_n=O(v_n)$$
⚠️ $\Theta\not\Rightarrow\sim$ : $n=\Theta(2n)$ mais $n\not\sim2n$ (rapport $\frac12\ne1$).

- $u_n\to0\iff u_n=o(1)$ ; $(u_n)$ bornée $\iff u_n=O(1)$.
- Pour $\ell\ne0$ : $u_n\to\ell\iff u_n\sim\ell$.

### 4.3 Hiérarchie des croissances 🎯

Pour $\alpha>0$, $k<\ell$, $q>1$ :
$$\ln n\ \ll\ n^{\alpha}\ ,\qquad n^k\ll n^\ell\ ,\qquad n^k\ll q^n\ ,\qquad q^n\ll n!\ \ll\ n^n$$
où $a_n\ll b_n$ signifie $a_n=o(b_n)$. (Dans ce cours : $n^k=o(n^\ell)$ et $n^k=o(q^n)$ sont démontrés — Prop. 2.15.)

### 4.4 Règles de calcul

**Équivalents (✅ autorisé)** : produit, quotient, puissance fixe.
Si $u_n\sim a_n$ et $v_n\sim b_n$ : $u_nv_n\sim a_nb_n$, $\frac{u_n}{v_n}\sim\frac{a_n}{b_n}$, $u_n^p\sim a_n^p$.
**Un équivalent conserve la limite et le signe** (à partir d'un rang).

**Équivalents (⚠️ INTERDIT)** :
- **Sommer** : $n^2+n\sim n^2$ et $-n^2+n\sim-n^2$, mais la somme $2n\not\sim0$.
- Écrire $u_n\sim0$ : seules les suites **nulles à partir d'un rang** sont $\sim0$. On écrit $u_n=o(1)$ ou $u_n\to0$.
- Composer par une fonction quelconque (ex. $e^{u_n}$ et $e^{v_n}$) sans justification.

**Équivalent d'une somme : on garde le terme dominant.** Si $v_n=o(u_n)$, alors $u_n+v_n\sim u_n$.
Ex. $4n^4-2n^2\sim4n^4$ ; $2^n+n^{10}\sim2^n$ ; un polynôme en $n$ est équivalent à son terme de plus haut degré.

**$o$ et $O$** :
- $o(a_n)+o(a_n)=o(a_n)$ ; $O(a_n)+O(a_n)=O(a_n)$.
- $O(a_n)\times O(b_n)=O(a_nb_n)$ ; $O(a_n)\times o(b_n)=o(a_nb_n)$.
- Transitivité : $u=o(v)$, $v=o(w)\Rightarrow u=o(w)$ (idem pour $O$).
- Constantes : $u_n=O(v_n)\Rightarrow au_n=O(bv_n)$ pour $a,b\ne0$.
- Prop. 1.44(a) : si $u_n=\Theta(a_n)$, $v_n=\Theta(b_n)$ et $u_n=o(v_n)$, alors $a_n=o(b_n)$ (on peut remplacer par un $\Theta$ dans un $o$/$O$/$\Omega$).

⚠️ **Le « = » n'est pas une égalité** (Avertissement 1.29) : $n=O(n^2)$ et $n^2=O(n^2)$ n'impliquent pas $n=n^2$. Penser $u_n\in O(v_n)$.

**Exemples du cours** : $4n^4+n^4\sin n+2n^3=O(n^4)$ ; $n\log n$ n'est **pas** $O(n)$ (le rapport $\log n\to+\infty$) ; $4n^4-n^2=\Theta(n^4)$.

---

## 5. Suites réelles

### 5.1 Limites infinies 🎯

$$u_n\to+\infty\iff\forall A\in\mathbb R,\ \exists N,\ \forall n\ge N,\ u_n\ge A.$$
$u_n\to-\infty\iff-u_n\to+\infty$.

Une suite qui tend vers $+\infty$ est minorée mais pas majorée. ⚠️ La réciproque est fausse : $u_n=n$ si $n$ pair, $0$ sinon, n'est pas majorée et ne tend pas vers $+\infty$.

Ex. $n^k\to+\infty$ ($k\ge1$) : pour $A$ donné, tout $N\ge A$ convient.

### 5.2 Passage à la limite dans les inégalités 🎯

Si $u_n\le v_n$ à partir d'un rang, $u_n\to\ell$, $v_n\to\ell'$ (dans $\overline{\mathbb R}$), alors $\ell\le\ell'$.
⚠️ **Les inégalités strictes deviennent larges** : $1-\frac1{n+1}<1+\frac1{n+1}$ mais même limite $1$.

### 5.3 Théorème des gendarmes 🎯✍️

Si $v_n\le u_n\le w_n$ et $v_n\to\ell$, $w_n\to\ell$ ($\ell\in\mathbb R$), alors $u_n\to\ell$.

Preuve : pour $n\ge\max(N,N')$, $-\varepsilon<v_n-\ell\le u_n-\ell\le w_n-\ell<\varepsilon$.

**Version infinie (comparaison)** : si $u_n\le v_n$ et $u_n\to+\infty$ alors $v_n\to+\infty$ ; si $v_n\to-\infty$ alors $u_n\to-\infty$. (Une seule inégalité suffit !)

**Exemple** : $2^n\ge n$ (récurrence) et $n\to+\infty$ ⇒ $2^n\to+\infty$.

### 5.4 Suites complexes via Re et Im (Prop. 2.7)

$u_n\to\ell\iff\mathrm{Re}\,u_n\to\mathrm{Re}\,\ell$ **et** $\mathrm{Im}\,u_n\to\mathrm{Im}\,\ell$.
(Grâce à $\lvert\mathrm{Re}\,z\rvert,\lvert\mathrm{Im}\,z\rvert\le\lvert z\rvert\le\lvert\mathrm{Re}\,z\rvert+\lvert\mathrm{Im}\,z\rvert$ + gendarmes.)

---

## 6. Formes indéterminées et croissances comparées

### 6.1 Tableaux 🎯

**Somme** :

| $u_n\to$ \ $v_n\to$ | $\ell'\in\mathbb R$ | $+\infty$ | $-\infty$ |
|---|---|---|---|
| $\ell\in\mathbb R$ | $\ell+\ell'$ | $+\infty$ | $-\infty$ |
| $+\infty$ | $+\infty$ | $+\infty$ | **FI** |
| $-\infty$ | $-\infty$ | **FI** | $-\infty$ |

**Produit** (limites positives ; sinon règle des signes) :

| | $\ell'>0$ | $+\infty$ | $0$ |
|---|---|---|---|
| $\ell>0$ | $\ell\ell'$ | $+\infty$ | $0$ |
| $+\infty$ | $+\infty$ | $+\infty$ | **FI** |
| $0$ | $0$ | **FI** | $0$ |

**Inverse** (Prop. 2.12) : $u_n\to+\infty\iff\frac1{u_n}\to0^+$ ; $u_n\to-\infty\iff\frac1{u_n}\to0^-$ ; $u_n\to\ell\notin\{0,\pm\infty\}\iff\frac1{u_n}\to\frac1\ell$.

Les 4 FI : $\infty-\infty$, $0\times\infty$, $\frac\infty\infty$, $\frac00$ (et $1^\infty$, $0^0$, $\infty^0$ avec les puissances).

### 6.2 Méthode 2.14 : factoriser par le terme dominant 🎯

$$\frac{n^3+n^2+1}{n^4-n^3}=\frac{n^3(1+n^{-1}+n^{-3})}{n^4(1-n^{-1})}=\frac1n\cdot\frac{1+n^{-1}+n^{-3}}{1-n^{-1}}\to0\times1=0.$$
**Fraction rationnelle** $\frac{a_pn^p+\cdots}{b_qn^q+\cdots}$ : équivalente à $\frac{a_p}{b_q}n^{p-q}$. Donc limite $0$ si $p<q$, $\frac{a_p}{b_q}$ si $p=q$, $\pm\infty$ si $p>q$.

### 6.3 Croissances comparées (Prop. 2.15) 🎯✍️

Pour $q>1$, $k\in\mathbb N$ : $\dfrac{q^n}{n^k}\to+\infty$, i.e. $n^k=o(q^n)$.

**Preuve (méthode du rapport)** : $u_n=\frac{q^n}{n^k}$, $\frac{u_{n+1}}{u_n}=q\left(1+\frac1n\right)^{-k}\to q$. Avec $1<q'<q$, à partir d'un rang $N$, $\frac{u_{n+1}}{u_n}\ge q'$, donc $u_n\ge u_N(q')^{n-N}\to+\infty$.

💡 Cette méthode du rapport (« si $\frac{u_{n+1}}{u_n}\to L>1$ alors $u_n\to+\infty$ ; si $L<1$ et $u_n>0$, alors $u_n\to0$ ») est réutilisable : ex. $\frac{2^n}{n!}\to0$ (rapport $\frac{2}{n+1}\to0$).

**Exemple 2.16** : $2^n-n^{10}=2^n\left(1-\frac{n^{10}}{2^n}\right)\to+\infty\times1=+\infty$.

**Exemple 2.10** : $q>1\Rightarrow q^n\to+\infty$, via **Bernoulli** $q^n\ge1+n(q-1)$ (récurrence).
Et $0<q<1\Rightarrow q^n\to0$ (car $q^n=\frac1{(1/q)^n}$). 🎯 Bilan : $q^n\to0$ si $\lvert q\rvert<1$, $\to1$ si $q=1$, diverge sinon ($q=-1$ : oscille ; $\lvert q\rvert>1$ : $\lvert q^n\rvert\to+\infty$).

### 6.4 Autres techniques utiles

- **Quantité conjuguée** : $\sqrt{n+1}-\sqrt n=\frac{1}{\sqrt{n+1}+\sqrt n}\to0$.
- **Encadrement** : $\frac{n!}{n^n}=\frac{1}{n}\cdot\frac{2}{n}\cdots\frac{n}{n}\le\frac1n\to0$.
- **Partie entière** : $\frac{\lfloor nx\rfloor}{n}\to x$ car $x-\frac1n<\frac{\lfloor nx\rfloor}{n}\le x$.

---

## 7. Suites monotones

### 7.1 Définitions

Croissante : $n\ge m\Rightarrow u_n\ge u_m$. En pratique on vérifie **$u_{n+1}-u_n\ge0$** (ou $\frac{u_{n+1}}{u_n}\ge1$ si $u_n>0$).

### 7.2 Théorème de la limite monotone 🎯✍️

- Croissante **non majorée** ⇒ $u_n\to+\infty$.
- Croissante **et majorée** ⇒ **converge**, vers $\ell=\sup\{u_n\}$, et $u_k\le\ell$ pour tout $k$.
- Décroissante non minorée ⇒ $-\infty$ ; décroissante minorée ⇒ converge vers $\inf\{u_n\}$.

**Corollaire** : toute suite réelle monotone a une limite dans $\overline{\mathbb R}$.

✍️ **Preuve (croissante majorée)** — repose sur la propriété de la borne sup :
$E=\{u_n\}$ non vide majoré ⇒ $\ell=\sup E$ existe. Soit $\varepsilon>0$ : $\ell-\varepsilon$ ne majore pas $E$, donc $\exists N,\ u_N>\ell-\varepsilon$. Pour $n\ge N$ : $\ell-\varepsilon<u_N\le u_n\le\ell$. Donc $\lvert u_n-\ell\rvert<\varepsilon$.

⚠️ Le théorème donne l'**existence** de la limite, pas sa valeur. Pour la trouver (suite récurrente $u_{n+1}=f(u_n)$, $f$ continue) : on passe à la limite, $\ell=f(\ell)$.

### 7.3 Remarque 2.21 : il suffit d'une sous-suite

Pour une suite **croissante**, si une sous-suite est majorée, la suite converge ; si une sous-suite n'est pas majorée, la suite tend vers $+\infty$.

**Exemple 2.22** : $u_n=\sum_{k=1}^n\frac1{k^2}$ croissante. On regroupe par paquets $[2^j,2^{j+1}[$ : chaque paquet a $2^j$ termes $\le\frac1{2^{2j}}$, donc vaut $\le\frac1{2^j}$. D'où $u_{2^n-1}\le\sum_{j=0}^{n-1}\frac1{2^j}\le2$ : sous-suite majorée ⇒ $(u_n)$ converge. (Sa limite est $\frac{\pi^2}{6}$, hors programme.)

**Exercice 2.23 — série harmonique** $H_n=\sum_{k=1}^n\frac1k\to+\infty$. ✍️
Paquet $\sum_{k=2^j+1}^{2^{j+1}}\frac1k$ : $2^j$ termes $\ge\frac1{2^{j+1}}$, donc $\ge\frac12$. Ainsi $H_{2^n}\ge1+\frac n2\to+\infty$ : sous-suite non majorée ⇒ $H_n\to+\infty$.

### 7.4 Suites récurrentes $u_{n+1}=f(u_n)$ — méthode type 🎯

1. Trouver un intervalle **stable** $I$ ($f(I)\subset I$) contenant $u_0$ ⇒ par récurrence $u_n\in I$.
2. Monotonie : étudier le signe de $u_{n+1}-u_n=f(u_n)-u_n$, ou, si $f$ croissante sur $I$, comparer $u_0$ et $u_1$ (même sens pour toute la suite, récurrence).
3. Monotone + bornée ⇒ converge vers $\ell$.
4. Passer à la limite ($f$ continue) : $\ell=f(\ell)$, et choisir la bonne solution grâce aux bornes.

---

## 8. Suites adjacentes 🎯

$(u_n)$ et $(v_n)$ sont **adjacentes** si : $u_n\le v_n$ ; $(u_n)$ croissante ; $(v_n)$ décroissante ; $v_n-u_n\to0$.

**Théorème.** Elles convergent vers la **même** limite $\ell$, et
$$\forall n,\ u_n\le\ell\le v_n,\qquad\text{donc}\qquad\lvert u_n-\ell\rvert\le v_n-u_n,\ \lvert v_n-\ell\rvert\le v_n-u_n.$$

✍️ Preuve : $u_n\le v_n\le v_0$ ⇒ $(u_n)$ croissante majorée ⇒ converge ; $(v_n)$ décroissante minorée par $u_0$ ⇒ converge ; $v_n-u_n\to0$ ⇒ même limite. Enfin $u_n\le u_k$ pour $k\ge n$, on fait $k\to\infty$ : $u_n\le\ell$ (idem $v_n\ge\ell$).

💡 Intérêt informatique : $[u_n,v_n]$ est un **encadrement de ℓ avec erreur contrôlée** $v_n-u_n$ — c'est le principe de la dichotomie.

**Exemples :**
- Approximations décimales (Ex. 2.31) : $u_n=\frac{\lfloor10^ny\rfloor}{10^n}$, $v_n=\frac{\lceil10^ny\rceil}{10^n}$ ⇒ adjacentes, limite $y$.
- Approximations de $\sqrt2$ (TD1 ex. 3, type Héron) : $u_{n+1}=\frac12\left(u_n+\frac2{u_n}\right)$ et $v_n=\frac{2}{u_n}$.
- $e$ : $u_n=\sum_{k=0}^n\frac1{k!}$, $v_n=u_n+\frac1{n\cdot n!}$ (voir exercices corrigés).

**Dichotomie** (application) : pour $f$ continue avec $f(a)<0<f(b)$, on coupe $[a_n,b_n]$ en deux en gardant le changement de signe : $(a_n)$, $(b_n)$ adjacentes, $b_n-a_n=\frac{b-a}{2^n}$.

---

## 9. Limites supérieure et inférieure 🎯

Pour $(u_n)$ réelle, on pose
$$I_n=\inf_{k\ge n}u_k\ (\text{croissante}),\qquad S_n=\sup_{k\ge n}u_k\ (\text{décroissante}).$$
(💡 En enlevant des termes, l'inf ne peut que monter et le sup que descendre.)

$$\liminf_{n\to\infty}u_n=\lim I_n,\qquad\limsup_{n\to\infty}u_n=\lim S_n\quad(\text{dans }\overline{\mathbb R}).$$

- Elles existent **toujours** (suites monotones), contrairement à la limite.
- $\liminf u_n\le\limsup u_n$.
- ⚠️ Pas définies pour une suite complexe.

**Prop. 2.36** : $(u_n)$ a une limite dans $\overline{\mathbb R}$ ⟺ $\liminf u_n=\limsup u_n$, et alors la limite est cette valeur commune. (Preuve : gendarmes avec $I_n\le u_n\le S_n$.)

💡 Intuition : $\limsup$ = la plus grande valeur dont la suite s'approche infiniment souvent (plus grande **valeur d'adhérence**) ; $\liminf$ = la plus petite.

**Exemples :**
- $(-1)^n$ : $I_n=-1$, $S_n=1$ ⇒ $\liminf=-1$, $\limsup=1$.
- $u_n=n$ si $n$ carré parfait, $13$ sinon : $\limsup=+\infty$, $\liminf=13$.
- $u_n=(-1)^n\left(1+\frac1n\right)$ : $\limsup=1$, $\liminf=-1$ (détails dans les exercices).
- $u_n=\frac1n$ : converge, donc $\liminf=\limsup=0$.

**Méthode de calcul pratique** : séparer en sous-suites qui couvrent tous les indices (pairs/impairs, $n \bmod 3$…), calculer leurs limites ; $\limsup$ = la plus grande, $\liminf$ = la plus petite (valable quand on a un nombre **fini** de sous-suites qui recouvrent tout ℕ et qui ont chacune une limite).

---

## ✅ Récap des « preuves à savoir refaire »

1. Unicité de la limite.
2. Convergente ⇒ bornée.
3. Bornée × (→0) ⇒ →0.
4. Gendarmes.
5. Croissante majorée ⇒ converge (borne sup).
6. $n^k=o(q^n)$ (méthode du rapport).
7. Suites adjacentes ⇒ même limite + encadrement.
8. $H_n\to+\infty$ et $\sum\frac1{k^2}$ converge (paquets de $2^j$).
9. $\varphi$ strictement croissante ⇒ $\varphi(n)\ge n$.
