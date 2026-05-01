# Corrections — Système d'exploitation, TDs 1 à 10
**L2 Informatique — Université Sorbonne Paris Nord — 2025-2026**

---

## Table des matières

- [TD1 — Processus & fork](#td1)
- [TD2 — execv, forkbomb](#td2)
- [TD3 — Threads, void*](#td3)
- [TD4 — Sémaphores](#td4)
- [TD5 — Coiffeur, Oracle, Lecteurs](#td5)
- [TD6 — Appel read, buffers](#td6)
- [TD7 — pipe & dup2](#td7)
- [TD8 — Opérations bit-à-bit](#td8)
- [TD9 — Sérialisation, UDP](#td9)
- [TD10 — TCP, clients/serveurs](#td10)

---

<a id="td1"></a>

# TD 1 — Processus, fork, getpid, wait

## Exercice 1 — Mousse au chocolat (parallélisme)

### Question 1

> _Durée pour un seul cuisinier ?_

Les 11 tâches séquentielles (1 casser + 1 fondre + 6 séparations + 1 mélange + 1 monter + 1 incorporer) :

- T1 (casser) : 2 min

- T2 (fondre) : 10 min

- T3_1..T3_6 (séparer chaque œuf) : 6 × 2 = 12 min

- T4 (mélanger jaunes + chocolat) : 2 min

- T5 (monter blancs) : 6 min

- T6 (incorporer) : 10 min

**Total séquentiel = 2 + 10 + 12 + 2 + 6 + 10 = 42 minutes**

### Question 2

> _Dépendances entre tâches, diagramme._

```
T1 (casser chocolat, 2min)
 └──► T2 (fondre, 10min)
         └──────────────────────────────────►┐
T3_k (séparer œuf k, 2min each, k=1..6)     │
 ├──► (jaunes) ──────────────────────────────► T4 (mélanger jaunes+chocolat, 2min)
 │                                                └──► T6 (incorporer, 10min) ◄──┐
 └──► (blancs) ──► T5 (monter en neige, 6min) ──────────────────────────────────┘
```

Règles : T2 dépend de T1 ; T4 dépend de T2 et de toutes les T3_k (besoin des jaunes et du chocolat fondu) ; T5 dépend de toutes les T3_k (besoin des blancs) ; T6 dépend de T4 et T5.

### Question 3

> _Parallélisation optimale._

Le **chemin critique** est T1 → T2 → T4 → T6 = 2+10+2+10 = **24 minutes**. C'est le minimum atteignable.

Stratégie : pendant que le cuisinier 1 exécute T2 (10 min), le cuisinier 2 réalise T3_1..T3_6 (12 min total). Avec un 3e cuisinier, les 6 œufs peuvent être séparés en 4 min (3 cuisiniers × 2 œufs), bien avant que T2 ne se termine.

> ✅ ✓Avec 2 cuisiniers, durée = max(12, 12) + 2 + 6 + 10 = 30 min. Avec suffisamment de cuisiniers, le minimum est 24 min (chemin critique T1→T2→T4→T6).

## Exercice 2 — Arbre de processus avec deux fork()

### Question 1

> _Combien de processus sont créés ?_

Le programme comporte **deux fork()**, et après le premier fork, chaque branche (parent et enfant) exécute le second fork. On obtient :

- fork 1 : P0 crée P1 → 2 processus

- fork 2 executé par P0 et P1 : P0 crée P2, P1 crée P3 → 2 processus supplémentaires

**3 nouveaux processus créés**, 4 processus au total (P0, P1, P2, P3).

### Question 2

> _Nombre d'occurrences de chaque chaîne._

| Chaîne | Qui l'affiche | Occurrences |
| --- | --- | --- |
| "Parent 1" | P0 (retour fork1 = PID de P1) | 1 |
| "Enfant 1" | P1 (retour fork1 = 0) | 1 |
| "Parent 2" | P0 et P1 (retour fork2 = PID de leur enfant) | 2 |
| "Enfant 2" | P2 (enfant de P0 via fork2) et P3 (enfant de P1 via fork2) | 2 |

De plus, chacun des 4 processus affiche `"Je suis le processus X et j'ai terminé"` → **4 fois**.

### Question 3

> _Arbre de création des processus._

```
P0 (processus initial)
 ├──[fork1]──► P1 ("Enfant 1")
 │               └──[fork2]──► P3 ("Enfant 2")
 └──[fork2]──► P2 ("Enfant 2")
```

P0 est le parent de P1 et P2. P1 est le parent de P3. P2 et P3 n'ont pas de descendants.

### Question 4

> _L'ordre de terminaison est-il fixé ?_

**Non.** L'ordonnanceur du noyau décide quel processus s'exécute à quel moment. On ne peut garantir aucun ordre de terminaison sans synchronisation explicite (appel à `wait`).

### Question 5

> _Modifier pour que chaque parent attende ses enfants._

On insère une boucle `wait` à la fin du `main`, que chaque processus exécutera pour attendre ses propres enfants.

```c
#include
#include
#include
#include

void aff_proc(const char *ch);

int main(void) {
    switch (fork()) {
        case -1: perror("fork 1"); return 1;
        case  0: aff_proc("Enfant 1"); break;
        default: aff_proc("Parent 1");
    }
    switch (fork()) {
        case -1: perror("fork 2"); return 1;
        case  0: aff_proc("Enfant 2"); break;
        default: aff_proc("Parent 2");
    }

    printf("Je suis le processus %d et j'ai terminé\n", getpid());

    /* Chaque processus attend tous ses enfants */
    pid_t pid;
    int status;
    while ((pid = wait(&status)) != -1) {
        printf("Je suis %d et mon enfant de pid %d est mort.\n",
               getpid(), pid);
    }
    return 0;
}
```

> ℹ️ ℹChaque processus appelle wait en boucle jusqu'à obtenir -1 (plus d'enfant). P2 et P3 n'ont pas d'enfants → wait retourne -1 immédiatement. P1 attend P3. P0 attend P1 et P2.

## Exercice 3 — Plein de fork

### Question 1

> _Valeur de num_iter sans argument ?_

`argc = 1` (seulement le nom du programme), donc `argc

### Question 2

> _Arbre pour ./plein_de_fork 2._

À chaque itération, le processus courant fait deux fork() : le **1er enfant** (case 0 du fork1) imprime "plop" et continue la boucle ; le **2e enfant** (case 0 du fork2) continue la boucle silencieusement ; le **parent** imprime "hop" et retourne.

```
P0 (i=0)
 ├─[fork1]─► P1 : imprime "plop", continue i=1
 │              ├─[fork1]─► P3 : imprime "plop", i=2 → "bloup"
 │              └─[fork2]─► P4 :                  i=2 → "bloup"
 │              └─ P1 imprime "hop", exit
 ├─[fork2]─► P2 : (silencieux), continue i=1
 │              ├─[fork1]─► P5 : imprime "plop", i=2 → "bloup"
 │              └─[fork2]─► P6 :                  i=2 → "bloup"
 │              └─ P2 imprime "hop", exit
 └─ P0 imprime "hop", exit
```

| Chaîne | Qui | Compte |
| --- | --- | --- |
| plop | P1 (i=0), P3 (i=1), P5 (i=1) | 3 |
| hop | P0, P1, P2 | 3 |
| bloup | P3, P4, P5, P6 | 4 |

Total : 7 processus (P0..P6).

### Question 3

> _Formule générale en fonction de n._

Soit T(n) le nombre total de processus (y compris le processus initial) avec n itérations :

- T(0) = 1 (juste le processus, imprime "bloup")

- T(n) = 1 + 2·T(n-1) (le processus initial + 2 sous-arbres de taille T(n-1))

Solution : **T(n) = 2n+1 − 1**

| n | Total | plop | hop | bloup |
| --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 0 | 1 |
| 1 | 3 | 1 | 1 | 1 |
| 2 | 7 | 3 | 3 | 4 |
| n | 2n+1−1 | 2n−1 | 2n−1 | 2n |

### Question 4 (Bonus)

> _Pourquoi ./a.out 2 | grep plop | wc -l donne 5 ?_

> ⚠️ ⚠Buffering de stdout : quand stdout est redirigé vers un pipe (et non vers un terminal), la libc passe en mode full-buffered (pas line-buffered). "plop\n" ne se retrouve pas immédiatement flushé. Quand le processus fait fork(), le buffer est dupliqué dans l'enfant. À la terminaison, parent et enfant flushent tous les deux le même contenu. Cela multiplie les occurrences de "plop".

---

<a id="td2"></a>

# TD 2 — execv, execvp, forkbomb récursive

## Exercice 1 — Qui dit quoi ?

### Question 1

> _Dessiner argv et new_args juste avant le fork avec ./a plop hop hello._

`argc = 4`, argv = `["./a", "plop", "hop", "hello", NULL]`

`new_args = malloc(4 * sizeof(char*))` → 4 pointeurs.

`memcpy(new_args+1, argv+2, 3 * sizeof(char*))` copie 3 pointeurs depuis `argv[2]` :

```
new_args[0] = "/bin/hello"   (affecté directement)
new_args[1] = "hop"           (copié depuis argv[2])
new_args[2] = "hello"         (copié depuis argv[3])
new_args[3] = NULL            (copié depuis argv[4])
```

> ℹ️ ℹnew_args[0] = "/bin/hello" est le nom du programme fictif transmis comme argv[0] à /bin/echo. /bin/echo n'utilise pas argv[0] pour afficher — il affiche argv[1], argv[2], etc.

### Question 2

> _Ce qui est affiché._

D'abord, le parent affiche `"Argument 1 : plop\n"`.

Après fork :

- **Enfant :** `execv("/bin/echo", new_args)` remplace le processus par /bin/echo avec argv = ["/bin/hello", "hop", "hello", NULL]. /bin/echo affiche ses arguments : **hop hello**. Le `printf("bar\n")` n'est jamais atteint.

- **Parent :** affiche `"foo\n"`, attend l'enfant, libère, affiche `"baz\n"`.

> ⚠️ ⚠L'ordre de "foo" et "hop hello" est une situation de compétition — le parent et l'enfant s'exécutent concurremment. La sortie finale est néanmoins : Argument 1 : plop, puis dans un ordre quelconque foo et hop hello, puis baz.

### Question 3

> _Si "/bin/echo" est remplacé par "a" ?_

`execv("a", new_args)` : `execv` n'utilise pas le PATH, il prend le chemin tel quel. "a" désigne un fichier nommé "a" dans le répertoire courant. Si le binaire compilé "a" s'y trouve, l'enfant devient une nouvelle instance de "a" avec argv = new_args. new_args[1..] = ["hop", "hello", NULL], et argc=3 (3 pointeurs avant NULL). On entre en récursion infinie : chaque exécution de "a" forke un enfant qui ré-exec "a"… **fork bomb**.

### Question 4

> _Avec execvp("a", new_args) ?_

`execvp` cherche dans le PATH si l'argument ne contient pas de `/`. "a" ne contient pas de slash → recherche dans les répertoires du PATH. Si le répertoire courant n'est pas dans le PATH (ce qui est le cas par défaut sur Linux pour des raisons de sécurité), `execvp` échoue. L'enfant affiche alors `"bar\n"` et appelle `exit(1)`.

## Exercice 2 — Forkbomb élaborée

### Question 1

> _Arbre et comptage pour ./encore (n=2, p=3)._

```
encore(n=2, p=3)  [racine, affiche Sortie 3]
 ├─fork─► enfant1 [FMT: n=2,p=3] → exec → encore(n=2, p=2) [affiche Sortie 3]
 │          ├─► enfant11 [FMT: n=2,p=2] → encore(n=2, p=1) [Sortie 3]
 │          │      ├─► [FMT: n=2,p=1] → encore(n=2,p=0) → Sortie 1
 │          │      └─► [FMT: n=2,p=1] → encore(n=2,p=0) → Sortie 1
 │          └─► enfant12 [FMT: n=2,p=2] → encore(n=2, p=1) [Sortie 3]
 │                 ├─► [FMT: n=2,p=1] → encore(n=2,p=0) → Sortie 1
 │                 └─► [FMT: n=2,p=1] → encore(n=2,p=0) → Sortie 1
 └─fork─► enfant2 [FMT: n=2,p=3] → (idem enfant1, arbre symétrique)
```

| Sortie | Quand | Nombre |
| --- | --- | --- |
| Sortie 1 | processus avec p=0 | 8 (= 2³) |
| Sortie 2 | si execl échoue — ne se produit pas | 0 |
| Sortie 3 | processus avec p>0 après wait | 7 (= 1+2+4) |

Total processus : **15**.

### Question 2

> _Récurrence u(n,p) et formule générale._

Soit u(n,p) le nombre total de processus (y compris le processus de départ) avec arguments (n, p).

- u(n, 0) = 1 (p=0 → Sortie 1 immédiate, pas d'enfants)

- u(n, p) = 1 + n · u(n, p−1) pour p > 0

En développant : **u(n, p) = 1 + n + n² + … + nᵖ = (np+1 − 1) / (n − 1)** pour n ≠ 1.

| Sortie | Formule | Pour n=2, p=3 |
| --- | --- | --- |
| Sortie 1 | nᵖ | 8 |
| Sortie 2 | 0 (execl réussit) | 0 |
| Sortie 3 | (nᵖ − 1)/(n − 1) | 7 |
| Affichages FMT_PROC | u(n,p) − 1 | 14 |

---

<a id="td3"></a>

# TD 3 — Threads POSIX — void* et pointeurs

## Exercice 1 — Adapter f au prototype void* f(void*)

### Méthode 1 — Variables globales

```c
#include
int n, m, r;  /* variables globales */
void *f(void *arg);

int main(void) {
    printf("n : "); scanf("%d", &n);
    printf("m : "); scanf("%d", &m);
    f(NULL);
    printf("r = %d\n", r);
    return 0;
}
void *f(void *arg) {
    r = n * m - (n + m);
    return NULL;
}
```

### Méthode 2 — Tableau d'int + malloc

```c
#include
#include
void *f(void *arg);

int main(void) {
    int n, m;
    printf("n : "); scanf("%d", &n);
    printf("m : "); scanf("%d", &m);
    int args[2] = {n, m};
    int *res = f(args);
    printf("r = %d\n", *res);
    free(res);
    return 0;
}
void *f(void *arg) {
    int *args = (int *)arg;
    int a = args[0], b = args[1];
    int *result = malloc(sizeof(int));
    *result = a * b - (a + b);
    return result;
}
```

### Méthode 3 — Structure avec champs arg + résultat

```c
#include
struct args_result { int a, b, r; };
void *f(void *arg);

int main(void) {
    struct args_result ar;
    printf("n : "); scanf("%d", &ar.a);
    printf("m : "); scanf("%d", &ar.b);
    f(&ar);
    printf("r = %d\n", ar.r);
    return 0;
}
void *f(void *arg) {
    struct args_result *ar = (struct args_result *)arg;
    ar->r = ar->a * ar->b - (ar->a + ar->b);
    return NULL;
}
```

## Exercice 2 — Exemples de threads

### Cas 1

`pthread_join` attend la fin du thread f. **Sortie déterministe : "hop\nplop\n"**.

### Cas 2

> ⚠️ ⚠Pas de pthread_join. main peut terminer avant que le thread ne s'exécute. Comportement indéfini : peut afficher "plop" seulement, ou "hop" + "plop" dans un ordre quelconque.

### Cas 3

> ❌ ✗Le thread envoie SIGTERM au processus. Ce signal peut être reçu n'importe quand → terminaison imprévisible. Comportement non-déterministe (le processus peut être tué avant ou après l'affichage de "plop").

### Cas 4

> ✅ ✓Le thread écrit dans ch[256] (sur la pile de main, transmis par adresse). Après join, main affiche ch. Sortie : "hop\nplop\n". Correct.

### Cas 5

> ✅ ✓Le thread alloue sur le tas, retourne le pointeur. Main récupère via ret, affiche, libère. Sortie : "hop\nplop\n". Correct — pas de fuite mémoire.

### Cas 6

> ❌ ✗Comportement indéfini ! Le thread retourne un pointeur vers une variable locale ch[256]. À la fin du thread, sa pile est libérée. main essaie d'utiliser ce pointeur pendouillant (dangling pointer) → accès mémoire invalide.

## Exercice 3 — Paralléliser somme et produit

### Questions 1, 2 et 3

```c
#include
#include
#include
#define N 65536

/* 1. Type structuré pour passer le tableau à un thread */
struct tableau { unsigned *tab; size_t taille; };

/* 2a. Fonction thread pour la somme */
void *somme_tab_thread(void *arg) {
    struct tableau *t = (struct tableau *)arg;
    long unsigned *res = malloc(sizeof(long unsigned));
    *res = somme_tab(t->tab, t->taille);
    return res;
}
/* 2b. Fonction thread pour le produit */
void *produit_tab_thread(void *arg) {
    struct tableau *t = (struct tableau *)arg;
    long unsigned *res = malloc(sizeof(long unsigned));
    *res = produit_tab(t->tab, t->taille);
    return res;
}

/* 3. Nouveau main */
int main(void) {
    unsigned tab[N];
    remplir_tab(tab, 10);

    struct tableau t = { tab, 10 };
    pthread_t th_s, th_p;
    void *ret_s, *ret_p;

    pthread_create(&th_s, NULL, somme_tab_thread, &t);
    pthread_create(&th_p, NULL, produit_tab_thread, &t);

    pthread_join(th_s, &ret_s);
    pthread_join(th_p, &ret_p);

    printf("somme : %lu\n", *(long unsigned *)ret_s);
    printf("produit : %lu\n", *(long unsigned *)ret_p);

    free(ret_s); free(ret_p);
    return 0;
}
```

> ℹ️ ℹLes deux threads lisent le même tableau sans l'écrire → pas besoin de mutex. On libère les deux résultats alloués sur le tas pour éviter les fuites mémoire.

---

<a id="td4"></a>

# TD 4 — Sémaphores POSIX

## Exercice 1 — Exemples de sémaphores

### Cas 1 — X=0, Y=1

hop attend sem2 (=1 → passe), pose res=42, poste sem1 (→1). plop attend sem1 (bloqué jusqu'à ce que hop l'incrémente), imprime res=42, poste sem2. Puis hop attend sem2 (qui vient d'être posté → passe), res=93, poste sem1. plop prend sem1, imprime 93. **Sortie déterministe : "42\n93\n"**.

### Cas 2 — X=1, Y=1

> ⚠️ ⚠Situation de compétition. sem1=1 dès le départ : plop peut exécuter sem_wait(sem1) avant que hop n'ait affecté res=42. plop afficherait alors la valeur non-initialisée de res (0 ou indéterminée). Sortie non-déterministe.

### Cas 3 — X=0, Y=0

> ❌ ✗Interblocage (deadlock). hop bloque sur sem_wait(sem2)=0, plop bloque sur sem_wait(sem1)=0. Personne ne peut débloquer l'autre.

### Cas 4 — X=0, Y=2

hop peut exécuter ses deux sem_wait(sem2) de suite (Y=2) sans attendre plop. Résultat : hop peut finir les deux itérations avant que plop ne démarre. Dans ce cas plop lit res=93 deux fois. Comportement non-déterministe selon l'ordonnancement.

### Cas 5 — Incrémentation avec sem, X=1

sem sert de mutex (X=1). Chaque thread incrémente res 3 fois dans une section critique → 6 incrémentations atomiques. **res = 6 de façon déterministe.**

### Cas 6 — X=2

> ❌ ✗Compétition. sem=2 permet à 2 threads d'entrer simultanément. res++ n'est pas atomique → résultat non déterministe (entre 2 et 6).

### Cas 7 — X=0

> ❌ ✗Deadlock immédiat. Les deux threads bloquent dès leur premier sem_wait(sem1) car sem1=0.

## Exercice 2 — A, puis B

### Questions 1 à 5

Stratégie : chaque thread fait son boulot en parallèle, mais B attend un signal d'A avant d'imprimer.

```c
#include
#include
#include

sem_t sem_ab, sem_bc;

void boulot(int n) { for (int i=0; i**Q2 :** Sans join, main peut sortir et tuer tous les threads avant qu'ils n'affichent quoi que ce soit.
          **Q3 :** Sans sémaphore, l'ordre n'est pas garanti — l'ordonnanceur est libre.

## Exercice 3 — Interblocage

### Scénarios possibles

f1 attend sem[0] puis sem[1]. f2 attend sem[1] puis sem[0]. Tous deux initialisés à 1.

| Scénario | Résultat |
| --- | --- |
| f1 prend sem[0], f1 prend sem[1], f1 finit, f2 prend les deux | Pas de deadlock — f1 imprime les 2 lignes, puis f2 imprime les 2 lignes |
| f2 prend sem[1], f2 prend sem[0], f2 finit, f1 prend les deux | Pas de deadlock — f2 d'abord, f1 ensuite |
| f1 prend sem[0], f2 prend sem[1], f1 attend sem[1], f2 attend sem[0] | Deadlock ! Les deux se bloquent mutuellement. |

> ℹ️ ℹSolution classique : imposer un ordre global des ressources — toujours prendre les sémaphores dans le même ordre. Si f2 prenait aussi sem[0] avant sem[1], le deadlock serait impossible.

---

<a id="td5"></a>

# TD 5 — Coiffeur endormi, Oracle/Singe, Lecteurs/Écrivains

## Exercice 1 — Le coiffeur endormi (Dijkstra)

### Modélisation complète

```c
#include
#include
#include

#define NUM_CLIENTS 10
#define NUM_CHAISES 6

int num_chaises_vides = NUM_CHAISES;
sem_t client_dispo;    /* nombre de clients en attente */
sem_t coiffeur_dispo;  /* coiffeur prêt pour un client */
pthread_mutex_t mutex; /* protège num_chaises_vides */

void *coiffeur(void *arg) {
    for (;;) {
        sem_wait(&client_dispo);   /* dort si pas de client */
        sem_post(&coiffeur_dispo);  /* indique qu'il est prêt */
        coiffer();
    }
}

void *client(void *arg) {
    for (;;) {
        pthread_mutex_lock(&mutex);
        if (num_chaises_vides == 0) {
            pthread_mutex_unlock(&mutex);
            continue; /* part, reviendra plus tard */
        }
        num_chaises_vides--;  /* s'asseoit */
        pthread_mutex_unlock(&mutex);

        sem_post(&client_dispo);   /* réveille le coiffeur */
        sem_wait(&coiffeur_dispo);  /* attend d'être appelé */

        pthread_mutex_lock(&mutex);
        num_chaises_vides++;  /* libère la chaise */
        pthread_mutex_unlock(&mutex);

        bavarder_avec_le_coiffeur();
    }
}
```

> ℹ️ ℹRaisonnement : deux ressources = disponibilité d'un client (client_dispo) et disponibilité du coiffeur (coiffeur_dispo). La variable partagée num_chaises_vides est protégée par un mutex.

## Exercice 2 — L'oracle et le singe

### Question 1 — Que se passe-t-il si la solution est 3 ?

          Singe : propose 0 (t=0), 1 (t=2), 2 (t=4), 3 (t=6)… Oracle : vérifie proposal=0 de t=0 à t=7, mais à t=7 proposition vaut 3 (pas 0 !). Oracle lit proposition=3 et le vérifie de t=7 à t=14. **La solution est trouvée mais ce n'est pas celle testée à t=0, il y a une course.**

> ❌ ✗L'oracle peut rater des propositions ou en vérifier une qui a déjà changé — comportement erroné.

### Question 2 — Solution 1 : alternance stricte

```c
sem_t tour_singe;   /* init=1 : singe commence */
sem_t tour_oracle;  /* init=0 */

void *singe(void *arg) {
    while (!trouve) {
        sem_wait(&tour_singe);
        proposition = inventer_proposition();
        sem_post(&tour_oracle);
    }
    return NULL;
}
void *oracle(void *arg) {
    while (!trouve) {
        sem_wait(&tour_oracle);
        trouve = verifier_proposition(proposition);
        sem_post(&tour_singe);
    }
    printf("Solution : %d\n", proposition);
    return NULL;
}
```

**Inconvénient :** le singe attend que l'oracle vérifie avant d'inventer la prochaine proposition → pas de parallélisme, donc lent.

### Question 3 — Solution 2 : pipeline

```c
int prop_courante = -1, prochaine = -1;
sem_t prete;       /* init=0 : oracle attend une prop */
sem_t peut_inventer; /* init=1 : singe peut commencer */

void *singe(void *arg) {
    while (!trouve) {
        sem_wait(&peut_inventer);
        prochaine = inventer_proposition();
        sem_post(&prete);
    }
    return NULL;
}
void *oracle(void *arg) {
    while (!trouve) {
        sem_wait(&prete);
        prop_courante = prochaine;
        sem_post(&peut_inventer); /* singe peut inventer la suivante */
        trouve = verifier_proposition(prop_courante);
    }
    printf("Solution : %d\n", prop_courante);
    return NULL;
}
```

### Question 4 — Solution 3 : file d'attente

```c
file *f;
sem_t nb_elements;     /* init=0 : oracle attend */
pthread_mutex_t mutex; /* protège la file */

void *singe(void *arg) {
    while (!trouve) {
        int p = inventer_proposition();
        pthread_mutex_lock(&mutex);
        enfiler(f, p);
        pthread_mutex_unlock(&mutex);
        sem_post(&nb_elements);
    }
    return NULL;
}
void *oracle(void *arg) {
    while (!trouve) {
        sem_wait(&nb_elements);
        pthread_mutex_lock(&mutex);
        int p = defiler(f);
        pthread_mutex_unlock(&mutex);
        trouve = verifier_proposition(p);
        if (trouve) printf("Solution : %d\n", p);
    }
    return NULL;
}
```

## Exercice 3 — Lecteurs et écrivains

### Question 1a — 3 lecteurs à t=0,1,2 + 1 écrivain à t=1

```
t=0 : L1 entre. num_lect=0 → sem_wait(bib_est_vide) [=1→0]. num_lect=1. lire (fini à t=2)
t=1 : L2 entre. num_lect=1 (≠0, pas de wait). num_lect=2. lire (fini à t=3)
      E1 arrive. sem_wait(bib_est_vide) [=0 → BLOQUE]
t=2 : L3 entre. num_lect=2. num_lect=3. lire (fini à t=4)
      L1 fini : num_lect=2, pas de sem_post.
t=3 : L2 fini : num_lect=1
t=4 : L3 fini : num_lect=0 → sem_post(bib_est_vide) [→1]
      E1 débloqué → écrire (fini à t=9)
```

### Question 1b — 1 écrivain à t=0 + 2 lecteurs à t=1

```
t=0 : E1 : sem_wait(bib_est_vide) [=1→0]. écrire (fini à t=5)
t=1 : L1 : num_lect=0 → sem_wait(bib_est_vide) [=0 → BLOQUE]
      L2 : mutex occupé par L1 → BLOQUE
t=5 : E1 fini : sem_post(bib_est_vide) [→1]
      L1 débloqué : num_lect=1. L2 entre : num_lect=2.
      L1 et L2 lisent en parallèle (fini à t=7)
```

### Question 2 — Famine pour l'écrivain

L1 et L2 en boucle infinie : dès que L1 finit et decrement num_lect, L2 est encore en train de lire (num_lect ≥ 1). Dès que L2 finit, L1 est déjà en train de lire à nouveau. num_lect ne vaut jamais 0 assez longtemps pour que l'écrivain puisse prendre bib_est_vide. **L'écrivain est en famine.**

### Question 3 — Priorité aux écrivains

```c
sem_t file_attente; /* init=1 : bloque les nouveaux lecteurs quand un écrivain attend */

void *ecrivain(void *arg) {
    sem_wait(&file_attente);    /* bloque les nouveaux lecteurs */
    sem_wait(&bib_est_vide);    /* attend que les lecteurs en cours finissent */
    ecrire();
    sem_post(&bib_est_vide);
    sem_post(&file_attente);    /* libère les nouveaux lecteurs */
}

void *lecteur(void *arg) {
    sem_wait(&file_attente);   /* attend si un écrivain est en attente */
    pthread_mutex_lock(&update_num_lects_bib);
    if (num_lect_bib == 0) sem_wait(&bib_est_vide);
    ++num_lect_bib;
    pthread_mutex_unlock(&update_num_lects_bib);
    sem_post(&file_attente);   /* libère les autres lecteurs */
    lire();
    pthread_mutex_lock(&update_num_lects_bib);
    --num_lect_bib;
    if (num_lect_bib == 0) sem_post(&bib_est_vide);
    pthread_mutex_unlock(&update_num_lects_bib);
}
```

---

<a id="td6"></a>

# TD 6 — Appel système read, buffers

## Exercice 1 — Implémentations avec read

### 1. mon_getc

```c
#define EOF -1
int mon_getc(int fd) {
    unsigned char c;
    ssize_t n = read(fd, &c, 1);
    if (n == 0) return EOF;   /* fin de fichier */
    return (int)((unsigned char)c); /* valeur 0..255 */
}
```

**Pourquoi int et pas char ?** char peut être signé (plage -128..127). L'octet 0xFF (255 en unsigned) correspondrait à -1 en char signé — soit la valeur d'EOF. Impossible de distinguer un octet 0xFF d'une fin de fichier. Retourner un `int` permet de retourner 0..255 pour les caractères et -1 pour EOF.

### 2. mon_get_nonblank_c

```c
#include
int mon_get_nonblank_c(int fd) {
    int c;
    while ((c = mon_getc(fd)) != EOF && isspace(c))
        ;  /* sauter les blancs */
    return c;
}
```

### 3. mon_gets

```c
void mon_gets(int fd, char *buf) {
    int c;
    while ((c = mon_getc(fd)) != EOF && c != '\n')
        *buf++ = (char)c;
    *buf = '\0';
}
```

**Pourquoi gets est-elle interdite ?** Elle n'a aucune limite de taille : si la ligne est plus longue que le buffer, elle écrit au-delà → **dépassement de tampon**, faille de sécurité classique. C'est pour cela que la norme C11 l'a supprimée.

### 4. mon_fgets

```c
char *mon_fgets(int fd, char *buf, size_t size) {
    if (size == 0) return NULL;
    size_t i = 0;
    int c;
    while (i

### 5. lire_nat

```c
int lire_nat(int fd, unsigned *n) {
    int c = mon_get_nonblank_c(fd);
    if (c == EOF) return EOF;
    if (c  '9') return 0;
    *n = 0;
    while (c >= '0' && c  ⚠️ ⚠Petit problème : le dernier caractère lu (qui n'est pas un chiffre) a été consommé par mon_getc et ne peut pas être "re-mis" dans le flux. scanf résout ce problème avec ungetc. (Voir exercice 2 question 6.)

### 6. lire_nat_bin

```c
#include
int lire_nat_bin(int fd, unsigned *n) {
    unsigned char buf[4];
    ssize_t total = 0, r;
    while (total

## Exercice 2 — Tampon (buffer) pour la lecture

### Implémentation de getchar et ungetchar

```c
int getchar(void) {
    /* 1. Allouer le buffer si besoin */
    if (stdin->buffer == NULL) {
        stdin->buffer = malloc(stdin->bufsz);
        stdin->next_char = stdin->buffer;
        stdin->last_read_char = stdin->buffer - 1; /* buffer vide */
    }
    /* 2. Recharger si buffer épuisé */
    if (stdin->next_char > stdin->last_read_char) {
        if (stdin->eof) return EOF;
        ssize_t n = read(0, stdin->buffer, stdin->bufsz);
        if (n == 0) { stdin->eof = 1; return EOF; }
        stdin->next_char = stdin->buffer;
        stdin->last_read_char = stdin->buffer + n - 1;
    }
    /* 3. Retourner le prochain caractère */
    return (unsigned char)(*stdin->next_char++);
}

int ungetchar(int c) {
    if (stdin->next_char buffer) return -1; /* impossible */
    *(--stdin->next_char) = (char)c;
    return c;
}
```

**Q5 — Avantage :** au lieu d'un appel système read par caractère (très coûteux), on fait un seul read de 1024 octets. Le rapport d'appels système est divisé par ~1024. Les appels système sont bien plus lents que l'accès mémoire (transition user/kernel, changement de contexte).

**Q6 — lire_nat avec ungetchar :** après avoir lu le caractère non-chiffre terminateur, appeler `ungetchar(c)` pour le remettre dans le buffer → il sera disponible pour le prochain appel.

---

<a id="td7"></a>

# TD 7 — Tubes (pipe) et redirection (dup2)

## Exercice 1 — Comportements

### Cas 1 — Boucle while + write en boucle

L'enfant écrit "foo\n" et "bar\n" dans tube[1] puis ferme. Le parent lit en boucle jusqu'à EOF (retour de read = 0 après fermeture de tube[1]). **Sortie : "foo\nbar\n"** — correct.

### Cas 2 — Un seul read

Le parent fait un seul `read(tube[0], buff, 1024)`. Pour une petite quantité de données (8 octets), le kernel les fournit en général en un seul appel. **Sortie : "foo\nbar\n"** — correct en pratique, mais techniquement pas garanti.

### Cas 3 — Enfant ferme tube[1] avant d'écrire

> ❌ ✗L'enfant ferme tube[0] et tube[1], puis tente d'écrire sur fd tube[1] — qui est fermé. Le signal SIGPIPE est envoyé au processus (terminaison par défaut). WTERMSIG(stat) vaudra SIGPIPE. Le parent lit 0 octets, écrit 0 octets. Rien n'est affiché.

### Cas 4 — Parent ferme tube[0] au lieu de tube[1]

> ❌ ✗Bug : le parent ferme tube[0] (extrémité de lecture) puis tente de lire dessus → read retourne -1 (EBADF). write(1, buff, -1) avec n=-1 cast en size_t = très grande valeur → comportement indéfini. De plus, personne ne lit le pipe → l'enfant reçoit SIGPIPE quand il écrit.

### Cas 5 — dup2 stdout → pipe, scanf en boucle

Enfant : `dup2(tube[1], 1)` → stdout = pipe. Ferme tube[1]. printf "foo\n", "bar\n" vont dans le pipe (line-buffered). Ferme fd 1 → l'extrémité d'écriture du pipe est fermée.

Parent : `dup2(tube[0], 0)` → stdin = pipe. scanf lit "foo" puis "bar" (tokens séparés par espaces/newlines). Affiche "foo\n" et "bar\n". Puis fermeture → scanf retourne ≤0. Affiche "lol\n". **Sortie : "foo\nbar\nlol\n"**.

### Cas 6 — Enfant oublie de fermer tube[1] après dup2

> ⚠️ ⚠Enfant : dup2(tube[1], 1), ne ferme PAS tube[1]. Affiche "foo\n" et "bar\n". Ferme fd 1. Mais tube[1] (fd original) est encore ouvert ! Le pipe a encore une extrémité d'écriture ouverte. Parent attend EOF sur le pipe… qui n'arrive qu'après que l'enfant sleep(100) et finalement termine. Programme bloqué 100 secondes, puis "foo\n", "bar\n", "lol\n".

## Exercice 2 — Pipe + sort

### Solution complète

```c
#include
#include
#include
#include

extern char **environ;

int main(void) {
    int tube[2];
    pipe(tube);

    if (fork() == 0) {
        /* Enfant : lit depuis le pipe (stdin) et exec sort */
        close(tube[1]);
        dup2(tube[0], 0);
        close(tube[0]);
        execlp("sort", "sort", NULL);
        perror("execlp sort");
        return 1;
    }

    /* Parent : écrit l'environnement dans le pipe */
    close(tube[0]);
    for (char **p = environ; *p != NULL; p++) {
        write(tube[1], *p, strlen(*p));
        write(tube[1], "\n", 1);
    }
    close(tube[1]); /* signal EOF à sort */
    wait(NULL);
    return 0;
}
```

---

<a id="td8"></a>

# TD 8 — Opérations bit-à-bit et boutisme

## Exercice 1 — Opérations bit-à-bit sur uint32_t

### Toutes les réponses

```c
/* 1. m = n × 4 (décalage gauche de 2) */
uint32_t m = n > 1;
uint32_t r = n & 1;

/* 3. Division euclidienne par 16 (2^4) */
uint32_t q = n >> 4;
uint32_t r = n & 0xF;

/* 4. Octet de poids fort (bits 31-24) */
uint8_t oct = (uint8_t)(n >> 24);

/* 5. Deuxième octet le plus fort (bits 23-16) */
uint8_t oct = (uint8_t)((n >> 16) & 0xFF);

/* 6. Bit numéro 0 = bit de poids le plus fort (bit 31) */
uint8_t b = (uint8_t)((n >> 31) & 1);

/* 7. Afficher tous les bits du plus fort au plus faible */
for (int i = 31; i >= 0; i--)
    printf("%d", (n >> i) & 1);
printf("\n");

/* 8. Rotation : échanger les 2 octets hauts avec les 2 octets bas */
uint32_t rot = (n >> 16) | (n

## Exercice 2 — Fonctions de conversion boutisme

### Sur machine little-endian (x86)

```c
/* Inverser l'ordre des 4 octets */
uint32_t swap32(uint32_t x) {
    return ((x & 0xFF)       >  8) |
           ((x & 0xFF000000) >> 24);
}
/* Sur little-endian : machine = little-endian */
uint32_t machine_to_big32   (uint32_t n) { return swap32(n); }
uint32_t machine_to_little32(uint32_t n) { return n;         }
uint32_t big_to_machine32   (uint32_t n) { return swap32(n); }
uint32_t little_to_machine32(uint32_t n) { return n;         }
```

**Sur big-endian :** la machine est déjà en gros-boutiste, donc `machine_to_big32` et `big_to_machine32` retournent n tel quel ; c'est `machine_to_little32` et `little_to_machine32` qui appellent `swap32`.

> ℹ️ ℹEn pratique, on utilise les fonctions POSIX htonl, ntohl, htons, ntohs qui font exactement ce travail de manière portable.

---

<a id="td9"></a>

# TD 9 — Sérialisation, UDP, alignement mémoire

## Exercice 1 — Échanges UDP (CRIP)

### Questions 1, 2 et 3

**Q1 — Informations nécessaires à A :** adresse IP de B (ex : 192.168.1.10), port de B (ex : 9000), et un socket UDP côté A (port attribué automatiquement par l'OS).

**Q2 — Opérations dans l'ordre :**

| Serveur B | Client A |
| --- | --- |
| socket(AF_INET, SOCK_DGRAM, 0) | socket(AF_INET, SOCK_DGRAM, 0) |
| bind(fd, port=9000) | — |
| recvfrom(fd, buf, ..., &addr_A) → reçoit chaîne + adresse de A | sendto(fd, chaîne, ..., addr_B) |
| Convertit minuscules → majuscules | — |
| 3× { sendto(fd, résultat, ..., addr_A); sleep(1); } | 3× recvfrom(fd, buf, ...) |
| (boucle infinie : retour à recvfrom) | close(fd) |

**Q3 — Problème :** si des requêtes arrivent toutes les secondes mais le serveur met 3 secondes à répondre (3 envois), il est occupé et ne peut pas traiter les nouvelles requêtes. **Solution :** utiliser des threads ou des processus fils — chaque requête est traitée par un thread dédié pendant que le thread principal continue d'accepter des requêtes.

## Exercice 2 — Alignement et remplissage

### Question 1 — Représentation des variables sur la pile

Adresses : c=0x2f, n=0x28, d=0x27, s=0x24

| `…24` **s[0]** _s_ |

            …25s[1]s
            …26???padding
            …27dd
            …28n[0]n
            …29n[1]n
            …2an[2]n
            …2bn[3]n
            …2c???padding
            …2d???padding
            …2e???padding
            …2fcc

Octets perdus (remplissage) : 0x26 et 0x2c..0x2e → **4 octets de padding**.

### Question 2 — struct s1 et struct s2

**struct s1** : alignement dominant = uint32_t → 4 octets.

| Champ | Offset | Taille | Padding avant |
| --- | --- | --- | --- |
| char s[3] | 0 | 3 | 0 |
| (padding) | 3 | 1 | int16 aligné sur 2 → offset 4 |
| int16_t i | 4 | 2 | — |
| char d | 6 | 1 | — |
| (padding) | 7 | 1 | uint32 aligné sur 4 → offset 8 |
| uint32_t n | 8 | 4 | — |

**Taille totale : 12 octets** (12 est multiple de 4 ✓)

**struct s2** : alignement dominant = double/pointeur → 8 octets.

| Champ | Offset | Taille | Padding avant |
| --- | --- | --- | --- |
| char c | 0 | 1 | — |
| (padding) | 1 | 7 | double aligné sur 8 |
| double x | 8 | 8 | — |
| uint16_t k | 16 | 2 | — |
| (padding) | 18 | 6 | int* (8 octets) aligné sur 8 |
| int *p | 24 | 8 | — |
| char d | 32 | 1 | — |
| (padding) | 33 | 7 | struct alignée sur 8 |

**Taille totale : 40 octets**

## Exercice 3 — Sérialisation de struct film

### Questions 1 à 5

**Q1 :** `int` et `short` ont des tailles dépendant du compilateur et de la plateforme (int peut être 16 ou 32 bits). `uint32_t` et `uint16_t` garantissent une taille précise, essentielle pour l'interopérabilité réseau.

**Q2 — Remplissage de struct film :**

- nom[61] à l'offset 0 → 61 octets

- padding 3 octets (uint32_t aligne sur 4, offset 61 → pad → offset 64)

- duree à l'offset 64 → 4 octets (offset 68)

- annee à l'offset 68 → 2 octets (68 % 2 = 0 ✓)

- padding 2 octets (struct aligne sur 4 : 70 % 4 = 2)

- **Total : 72 octets**

**Q3 — Problème avec sendto(&f, sizeof(struct film)) :**

- Les octets de padding contiennent des données indéterminées de la pile → fuite d'information, résultat non reproductible.

- Si client et serveur ont des boutismes différents, uint32_t et uint16_t sont mal interprétés.

**Q4 — Fonctions htonfilm/ntohfilm :**

```c
#include
#include   /* htonl, htons, ntohl, ntohs */

#define FILM_MSG_SIZE (61 + 4 + 2)  /* 67 octets sans padding */

void htonfilm(const struct film *src, uint8_t *dest) {
    memcpy(dest, src->nom, 61);       dest += 61;
    uint32_t d = htonl(src->duree);
    memcpy(dest, &d, 4);               dest += 4;
    uint16_t a = htons(src->annee);
    memcpy(dest, &a, 2);
}

void ntohfilm(const uint8_t *src, struct film *dest) {
    memcpy(dest->nom, src, 61);       src += 61;
    uint32_t d; memcpy(&d, src, 4);   src += 4;
    dest->duree = ntohl(d);
    uint16_t a; memcpy(&a, src, 2);
    dest->annee = ntohs(a);
}
```

**Q5 — Titre de longueur variable :** remplacer `char nom[61]` par `char *nom` (ou allouer dynamiquement). Dans le message sérialisé, ajouter 2 octets de longueur avant les caractères du titre (sans délimiteur) :

```c
/* Format du message : [uint16_t len_titre][titre sans \0][uint32_t duree][uint16_t annee] */
void htonfilm_v2(const struct film *src, uint8_t *dest) {
    uint16_t len = (uint16_t)strlen(src->nom);
    uint16_t len_be = htons(len);
    memcpy(dest, &len_be, 2);  dest += 2;
    memcpy(dest, src->nom, len); dest += len;
    uint32_t d = htonl(src->duree);
    memcpy(dest, &d, 4);         dest += 4;
    uint16_t a = htons(src->annee);
    memcpy(dest, &a, 2);
}
```

En UDP, chaque datagramme est reçu en entier → la longueur du titre est déductible de la taille du datagramme. Le champ de longueur n'est donc **pas strictement nécessaire** en UDP, mais il est bonne pratique de l'inclure.

---

<a id="td10"></a>

# TD 10 — TCP — Clients, serveurs et protocoles

## Exercice 1 — exact_read et stratégies de protocoles

### Question 1 — exact_read

```c
/* Lire exactement nbytes octets ou jusqu'à la fin du fichier.
 * Retourne le nombre d'octets lus, ou -1 en cas d'erreur. */
ssize_t exact_read(int fd, void *buf, size_t nbytes) {
    size_t total = 0;
    ssize_t n;
    while (total

### Question 2 — Applicabilité

| Cas | Adapté ? | Raison / Protocole possible |
| --- | --- | --- |
| 10 lettres → mot le plus long | Partiellement | Requête fixe = 10 octets. Réponse variable (longueur du mot inconnue). Mieux : envoyer d'abord un uint16 de longueur, puis le mot. |
| Jeu d'échecs | Oui | Un coup peut être encodé sur 4 octets (case source + case dest + promotion). Chaque message fait exactement 4 octets. |
| Numéro étudiant → prénom + nom | Oui (avec taille fixe) | Réponse = 64 octets pour prénom + 64 octets pour nom. Ou envoyer deux longueurs + les chaînes. |
| Nom de fichier → contenu | Non direct | La taille du fichier est inconnue. Solution : serveur envoie d'abord uint64_t (taille), client appelle exact_read(fd, buf, taille). |

## Exercice 2 — Protocole de transfert de fichier

### Questions 1 à 3

**Q1 — Étapes de connexion TCP :**

- Serveur : `socket → bind → listen → accept` (bloque jusqu'à une connexion)

- Client : `socket → connect` (déclenche le handshake SYN/SYN-ACK/ACK)

- Échange de données → `close`

**Q2a — Format de la requête (délimité par '\n') :**

```c
/* Serveur : lire le nom de fichier jusqu'au '\n' */
char filename[256];
size_t i = 0;
char c;
while (i  0)
    write(1, buf, n);
```

**Q2b-ii — Stocker dans la RAM :**

```c
char *data = NULL; size_t total = 0;
char buf[4096]; ssize_t n;
while ((n = read(fd, buf, sizeof(buf))) > 0) {
    data = realloc(data, total + n);
    memcpy(data + total, buf, n);
    total += n;
}
/* utiliser data (total octets) puis : */
free(data);
```

**Q3 — Protocole avec en-tête de statut :**

```c
/* En-tête fixe (5 octets) :
 *   [1 octet] status : 0=OK, 1=not found, 2=forbidden
 *   [4 octets] taille du fichier (big-endian, 0 si status != 0)
 */
#define STATUS_OK         0
#define STATUS_NOT_FOUND  1
#define STATUS_FORBIDDEN  2

/* Serveur : envoyer l'en-tête */
uint8_t header[5];
header[0] = status;
uint32_t size_be = htonl(file_size);
memcpy(header + 1, &size_be, 4);
write(fd_client, header, 5);

/* Client : lire l'en-tête puis le fichier */
uint8_t header[5];
exact_read(fd, header, 5);
uint8_t status = header[0];
uint32_t size_be; memcpy(&size_be, header + 1, 4);
uint32_t file_size = ntohl(size_be);
if (status == STATUS_OK)
    /* lire file_size octets avec exact_read */;
```

## Exercice 3 — Exemple de poll

### Questions 1, 2 et 3

**Q1 — Que fait ce programme ?**
          Il crée un processus enfant exécutant `tr a-z A-Z` (conversion minuscules→majuscules). Le parent relaie ce que l'utilisateur tape vers `tr` via tube1, et relaie la sortie de `tr` vers son propre stdout via tube2. C'est un proxy bidirectionnel. `poll` permet d'attendre _simultanément_ que stdin ou tube2 soit prêt, sans bloquer sur l'un en ignorant l'autre.

**Q2 — Problème de buffering résolu par stdbuf :**
          Quand stdout d'un processus est connecté à un pipe (pas à un terminal), la libc passe en mode _full-buffered_. `tr` n'enverrait ses résultats qu'une fois son buffer plein (4096 octets typiquement). `stdbuf -oL` force le mode _line-buffered_ : chaque ligne est envoyée dès qu'elle est produite.

**Q3 — Terminer proprement sur Ctrl-D :**

```c
for (;;) {
    if (poll(fds, 2, -1) ℹQuand l'utilisateur tape Ctrl-D, `read(0,...)` retourne 0 (EOF). On ferme alors l'entrée de `tr` (tube1[1]). `tr` reçoit EOF, imprime ce qui reste dans son buffer et termine. POLLHUP se déclenche sur tube2[0] → on sort de la boucle.

---
