# Corrigé — Partiel 1 : Système et Réseaux 2025-2026
**Pierre Rousselin · Université Sorbonne Paris Nord · L2 Informatique**

---

## Exercice 1 : parallel for (12 points)

### Question 1 — `notparallelfor.c` : version séquentielle (6 pts)

**Points importants :**
- Utiliser `sscanf` (et **non** `atoi`) pour détecter les arguments non numériques : `atoi` retourne 0 en cas d'erreur, indiscernable de l'entrée `"0"`.
- Vérifier que `argc == 2` exactement (ni moins, ni plus).
- Allouer `results` sur le tas, libérer en fin de programme.

```c
#include <stdio.h>
#include <stdlib.h>

double compute(int k); /* supposée donnée */

int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return 1;
    }
    if (sscanf(argv[1], "%d", &n) != 1) {
        fprintf(stderr, "Argument invalide : '%s'\n", argv[1]);
        return 1;
    }
    double *results = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
        results[i] = compute(i);
    for (int i = 0; i < n; i++)
        printf("%g\n", results[i]);
    free(results);
    return 0;
}
```

---

### Question 2 — `parallelfor.c` : version parallèle avec `NUM_THREADS` threads (6 pts)

**Répartition interleaved :** le thread numéro `i` calcule `results[i]`, `results[i + NUM_THREADS]`, `results[i + 2*NUM_THREADS]`, …

**Piège critique :** il faut allouer **un `struct worker_arg` distinct sur le tas pour chaque thread**. Si on réutilisait la même variable en boucle, le thread suivant écraserait les champs `id` avant que le thread précédent ne les ait lus → race condition.

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 8

double compute(int k); /* supposée donnée */

struct worker_arg {
    int    id;       /* indice du thread (0..NUM_THREADS-1) */
    int    n;        /* taille totale du tableau            */
    double *results; /* tableau partagé en écriture         */
};

void *worker(void *arg) {
    struct worker_arg *wa = arg;
    for (int k = wa->id; k < wa->n; k += NUM_THREADS)
        wa->results[k] = compute(k);
    free(wa); /* chaque thread libère son propre struct */
    return NULL;
}

int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) { fprintf(stderr, "Usage: %s n\n", argv[0]); return 1; }
    if (sscanf(argv[1], "%d", &n) != 1) {
        fprintf(stderr, "Argument invalide\n"); return 1;
    }
    double *results = malloc(n * sizeof(double));
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        struct worker_arg *wa = malloc(sizeof(struct worker_arg));
        wa->id = i;  wa->n = n;  wa->results = results;
        pthread_create(&threads[i], NULL, worker, wa);
    }
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);
    for (int i = 0; i < n; i++)
        printf("%g\n", results[i]);
    free(results);
    return 0;
}
```

> **Libération mémoire :** chaque thread libère son propre `worker_arg` via `free(wa)`. Le tableau `results` est libéré par le thread principal après tous les `pthread_join`.

---

## Exercice 2 : fork, wait, kill et exec (6 points)

### Question 1 — Arbre de création pour `./a.out` (sans argument → n = 3) (4 pts)

**Analyse clé :** `p = getpid()` est capturé **avant** le `fork()`. Après le fork, les deux copies (parent et enfant) ont la même valeur de `p` (le PID du parent). L'enfant exécute immédiatement `kill(p, SIGKILL)` — ce qui tue son propre parent. Le parent, bloqué dans `wait()`, reçoit SIGKILL et meurt **sans jamais afficher `"plop"`**.

| Processus | Actions (dans l'ordre) |
|---|---|
| **P0** (initial) | `print "prem's !"` → `print "lol"` → `fork()` → `wait()` → **tué par P1** |
| **P1** (enfant de P0) | `kill(PID_P0)` → n=2 → `print "lol"` → `fork()` → `wait()` → **tué par P2** |
| **P2** (enfant de P1) | `kill(PID_P1)` → n=1 → `print "lol"` → `fork()` → `wait()` → **tué par P3** |
| **P3** (enfant de P2) | `kill(PID_P2)` → n=0 → `execlp("./a.out", "0")` |
| **P3 après exec** | n=0 ≤ 0 → `print "der !"` → `return 0` |

**Affichages pour n = 3 :**

| Chaîne | Nombre | Raison |
|---|:---:|---|
| `"prem's !"` | **1** | Affiché par P0 avant la boucle |
| `"lol"` | **3** | Une fois par itération (P0, P1, P2) |
| `"plop"` | **0** | Parent tué par l'enfant avant de sortir de `wait()` |
| `"der !"` | **1** | Affiché par P3 après exec avec n=0 |
| `"haha"` | **0** | `execlp` réussit → `printf` suivant jamais atteint |

---

### Question 2 — Généralisation pour n > 0 quelconque (2 pts)

La chaîne de kills se répète identiquement à chaque itération. Après n itérations, le dernier processus sort de la boucle avec n=0 et fait `execlp("0")`.

| Chaîne | Nombre d'affichages |
|---|:---:|
| `"prem's !"` | **1** |
| `"lol"` | **n** |
| `"plop"` | **0** |
| `"der !"` | **1** |
| `"haha"` | **0** |

> **Preuve de `"plop" = 0` :** l'enfant exécute `kill(p_parent)` avant toute autre chose. Le parent est bloqué dans `wait()` et ne peut pas atteindre `printf("plop")` avant que `wait()` retourne. Or `wait()` ne retourne jamais car le parent est tué. D'où : `printf("plop")` n'est exécuté pour aucune valeur de n.

---

## Exercice 3 : Un petit calcul... (10 points)

### Question 1 — Diagramme de dépendances (2 pts)

```
         ┌──────── a ─────────────────┐
         │                            ↓
