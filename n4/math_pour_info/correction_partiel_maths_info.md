# Correction — Partiel Mathématiques pour l'Informatique
**USPN — Licence 2 Informatique, 2025-2026**

---

## Exercice 1 (6 pts) — Applications affines sur ℤ/nℤ

On note $f_{a,b} : \mathbb{Z}/n\mathbb{Z} \to \mathbb{Z}/n\mathbb{Z},\ x \mapsto ax + b$.

---

### Question 1 (2 pts) — CNS pour que $f_{a,b}$ soit bijective

**Réponse :** $f_{a,b}$ est bijective **si et seulement si** $\gcd(a, n) = 1$.

**Justification :**

Comme l'ensemble de départ et d'arrivée sont finis de même cardinal, bijectivité ⟺ injectivité.

Supposons $f_{a,b}(x) = f_{a,b}(y)$. Alors $ax + b \equiv ay + b \pmod{n}$, donc $a(x - y) \equiv 0 \pmod{n}$.

- **Si $\gcd(a,n) = 1$ :** alors $n \mid (x-y)$, donc $x \equiv y \pmod{n}$ → injectivité ✓
- **Si $\gcd(a,n) = d > 1$ :** alors $x_0 = n/d \not\equiv 0$ vérifie $a \cdot (n/d) \equiv 0 \pmod{n}$, donc $f_{a,b}(0) = f_{a,b}(n/d)$ → pas injective ✗

**Conclusion : $f_{a,b}$ est bijective $\iff \gcd(a, n) = 1$.**

---

### Question 2 (2 pts) — Nombre d'applications affines bijectives $\mathbb{Z}/n\mathbb{Z} \to \mathbb{Z}/n\mathbb{Z}$

