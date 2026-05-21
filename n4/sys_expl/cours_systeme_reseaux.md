# Cours Complet — Système & Réseaux
> **L2 Informatique — Université Sorbonne Paris Nord (Institut Galilée)**
> Pierre Rousselin · 2025-2026

---

## Table des matières

1. [Rappels C essentiels](#1-rappels-c-essentiels)
2. [Le noyau et les processus](#2-le-noyau-et-les-processus)
3. [exit, wait, exec, signaux et zombies](#3-exit-wait-exec-signaux-et-zombies)
4. [Threads, void\* et pointeurs de fonctions](#4-threads-void-et-pointeurs-de-fonctions)
5. [Race conditions, atomicité et sémaphores](#5-race-conditions-atomicité-et-sémaphores)
6. [Mutex, deadlock et problèmes classiques](#6-mutex-deadlock-et-problèmes-classiques)
7. [Entrées-Sorties bas niveau Unix](#7-entrées-sorties-bas-niveau-unix)
8. [stdio.h, bufferisation et tubes (pipes)](#8-stdioh-bufferisation-et-tubes-pipes)
9. [Réseaux, ports, UDP et sockets](#9-réseaux-ports-udp-et-sockets)
10. [Sérialisation, TCP et poll](#10-sérialisation-tcp-et-poll)
11. [DNS, IPv6 et getaddrinfo](#11-dns-ipv6-et-getaddrinfo)
12. [Récapitulatif et pièges aux partiels](#12-récapitulatif-et-pièges-aux-partiels)

---

## 1. Rappels C essentiels

### 1.1 Compilation

```bash
gcc -Wall -Wextra -g -std=c99 -o mon_prog mon_prog.c
# Pour les threads :
gcc -Wall -Wextra -g -pthread -o mon_prog mon_prog.c
```

| Drapeau | Rôle |
|---------|------|
| `-Wall` | Active la majorité des warnings utiles |
| `-Wextra` | Warnings supplémentaires |
| `-g` | Infos de débogage (GDB, Valgrind) |
| `-pthread` | Indispensable pour POSIX threads |
| `-std=c99` | Standard C99 (types `uint32_t` etc.) |

### 1.2 Types entiers garantis

Ne jamais utiliser `int` quand la taille compte (réseau, fichiers binaires). Utiliser `<stdint.h>` :

```c
#include <stdint.h>
uint8_t   // non signé, exactement 8 bits
uint16_t  // non signé, exactement 16 bits
uint32_t  // non signé, exactement 32 bits
int32_t   // signé,     exactement 32 bits
```

### 1.3 Pointeurs — rappels indispensables

```c
int i = 42;
int *p;       // p est un pointeur vers un int

p = &i;       // & = "adresse de"
*p = 100;     // * = déréférencement (accède à la valeur pointée)
              // maintenant i vaut 100

// Passage "par référence" (simulation)
void increment(int *n) { (*n)++; }
increment(&i);  // i vaut 101
```

**Avec les structures :**
```c
struct point { int x; int y; };
struct point p = {3, 4};
struct point *ptr = &p;

ptr->x = 10;   // équivaut à (*ptr).x = 10
```

### 1.4 Gestion des erreurs systèmes

Presque tous les appels système retournent **-1** en cas d'erreur, et renseignent la variable globale `errno`.

```c
int fd = open("fichier.txt", O_RDONLY);
if (fd == -1) {
    perror("open");   // affiche "open: No such file or directory"
    exit(1);
}
```

> **Réflexe OBLIGATOIRE** : tester le retour de TOUS les appels système. Jamais d'exception.

### 1.5 Boutisme (endianness)

Les processeurs x86/x86-64 sont **little-endian** : l'octet de **poids faible** est stocké en premier. Les protocoles réseau utilisent le **big-endian** (octet de poids fort en premier).

```
Valeur 0x01020304 stockée en mémoire :
  Little-endian (x86) : 04 03 02 01  ← vers les adresses croissantes
  Big-endian (réseau) : 01 02 03 04
```

Fonctions de conversion (POSIX) :
```c
#include <arpa/inet.h>
uint16_t htons(uint16_t x);  // host to network short (16 bits)
uint32_t htonl(uint32_t x);  // host to network long  (32 bits)
uint16_t ntohs(uint16_t x);  // network to host short
uint32_t ntohl(uint32_t x);  // network to host long
```

### 1.6 Opérations bit-à-bit

```c
uint32_t n = 0b10110100;

n >> k       // décalage droit de k (= division par 2^k)
n << k       // décalage gauche de k (= multiplication par 2^k)
n & 0xFF     // masque : garde seulement les 8 bits de poids faible
n | (1 << k) // met le bit k à 1
n ^ (1 << k) // inverse le bit k
(n >> k) & 1 // valeur du bit k (0 ou 1)

// Extraire l'octet de poids fort d'un uint32_t :
uint8_t octet_fort = (uint8_t)(n >> 24);

// Rotation gauche de 16 bits (échanger les 2 octets hauts et bas) :
uint32_t rot = (n >> 16) | (n << 16);

// Inverser les 4 octets (swap32, utile pour changer d'endianness) :
uint32_t swap32(uint32_t x) {
    return ((x & 0xFF)       << 24) |
           ((x & 0xFF00)     <<  8) |
           ((x & 0xFF0000)   >>  8) |
           ((x & 0xFF000000) >> 24);
}
```

---

## 2. Le noyau et les processus

### 2.1 Rôle du noyau (kernel)

Le **noyau** est le programme central du système d'exploitation, chargé en mémoire au démarrage. Il a **le monopole d'accès au matériel** (CPU, RAM, disque, réseau...).

Il offre deux abstractions fondamentales sous Unix :

| Abstraction | Description |
|-------------|-------------|
| **Le processus** | Un programme en cours d'exécution — entité dynamique qui naît, tourne et meurt. |
| **Le fichier** | Tout ce dans quoi on peut lire/écrire : fichier normal, terminal, socket réseau, tube... |

### 2.2 Les appels système

Un **appel système** est une requête d'un processus vers le noyau. Il entraîne un passage temporaire en **mode privilégié** (mode noyau), puis retour au programme.

| Appel système | Rôle |
|--------------|------|
| `fork()` | Créer un processus fils (clone du courant) |
| `exit(n)` | Terminer avec le statut n |
| `wait()` / `waitpid()` | Attendre la fin d'un fils |
| `execve()` / famille exec | Remplacer l'image par un nouveau programme |
| `open()` / `close()` | Ouvrir / fermer un fichier |
| `read()` / `write()` | Lire / écrire |
| `kill(pid, sig)` | Envoyer un signal |

### 2.3 Qu'est-ce qu'un processus ?

Un **programme** = fichier exécutable inerte sur disque.  
Un **processus** = instance d'un programme en cours d'exécution dans la RAM.

Chaque processus possède :
- Un **PID** (Process Identifier) : entier unique > 0
- Son propre **espace mémoire** virtuel (isolé des autres)
- Un **état** (Running, Sleeping, Zombie...)
- Des fichiers ouverts (dont `stdin` fd=0, `stdout` fd=1, `stderr` fd=2)
- Un processus **parent** (PPID)

| État | Lettre | Signification |
|------|--------|---------------|
| Running | `R` | En exécution ou en attente de CPU |
| Sleeping | `S` | En attente d'un événement |
| Stopped | `T` | Mis en pause (Ctrl+Z) |
| Zombie | `Z` | Terminé mais le père n'a pas récupéré son statut |

### 2.4 fork() — créer un processus fils

`fork()` crée un fils **clone quasi-identique** du père. La seule différence : la valeur de retour de `fork()`.

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    pid_t pid = fork();

    switch (pid) {
        case -1:   // fork a échoué
            perror("fork");
            return 1;

        case 0:    // On est dans le FILS — fork retourne 0
            printf("Fils : mon PID = %d, PID de mon père = %d\n",
                   getpid(), getppid());
            return 0;

        default:   // On est dans le PÈRE — fork retourne le PID du fils
            printf("Père : PID du fils = %d\n", pid);
            return 0;
    }
}
```

> **Règle d'or** : `fork()` retourne **0 dans le fils**, le **PID du fils dans le père**, et **-1 en cas d'erreur**. Toujours traiter les 3 cas.

**Ce qui est partagé / copié après un fork :**

| Élément | Partagé ou copié ? |
|---------|-------------------|
| Code (segment texte) | Partagé (read-only) |
| Variables, pile, tas | **Copié** (Copy-on-Write) |
| Descripteurs de fichiers | Copiés (pointent vers les mêmes fichiers ouverts) |
| PID | Différent (fils reçoit un nouveau PID) |

### 2.5 L'ordonnanceur (scheduler)

Le noyau partage le(s) processeur(s) entre tous les processus actifs par un algorithme **round-robin** : chaque processus reçoit une tranche de temps CPU, puis retourne en file d'attente. L'**ordre d'exécution est non déterministe** (sauf synchronisation explicite).

---

## 3. exit, wait, exec, signaux et zombies

### 3.1 La mort d'un processus

Un processus peut mourir :
- **Normalement** : `return n` depuis `main`, ou `exit(n)` depuis n'importe où
- **Par signal** : `SIGTERM` (tuer poliment), `SIGKILL` (force brute, impossible à ignorer), `SIGPIPE` (écriture sur pipe fermé)...

La valeur `n` passée à `exit()` est le **statut de sortie** : `0` = succès, valeur positive = erreur.

### 3.2 Zombies et wait()

Quand un fils se termine, il reste en état **zombie** jusqu'à ce que son père récupère son statut de sortie avec `wait()` ou `waitpid()`. Si le père ne fait jamais `wait()`, le zombie persiste jusqu'à la mort du père.

```c
#include <sys/wait.h>

pid_t pid = fork();
if (pid == 0) {
    // code du fils
    exit(42);
} else {
    int status;
    pid_t enfant = wait(&status);  // attend N'IMPORTE QUEL fils

    if (WIFEXITED(status)) {
        printf("Fils %d terminé, code = %d\n",
               enfant, WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("Fils tué par le signal %d\n", WTERMSIG(status));
    }
}
```

**`waitpid()`** — attendre un fils spécifique :
```c
waitpid(pid_fils, &status, 0);  // attend ce fils précis

// Boucle pour attendre TOUS les fils :
pid_t p;
int status;
while ((p = wait(&status)) != -1)
    printf("Fils %d terminé\n", p);
```

### 3.3 Les signaux

Un **signal** est une notification asynchrone envoyée à un processus.

```c
#include <signal.h>

kill(pid, SIGTERM);   // demander poliment à un processus de s'arrêter
kill(pid, SIGKILL);   // forcer l'arrêt (ne peut pas être ignoré)
kill(pid, SIGKILL);   // auto-suicide : kill(getpid(), SIGKILL)
```

Signaux importants :

| Signal | Valeur | Action par défaut | Description |
|--------|--------|-------------------|-------------|
| `SIGTERM` | 15 | Terminer | Terminaison propre demandée |
| `SIGKILL` | 9 | Terminer | Force brute, impossible à capturer |
| `SIGPIPE` | 13 | Terminer | Écriture sur un pipe sans lecteur |
| `SIGCHLD` | 17 | Ignorer | Un fils vient de changer d'état |
| `SIGINT` | 2 | Terminer | Ctrl+C |
| `SIGSTOP` | 19 | Stopper | Mettre en pause |

### 3.4 La famille exec — remplacer un programme

`exec` remplace l'image mémoire du processus courant par un nouveau programme. Le **PID reste identique**. Si `exec` réussit, le code suivant ne s'exécute **jamais**.

```c
// execlp : cherche dans le PATH, arguments en liste
execlp("ls", "ls", "-l", "/tmp", NULL);  // ← NULL obligatoire à la fin !

// execvp : cherche dans le PATH, arguments en tableau
char *args[] = {"ls", "-l", "/tmp", NULL};
execvp("ls", args);

// execv : chemin absolu, pas de recherche dans PATH
char *args[] = {"/bin/ls", "-l", NULL};
execv("/bin/ls", args);

// Motif classique fork + exec :
if (fork() == 0) {
    execlp("ls", "ls", "-l", NULL);
    perror("execlp");  // exécuté seulement si exec a échoué
    exit(1);
}
wait(NULL);
```

> **Convention** : le premier argument de `execlp`/`execvp` est le nom du programme (dans PATH), le second est `argv[0]` (souvent identique), puis viennent les vrais arguments, puis `NULL`.

---

## 4. Threads, void\* et pointeurs de fonctions

### 4.1 Processus vs Threads

| | Processus | Thread |
|---|-----------|--------|
| Mémoire | Espace isolé (fork = copie) | **Mémoire partagée** |
| Communication | IPC (tubes, sockets) | Variables globales directes |
| Coût de création | Élevé | Faible |
| Isolation | Forte | Faible (bug = crashe tout) |

Les threads permettent d'exploiter le **parallélisme multi-cœur** et de partager facilement des données.

### 4.2 Créer et rejoindre un thread

```c
#include <pthread.h>

// Signature obligatoire : void* fonction(void *arg)
void *ma_fonction(void *arg) {
    int *n = (int *)arg;  // cast du void*
    printf("Thread reçoit : %d\n", *n);
    return NULL;  // ou retourner une valeur récupérée par pthread_join
}

int main(void) {
    pthread_t th;
    int valeur = 42;

    // Créer le thread
    if (pthread_create(&th, NULL, ma_fonction, &valeur) != 0) {
        perror("pthread_create");
        return 1;
    }

    // Attendre la fin du thread (comme wait() pour les processus)
    void *retour;
    pthread_join(th, &retour);

    return 0;
}
```

**Créer N threads :**
```c
pthread_t threads[N];
struct mon_arg args[N];  // UN struct DISTINCT par thread (jamais partager)

for (int i = 0; i < N; i++) {
    args[i].id = i;
    args[i].data = ...;
    pthread_create(&threads[i], NULL, fonction, &args[i]);
}
for (int i = 0; i < N; i++)
    pthread_join(threads[i], NULL);
```

> **Piège classique** : allouer un struct distinct par thread. Réutiliser la même variable en boucle entraîne une **race condition** sur l'argument.

### 4.3 Le type void\*

`void *` = « pointeur vers n'importe quoi ». Il permet à `pthread_create` d'accepter n'importe quel type d'argument.

```c
void *p;

// On peut assigner sans cast :
int i = 5;
p = &i;          // OK

// On doit caster avant de déréférencer :
int *q = (int *)p;
printf("%d\n", *q);  // OK
```

### 4.4 Pointeurs de fonctions

En C, une fonction a une adresse en mémoire. Un **pointeur de fonction** stocke cette adresse.

```c
// Déclaration : type (*nom)(paramètres)
int (*f)(int);        // pointeur vers une fonction int → int
void *(*g)(void *);   // pointeur vers une fonction void* → void* (= pthread)

int triple(int n) { return n * 3; }
int double_it(int n) { return n * 2; }

f = triple;      // affecter
printf("%d\n", f(5));   // appeler via le pointeur → 15

f = double_it;
printf("%d\n", f(5));   // → 10
```

C'est pour ça que `pthread_create` a cette signature :
```c
int pthread_create(pthread_t *thread,
                   const pthread_attr_t *attr,
                   void *(*start_routine)(void *),  // ← pointeur de fonction
                   void *arg);
```

Et `qsort` :
```c
void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *));
```

---

## 5. Race conditions, atomicité et sémaphores

### 5.1 Le problème de l'indéterminisme

Plusieurs threads accèdent à la même mémoire → le résultat dépend de l'ordre d'exécution → **indéterminisme**. On parle de **race condition** (situation de compétition).

**Exemple du million :**
```c
int compteur = 0;
// 1000 threads font chacun : for (int i=0; i<1000; i++) compteur++;
// Résultat attendu : 1 000 000
// Résultat réel : souvent moins, par exemple 843 217
```

**Pourquoi ?** `compteur++` se décompose en 3 instructions assembleur :
```
LOAD  reg, compteur   // lire la valeur
ADD   reg, 1          // incrémenter
STORE compteur, reg   // réécrire
```
Si deux threads font `LOAD` avec la même valeur, l'un écrase le résultat de l'autre.

### 5.2 Atomicité

Une opération est **atomique** si elle se passe « tout d'un coup » — aucun autre thread ne peut s'insérer au milieu. `i++` en C **n'est PAS atomique** sur la plupart des architectures.

### 5.3 Attente active — à ÉVITER

```c
// Mauvais ! Consomme du CPU pour rien
int alice_a_fini = 0;
while (!alice_a_fini)
    ;  // tourner en rond

// Préférer : appel système bloquant (le thread dort vraiment)
```

### 5.4 Les sémaphores POSIX

Un **sémaphore** est un compteur entier avec deux opérations **atomiques** :

| Opération | Effet |
|-----------|-------|
| `sem_wait(&s)` | Décrémente. Si le compteur est à **0**, le thread **dort** jusqu'à ce qu'il repasse > 0 |
| `sem_post(&s)` | Incrémente. **Réveille** un thread en attente s'il y en a un |

```c
#include <semaphore.h>

sem_t verrou;
int compteur = 0;

// Dans main :
sem_init(&verrou, 0, 1);  // init à 1 : "ressource disponible"
// 2ème arg = 0 : partagé entre threads (pas entre processus)

void *thread_func(void *arg) {
    sem_wait(&verrou);   // entrer en section critique
    ++compteur;          // opération protégée
    sem_post(&verrou);   // sortir
    return NULL;
}

// À la fin :
sem_destroy(&verrou);
```

**Sémaphore pour signaler un événement** (valeur initiale = 0) :
```c
sem_t pret;
sem_init(&pret, 0, 0);  // init à 0 : "pas encore prêt"

// Thread A fait son travail puis :
sem_post(&pret);         // "c'est prêt"

// Thread B attend :
sem_wait(&pret);         // bloque jusqu'à ce que A fasse sem_post
// maintenant B peut continuer
```

---

## 6. Mutex, deadlock et problèmes classiques

### 6.1 Section critique

> **Définition** : portion de code dans laquelle **un seul thread à la fois** peut se trouver (accès à une ressource partagée).

### 6.2 Les mutex

Un **mutex** (MUTual EXclusion) protège les sections critiques. Contrairement aux sémaphores, il est toujours verrouillé **et déverrouillé par le même thread**.

```c
#include <pthread.h>

pthread_mutex_t verrou;
int compteur = 0;

void *bosser(void *arg) {
    for (int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&verrou);    // verrouiller (bloquant)
        ++compteur;                     // section critique
        pthread_mutex_unlock(&verrou);  // déverrouiller
    }
    return NULL;
}

int main(void) {
    pthread_mutex_init(&verrou, NULL);
    // ... créer et joindre les threads ...
    printf("Résultat : %d\n", compteur);  // garantit 1 000 000
    pthread_mutex_destroy(&verrou);
}
```

| Appel | Rôle |
|-------|------|
| `pthread_mutex_init(&m, NULL)` | Initialiser (déverrouillé au départ) |
| `pthread_mutex_lock(&m)` | Verrouiller — **bloque** si déjà verrouillé |
| `pthread_mutex_unlock(&m)` | Déverrouiller |
| `pthread_mutex_destroy(&m)` | Libérer les ressources |

**Mutex vs Sémaphore :**
```
MUTEX                              SÉMAPHORE
───────────────────────────────────────────────────
lock/unlock par le MÊME thread     wait/post par des threads DIFFÉRENTS OK
Pour protéger une section critique Pour signaler un événement
Initialisé à "libre"               Initialisé à 0 (attendre) ou N (N ressources)
```

### 6.3 Le Deadlock (interblocage)

Un **deadlock** se produit quand deux threads (ou plus) s'attendent mutuellement **indéfiniment**.

```
Thread 1 : lock(A) ... attend lock(B)
Thread 2 : lock(B) ... attend lock(A)
           ↑_________________________↑
                    DEADLOCK !
```

**Le dîner des philosophes :** N philosophes, N fourchettes, chacun a besoin des 2 fourchettes adjacentes. Si chacun prend sa fourchette gauche simultanément → personne ne peut prendre sa fourchette droite → deadlock.

**Solutions :**
1. Toujours acquérir les ressources dans le **même ordre** (ex : toujours mutex_A avant mutex_B)
2. Utiliser un sémaphore « portier » qui limite le nombre de threads en section critique simultanément

### 6.4 Producteurs / Consommateurs

Schéma classique : threads *producteurs* créent des données dans un tampon, threads *consommateurs* les lisent.

```
3 primitives nécessaires :
- mutex          : accès exclusif au tampon
- sem_t vide     : nombre de places libres dans le tampon (init = TAILLE)
- sem_t plein    : nombre d'éléments disponibles (init = 0)

Producteur :                    Consommateur :
  sem_wait(&vide);                sem_wait(&plein);
  mutex_lock;                     mutex_lock;
  deposer(element);               element = prendre();
  mutex_unlock;                   mutex_unlock;
  sem_post(&plein);               sem_wait(&vide);  // non, sem_post(&vide)
```

### 6.5 Lecteurs / Écrivains

- Plusieurs lecteurs peuvent lire **simultanément**
- Un écrivain doit avoir un **accès exclusif** (personne d'autre)

```c
int num_lect = 0;
pthread_mutex_t mutex_lect;  // protège num_lect
sem_t bib_est_vide;          // init=1

void *lecteur(void *arg) {
    pthread_mutex_lock(&mutex_lect);
    if (num_lect == 0)
        sem_wait(&bib_est_vide);  // 1er lecteur bloque les écrivains
    ++num_lect;
    pthread_mutex_unlock(&mutex_lect);

    lire();  // lecture simultanée OK

    pthread_mutex_lock(&mutex_lect);
    --num_lect;
    if (num_lect == 0)
        sem_post(&bib_est_vide);  // dernier lecteur libère les écrivains
    pthread_mutex_unlock(&mutex_lect);
    return NULL;
}

void *ecrivain(void *arg) {
    sem_wait(&bib_est_vide);  // accès exclusif
    ecrire();
    sem_post(&bib_est_vide);
    return NULL;
}
```

> **Attention à la famine de l'écrivain !** Si des lecteurs arrivent sans cesse, l'écrivain peut ne jamais obtenir l'accès. Solution : ajouter un sémaphore `file_attente` qui bloque les nouveaux lecteurs quand un écrivain attend.

### 6.6 Garder les sections critiques courtes !

```c
// Mauvais : calcul lent dans la section critique
pthread_mutex_lock(&m);
double res = calcul_tres_long(x);  // ← bloque tout le monde
tableau[i] = res;
pthread_mutex_unlock(&m);

// Bon : seul l'accès à la variable partagée est protégé
double res = calcul_tres_long(x);  // ← en dehors du mutex
pthread_mutex_lock(&m);
tableau[i] = res;
pthread_mutex_unlock(&m);
```

---

## 7. Entrées-Sorties bas niveau Unix

### 7.1 Deux niveaux d'I/O

| Niveau | Fonctions | Caractéristiques |
|--------|-----------|-----------------|
| **Bas niveau (Unix)** | `open`, `read`, `write`, `close` | Sans tampon, spécifiques Unix |
| **Bibliothèque standard** | `fopen`, `fread`, `fprintf`, `fclose` | Avec tampon, portables |

### 7.2 Les descripteurs de fichiers

Quand on ouvre un fichier, le noyau attribue un **descripteur de fichier** (fd) : un entier > 0.

| fd | Nom | Correspond à |
|----|-----|-------------|
| 0 | `stdin` | Entrée standard (clavier) |
| 1 | `stdout` | Sortie standard (terminal) |
| 2 | `stderr` | Sortie d'erreur (terminal) |
| 3+ | — | Fichiers ouverts par le programme |

### 7.3 open()

```c
#include <fcntl.h>

// Lecture seule
int fd = open("fichier.txt", O_RDONLY);

// Écriture (crée le fichier si inexistant, le vide si existant)
int fd = open("sortie.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//                                                          ↑ permissions

if (fd == -1) { perror("open"); exit(1); }  // TOUJOURS tester
```

**Flags :**

| Flag | Signification |
|------|---------------|
| `O_RDONLY` | Lecture seule |
| `O_WRONLY` | Écriture seule |
| `O_RDWR` | Lecture et écriture |
| `O_CREAT` | Créer si inexistant |
| `O_TRUNC` | Vider si existant |
| `O_APPEND` | Écriture toujours à la fin |
| `O_EXCL` | Avec `O_CREAT` : échoue si le fichier existe déjà |

**Permissions (mode) :**
```
0644 → rw-r--r--  (lecture/écriture propriétaire, lecture autres)
0755 → rwxr-xr-x  (lecture/écriture/exécution propriétaire, lecture/exécution autres)
0600 → rw-------  (lecture/écriture propriétaire seulement)

Formule : r=4, w=2, x=1 → un chiffre par catégorie [propriétaire][groupe][autres]
```

### 7.4 read() et write()

```c
#include <unistd.h>

// Retourne : nb octets lus, 0 = fin de fichier, -1 = erreur
ssize_t n = read(fd, buf, count);

// Retourne : nb octets écrits, -1 = erreur
ssize_t n = write(fd, buf, count);
```

**Copie de fichier :**
```c
char buf[4096];
ssize_t n;
while ((n = read(fd_in, buf, sizeof(buf))) > 0) {
    write(fd_out, buf, n);
}
if (n == -1) { perror("read"); exit(1); }
```

> **Lectures partielles !** `read()` peut retourner moins d'octets que demandé (pipe, réseau). Toujours boucler pour lire exactement ce qu'on veut.

**`exact_read` — lire exactement N octets :**
```c
ssize_t exact_read(int fd, void *buf, size_t nbytes) {
    size_t total = 0;
    ssize_t n;
    while (total < nbytes) {
        n = read(fd, (char *)buf + total, nbytes - total);
        if (n <= 0) return (n == 0 && total > 0) ? (ssize_t)total : n;
        total += n;
    }
    return (ssize_t)total;
}
```

### 7.5 close()

```c
close(fd);  // libère le descripteur
```

**IMPORTANT** : après un `fork()`, le fils hérite de tous les descripteurs ouverts du père. Toujours fermer ceux qu'on n'utilise pas !

### 7.6 Implémentation de getchar avec read()

```c
// Pourquoi retourner int et pas char ?
// char signé: plage -128..127. L'octet 0xFF = -1 = valeur d'EOF → ambiguïté !
// int: peut représenter 0..255 pour les caractères, ET -1 pour EOF.
int mon_getc(int fd) {
    unsigned char c;
    ssize_t n = read(fd, &c, 1);
    if (n == 0) return EOF;
    if (n == -1) { perror("read"); exit(1); }
    return (int)c;
}
```

---

## 8. stdio.h, bufferisation et tubes (pipes)

### 8.1 stdio.h — la couche standard

Au lieu d'un `int` (descripteur), on manipule des **flux** (`FILE *`) avec un buffer interne.

```c
FILE *f = fopen("data.txt", "r");   // ouvrir
if (!f) { perror("fopen"); exit(1); }

// Lire caractère par caractère
int c;
while ((c = fgetc(f)) != EOF) { ... }

// Lire une ligne (recommandé : limite de taille)
char ligne[256];
fgets(ligne, sizeof(ligne), f);

// Écriture formatée
fprintf(f, "Valeur : %d\n", n);

fclose(f);  // fermer ET vider le buffer !
```

### 8.2 Les 3 types de bufferisation

| Type | Quand écrit-on vraiment ? | Exemple |
|------|--------------------------|---------|
| **Fully buffered** | Quand le buffer est plein, ou à la fermeture | Fichier normal |
| **Line buffered** | À chaque `\n`, ou buffer plein | `stdout` vers terminal |
| **Unbuffered** | Immédiatement | `stderr` |

**Piège :**
```c
printf("message");   // sans \n → peut ne pas s'afficher immédiatement !
fflush(stdout);      // forcer l'affichage
```

**Problème critique avec fork() :** si stdout est en mode full-buffered (redirection vers pipe), les données dans le buffer sont **dupliquées** lors du fork. Chaque processus flush son propre buffer → double affichage.

```c
// Solution avant fork si on utilise stdio :
fflush(stdout);
fork();
```

### 8.3 Les tubes (pipes)

Un **pipe** est un canal de communication inter-processus unidirectionnel et FIFO. Il est représenté par deux descripteurs.

```c
#include <unistd.h>

int tube[2];  // tube[0] = lecture, tube[1] = écriture

if (pipe(tube) == -1) { perror("pipe"); exit(1); }

switch (fork()) {
    case 0:  // FILS : écrit dans le tube
        close(tube[0]);                      // fermer le côté lecture (inutilisé)
        write(tube[1], "Bonjour", 7);
        close(tube[1]);
        exit(0);

    default:  // PÈRE : lit depuis le tube
        close(tube[1]);                      // fermer le côté écriture (inutilisé)
        char buf[64];
        ssize_t n = read(tube[0], buf, sizeof(buf));
        write(1, buf, n);
        close(tube[0]);
        wait(NULL);
}
```

> **Règle des pipes** : chaque processus ferme les extrémités qu'il n'utilise pas. Si l'extrémité d'écriture reste ouverte quelque part, le lecteur n'obtiendra **jamais** EOF !

### 8.4 dup2() — rediriger les descripteurs

`dup2(ancien_fd, nouveau_fd)` : fait pointer `nouveau_fd` vers le même fichier que `ancien_fd`.

```c
// Rediriger stdout vers le pipe (côté écriture)
dup2(tube[1], 1);
close(tube[1]);   // fermer l'original après duplication

// Rediriger stdin depuis le pipe (côté lecture)
dup2(tube[0], 0);
close(tube[0]);

// Maintenant : printf() va dans le pipe, scanf() lit depuis le pipe
```

**Schéma `commande1 | commande2` (ce que fait le shell) :**
```c
int tube[2];
pipe(tube);

if (fork() == 0) {           // commande1
    close(tube[0]);
    dup2(tube[1], 1);        // stdout → tube
    close(tube[1]);
    execlp("ls", "ls", NULL);
}
if (fork() == 0) {           // commande2
    close(tube[1]);
    dup2(tube[0], 0);        // stdin ← tube
    close(tube[0]);
    execlp("sort", "sort", NULL);
}
close(tube[0]); close(tube[1]);
wait(NULL); wait(NULL);
```

---

## 9. Réseaux, ports, UDP et sockets

### 9.1 Le modèle en couches (simplifié)

```
┌───────────────────────────────────┐
│         APPLICATION               │  HTTP, SSH, DNS, SMTP...
├───────────────────────────────────┤
│         TRANSPORT                 │  TCP, UDP — identification par PORT
├───────────────────────────────────┤
│         RÉSEAU                    │  IP — identification par ADRESSE IP
├───────────────────────────────────┤
│         LIAISON / PHYSIQUE        │  Ethernet (adresses MAC), Wi-Fi...
└───────────────────────────────────┘
```

### 9.2 Adresses IP et ports

- **Adresse IP** : identifie une **machine** sur le réseau (IPv4 : 32 bits, ex : `192.168.1.42`)
- **Port** : identifie un **processus** sur cette machine (entier 16 bits, 0–65535)

Ports réservés (0–1023, root seulement) :

| Port | Service |
|------|---------|
| 22 | SSH |
| 53 | DNS |
| 80 | HTTP |
| 443 | HTTPS |

Un **port éphémère** (>1024) est choisi automatiquement pour le client.

### 9.3 UDP vs TCP

| | **UDP** | **TCP** |
|---|---------|---------|
| Connexion | Non (sans connexion) | Oui (handshake SYN/SYN-ACK/ACK) |
| Données | **Datagrammes** (avec bords, atomiques) | **Flux** (sans bords) |
| Fiabilité | Aucune garantie | Garantie, ordre préservé |
| Poids | Léger, rapide | Plus lourd |
| Utilisé pour | DNS, streaming, jeux | HTTP, SSH, FTP |

### 9.4 Sockets UDP (SOCK_DGRAM)

```c
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Créer une socket UDP
int sock = socket(AF_INET, SOCK_DGRAM, 0);
if (sock == -1) { perror("socket"); exit(1); }

// Adresse du serveur
struct sockaddr_in srv;
memset(&srv, 0, sizeof(srv));
srv.sin_family = AF_INET;
srv.sin_port   = htons(30000);              // port en big-endian
inet_pton(AF_INET, "192.168.1.10", &srv.sin_addr);

// Envoyer un datagramme (côté client)
sendto(sock, "Bonjour", 7, 0,
       (struct sockaddr *)&srv, sizeof(srv));

// Recevoir un datagramme (côté serveur, après bind)
char buf[512];
struct sockaddr_in client;
socklen_t len = sizeof(client);
ssize_t n = recvfrom(sock, buf, sizeof(buf), 0,
                     (struct sockaddr *)&client, &len);
// client contient maintenant l'adresse de l'expéditeur
```

**bind() côté serveur :**
```c
struct sockaddr_in addr;
memset(&addr, 0, sizeof(addr));
addr.sin_family      = AF_INET;
addr.sin_port        = htons(30000);
addr.sin_addr.s_addr = INADDR_ANY;  // écouter sur toutes les interfaces

if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("bind"); exit(1);
}
```

### 9.5 Schéma complet UDP

```
CLIENT                                SERVEUR
  socket(SOCK_DGRAM)                    socket(SOCK_DGRAM)
                                        bind(port=30000)
  sendto(données, addr_serveur)  ────►  recvfrom(&addr_client)
                                        traitement
  recvfrom()                    ◄────   sendto(réponse, addr_client)
  close()                               (boucle infinie)
```

---

## 10. Sérialisation, TCP et poll

### 10.1 Alignement mémoire et padding

Les processeurs exigent que les données soient alignées sur des adresses multiples de leur taille. Le compilateur ajoute des **octets de remplissage** (padding) :

```c
struct foo {
    uint32_t n;  // 4 octets, offset 0
    char     c;  // 1 octet,  offset 4
                 // 3 octets de PADDING ici !
    uint32_t m;  // 4 octets, offset 8
};
// sizeof(struct foo) = 12, pas 9 !
```

**Règle du padding :** un champ de taille T est placé à une adresse multiple de T. La taille totale de la struct est un multiple de l'alignement du plus grand champ.

```c
struct s1 {             // sizeof = 12
    char s[3];          // offset 0, taille 3
    // padding 1 octet  // offset 3
    int16_t i;          // offset 4, taille 2
    char d;             // offset 6, taille 1
    // padding 1 octet  // offset 7
    uint32_t n;         // offset 8, taille 4
};
```

> **Structures et réseau ne s'entendent pas.** Jamais envoyer une `struct` directement sur le réseau : padding aléatoire, endianness variable. Il faut **sérialiser**.

### 10.2 Sérialisation / Désérialisation

```c
// SÉRIALISER (envoyer) : écrire champ par champ en big-endian
void htonfilm(const struct film *src, uint8_t *dest) {
    memcpy(dest, src->nom, 61);          dest += 61;
    uint32_t d = htonl(src->duree);
    memcpy(dest, &d, 4);                 dest += 4;
    uint16_t a = htons(src->annee);
    memcpy(dest, &a, 2);
}

// DÉSÉRIALISER (recevoir) : lire champ par champ
void ntohfilm(const uint8_t *src, struct film *dest) {
    memcpy(dest->nom, src, 61);          src += 61;
    uint32_t d; memcpy(&d, src, 4);      src += 4;
    dest->duree = ntohl(d);
    uint16_t a; memcpy(&a, src, 2);
    dest->annee = ntohs(a);
}
```

**Pourquoi `uint32_t` et non `int` pour les champs réseau ?** Les tailles d'`int` varient selon la plateforme (16 ou 32 bits). `uint32_t` garantit exactement 32 bits.

### 10.3 Sockets TCP (SOCK_STREAM)

TCP est fiable mais nécessite d'établir une connexion.

**Handshake TCP (3-way) :**
```
CLIENT                SERVEUR
  SYN         ────►
              ◄────   SYN-ACK
  ACK         ────►
═══════ connexion établie ═══════
  data        ⟺       data
  FIN         ────►
              ◄────   FIN-ACK
```

**Côté serveur :**
```c
int sock = socket(AF_INET, SOCK_STREAM, 0);  // TCP

// Optionnel mais recommandé : réutilisation rapide du port
int opt = 1;
setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

bind(sock, (struct sockaddr *)&addr, sizeof(addr));
listen(sock, 5);  // file d'attente de 5 connexions en attente

while (1) {
    struct sockaddr_in addr_client;
    socklen_t len = sizeof(addr_client);
    int client = accept(sock, (struct sockaddr *)&addr_client, &len);
    // client est le fd pour parler à CE client précis

    char buf[1024];
    ssize_t n = read(client, buf, sizeof(buf));
    write(client, "OK\n", 3);
    close(client);
}
```

**Côté client :**
```c
int sock = socket(AF_INET, SOCK_STREAM, 0);

struct sockaddr_in srv;
srv.sin_family = AF_INET;
srv.sin_port   = htons(80);
inet_pton(AF_INET, "93.184.216.34", &srv.sin_addr);

connect(sock, (struct sockaddr *)&srv, sizeof(srv));  // établit la connexion

write(sock, "GET / HTTP/1.0\r\n\r\n", 18);

char buf[4096];
ssize_t n;
while ((n = read(sock, buf, sizeof(buf))) > 0)
    write(1, buf, n);

close(sock);
```

> **TCP = flux sans bords !** Deux `write()` consécutifs peuvent arriver en un seul `read()` ou être découpés différemment. Toujours définir un **protocole applicatif** (ex : longueur en tête de message, délimiteur, taille fixe).

### 10.4 poll() — gérer plusieurs connexions sans threads

`poll()` attend que l'un des descripteurs soit **prêt**, sans bloquer sur un seul.

```c
#include <poll.h>

struct pollfd fds[2];
fds[0].fd = sock_ecoute;   fds[0].events = POLLIN;
fds[1].fd = sock_client;   fds[1].events = POLLIN;

int ret = poll(fds, 2, -1);  // -1 = attendre indéfiniment

if (ret == -1) { perror("poll"); exit(1); }

if (fds[0].revents & POLLIN) {
    // Nouvelle connexion à accepter sur sock_ecoute
    int nouveau = accept(sock_ecoute, NULL, NULL);
}
if (fds[1].revents & POLLIN) {
    // Données disponibles sur sock_client
    char buf[512];
    ssize_t n = read(sock_client, buf, sizeof(buf));
    if (n == 0) { /* client déconnecté */ close(sock_client); }
}
```

**`stdbuf -oL commande`** : force le mode line-buffered pour une commande (utile quand stdout est connecté à un pipe).

---

## 11. DNS, IPv6 et getaddrinfo

### 11.1 Le problème : noms vs adresses

On retient facilement `"google.com"` mais difficilement `"142.250.74.110"`. Le **DNS** (Domain Name System) est l'annuaire d'Internet.

### 11.2 Structure d'un nom de domaine

```
galilee.univ-paris13.fr

  fr           → TLD (domaine de 1er niveau)
  univ-paris13 → domaine de 2ème niveau
  galilee      → sous-domaine

Lecture de droite à gauche : fr → univ-paris13 → galilee
```

### 11.3 Fonctionnement du DNS

```
Ta machine → Résolveur local (box internet)
    │
    ├→ Serveur RACINE (.)
    │    "Pour .fr, contacte : e.ext.nic.fr"
    │
    ├→ Serveur TLD .fr
    │    "Pour univ-paris13.fr, contacte : dns1.univ-paris13.fr"
    │
    └→ Serveur autoritaire (dns1.univ-paris13.fr)
         "galilee.univ-paris13.fr = 81.194.43.211"
```

Chaque réponse est **mise en cache** (TTL) pour éviter de répéter la résolution.

### 11.4 IPv6

IPv4 = 32 bits ≈ 4 milliards d'adresses. Insuffisant. IPv6 = **128 bits**.

```
IPv4 : 192.168.1.42
IPv6 : 2001:0db8:85a3:0000:0000:8a2e:0370:7334
       (abréviation possible) : 2001:db8:85a3::8a2e:370:7334
```

### 11.5 getaddrinfo() — la fonction universelle

Résout un nom de domaine en adresses exploitables directement avec `socket()`, `connect()`, `bind()`.

```c
#include <netdb.h>

struct addrinfo hints, *res;
memset(&hints, 0, sizeof(hints));
hints.ai_family   = AF_UNSPEC;    // IPv4 ou IPv6 indifféremment
hints.ai_socktype = SOCK_STREAM;  // TCP

int err = getaddrinfo("google.com", "80", &hints, &res);
if (err != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
    exit(1);
}

// Essayer chaque adresse retournée jusqu'à ce que ça marche
int sock = -1;
for (struct addrinfo *p = res; p != NULL; p = p->ai_next) {
    sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (sock == -1) continue;
    if (connect(sock, p->ai_addr, p->ai_addrlen) == 0)
        break;  // connexion réussie !
    close(sock);
    sock = -1;
}

freeaddrinfo(res);  // TOUJOURS libérer !

if (sock == -1) { fprintf(stderr, "Impossible de se connecter\n"); exit(1); }
```

---

## 12. Récapitulatif et pièges aux partiels

### 12.1 Fonctions indispensables à maîtriser

| Domaine | Fonctions clés |
|---------|----------------|
| Processus | `fork()`, `exit()`, `wait()`, `waitpid()`, `execlp()`, `execvp()` |
| Threads | `pthread_create()`, `pthread_join()` |
| Sémaphores | `sem_init()`, `sem_wait()`, `sem_post()`, `sem_destroy()` |
| Mutex | `pthread_mutex_init()`, `pthread_mutex_lock()`, `pthread_mutex_unlock()`, `pthread_mutex_destroy()` |
| I/O bas niveau | `open()`, `read()`, `write()`, `close()` |
| stdio.h | `fopen()`, `fclose()`, `fgetc()`, `fgets()`, `fprintf()`, `fflush()` |
| Tubes | `pipe()`, `dup2()` |
| Sockets UDP | `socket()`, `bind()`, `sendto()`, `recvfrom()` |
| Sockets TCP | `socket()`, `bind()`, `listen()`, `accept()`, `connect()` |
| Sérialisation | `htonl()`, `htons()`, `ntohl()`, `ntohs()`, `memcpy()` |
| DNS / IPv6 | `getaddrinfo()`, `freeaddrinfo()` |

### 12.2 Les pièges classiques

> **🚨 JAMAIS OUBLIER**
>
> 1. Tester le retour de TOUS les appels système → `-1` = `perror()` + `exit(1)`
> 2. Après `fork()`, le fils hérite de TOUS les descripteurs → fermer ceux inutiles
> 3. Dans un tube, chaque processus ferme l'extrémité qu'il n'utilise pas
> 4. Jamais envoyer une `struct` directement sur le réseau → sérialiser
> 5. Convertir en big-endian pour le réseau : `htons()`, `htonl()`
> 6. TCP ne préserve pas les bords → toujours boucler sur `read()`
> 7. Les sections critiques doivent être les plus COURTES possibles
> 8. Compiler avec `-pthread` pour les threads (sinon erreur de linker)
> 9. Initialiser les sémaphores à **0** pour signaler un événement, **1** pour exclusion mutuelle
> 10. `sem_b` attendu par 2 threads → faire `sem_post(&sem_b)` **deux fois** dans le thread producteur

### 12.3 Mémos visuels

**fork() :**
```
         avant fork()
              │
          fork()
         ╱        ╲
      PÈRE           FILS
  pid = PID_fils    pid = 0
   (valeur > 0)
```

**Cycle de vie processus :**
```
fork() → Running ↔ Sleeping → exit() → Zombie → wait() → disparu
```

**Architecture socket TCP :**
```
SERVEUR                          CLIENT
  socket()                         socket()
  bind()
  listen()
  accept() [bloquant]  ←──────    connect()
  fd_client ──────────────────────────────
  read(fd_client)      ←──────    write(sock, ...)
  write(fd_client)     ──────►    read(sock, ...)
  close(fd_client)                 close(sock)
```

**Séquence de sérialisation :**
```
struct → champ par champ → htonl/htons → memcpy vers buffer → sendto/write
                                                                    ↓
struct ← champ par champ ← ntohl/ntohs ← memcpy depuis buffer ← recvfrom/read
```

---

*Bon courage pour le partiel !*