x, n ────┤──────── b ──────┬────────→ d ──┐
         │                 ↓              ↓
         └──────── c ──────→ e ───────────→ calcul_f(e - d) = res
```

| Calcul | Dépend de | Peut commencer quand |
|---|---|---|
| `a = calcul_a(x, n)` | x, n | Immédiatement |
| `b = calcul_b(x, n)` | x, n | Immédiatement |
| `c = calcul_c(x, n)` | x, n | Immédiatement |
| `d = calcul_d(a, b)` | a et b | Quand a **ET** b sont prêts |
| `e = calcul_e(b+c)` | b et c | Quand b **ET** c sont prêts |
| `res = calcul_f(e-d)` | e et d | Quand e **ET** d sont prêts |

---

### Question 2 — Parallélisation avec threads et sémaphores (8 pts)

**Stratégie :** 5 threads (un par calcul intermédiaire) + 5 sémaphores. Le thread `b` fait **deux `sem_post`** car `b` est attendu à la fois par `thread_d` et par `thread_e`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

/* ZONE GLOBALE — uniquement les sémaphores */
sem_t sem_a, sem_b, sem_c, sem_d, sem_e;

double calcul_a(double x, int n);
double calcul_b(double x, int n);
double calcul_c(double x, int n);
double calcul_d(double x, double y);
double calcul_e(double x);
double calcul_f(double x);

struct calcul {
    double x, a, b, c, d, e;
    int n;
};

void *thread_a(void *arg) {
    struct calcul *calc = arg;
    calc->a = calcul_a(calc->x, calc->n);
    sem_post(&sem_a);
    return NULL;
}

void *thread_b(void *arg) {
    struct calcul *calc = arg;
    calc->b = calcul_b(calc->x, calc->n);
    sem_post(&sem_b); /* pour thread_d */
    sem_post(&sem_b); /* pour thread_e */
    return NULL;
}

void *thread_c(void *arg) {
    struct calcul *calc = arg;
    calc->c = calcul_c(calc->x, calc->n);
    sem_post(&sem_c);
    return NULL;
}

void *thread_d(void *arg) {
    struct calcul *calc = arg;
    sem_wait(&sem_a); /* attend a */
    sem_wait(&sem_b); /* attend b (1re des 2 posts) */
    calc->d = calcul_d(calc->a, calc->b);
    sem_post(&sem_d);
    return NULL;
}

void *thread_e(void *arg) {
    struct calcul *calc = arg;
    sem_wait(&sem_b); /* attend b (2e des 2 posts) */
    sem_wait(&sem_c); /* attend c */
    calc->e = calcul_e(calc->b + calc->c);
    sem_post(&sem_e);
    return NULL;
}

int main(void) {
    struct calcul calc;
    scanf("%lf %d", &(calc.x), &(calc.n));

    sem_init(&sem_a, 0, 0);
    sem_init(&sem_b, 0, 0);
    sem_init(&sem_c, 0, 0);
    sem_init(&sem_d, 0, 0);
    sem_init(&sem_e, 0, 0);

    pthread_t ta, tb, tc, td, te;
    pthread_create(&ta, NULL, thread_a, &calc);
    pthread_create(&tb, NULL, thread_b, &calc);
    pthread_create(&tc, NULL, thread_c, &calc);
    pthread_create(&td, NULL, thread_d, &calc);
    pthread_create(&te, NULL, thread_e, &calc);

    /* Attendre que d et e soient calculés avant calcul_f */
    sem_wait(&sem_d);
    sem_wait(&sem_e);
    double res = calcul_f(calc.e - calc.d);
    printf("Résultat : %g\n", res);

    pthread_join(ta, NULL); pthread_join(tb, NULL);
    pthread_join(tc, NULL); pthread_join(td, NULL);
    pthread_join(te, NULL);

    sem_destroy(&sem_a); sem_destroy(&sem_b); sem_destroy(&sem_c);
    sem_destroy(&sem_d); sem_destroy(&sem_e);
    return 0;
}
```

