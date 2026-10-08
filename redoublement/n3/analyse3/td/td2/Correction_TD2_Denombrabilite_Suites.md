# Analyse 3 — Correction détaillée du TD 2 : Dénombrabilité, Suites (I)

> L2 Informatique — USPN, 2026-27.
> Pour chaque exercice : 🧭 **Méthode**, ✍️ **Rédaction**, 💡 **À retenir**, ⚠️ **Piège**.

---

## Exercice 1 — La bijection de Cantor $\mathbb N^2\to\mathbb N$

🧭 **Idée générale** : $M(a,b)=S(a+b)+b$. On numérote les couples **par diagonales** $a+b=s$. Avant la diagonale $s$ il y a $1+2+\dots+s=S(s)$ couples, et $b$ donne la position dans la diagonale.

#### (a) $S(n)=\sum_{k=0}^nk$

Récurrence (cf. TD1 Ex. 4) ou méthode de Gauss : en écrivant $T=\sum_{k=0}^nk$ à l'endroit et à l'envers,
$$2T=\sum_{k=0}^n\big(k+(n-k)\big)=(n+1)\,n\quad\Longrightarrow\quad T=\frac{n(n+1)}{2}=S(n).$$

#### (b) Si $n\ne n'$, alors $\lvert S(n)-S(n')\rvert\ge\max(n,n')$