- Le nombre de valeurs valides pour $a$ est $\varphi(n)$ (indicatrice d'Euler).
- $b$ peut prendre $n$ valeurs quelconques.

**Réponse : il y a $n \cdot \varphi(n)$ applications affines bijectives.**

---

### Question 3 (2 pts) — Bijectivité de $g : x \mapsto 5x - 3$ sur $\mathbb{Z}/7\mathbb{Z}$, et calcul de $g^{-1}$

**Bijectivité :** $g = f_{5,-3}$. On a $\gcd(5, 7) = 1$ ✓ → $g$ est bijective.

**Calcul de $g^{-1}$ :**

On résout $5x - 3 \equiv y \pmod{7}$, soit $5x \equiv y + 3 \pmod{7}$.

Inverse de 5 mod 7 : $5 \times 3 = 15 \equiv 1 \pmod{7}$, donc $5^{-1} \equiv 3$.

Alors $x \equiv 3(y+3) \equiv 3y + 9 \equiv 3y + 2 \pmod{7}$.

**Donc $g^{-1} = f_{3,2}$, c'est-à-dire $a = 3$, $b = 2$.**

*Vérification :* $g(g^{-1}(y)) = 5(3y+2) - 3 = 15y + 7 \equiv y \pmod{7}$ ✓

---

## Exercice 2 (7 pts) — Théorème Chinois des Restes

### Question 1(a) (2 pts) — CNS pour que le système ait une solution

$$\begin{cases} x \equiv r_1 \pmod{n_1} \\ x \equiv r_2 \pmod{n_2} \end{cases}$$

**Théorème :** Ce système admet une solution $x \in \mathbb{Z}$ **si et seulement si** $\gcd(n_1, n_2) \mid (r_1 - r_2)$.

**Preuve :** On pose $x = r_1 + k n_1$ (1ère congruence). On substitue dans la 2ème :
$$r_1 + k n_1 \equiv r_2 \pmod{n_2} \implies k n_1 \equiv r_2 - r_1 \pmod{n_2}$$
Cette équation en $k$ a une solution ssi $\gcd(n_1, n_2) \mid (r_2 - r_1)$.

---

### Question 1(b) (1 pt) — Ensemble de toutes les solutions

Lorsqu'une solution $x_0$ existe, l'ensemble de toutes les solutions est :
$$\{ x_0 + k \cdot \text{lcm}(n_1, n_2) \mid k \in \mathbb{Z} \}$$
Autrement dit, la solution est **unique modulo $\text{lcm}(n_1, n_2)$**.

---

### Question 2 (1 pt) — Résoudre $x \equiv 1 \pmod{4}$ et $x \equiv 5 \pmod{8}$

**CNS :** $\gcd(4, 8) = 4$. Il faut $4 \mid (1 - 5) = -4$ ✓ → solution existe.

$x \equiv 5 \pmod{8}$ implique $x \equiv 5 \equiv 1 \pmod{4}$ ✓ (la 2ème congruence est plus forte).

$$\boxed{x \equiv 5 \pmod{8}}$$

---

### Question 3 (3 pts) — Système à 3 congruences

$$\begin{cases} x \equiv 13 \pmod{3} \\ x \equiv 1 \pmod{4} \\ x \equiv 5 \pmod{8} \end{cases}$$

**Étape 1 :** $13 \equiv 1 \pmod{3}$, donc la 1ère devient $x \equiv 1 \pmod{3}$.

**Étape 2 :** D'après la question 2, les deux dernières donnent $x \equiv 5 \pmod{8}$.

**Étape 3 :** On résout :
$$\begin{cases} x \equiv 1 \pmod{3} \\ x \equiv 5 \pmod{8} \end{cases}$$

$\gcd(3, 8) = 1 \mid (1-5)$ ✓. On pose $x = 5 + 8k$ :
$$5 + 8k \equiv 1 \pmod{3} \implies 2k \equiv -4 \equiv 2 \pmod{3} \implies k \equiv 1 \pmod{3}$$

Donc $k = 1 + 3m$, et $x = 5 + 8(1 + 3m) = 13 + 24m$.

$$\boxed{x \equiv 13 \pmod{24}}$$

*Vérification :* $13 \equiv 1 \pmod{3}$ ✓ ; $13 \equiv 1 \pmod{4}$ ✓ ; $13 \equiv 5 \pmod{8}$ ✓

---

## Exercice 3 (8 pts) — Cryptographie RSA

*Rappel :* une clé RSA est un couple $(n, e) \in \mathbb{N}^2$ avec $n = pq$ ($p, q$ premiers distincts) et $\gcd(\varphi(n), e) = 1$.

---

### Question 1(a) (1 pt) — $(18, 73)$ est-elle une clé RSA ?

$18 = 2 \times 3^2$. Ce n'est **pas** un produit de deux premiers distincts (3 est répété).

**Non, $(18, 73)$ n'est pas une clé RSA.**

---

### Question 1(b) (1 pt) — $(77, 55)$ est-elle une clé RSA ?

$77 = 7 \times 11$ ✓. On calcule $\varphi(77) = 6 \times 10 = 60$.

$\gcd(55, 60)$ : $60 = 1 \times 55 + 5$, $55 = 11 \times 5$, donc $\gcd(55, 60) = 5 \neq 1$.

**Non, $(77, 55)$ n'est pas une clé RSA** car $\gcd(\varphi(77), 55) = 5 \neq 1$.

---

### Question 2 (0,5 + 1 pts) — 37 divise 407, décomposition, $\varphi(407)$

**37 divise 407 :** $407 \div 37 = 11$, donc $407 = 37 \times 11$ ✓.

11 et 37 sont bien premiers (vérifications élémentaires).

**Décomposition :** $407 = 11 \times 37$

**Calcul de $\varphi(407)$ :**
$$\varphi(407) = (11-1)(37-1) = 10 \times 36 = \boxed{360}$$

---

### Question 3 (1 pt) — $(407, 19)$ est une clé RSA ?

$407 = 11 \times 37$ ✓. $\varphi(407) = 360$.

19 est premier et $19 \nmid 360$ (car $360 = 2^3 \times 3^2 \times 5$), donc $\gcd(19, 360) = 1$ ✓.

**Oui, $(407, 19)$ est une clé RSA.**

---

### Question 4 (1 pt) — Trouver $(u, v) \in \mathbb{Z} \times \mathbb{N}$ tel que $\varphi(407) \cdot u + 19v = 1$

On applique l'algorithme d'Euclide étendu sur $(360, 19)$ :

| Division euclidienne | Reste |
|---|---|
| $360 = 18 \times 19 + 18$ | $r = 18$ |
| $19 = 1 \times 18 + 1$ | $r = 1$ |
| $18 = 18 \times 1 + 0$ | fin |

Remontée :
$$1 = 19 - 1 \times 18 = 19 - (360 - 18 \times 19) = 19 \times 19 - 1 \times 360$$

$$\boxed{u = -1, \quad v = 19}$$

*Vérification :* $360 \times (-1) + 19 \times 19 = -360 + 361 = 1$ ✓

---

### Question 5 (1,5 pts) — Bijectivité de $x \mapsto x^{19}$ sur $\mathbb{Z}/407\mathbb{Z}$ et réciproque

**Bijectivité :**

De la question 4, $19 \times 19 \equiv 1 \pmod{360}$, donc $19^{-1} \equiv 19 \pmod{\varphi(407)}$.

On définit $\psi : x \mapsto x^{19}$ et on vérifie que $\psi \circ \phi = \mathrm{id}$ :
$$\psi(\phi(x)) = (x^{19})^{19} = x^{361} = x^{360} \cdot x \equiv x \pmod{407}$$
par le théorème d'Euler (et le lemme chinois des restes pour les cas $\gcd(x, 407) > 1$).

Donc $\phi$ est bijective. **L'application réciproque est :**
$$g^{-1} : \mathbb{Z}/407\mathbb{Z} \to \mathbb{Z}/407\mathbb{Z}, \quad x \mapsto x^{19}$$

C'est la même application ! (Car $19^2 \equiv 1 \pmod{360}$ : c'est une **involution**.)

---

### Question 6 (1 pt) — A envoie $x$, B reçoit $y = 406$. Retrouver $x$.

Le chiffrement RSA donne $y \equiv x^{19} \pmod{407}$.

Le déchiffrement utilise la clé privée $d = 19$ (ici $d = e$ car l'application est une involution) :
$$x \equiv y^{19} \equiv 406^{19} \pmod{407}$$

**Calcul :** $406 \equiv -1 \pmod{407}$, donc $406^{19} \equiv (-1)^{19} = -1 \equiv 406 \pmod{407}$.

$$\boxed{x = 406}$$

---

## Récapitulatif

| Question | Résultat |
|---|---|
| Ex1 Q1 | $f_{a,b}$ bijective $\iff \gcd(a,n)=1$ |
| Ex1 Q2 | $n \cdot \varphi(n)$ applications affines bijectives |
| Ex1 Q3 | $g^{-1} = f_{3,2}$ (i.e. $a=3, b=2$) |
| Ex2 Q2 | $x \equiv 5 \pmod{8}$ |
| Ex2 Q3 | $x \equiv 13 \pmod{24}$ |
| Ex3 Q2 | $407 = 11 \times 37$, $\varphi(407) = 360$ |
| Ex3 Q4 | $u = -1$, $v = 19$ |
| Ex3 Q5 | Réciproque : $x \mapsto x^{19}$ (involution) |
| Ex3 Q6 | $x = 406$ |