> **Pourquoi `sem_post(&sem_b)` deux fois ?** Le sémaphore `sem_b` est consommé par deux threads distincts (`thread_d` et `thread_e`). Chaque `sem_wait` consomme 1 unité. `thread_b` doit donc en produire 2. Avec un seul `sem_post`, l'un des deux resterait bloqué → deadlock garanti.

> **Pourquoi `main` fait `sem_wait` avant `calcul_f` ?** Cela permet d'agir dès que les deux dépendances de `calcul_f` sont satisfaites, sans attendre la fin de tous les threads (a, b, c pourraient encore se terminer).

---

## Exercice 4 : Le cuisinier et les mangeurs (10 points)

### Question 1 — Attente de la fin des threads (ZONE D'AJOUT 3) (2 pts)

```c
/* ZONE D'AJOUT 3 */
pthread_join(cuisto, NULL);
for (i = 0; i < NB_MANGEURS; i++)
    pthread_join(mangeurs[i], NULL);

/* Libération des ressources */
sem_destroy(&plein);
sem_destroy(&marmite_vide);
pthread_mutex_destroy(&mut);
```

---

### Question 2 — Synchronisation cuisinier ↔ mangeurs (8 pts)

**Primitives de synchronisation :**

| Primitive | Valeur initiale | Rôle |
|---|:---:|---|
| `sem_t plein` | **0** | Nombre de repas disponibles dans la marmite |
| `sem_t marmite_vide` | **1** | 1 = marmite vide au départ, cuisinier peut démarrer |
| `pthread_mutex_t mut` | — | Accès exclusif à `nb_repas_marmite` et `marmite[]` |

```c
/* ZONE D'AJOUT 1 — variables globales */
sem_t plein;
sem_t marmite_vide;
pthread_mutex_t mut;
```

```c
/* ZONE D'AJOUT 2 — dans main(), avant pthread_create */
sem_init(&plein,        0, 0); /* marmite vide au départ           */
sem_init(&marmite_vide, 0, 1); /* cuisinier doit cuisiner tout de suite */
pthread_mutex_init(&mut, NULL);
```

```c
/* À MODIFIER 1 — cuisinier synchronisé */
void *cuisinier(void *arg) {
    for (;;) {
        sem_wait(&marmite_vide); /* attend que la marmite soit vide     */
        int repas = cuisiner();  /* cuisine HORS mutex (peut être long) */
        remplir_marmite(repas);  /* remplit N repas                     */
        for (int i = 0; i < N; i++)
            sem_post(&plein);    /* signale N repas disponibles         */
    }
}
```

```c
/* À MODIFIER 2 — mangeur synchronisé */
void *mangeur(void *arg) {
    for (;;) {
        sem_wait(&plein);                      /* attend qu'il y ait un repas  */
        pthread_mutex_lock(&mut);              /* accès exclusif à la marmite  */
        int repas = se_servir_dans_marmite();
        int vide = (nb_repas_marmite == 0);    /* dernier repas pris ?         */
        pthread_mutex_unlock(&mut);
        if (vide)
            sem_post(&marmite_vide);           /* réveille le cuisinier        */
        manger(repas);                         /* mange HORS mutex             */
    }
}
```

**Analyse des contraintes respectées :**

| Contrainte | Mécanisme |
|---|---|
| Un seul mangeur accède à la marmite à la fois | `pthread_mutex_lock/unlock` autour de `se_servir_dans_marmite()` |
| Mangeur attend qu'il y ait un repas | `sem_wait(&plein)` — bloque si marmite vide |
| Cuisinier attend que la marmite soit vide | `sem_wait(&marmite_vide)` |
| Cuisinier cuisine pendant que les mangeurs se servent | `cuisiner()` appelé **hors mutex** |
| Les mangeurs peuvent manger simultanément | `manger()` appelé **hors mutex** |
| Un seul mangeur réveille le cuisinier | Test `nb_repas_marmite == 0` **sous mutex** → un seul thread verra 0 |

> **Preuve d'absence de race condition :** le test `nb_repas_marmite == 0` est effectué sous mutex. Un seul thread peut décrementer et tester simultanément. Un seul thread verra 0 et fera `sem_post(&marmite_vide)` — le cuisinier n'est réveillé qu'une seule fois par vidage.

> **Preuve d'absence de deadlock :** le cuisinier est hors mutex. Il ne peut pas être bloqué en attente du mutex pendant qu'un mangeur attend la marmite pleine. `sem_wait(&plein)` se débloquera dès que le cuisinier aura rempli la marmite — ce qui arrivera toujours car le cuisinier n'est jamais bloqué par les mangeurs.