✍️ Par symétrie, on suppose $n'<n$, donc $\max(n,n')=n$. Alors
$$S(n)-S(n')=\sum_{k=n'+1}^{n}k=n+\underbrace{\sum_{k=n'+1}^{n-1}k}_{\ge0}\ \ge\ n.$$
(La somme contient le terme $k=n$ puisque $n'+1\le n$, et les autres termes sont positifs.) ∎

💡 Les valeurs $S(0),S(1),S(2),\ldots=0,1,3,6,10,\ldots$ sont de plus en plus espacées : l'écart entre $S(n)$ et $S(n')$ est au moins le plus grand des deux indices.

#### (c) $M(a,b)=M(a',b')\Rightarrow a+b=a'+b'$

✍️ Posons $s=a+b$, $s'=a'+b'$, de sorte que $M(a,b)=S(s)+b$. Par l'absurde, supposons $s\ne s'$, et par symétrie $s'<s$. Par (b), $S(s)-S(s')\ge s$. Donc
$$M(a,b)-M(a',b')=\big(S(s)-S(s')\big)+b-b'\ \ge\ s+b-b'\ \ge\ s-b'.$$
Or $b'\le a'+b'=s'<s$, donc $s-b'>0$. Ainsi $M(a,b)>M(a',b')$ : contradiction. Donc $s=s'$. ∎

#### (d) $M$ est injective

✍️ Si $M(a,b)=M(a',b')$, alors $s=s'$ par (c), donc $S(s)=S(s')$ et
$b=M(a,b)-S(s)=M(a',b')-S(s')=b'$, puis $a=s-b=s'-b'=a'$. Donc $(a,b)=(a',b')$. ∎

#### (e) Surjectivité

**Existence et unicité de $k$.** Soit $n\in\mathbb N$ et $K=\{k\in\mathbb N : S(k)\le n\}$.
- $K\ne\emptyset$ car $S(0)=0\le n$.
- $K$ est majoré par $n$ : si $k\in K$, $k\le S(k)\le n$ (car $S(k)\ge k$ par (b) avec $n'=0$, ou directement).

Une partie non vide et majorée de ℤ a un **plus grand élément** (propriété (b) du §2.3 du cours) : soit $k=\max K$. Alors $S(k)\le n$ et $k+1\notin K$, i.e. $n<S(k+1)$.
**Unicité** : $S$ est strictement croissante. Si $k<k'$ vérifiaient tous deux la propriété, on aurait $S(k+1)\le S(k')\le n<S(k+1)$ : absurde.

**Antécédent.** Posons $b=n-S(k)$ et $a=k-b$.
- $b\ge0$ car $S(k)\le n$.
- $n<S(k+1)=S(k)+k+1$, donc $b=n-S(k)<k+1$, i.e. $b\le k$, donc $a\ge0$.

Ainsi $(a,b)\in\mathbb N^2$, $a+b=k$ et $M(a,b)=S(k)+b=n$. ✅

**Conclusion** : $M$ est injective et surjective, donc **bijective**.

*Exemple* : $n=7$. $S(3)=6\le7<10=S(4)$, donc $k=3$, $b=1$, $a=2$ : $M(2,1)=S(3)+1=7$ ✅ (cohérent avec le tableau du cours).

💡 Cet argument « $k=\max\{k : S(k)\le n\}$ » est exactement le calcul d'une **racine entière** (comme $\lfloor\sqrt N\rfloor$ au TD1) : ici $k\approx\sqrt{2n}$.

#### (f) Bijection $\mathbb N^p\to\mathbb N$ pour $p\ge2$

✍️ Récurrence sur $p\ge2$, avec $P(p)$ : « il existe une bijection $f_p:\mathbb N^p\to\mathbb N$ ».
- **Init.** $p=2$ : $f_2=M$.
- **Hérédité.** Supposons $f_p$ bijective. Définissons
$$f_{p+1}(x_1,\dots,x_{p+1})=M\big(f_p(x_1,\dots,x_p),\,x_{p+1}\big).$$
C'est la composée de $g:(x,y)\mapsto(f_p(x),y)$, de $\mathbb N^p\times\mathbb N=\mathbb N^{p+1}$ dans $\mathbb N^2$, et de $M$. Or $g$ est bijective (de réciproque $(m,y)\mapsto(f_p^{-1}(m),y)$) et $M$ aussi : la composée de deux bijections est une bijection.
- **Conclusion.** $P(p)$ pour tout $p\ge2$.

**Formule pour $p=3$** :
$$f_3(a,b,c)=M\big(M(a,b),c\big)=\frac{(m+c)(m+c+1)}{2}+c,\qquad\text{où } m=M(a,b)=\frac{(a+b)(a+b+1)}2+b.$$

#### (g) Interprétation

**Définition** : $E$ est **dénombrable** s'il existe une bijection de $E$ dans ℕ (i.e. $\mathrm{card}\,E=\mathrm{card}\,\mathbb N$).
On a démontré : **$\mathbb N^p$ est dénombrable pour tout $p\ge1$** (Prop. 5.10 du cours, ici avec une bijection explicite, sans Cantor–Bernstein).

#### (h) $\mathbb N^{\mathbb N}$ est-il dénombrable ?

**Non.** ✍️ L'ensemble $\{0,1\}^{\mathbb N}$ des suites de 0 et de 1 est inclus dans $\mathbb N^{\mathbb N}$ : l'inclusion est une injection, donc $\mathrm{card}\,\{0,1\}^{\mathbb N}\le\mathrm{card}\,\mathbb N^{\mathbb N}$. D'après le cours, $\{0,1\}^{\mathbb N}$ est en bijection avec $\mathcal P(\mathbb N)$, et par le **théorème de Cantor** $\mathrm{card}\,\mathbb N<\mathrm{card}\,\mathcal P(\mathbb N)$. Si $\mathbb N^{\mathbb N}$ était dénombrable, on aurait une injection $\mathcal P(\mathbb N)\to\mathbb N$, donc $\mathrm{card}\,\mathcal P(\mathbb N)\le\mathrm{card}\,\mathbb N$, et par Cantor–Bernstein une bijection : contradiction.

*Variante directe (diagonale)* : si $n\mapsto u^{(n)}$ énumérait $\mathbb N^{\mathbb N}$, la suite $v_k=u^{(k)}_k+1$ différerait de chaque $u^{(n)}$ en position $n$.

⚠️ **Piège** : $\mathbb N^p$ (produit **fini**) est dénombrable, mais $\mathbb N^{\mathbb N}$ (produit **infini**) ne l'est pas.

---

## Exercice 2 — Variantes de la définition de la limite

🧭 **Méthode** : comparer chaque énoncé à la définition officielle (Déf. 1.11) : $\forall\varepsilon>0,\ \exists N,\ \forall n\ge N,\ \lvert u_n-\ell\rvert<\varepsilon$.

**Énoncé 1** : $\forall\varepsilon>0,\ \exists N,\ \forall n\ge N,\ \lvert u_n-\ell\rvert\le\varepsilon$. → **Équivalent.**
- Définition ⇒ (1) : $<\varepsilon$ implique $\le\varepsilon$.
- (1) ⇒ définition : soit $\varepsilon>0$. On applique (1) avec $\varepsilon'=\frac\varepsilon2>0$ : il existe $N$ tel que pour $n\ge N$, $\lvert u_n-\ell\rvert\le\frac\varepsilon2<\varepsilon$.

**Énoncé 2** : $\forall\varepsilon\ge0,\ \exists N,\ \forall n\ge N,\ \lvert u_n-\ell\rvert<\varepsilon$. → **Non équivalent : il est toujours faux.**
Pour $\varepsilon=0$, il demanderait $\lvert u_n-\ell\rvert<0$, ce qui est impossible. Aucune suite ne le vérifie, alors que des suites convergentes existent (ex. $u_n=\ell$).

💡 Inégalité stricte ou large après le ε : **peu importe**. Mais $\varepsilon>0$ strictement : **indispensable**.

---

## Exercice 3 — Suite arithmético-géométrique $u_{n+1}=au_n+b$

🧭 **Méthode** (fiche M12) : chercher un **point fixe** $c$ ($c=ac+b$), puis poser $v_n=u_n-c$.

**Cas $a=0$** : $u_{n+1}=b$, donc $u_n=b$ pour tout $n\ge1$ (et $u_0$ quelconque). Suite stationnaire.

**Cas $a=1$** : $u_{n+1}=u_n+b$ : suite **arithmétique** de raison $b$, $u_n=u_0+nb$.

**Cas $a\notin\{0,1\}$** :
- Point fixe : $c=ac+b\iff c(1-a)=b\iff c=\dfrac{b}{1-a}$ (possible car $a\ne1$).
- $v_n=u_n-c$ vérifie $v_{n+1}=au_n+b-c=au_n+b-(ac+b)=a(u_n-c)=av_n$ : **géométrique** de raison $a$.
- Donc $v_n=a^nv_0$, soit
$$\boxed{u_n=\frac{b}{1-a}+a^n\left(u_0-\frac{b}{1-a}\right)}$$

💡 Comportement (avec l'Ex. 4 sur $q^n$) : si $\lvert a\rvert<1$, $u_n\to\frac b{1-a}$ ; si $\lvert a\rvert\ge1$ ($a\ne1$), $u_n$ diverge sauf si $u_0=c$ (suite constante).
Application informatique : coût $T(n)=2T(n-1)+1$ (tours de Hanoï) donne $T(n)=2^n-1$ avec $T(0)=0$.

---

## Exercice 4 — Convergence dans ℂ

🧭 **Méthodes** : opérations sur les limites (Prop. 1.18), factorisation par le terme dominant (Méthode 2.14), suite non bornée ⇒ divergente (Prop. 1.21), quantité conjuguée.

#### $u_n=\dfrac{n^2(1+3i)-2i+1}{n(n+i)}$

On factorise par $n^2$ en haut et en bas :
$$u_n=\frac{n^2\left[(1+3i)+\frac{1-2i}{n^2}\right]}{n^2\left(1+\frac in\right)}=\frac{(1+3i)+\frac{1-2i}{n^2}}{1+\frac in}.$$
$\frac{1-2i}{n^2}\to0$ et $\frac in\to0$ (module $\frac1n$), donc par opérations sur les limites (le dénominateur tend vers $1\ne0$) : $u_n\to1+3i$. **Convergente.**

#### $u_n=\dfrac{2in^3-n^2\cos n}{n^2+2n-2}$

$$u_n=n\cdot\frac{2i-\frac{\cos n}{n}}{1+\frac2n-\frac2{n^2}}.$$
$\frac{\cos n}{n}\to0$ (bornée × →0), donc la fraction tend vers $2i$ et son module vers $2$. Ainsi $\lvert u_n\rvert=n\cdot\lvert\ldots\rvert\to+\infty$ : $(u_n)$ **n'est pas bornée, donc diverge** (une suite convergente est bornée).
(En fait $\mathrm{Im}\,u_n=\frac{2n^3}{n^2+2n-2}\to+\infty$.)

#### $u_n=q^n$ selon $q\in\mathbb C$

| Cas | Conclusion |
|---|---|
| $\lvert q\rvert<1$ | $\lvert q^n\rvert=\lvert q\rvert^n\to0$, donc $q^n\to0$ |
| $q=1$ | constante, $\to1$ |
| $\lvert q\rvert>1$ | $\lvert q^n\rvert=\lvert q\rvert^n\to+\infty$ : non bornée ⇒ **diverge** |
| $\lvert q\rvert=1,\ q\ne1$ | **diverge** (preuve ci-dessous) |

✍️ *Cas $\lvert q\rvert=1$, $q\ne1$.* Supposons $q^n\to\ell$. La suite extraite $(q^{n+1})$ tend aussi vers $\ell$ (Prop. 1.17). Mais $q^{n+1}=q\cdot q^n\to q\ell$. Par unicité de la limite, $\ell=q\ell$, soit $\ell(1-q)=0$, donc $\ell=0$. Or $\lvert q^n\rvert=1$ pour tout $n$, donc $\lvert\ell\rvert=1$ (continuité du module) : contradiction.

💡 Résumé : **$q^n$ converge ⟺ $\lvert q\rvert<1$ ou $q=1$.** Exemples : $i^n$, $(-1)^n$, $e^{in}$ divergent.

#### $u_n=\sqrt{n+1}-\sqrt n$

Forme indéterminée $\infty-\infty$ → **quantité conjuguée** :
$$u_n=\frac{(\sqrt{n+1}-\sqrt n)(\sqrt{n+1}+\sqrt n)}{\sqrt{n+1}+\sqrt n}=\frac{1}{\sqrt{n+1}+\sqrt n}\to0.$$
(De plus $u_n\sim\frac{1}{2\sqrt n}$.)

#### $u_n=\sqrt{n^2+n}-n$

$$u_n=\frac{n^2+n-n^2}{\sqrt{n^2+n}+n}=\frac{n}{n\left(\sqrt{1+\frac1n}+1\right)}=\frac{1}{\sqrt{1+\frac1n}+1}\to\frac12.$$

⚠️ Une erreur fréquente : « $\sqrt{n^2+n}\sim n$ donc $\sqrt{n^2+n}-n\sim n-n=0$ ». **On ne soustrait pas des équivalents** (Avertissement 1.46).

---

## Exercice 5 — Somme géométrique $G(n)=\sum_{k=0}^{n-1}q^k$

#### (a) $q=1$
$G(n)=\sum_{k=0}^{n-1}1=n$.

#### (b) $q\ne1$
**Somme télescopique** : $G(n)-\sum_{k=1}^{n}q^k=(1+q+\dots+q^{n-1})-(q+\dots+q^n)=1-q^n$.
Or $\sum_{k=1}^nq^k=q\sum_{k=0}^{n-1}q^k=qG(n)$. Donc
$$(1-q)G(n)=1-q^n\quad\Longrightarrow\quad\boxed{G(n)=\frac{1-q^n}{1-q}}$$

#### (c) Équivalents quand $\lvert q\rvert\ne1$

**$\lvert q\rvert<1$** : $q^n\to0$, donc $G(n)\to\frac1{1-q}\ne0$. Par la Prop. 1.34 (limite non nulle ⟺ équivalent à la limite) :
$$G(n)\sim\frac{1}{1-q}.$$

**$\lvert q\rvert>1$** : on factorise par le terme dominant $q^n$ :
$$G(n)=\frac{q^n-1}{q-1}=\frac{q^n}{q-1}\left(1-q^{-n}\right),\quad\text{et } q^{-n}\to0\ \text{ car } \lvert q^{-1}\rvert<1.$$
Donc $\dfrac{G(n)}{q^n/(q-1)}\to1$ :
$$G(n)\sim\frac{q^n}{q-1}.$$

**A-t-on $G(n)\sim q^n$ ?**
- Si $\lvert q\rvert>1$ : $\frac{G(n)}{q^n}\to\frac1{q-1}$, qui vaut $1$ **ssi $q=2$**. Donc $G(n)\sim q^n$ uniquement pour $q=2$ (et alors $G(n)=2^n-1\sim2^n$).
- Si $0<\lvert q\rvert<1$ : $\lvert G(n)\rvert\to\frac{1}{\lvert1-q\rvert}>0$ tandis que $\lvert q^n\rvert\to0$, donc $\left\lvert\frac{G(n)}{q^n}\right\rvert\to+\infty$ : non.
- Si $q=0$ : $q^n=0$ pour $n\ge1$ alors que $G(n)=1$ : non.

💡 Lien info : $1+2+4+\dots+2^{n-1}=2^n-1$ (nombre de nœuds d'un arbre binaire complet, coût amorti du doublement d'un tableau dynamique) ; et pour $\lvert q\rvert>1$, **la somme est du même ordre que son dernier terme** : $G(n)=\Theta(q^n)$.

#### (d) $\lvert q\rvert=1$ : quand $(G(n))$ est-elle bornée ?

- $q=1$ : $G(n)=n$ **non bornée**.
- $q\ne1$ : $\lvert G(n)\rvert=\dfrac{\lvert1-q^n\rvert}{\lvert1-q\rvert}\le\dfrac{1+\lvert q\rvert^n}{\lvert1-q\rvert}=\dfrac{2}{\lvert1-q\rvert}$ : **bornée**.

Réponse : **bornée ⟺ $q\ne1$**. (Ex. $q=-1$ : $G(n)\in\{0,1\}$ ; $q=i$ : $G(n)\in\{0,1,1+i,i\}$.)

---

## Exercice 6 — Manipulation des équivalents

🧭 **Méthode** : comme $u_n,v_n\ne0$, $u_n\sim v_n\iff\frac{u_n}{v_n}\to1$ (Prop. 1.33). Pour **réfuter**, un **contre-exemple** simple suffit.

#### (a)
- **$u_n^2\sim v_n^2$ : OUI.** $\frac{u_n^2}{v_n^2}=\left(\frac{u_n}{v_n}\right)^2\to1^2=1$.
- **$2^{u_n}\sim2^{v_n}$ : NON en général.** Contre-exemple : $u_n=n+1$, $v_n=n$. On a $u_n\sim v_n$, mais $\frac{2^{n+1}}{2^n}=2\not\to1$.

💡 Un équivalent contrôle le **rapport** $u_n/v_n$, pas la **différence** $u_n-v_n$ ; or $\frac{2^{u_n}}{2^{v_n}}=2^{u_n-v_n}$ dépend de la différence. On ne compose pas les équivalents par une fonction (ici $\exp$).

#### (b)
- **$u_n+a_n\sim v_n+a_n$ : NON en général.** Contre-exemple : $u_n=n^2+n$, $v_n=n^2$, $a_n=1-n^2$. Alors $u_n\sim v_n$, mais $u_n+a_n=n+1$ et $v_n+a_n=1$, et $\frac{n+1}{1}\to+\infty$.
- **$u_na_n\sim v_na_n$ : OUI.** Avec la définition : $u_n-v_n=o(v_n)$, i.e. pour tout $\varepsilon>0$, $\lvert u_n-v_n\rvert\le\varepsilon\lvert v_n\rvert$ à partir d'un rang. En multipliant par $\lvert a_n\rvert$ : $\lvert u_na_n-v_na_n\rvert\le\varepsilon\lvert v_na_n\rvert$. Donc $u_na_n-v_na_n=o(v_na_n)$. (Si $a_n\ne0$ : directement $\frac{u_na_n}{v_na_n}=\frac{u_n}{v_n}\to1$.)

#### (c) Tout est strictement positif : **OUI**.
✍️
$$\left\lvert\frac{u_n+a_n}{v_n+a_n}-1\right\rvert=\frac{\lvert u_n-v_n\rvert}{v_n+a_n}\le\frac{\lvert u_n-v_n\rvert}{v_n}=\left\lvert\frac{u_n}{v_n}-1\right\rvert\to0,$$
car $v_n+a_n\ge v_n>0$. Par gendarmes, $\frac{u_n+a_n}{v_n+a_n}\to1$.

💡 Le contre-exemple de (b) fonctionnait grâce à une **compensation** ($a_n$ négatif annule le terme principal). Avec des termes positifs, aucune compensation n'est possible : c'est pour cela qu'en complexité (coûts positifs) on peut additionner sans danger.

---

## Exercice 7 — Comparaisons avec $u_n=n^3$

🧭 **Méthode** (fiche M10) : étudier $\dfrac{u_n}{a_n}$ (ou les modules).
- $\to1$ : $\sim$ (donc aussi $O$, $\Omega$, $\Theta$) ;
- $\to L$ avec $0<\lvert L\rvert<\infty$, ou rapport borné et « loin de 0 » : $\Theta$ ;
- $\to0$ : $u=o(a)$ (donc $O$, pas $\Omega$) ;
- module $\to+\infty$ : $a=o(u)$ (donc $\Omega$, pas $O$).

| | $u\sim a$ | $u=o(a)$ | $a=o(u)$ | $u=O(a)$ | $u=\Omega(a)$ | $u=\Theta(a)$ |
|---|---|---|---|---|---|---|
| (a) $n^3+n^2+2\sin n$ | ✅ | ❌ | ❌ | ✅ | ✅ | ✅ |
| (b) $e^{in}n^3$ | ❌ | ❌ | ❌ | ✅ | ✅ | ✅ |
| (c) $2^n$ | ❌ | ✅ | ❌ | ✅ | ❌ | ❌ |
| (d) $\frac{n^4+1}{n^2-3}$ | ❌ | ❌ | ✅ | ❌ | ✅ | ❌ |

**Justifications.**

**(a)** $\dfrac{a_n}{n^3}=1+\dfrac1n+\dfrac{2\sin n}{n^3}\to1$ ($\sin n$ borné). Donc $u_n\sim a_n$, ce qui entraîne $\Theta$, $O$, $\Omega$ ; et ni $o$ dans un sens ni dans l'autre (le rapport tend vers 1, pas vers 0 ni ∞).

**(b)** $\lvert a_n\rvert=n^3=\lvert u_n\rvert$, donc $\lvert u_n\rvert\le1\cdot\lvert a_n\rvert$ et $\lvert u_n\rvert\ge1\cdot\lvert a_n\rvert$ : $O$, $\Omega$, $\Theta$ ✅. Mais $\frac{u_n}{a_n}=e^{-in}$, qui **ne tend pas vers 1** (c'est $q^n$ avec $q=e^{-i}$, $\lvert q\rvert=1$, $q\ne1$ : divergente par l'Ex. 4). Donc $u_n\not\sim a_n$.
💡 **Exemple parfait de $\Theta\not\Rightarrow\sim$** (avec le Rem. 1.42 du cours : $n$ et $2n$).

**(c)** $\frac{n^3}{2^n}\to0$ par **croissances comparées** (Prop. 2.15) : $u_n=o(2^n)$, donc $O$. Pas $\Omega$ (sinon $\frac{n^3}{2^n}\ge c>0$ à partir d'un rang, contredit la limite nulle), donc pas $\Theta$.

**(d)** Défini pour tout $n$ car $n^2=3$ n'a pas de solution entière. Factorisation : $a_n=\frac{n^4(1+n^{-4})}{n^2(1-3n^{-2})}\sim n^2$. Donc $\frac{a_n}{n^3}\sim\frac1n\to0$ : $a_n=o(u_n)$, donc $u_n=\Omega(a_n)$ ; et $\frac{u_n}{a_n}\to+\infty$ : pas $O$, pas $\Theta$.

---

## Exercice 8 — Limites dans $\overline{\mathbb R}$

> Lecture de l'énoncé (mise en page du PDF) : les suites sont
> ① $\sqrt{n^2+n+1}-\sqrt n$ ② $\frac{n\sin n}{n^2+1}$ ③ $\frac1n+(-1)^n$ ④ $(-1)^nn$ ⑤ $\frac{(1{,}1)^n}{n^{10}+5}$ ⑥ $n^{20}(0{,}1)^n$ ⑦ $\frac{n^4+2n^2-1}{n^3-n\cos n}$ ⑧ $\frac{2^{n+1}+3^{n+1}}{2^n+3^n}$ ⑨ $\frac{n\sin(n!)}{n^2}$ ⑩ $\frac{\lfloor a_n\rfloor}{a_n}$ avec $a_n\to+\infty$.

**① $\sqrt{n^2+n+1}-\sqrt n\to+\infty$.**
Ici, pas besoin de conjuguée : les deux termes ne sont pas du même ordre ($n$ contre $\sqrt n$). On factorise par le dominant $n$ :
$$\sqrt{n^2+n+1}-\sqrt n=n\left(\sqrt{1+\tfrac1n+\tfrac1{n^2}}-\tfrac{1}{\sqrt n}\right),$$
et la parenthèse tend vers $1-0=1$. Produit $+\infty\times1=+\infty$.
⚠️ Toujours **comparer les ordres de grandeur** avant de dégainer la conjuguée.

**② $\frac{n\sin n}{n^2+1}\to0$.**
$\left\lvert\frac{n\sin n}{n^2+1}\right\rvert\le\frac{n}{n^2+1}\le\frac{n}{n^2}=\frac1n\to0$ : **gendarmes** (ou bornée × →0).

**③ $\frac1n+(-1)^n$ : pas de limite.**
Suites extraites : $u_{2n}=1+\frac1{2n}\to1$ et $u_{2n+1}=-1+\frac1{2n+1}\to-1$. Deux limites différentes ⇒ divergence (Prop. 1.17). (lim sup/inf : Ex. 12.)

**④ $(-1)^nn$ : pas de limite.**
$u_{2n}=2n\to+\infty$ et $u_{2n+1}=-(2n+1)\to-\infty$ : pas de limite dans $\overline{\mathbb R}$.

**⑤ $\frac{(1{,}1)^n}{n^{10}+5}\to+\infty$.**
$\frac{(1{,}1)^n}{n^{10}+5}=\frac{(1{,}1)^n}{n^{10}}\cdot\frac{1}{1+5n^{-10}}$. Par **croissances comparées** ($q=1{,}1>1$, $k=10$), $\frac{(1{,}1)^n}{n^{10}}\to+\infty$, et le second facteur tend vers $1$.
💡 Même une exponentielle « lente » finit par écraser $n^{10}$ (mais il faut $n$ très grand : $(1{,}1)^n>n^{10}$ seulement à partir de $n\approx 690$). C'est pourquoi un algorithme exponentiel est inutilisable même à base $1{,}1$.

**⑥ $n^{20}(0{,}1)^n=\frac{n^{20}}{10^n}\to0$.** Croissances comparées avec $q=10$.

**⑦ $\frac{n^4+2n^2-1}{n^3-n\cos n}\to+\infty$.**
$$=\frac{n^4(1+2n^{-2}-n^{-4})}{n^3\left(1-\frac{\cos n}{n^2}\right)}=n\cdot\frac{1+2n^{-2}-n^{-4}}{1-\frac{\cos n}{n^2}},$$
la fraction tend vers $1$ ($\frac{\cos n}{n^2}\to0$ : bornée × →0). Donc $+\infty$.

**⑧ $\frac{2^{n+1}+3^{n+1}}{2^n+3^n}\to3$.**
Terme dominant $3^n$ :
$$\frac{3^n\left(2\left(\frac23\right)^n+3\right)}{3^n\left(\left(\frac23\right)^n+1\right)}=\frac{2\left(\frac23\right)^n+3}{\left(\frac23\right)^n+1}\to\frac{0+3}{0+1}=3.$$

**⑨ $\frac{n\sin(n!)}{n^2}=\frac{\sin(n!)}{n}\to0$.** $\lvert\sin(n!)\rvert\le1$ : bornée × $\frac1n$.
💡 On ne sait rien de $\sin(n!)$ et on n'en a pas besoin : seule sa **bornitude** compte.

**⑩ $\frac{\lfloor a_n\rfloor}{a_n}\to1$.**
Comme $a_n\to+\infty$, il existe $N$ tel que $a_n>0$ pour $n\ge N$. Pour ces $n$, $a_n-1<\lfloor a_n\rfloor\le a_n$, et en divisant par $a_n>0$ :
$$1-\frac1{a_n}<\frac{\lfloor a_n\rfloor}{a_n}\le1.$$
$\frac1{a_n}\to0^+$ (Prop. 2.12), donc par **gendarmes**, la limite est $1$. Autrement dit $\lfloor a_n\rfloor\sim a_n$.

---

## Exercice 9 — La suite $\left\lfloor\frac{n}{10}\right\rfloor$

**Croissante : OUI.** Lemme : $x\le y\Rightarrow\lfloor x\rfloor\le\lfloor y\rfloor$. En effet $\lfloor x\rfloor\le x\le y$, donc $\lfloor x\rfloor$ est un entier $\le y$ ; or $\lfloor y\rfloor$ est **le plus grand** entier $\le y$, d'où $\lfloor x\rfloor\le\lfloor y\rfloor$. Avec $x=\frac n{10}\le y=\frac{n+1}{10}$ : $u_n\le u_{n+1}$.

**Strictement croissante : NON.** $u_0=\lfloor0\rfloor=0$ et $u_1=\lfloor0{,}1\rfloor=0$. (La suite est constante par paliers de 10 : $0,\dots,0,1,\dots,1,2,\dots$)

**Limite : $+\infty$.** $u_n>\frac{n}{10}-1\to+\infty$, donc par comparaison (Prop. 2.6) $u_n\to+\infty$. (Ou : croissante et non majorée, Th. 2.20.)

💡 C'est la division entière `n // 10` : elle donne le nombre de dizaines.

---

## Exercice 10 — Approximations décimales

Soit $x>0$, $u_n=\dfrac{\lfloor10^nx\rfloor}{10^n}$, $v_n=u_n+\dfrac1{10^n}=\dfrac{\lfloor10^nx\rfloor+1}{10^n}$.

#### (a) Suites adjacentes, de limite $x$

🧭 On vérifie les **4 points** de la Déf. 2.27. Notons $p_n=\lfloor10^nx\rfloor\in\mathbb Z$.

1. **$u_n\le v_n$** : évident, $v_n-u_n=10^{-n}>0$.
2. **$(u_n)$ croissante.** $10p_n$ est un entier et $10p_n\le10\cdot10^nx=10^{n+1}x$ ; or $p_{n+1}$ est le plus grand entier $\le10^{n+1}x$, donc $10p_n\le p_{n+1}$. En divisant par $10^{n+1}$ : $u_n=\frac{10p_n}{10^{n+1}}\le\frac{p_{n+1}}{10^{n+1}}=u_{n+1}$.
3. **$(v_n)$ décroissante.** $10^{n+1}x<10(p_n+1)$ (car $10^nx<p_n+1$). Comme $p_{n+1}\le10^{n+1}x<10(p_n+1)$ et que ce sont des entiers, $p_{n+1}+1\le10(p_n+1)$. En divisant par $10^{n+1}$ : $v_{n+1}\le v_n$.
4. **$v_n-u_n=10^{-n}\to0$.**

Donc $(u_n)$ et $(v_n)$ sont **adjacentes** et convergent vers une limite commune $\ell$. De plus $p_n\le10^nx<p_n+1$ donne $u_n\le x<v_n$ ; par **gendarmes**, $\ell=x$.

#### (b) $\lvert x-u_n\rvert<10^{-n}$

De $10^nx-1<p_n\le10^nx$, en divisant par $10^n$ : $x-10^{-n}<u_n\le x$, donc
$$0\le x-u_n<10^{-n}.$$
**Interprétation** : $u_n$ est l'**approximation décimale par défaut de $x$ à $10^{-n}$ près** (on garde $n$ chiffres après la virgule et on tronque) ; $v_n$ est l'approximation **par excès**. Ex. $x=\pi$ : $u_2=3{,}14$, $v_2=3{,}15$.

#### (c) L'algorithme calcule les décimales

Notons $y_0=x$ et $y_n$ la valeur de $y$ à la fin du tour $n$. L'algorithme fait : $a_n=\lfloor10y_{n-1}\rfloor$ et $y_n=10y_{n-1}-a_n$.

**Invariant 1 : $y_n\in[0,1[$ et $a_n\in\{0,\dots,9\}$** (récurrence).
- $y_0=x\in[0,1[$ par hypothèse.
- Si $y_{n-1}\in[0,1[$, alors $10y_{n-1}\in[0,10[$, donc $a_n=\lfloor10y_{n-1}\rfloor\in\{0,\dots,9\}$, et $y_n=10y_{n-1}-\lfloor10y_{n-1}\rfloor\in[0,1[$ (partie fractionnaire, car $\lfloor t\rfloor\le t<\lfloor t\rfloor+1$).

**Invariant 2 : $10^nx=\displaystyle\sum_{k=1}^na_k10^{n-k}+y_n$** (récurrence).
- $n=0$ : $x=0+y_0$ ✅.
- Si c'est vrai au rang $n$, on multiplie par 10 :
$$10^{n+1}x=\sum_{k=1}^na_k10^{n+1-k}+10y_n=\sum_{k=1}^na_k10^{n+1-k}+a_{n+1}+y_{n+1}=\sum_{k=1}^{n+1}a_k10^{n+1-k}+y_{n+1}.$$

**Conclusion.** $E_n=\sum_{k=1}^na_k10^{n-k}$ est un entier et $10^nx=E_n+y_n$ avec $y_n\in[0,1[$, donc $E_n\le10^nx<E_n+1$ : par **unicité** de la partie entière, $\lfloor10^nx\rfloor=E_n$. En divisant par $10^n$ :
$$u_N=\sum_{k=1}^N\frac{a_k}{10^k}=0{,}a_1a_2\dots a_N.$$

#### (d) $x=\frac37$, $N=10$

On peut travailler **exactement** avec les fractions $y=\frac r7$ (c'est la division posée) :

| $n$ | $10y$ | $a_n$ | nouveau $y$ |
|---|---|---|---|
| 1 | $30/7$ | 4 | $2/7$ |
| 2 | $20/7$ | 2 | $6/7$ |
| 3 | $60/7$ | 8 | $4/7$ |
| 4 | $40/7$ | 5 | $5/7$ |
| 5 | $50/7$ | 7 | $1/7$ |
| 6 | $10/7$ | 1 | $3/7$ ← retour au départ ! |
| 7–10 | … | 4, 2, 8, 5 | … |

$$u_{10}=0{,}4285714285$$

**Phénomène : les décimales sont périodiques** de période 6 : $\frac37=0{,}\overline{428571}$.
**Explication** : $y$ est toujours de la forme $\frac r7$ avec $r\in\{0,\dots,6\}$ (au plus 7 états possibles). Dès qu'un état se répète (ici au tour 6), l'algorithme étant **déterministe**, il refait exactement les mêmes calculs : la suite $(a_n)$ est périodique. Plus généralement, **tout rationnel a un développement décimal périodique** (à partir d'un certain rang).

💡 Côté informatique : si on programme cet algorithme avec des flottants (`double`), les erreurs d'arrondi (en binaire, $\frac37$ n'est pas représentable exactement) finissent par **casser la périodicité** au bout de ~16 chiffres. Avec `fractions.Fraction` en Python, on obtient le résultat exact.

```python
from fractions import Fraction
def decimales(x, N):
    y, a = x, []
    for _ in range(N):
        y *= 10
        d = y.numerator // y.denominator   # floor pour y >= 0
        a.append(d)
        y -= d
    return a
print(decimales(Fraction(3, 7), 10))   # [4, 2, 8, 5, 7, 1, 4, 2, 8, 5]
```

---

## Exercice 11 — Moyenne arithmético-géométrique

$u_0,v_0>0$, $u_{n+1}=\sqrt{u_nv_n}$ (moyenne **géométrique**), $v_{n+1}=\frac{u_n+v_n}{2}$ (moyenne **arithmétique**).

**Étape 1 : bonne définition et positivité.** Récurrence : $u_0,v_0>0$ ; si $u_n,v_n>0$, alors $u_nv_n>0$ donc $u_{n+1}=\sqrt{u_nv_n}$ est défini et $>0$, et $v_{n+1}>0$.

**Étape 2 : $u_n\le v_n$ pour $n\ge1$** (inégalité arithmético-géométrique). Pour $n\ge0$ :
$$v_{n+1}-u_{n+1}=\frac{u_n+v_n}{2}-\sqrt{u_nv_n}=\frac{(\sqrt{v_n}-\sqrt{u_n})^2}{2}\ge0.$$
⚠️ C'est vrai à partir de $n=1$ seulement : rien n'impose $u_0\le v_0$ (d'où le « à partir de $n\ge1$ » de l'énoncé).

**Étape 3 : monotonie pour $n\ge1$.** Puisque $0<u_n\le v_n$ :
- $u_{n+1}=\sqrt{u_nv_n}\ge\sqrt{u_n\cdot u_n}=u_n$ : $(u_n)_{n\ge1}$ **croissante** ;
- $v_{n+1}=\frac{u_n+v_n}2\le\frac{v_n+v_n}2=v_n$ : $(v_n)_{n\ge1}$ **décroissante**.

**Étape 4 : $v_n-u_n\to0$.** Pour $n\ge1$, comme $u_{n+1}\ge u_n$ :
$$0\le v_{n+1}-u_{n+1}\le v_{n+1}-u_n=\frac{u_n+v_n}{2}-u_n=\frac{v_n-u_n}{2}.$$
Par récurrence, $0\le v_n-u_n\le\frac{v_1-u_1}{2^{n-1}}$ pour $n\ge1$, et par gendarmes $v_n-u_n\to0$.

**Conclusion.** $(u_n)_{n\ge1}$ et $(v_n)_{n\ge1}$ sont **adjacentes** : elles convergent vers une même limite $M(u_0,v_0)$, la **moyenne arithmético-géométrique** (Gauss), avec $u_n\le M\le v_n$.

💡 La convergence est en réalité **quadratique** (le nombre de décimales exactes double à chaque étape), bien plus rapide que la majoration $2^{-n}$. Cette suite sert à calculer $\pi$ avec des milliards de décimales (algorithme de Gauss–Legendre / Brent–Salamin).

---

## Exercice 12 — Limites supérieure et inférieure (suites de l'Ex. 8 sans limite)

🧭 **Méthode** (Déf. 2.32) : calculer $S_n=\sup_{k\ge n}u_k$ et $I_n=\inf_{k\ge n}u_k$, ou utiliser des sous-suites qui recouvrent ℕ.

Les suites sans limite dans $\overline{\mathbb R}$ sont ③ et ④.

#### ③ $u_n=\frac1n+(-1)^n$ ($n\ge1$)

Les termes pairs $1+\frac1k$ sont **décroissants** en $k$ et tous $>1$ ; les termes impairs $-1+\frac1k$ sont tous $\le0$.
- $S_n$ = le premier terme pair de rang $\ge n$ : $S_n=1+\frac1{p_n}$ où $p_n\in\{n,n+1\}$ est pair. Donc $S_n\to1$.
- $I_n$ : les termes impairs $-1+\frac1k$ décroissent vers $-1$ sans l'atteindre, donc $I_n=\inf_{k\ge n,\ k\text{ impair}}\left(-1+\frac1k\right)=-1$ pour tout $n$.

$$\limsup u_n=1,\qquad\liminf u_n=-1.$$
(Cohérent avec les sous-suites $u_{2n}\to1$, $u_{2n+1}\to-1$.)

#### ④ $u_n=(-1)^nn$

Pour tout $n$, l'ensemble $\{u_k : k\ge n\}$ contient les $u_{2m}=2m$ (non majorés) et les $u_{2m+1}=-(2m+1)$ (non minorés). Donc $S_n=+\infty$ et $I_n=-\infty$ pour tout $n$ :
$$\limsup u_n=+\infty,\qquad\liminf u_n=-\infty.$$

💡 Vérification avec la Prop. 2.36 : dans les deux cas $\liminf\ne\limsup$, ce qui confirme l'**absence de limite**. Pour toutes les autres suites de l'Ex. 8, $\liminf=\limsup=$ la limite trouvée.

---

## 🎯 Bilan du TD 2 : réflexes à acquérir

1. **Dénombrabilité** : bijection explicite (Cantor par diagonales), récurrence pour $\mathbb N^p$, **Cantor** pour montrer la non-dénombrabilité ($\mathbb N^{\mathbb N}\supset\{0,1\}^{\mathbb N}$).
2. **Définition de la limite** : « $<$ » ou « $\le$ » indifférent, mais **$\varepsilon>0$ strict**.
3. **Suites récurrentes affines** : point fixe + suite géométrique.
4. **$q^n$** : converge ⟺ $\lvert q\rvert<1$ ou $q=1$ ; argument « $\ell=q\ell$ ».
5. **FI** : terme dominant, conjuguée (seulement si les termes sont du même ordre), croissances comparées, bornée × →0.
6. **Équivalents** : produits/quotients/puissances ✅, sommes/compositions ❌ (sauf termes positifs pour les sommes).
7. **Landau** : regarder le rapport ; **$\Theta\not\Rightarrow\sim$** ($e^{in}n^3$).
8. **Adjacentes** : vérifier les 4 points ; la différence se majore souvent par $\frac{\text{qqch}}{2^n}$ ou $10^{-n}$.
9. **lim sup / lim inf** : via $S_n$, $I_n$ ou via les sous-suites paires/impaires.
