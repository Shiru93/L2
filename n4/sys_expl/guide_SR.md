# Système & Réseaux — Guide Complet Partiels
> L2 Informatique — Université Sorbonne Paris Nord — Pierre Rousselin

---

## Table des matières

1. [CM0-1 — Le Noyau et les Processus](#cm0-1--le-noyau-et-les-processus)
2. [CM2 — exit, wait, exec, signaux, zombies](#cm2--exit-wait-exec-signaux-zombies)
3. [CM3 — Threads, void* et pointeurs de fonctions](#cm3--threads-void-et-pointeurs-de-fonctions)
4. [CM4 — Race conditions, atomicité et sémaphores](#cm4--race-conditions-atomicité-et-sémaphores)
5. [CM5 — Mutex, deadlock et problèmes classiques](#cm5--mutex-deadlock-et-problèmes-classiques)
6. [CM6 — Entrées-Sorties bas niveau Unix](#cm6--entrées-sorties-bas-niveau-unix)
7. [CM7 — stdio.h, bufferisation et tubes](#cm7--stdioh-bufferisation-et-tubes)
8. [CM8 — Réseaux, ports, UDP et sockets](#cm8--réseaux-ports-udp-et-sockets)
9. [CM9 — Sérialisation, TCP et poll](#cm9--sérialisation-tcp-et-poll)
10. [CM11 — DNS, IPv6 et getaddrinfo](#cm11--dns-ipv6-et-getaddrinfo)
11. [Récapitulatif pour les partiels](#récapitulatif-pour-les-partiels)

---

## CM0-1 — Le Noyau et les Processus

### C'est quoi un système d'exploitation ?

Ton ordinateur a du matériel (processeur, RAM, disque dur, clavier...). Les programmes ont besoin d'accéder à ce matériel. Mais si chaque programme pouvait tout faire directement, ce serait le chaos : un programme pourrait écraser la mémoire d'un autre, monopoliser le CPU, etc. Le **système d'exploitation** est là pour arbitrer tout ça.

Au cœur du système d'exploitation, il y a le **noyau** (*kernel*).

> **Définition — Noyau (kernel)**
> Le noyau est un programme chargé en mémoire au démarrage de la machine. Il gère les autres logiciels (ordonnancement, communication entre processus) et les interactions avec le matériel (mémoire, réseau, périphériques...). C'est lui qui a **le monopole d'accès au matériel**.

Sous Unix, le noyau offre deux abstractions principales :

| Abstraction | Description |
|---|---|
| **Le processus** | Un programme en cours d'exécution. Entité dynamique qui naît, fait des choses, puis meurt. |
| **Le fichier** | Toute chose dans laquelle on peut lire/écrire — fichier normal, terminal, socket réseau... |

### Les appels système

Quand un programme a besoin d'un service du noyau, il fait un **appel système**. C'est une instruction spéciale qui :

1. Fait passer le CPU en **mode privilégié** (mode noyau)
2. Saute dans le code noyau correspondant à la demande
3. Le noyau décide si l'accès est autorisé, vérifie que la ressource est dispo
4. Retourne à l'application avec le résultat (ou un code d'erreur)

Les appels système importants à connaître :

| Appel système | Rôle |
|---|---|
| `fork()` | Créer un processus fils (clone du processus courant) |
| `exit(n)` | Terminer le processus avec le statut de sortie n |
| `wait()` | Attendre la fin d'un processus fils |
| `execve()` | Remplacer l'image du processus par un nouveau programme |
| `open()` / `close()` | Ouvrir / fermer un fichier |
| `read()` / `write()` | Lire / écrire dans un fichier |
| `kill(pid, sig)` | Envoyer un signal à un processus |

### Un processus, c'est quoi exactement ?

Un **programme** est un fichier exécutable (inerte, sur le disque). Un **processus** est une *instance* de ce programme en cours d'exécution — c'est dynamique, ça vit dans la RAM.

Chaque processus a :
- Un **PID** (Process Identifier) : un entier unique > 0
- Son propre **espace mémoire**
- Un **état** (Running, Sleeping, Zombie...)
- Des fichiers ouverts (dont stdin/stdout/stderr)
- Un processus **parent** (celui qui l'a créé avec fork)

| État | Lettre | Signification |
|---|---|---|
| Running | `R` | En cours d'exécution ou dans la file d'attente CPU |
| Sleeping | `S` | En attente d'un événement (entrée clavier, fin d'un autre processus...) |
| Stopped | `T` | Mis en pause par un signal (ex: Ctrl+Z) |
| Zombie | `Z` | Mort mais le parent n'a pas encore récupéré son statut de sortie |

### fork() — créer un processus fils

`fork()` est l'appel système qui crée un nouveau processus. Le fils est une copie quasi-identique du père. La seule différence : la valeur de retour de `fork()`.

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    pid_t pid;

    pid = fork();   /* On crée un processus fils */

    switch (pid) {
        case -1:           /* fork a échoué */
            perror("fork");
            return 1;

        case 0:            /* On est DANS LE FILS */
            printf("Je suis le fils, mon PID = %d\n", getpid());
            return 0;

        default:           /* On est DANS LE PÈRE, pid = PID du fils */
            printf("Je suis le père, PID du fils = %d\n", pid);
            return 0;
    }
}
```

> **Règle d'or de fork()**
> `fork()` retourne **0 dans le fils**, le **PID du fils dans le père**, et **-1 en cas d'erreur**. Toujours tester les 3 cas !

### L'ordonnanceur (scheduler)

Le noyau partage le(s) processeur(s) entre tous les processus actifs avec un algorithme *round-robin* (tourniquet) : chaque processus reçoit une tranche de temps CPU, puis retourne en file d'attente. Les processus qui attendent un événement (I/O, signal...) sont mis en sommeil et réveillés le moment venu.

---

## CM2 — exit, wait, exec, signaux, zombies

### La mort d'un processus

Un processus peut mourir de deux façons :
- **Normalement** : `return n;` depuis `main`, ou `exit(n);` depuis n'importe où
- **Par signal** : en recevant un signal comme `SIGTERM` (tuer poliment) ou `SIGKILL` (tuer sans pitié)

Le `n` passé à `exit()` est le **statut de sortie** : `0` = succès, valeur positive = erreur.

### errno et perror — gérer les erreurs

Presque tous les appels système retournent `-1` en cas d'erreur, et positionnent une variable globale `errno` avec un code décrivant l'erreur.

```c
int fd = open("fichier.txt", O_RDONLY);

if (fd == -1) {
    /* perror affiche "open: No such file or directory" */
    perror("open");
    exit(1);
}
```

> **Réflexe indispensable**
> Toujours tester la valeur de retour des appels système. Si c'est `-1`, appeler `perror("nom_de_l_appel")` puis `exit(1)` si l'erreur est irrécupérable.

### Attendre un fils : wait()

Après un `fork()`, le père doit généralement attendre la fin du fils avec `wait()`. Sans ça, le fils devient un **zombie** : il est mort mais son entrée dans la table des processus reste présente car le père n'a pas récupéré son statut de sortie.

```c
#include <sys/wait.h>

pid_t pid = fork();
if (pid == 0) {
    /* code du fils */
    exit(42);
} else {
    int status;
    wait(&status);   /* le père attend la fin du fils */
    if (WIFEXITED(status)) {
        printf("Fils terminé avec code %d\n", WEXITSTATUS(status));
    }
}
```

### Remplacer un programme : exec

La famille `exec` (execlp, execvp...) remplace l'image mémoire du processus courant par un **nouveau programme**. Le PID reste le même. Si `exec` réussit, le code qui suit ne s'exécute jamais.

```c
/* Exemple : le fils exécute "ls -l" */
if (fork() == 0) {
    execlp("ls", "ls", "-l", NULL);
    /* Si on arrive ici, execlp a échoué */
    perror("execlp");
    exit(1);
}
```

### Les pointeurs en C (rappels essentiels)

Un pointeur est une variable qui contient une **adresse mémoire**.

```c
int i = 42;
int *p;      /* p est un pointeur vers un int */

p = &i;      /* &i = adresse de la variable i */
*p = 100;   /* *p = déréférencement : accède à ce que pointe p */
             /* Maintenant i vaut 100 ! */

/* Passage par pointeur (simulation de "passage par référence") */
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
swap(&i, &j);  /* on passe les adresses */
```

> **Notation avec struct**
> Pour accéder aux champs d'une structure via un pointeur, on utilise `->` au lieu de `.` : `ptr->champ` est équivalent à `(*ptr).champ`.

---

## CM3 — Threads, void* et pointeurs de fonctions

### Pourquoi les threads ?

Avec `fork()`, chaque processus a son propre espace mémoire — partager des données est compliqué. Les **threads** (fils d'exécution) résolvent ça : plusieurs threads dans un même processus **partagent la même mémoire**. Ils peuvent communiquer directement via des variables globales.

De plus, les processeurs modernes ont plusieurs cœurs. Les threads permettent d'exploiter ce parallélisme réel.

### Créer et attendre un thread

```c
#include <pthread.h>
#include <stdio.h>

/* La fonction que le thread va exécuter */
/* Elle prend un void* et retourne un void* */
void *ma_fonction(void *arg) {
    char *message = arg;  /* on caste void* en char* */
    printf("Thread dit : %s\n", message);
    return NULL;
}

int main(void) {
    pthread_t th;

    /* Créer le thread */
    pthread_create(&th, NULL, ma_fonction, "Bonjour !");

    /* Attendre que le thread se termine */
    pthread_join(th, NULL);

    return 0;
}
```

> **Compilation**
> Pour utiliser les pthreads, compiler avec : `gcc -Wall programme.c -pthread`

### Les pointeurs génériques : void*

`void *` est le type "pointeur vers n'importe quoi". C'est ce qui permet à `pthread_create` d'accepter n'importe quel type d'argument.

| Ce qu'on **peut** faire | Ce qu'on **ne peut pas** faire |
|---|---|
| Assigner n'importe quel pointeur à un `void *` sans cast | Déréférencer un `void *` (type inconnu) |
| Assigner un `void *` à n'importe quel pointeur sans cast | Faire de l'arithmétique de pointeur |

### Les pointeurs de fonctions

En C, une fonction a une adresse en mémoire. On peut stocker cette adresse dans un **pointeur de fonction** et l'appeler plus tard. C'est indispensable pour `pthread_create`, `qsort`, etc.

```c
/* Type : pointeur vers une fonction qui prend un int et retourne un int */
int (*f)(int);

int triple(int n)   { return n * 3; }
int plus_deux(int n){ return n + 2; }

/* img_de_0 : prend un pointeur de fonction et l'appelle avec 0 */
int img_de_0(int (*f)(int)) {
    return f(0);   /* appel via le pointeur */
}

int main(void) {
    printf("%d\n", img_de_0(triple));    /* affiche 0 */
    printf("%d\n", img_de_0(plus_deux)); /* affiche 2 */
    return 0;
}
```

> **Syntaxe du type pointeur de fonction**
> Le type d'un pointeur vers une fonction prenant `p1, p2` et retournant `r` s'écrit : `r (*)(p1, p2)`.

C'est pourquoi `pthread_create` a cette signature :

```c
int pthread_create(pthread_t *thread,
                   const pthread_attr_t *attr,
                   void *(*start_routine)(void *),  /* ← pointeur de fonction */
                   void *arg);
```

---

## CM4 — Race conditions, atomicité et sémaphores

### Le problème : l'indéterminisme

Quand plusieurs threads accèdent à la même mémoire, le résultat peut varier d'une exécution à l'autre — c'est l'**indéterminisme**. On parle de **race condition** (situation de compétition) quand le résultat dépend de l'ordre aléatoire dans lequel les threads s'exécutent.

> **Exemple concret : le problème du million**
> 1000 threads, chacun fait `++compteur` 1000 fois. On s'attend à 1 000 000. En pratique on obtient souvent moins, car `++compteur` n'est pas atomique : c'est 3 instructions assembleur (LOAD, ADD, STORE). Deux threads peuvent interférer entre ces instructions.

### L'atomicité

Une opération est **atomique** si elle se passe "tout d'un coup" sans qu'un autre thread puisse s'insérer au milieu. `++i` en C n'est **PAS** atomique sur la plupart des architectures.

### Attente active — à ÉVITER

```c
/* Attente active : mauvaise pratique ! */
int alice_a_fini = 0;

void *bob(void *arg) {
    while (!alice_a_fini)  /* Bob tourne en rond, consomme du CPU inutilement */
        ;
    printf("Alice a fini !\n");
    return NULL;
}
```

C'est une horreur en termes de performance. On préfère les **appels système bloquants** qui mettent le thread en sommeil.

### Les sémaphores

Un sémaphore est un compteur entier avec deux opérations atomiques :

| Opération | Effet |
|---|---|
| `sem_wait(s)` | Décrémente le compteur. Si le compteur est à 0, le thread **dort** jusqu'à ce qu'il repasse à > 0. |
| `sem_post(s)` | Incrémente le compteur. **Réveille** un thread en attente (s'il y en a un). |

```c
#include <semaphore.h>

sem_t verrou;

int main(void) {
    sem_init(&verrou, 0, 1); /* init à 1 : "ressource disponible" */
    /* ... créer les threads ... */
    sem_destroy(&verrou);
}

void *thread_func(void *arg) {
    sem_wait(&verrou);    /* Entrer dans la section critique */
    ++compteur;           /* ← section critique */
    sem_post(&verrou);    /* Sortir de la section critique */
    return NULL;
}
```

> **Paramètres de sem_init**
> `sem_init(&s, 0, valeur_initiale)` — le 2ème paramètre (`0`) indique que le sémaphore est partagé entre threads du même processus. La valeur initiale : `1` pour protéger une section critique, `0` pour signaler un événement.

---

## CM5 — Mutex, deadlock et problèmes classiques

### Section critique

> **Définition**
> Une **section critique** est une portion de code dans laquelle on doit garantir qu'**un seul thread à la fois** peut s'y trouver (pour accéder à une ressource partagée).

### Les mutex — verrous d'exclusion mutuelle

Un **mutex** (MUTual EXclusion) est une version spécialisée du sémaphore binaire, conçue pour protéger les sections critiques. Un mutex est toujours verrouillé et déverrouillé par le *même thread*.

```c
#include <pthread.h>

pthread_mutex_t verrou;
int compteur = 0;

void *bosser(void *arg) {
    for (int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&verrou);   /* verrouiller (bloquant) */
        ++compteur;                    /* section critique */
        pthread_mutex_unlock(&verrou); /* déverrouiller */
    }
    return NULL;
}

int main(void) {
    pthread_mutex_init(&verrou, NULL);
    /* ... créer et joindre les threads ... */
    pthread_mutex_destroy(&verrou);
}
```

| Appel | Rôle |
|---|---|
| `pthread_mutex_init(&m, NULL)` | Initialiser le mutex (déverrouillé au départ) |
| `pthread_mutex_lock(&m)` | Verrouiller — bloque si déjà verrouillé |
| `pthread_mutex_unlock(&m)` | Déverrouiller — réveille un thread en attente |
| `pthread_mutex_destroy(&m)` | Libérer les ressources |

> **Mutex vs Sémaphore**
> **Mutex** → pour protéger une section critique (même thread lock/unlock).
> **Sémaphore** → pour signaler qu'une ressource est disponible ou qu'un événement s'est produit (un thread peut faire wait et un autre peut faire post).

### Le deadlock (interblocage)

Un **deadlock** se produit quand deux threads (ou plus) s'attendent mutuellement indéfiniment. C'est le *problème du dîner des philosophes* : N philosophes autour d'une table, N fourchettes. Chacun a besoin de 2 fourchettes. Si chacun prend sa fourchette gauche en même temps, ils se bloquent tous.

```
Philosophe 1 → tient fourchette 1, attend fourchette 2
Philosophe 2 → tient fourchette 2, attend fourchette 3
Philosophe 3 → tient fourchette 3, attend fourchette 1
          ↑________________________________↑
                      DEADLOCK !
```

Solutions classiques : toujours prendre les ressources dans le même ordre, ou utiliser un sémaphore "portier" qui limite le nombre de philosophes à table.

### Producteurs / Consommateurs

Des threads *producteurs* créent des données et les mettent dans un *tampon partagé* ; des threads *consommateurs* lisent ces données. Il faut :
- Que le consommateur attende si le tampon est vide
- Que le producteur attende si le tampon est plein
- Que l'accès au tampon soit protégé par un mutex

On utilise typiquement 3 outils : un mutex (accès au tampon) + un sémaphore *vide* (places libres) + un sémaphore *plein* (éléments disponibles).

### Lecteurs / Écrivains

Plusieurs lecteurs peuvent lire simultanément, mais un écrivain doit avoir un accès exclusif. Solution : compteur de lecteurs actifs + mutex pour le compteur + sémaphore d'accès en écriture.

> **Garder les sections critiques courtes !**
> Plus une section critique est longue, moins les threads peuvent travailler en parallèle. Seul l'accès à la variable partagée doit être dans la section critique, pas les calculs qui précèdent.

---

## CM6 — Entrées-Sorties bas niveau Unix

### Deux niveaux d'I/O

| Niveau | Fonctions | Caractéristiques |
|---|---|---|
| **Bas niveau (Unix)** | `open`, `read`, `write`, `close` | Directs, sans tampon, spécifiques à Unix. Grande liberté. |
| **Bibliothèque standard** | `fopen`, `fread`, `fwrite`, `fclose` | Portables, avec tampon. Plus de confort. |

### Le descripteur de fichier

Quand un processus ouvre un fichier, le noyau lui attribue un **descripteur de fichier** (file descriptor) : un petit entier servant d'identifiant dans tous les appels système.

| Descripteur | Nom | Correspond à |
|---|---|---|
| `0` | stdin | Entrée standard (clavier) |
| `1` | stdout | Sortie standard (terminal) |
| `2` | stderr | Sortie d'erreur (terminal) |
| `3+` | — | Fichiers ouverts par le programme |

### open() — ouvrir un fichier

```c
#include <fcntl.h>

/* Ouvrir en lecture */
int fd = open("fichier.txt", O_RDONLY);

/* Ouvrir en écriture, créer si inexistant, vider si existant */
int fd = open("sortie.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
/*                                                          ↑ permissions */

if (fd == -1) { perror("open"); exit(1); } /* TOUJOURS tester */
```

Flags principaux :

| Flag | Signification |
|---|---|
| `O_RDONLY` | Lecture seule |
| `O_WRONLY` | Écriture seule |
| `O_RDWR` | Lecture et écriture |
| `O_CREAT` | Créer le fichier s'il n'existe pas |
| `O_TRUNC` | Vider le fichier s'il existe |
| `O_APPEND` | Écriture toujours à la fin du fichier |
| `O_EXCL` | Avec O_CREAT : échouer si le fichier existe déjà |

### Permissions (mode)

```
Permissions : 3 chiffres octaux → [propriétaire][groupe][autres]
Chaque chiffre : r=4, w=2, x=1

0644 → rw-r--r--  (lecture/écriture propriétaire, lecture pour les autres)
0755 → rwxr-xr-x  (lecture/écriture/exécution propriétaire, lecture/exécution autres)
0600 → rw-------  (lecture/écriture propriétaire seulement)
```

> **umask**
> L'umask est un masque appliqué aux permissions demandées. Si l'umask est 0022, les permissions 0666 donnent en pratique 0644 (on "enlève" les bits de l'umask).

### read() et write()

```c
#include <unistd.h>

/* read : lit au plus count octets depuis fd, les met dans buf */
ssize_t n = read(fd, buf, count);
/* retourne : nb d'octets lus, 0 = fin de fichier, -1 = erreur */

/* write : écrit count octets depuis buf vers fd */
ssize_t n = write(fd, buf, count);
/* retourne : nb d'octets écrits, -1 = erreur */

/* Exemple : copie d'un fichier, morceau par morceau */
char buf[4096];
ssize_t n;
while ((n = read(fd_in, buf, sizeof(buf))) > 0) {
    write(fd_out, buf, n);
}
```

> **Attention aux lectures partielles !**
> `read()` peut retourner moins d'octets que demandé (notamment sur un terminal, un pipe, ou en réseau). Il faut boucler jusqu'à avoir lu tout ce qu'on voulait.

### close()

```c
close(fd); /* libère l'entrée dans la table des fichiers ouverts */
```

Toujours fermer les descripteurs qu'on n'utilise plus, notamment après un `fork()` — les fils héritent des descripteurs ouverts du père !

---

## CM7 — stdio.h, bufferisation et tubes

### stdio.h — la couche au-dessus

`stdio.h` est une bibliothèque standard qui encapsule les appels système bruts. Au lieu d'un descripteur de fichier entier, on manipule des **flux** (`FILE *`), qui contiennent un buffer interne.

```c
FILE *f = fopen("data.txt", "r");  /* ouvrir */

int c;
while ((c = fgetc(f)) != EOF) {    /* lire octet par octet */
    putchar(c);
}

char ligne[256];
fgets(ligne, sizeof(ligne), f);     /* lire une ligne */

fprintf(f, "Valeur : %d\n", n);     /* écriture formatée */

fclose(f);                           /* fermer (vide le buffer !) */
```

### Les 3 types de bufferisation

| Type | Quand écrit-on vraiment ? | Exemple |
|---|---|---|
| **Fully buffered** | Quand le buffer est plein, ou à la fermeture | Fichier normal |
| **Line buffered** | Quand on écrit un `\n`, ou buffer plein | stdout (terminal) |
| **Unbuffered** | Immédiatement | stderr |

> **Piège classique**
> `printf("message")` sans `\n` peut ne pas s'afficher immédiatement si stdout est line-buffered. Pour forcer l'affichage : `fflush(stdout);`

### Les tubes (pipes)

Un **tube** (pipe) est un mécanisme de communication inter-processus sur la même machine. Il est unidirectionnel et FIFO (premier entré, premier sorti). Le `|` dans le shell crée des tubes entre commandes.

```c
#include <unistd.h>

int tube[2];   /* tube[0] = côté lecture, tube[1] = côté écriture */

if (pipe(tube) == -1) { perror("pipe"); exit(1); }

switch (fork()) {
    case 0: /* FILS : il écrit dans le tube */
        close(tube[0]);   /* fermer le côté lecture (pas utilisé) */
        write(tube[1], "Bonjour", 7);
        close(tube[1]);
        exit(0);

    default: /* PÈRE : il lit depuis le tube */
        close(tube[1]);   /* fermer le côté écriture (pas utilisé) */
        char buf[64];
        ssize_t n = read(tube[0], buf, sizeof(buf));
        write(1, buf, n);
        close(tube[0]);
        wait(NULL);
}
```

> **Règle des tubes**
> Chaque processus doit fermer les extrémités du tube qu'il n'utilise pas ! Si le côté écriture n'est pas fermé par tous ceux qui ne l'utilisent pas, le lecteur n'obtiendra jamais EOF.

### dup2() — rediriger les descripteurs

`dup2(ancien_fd, nouveau_fd)` fait pointer `nouveau_fd` vers le même fichier que `ancien_fd`. C'est ce qui permet de rediriger stdin/stdout/stderr.

```c
dup2(tube[0], 0);  /* stdin pointe maintenant vers tube[0] */
close(tube[0]);    /* on peut fermer l'original */
```

---

## CM8 — Réseaux, ports, UDP et sockets

### Le modèle en couches

```
┌─────────────────────────────┐
│   Couche APPLICATION        │  HTTP, SSH, DNS, SMTP...
├─────────────────────────────┤
│   Couche TRANSPORT          │  TCP, UDP (ports)
├─────────────────────────────┤
│   Couche RÉSEAU             │  IP (adresses IP, routage)
├─────────────────────────────┤
│   Couche LIAISON            │  Ethernet (adresses MAC)
├─────────────────────────────┤
│   Couche PHYSIQUE           │  Bits dans le câble / l'air
└─────────────────────────────┘
```

Chaque couche encapsule les données de la couche supérieure en ajoutant ses propres en-têtes.

### Les ports

L'adresse IP identifie une machine. Le **port** identifie un processus sur cette machine. C'est un entier sur 16 bits (0 à 65535). Les ports 0–1023 sont réservés aux services bien connus (root seulement) :

| Port | Protocole |
|---|---|
| 22 | SSH |
| 53 | DNS |
| 80 | HTTP |
| 443 | HTTPS |

Un processus client utilise un **port éphémère** choisi automatiquement par le système.

### UDP vs TCP

| | UDP | TCP |
|---|---|---|
| Connexion | Non (sans connexion) | Oui (avec connexion) |
| Données | Datagrammes (avec bords) | Flux continu (sans bords) |
| Fiabilité | Aucune garantie d'ordre ou de livraison | Garanti, ordre préservé |
| Poids | Léger, rapide | Plus lourd |
| Utilisé pour | DNS, streaming, jeux | HTTP, SSH, IMAP |

### Les sockets de Berkeley

Une **socket** est l'interface de programmation pour la communication réseau sous Unix. C'est un fichier spécial — on peut y faire `read()` et `write()`.

```c
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* Créer une socket UDP */
int sock = socket(AF_INET, SOCK_DGRAM, 0);
/*              ↑ IPv4    ↑ UDP         */

/* Adresse du serveur */
struct sockaddr_in srv;
srv.sin_family = AF_INET;
srv.sin_port   = htons(30000);         /* port en big-endian */
inet_pton(AF_INET, "10.0.0.1", &srv.sin_addr);

/* Envoyer un datagramme */
sendto(sock, "Bonjour", 7, 0,
       (struct sockaddr *) &srv, sizeof(srv));

/* Recevoir un datagramme (côté serveur, après bind) */
char buf[512];
struct sockaddr_in client;
socklen_t len = sizeof(client);
recvfrom(sock, buf, sizeof(buf), 0,
         (struct sockaddr *) &client, &len);
```

> **Big-endian (gros-boutisme) réseau**
> Les protocoles réseau utilisent la convention *big-endian* (octet de poids fort en premier). `htons()`/`htonl()` convertissent de l'ordre de l'hôte vers l'ordre réseau. `ntohs()`/`ntohl()` font l'inverse.

### bind() — pour les serveurs

```c
struct sockaddr_in addr;
addr.sin_family      = AF_INET;
addr.sin_port        = htons(30000);
addr.sin_addr.s_addr = INADDR_ANY;  /* accepter depuis n'importe quelle interface */

bind(sock, (struct sockaddr *) &addr, sizeof(addr));
```

---

## CM9 — Sérialisation, TCP et poll

### Alignement mémoire et padding

Les processeurs ont des contraintes d'accès mémoire : ils lisent les données à des adresses multiples de leur taille. Pour respecter ça, le compilateur ajoute des **octets de remplissage** (padding) dans les structures.

```c
struct foo {
    uint32_t n;  /* 4 octets, offset 0 */
    char     c;  /* 1 octet,  offset 4 */
                 /* 3 octets de padding ici ! */
    uint32_t m;  /* 4 octets, offset 8 */
};
/* sizeof(struct foo) = 12, pas 9 ! */
```

> **Structures et réseau ne s'entendent pas**
> On ne peut jamais envoyer une `struct` directement sur le réseau : l'alignement, le padding et l'ordre des octets (endianness) peuvent différer entre machines. Il faut **sérialiser** les données.

### Sérialisation / Désérialisation

Sérialiser = convertir une structure en une séquence d'octets bien définie pour la transmission. Le protocole applicatif définit précisément l'ordre et la taille de chaque champ.

```c
/* Sérialiser : écrire champ par champ, en big-endian */
uint32_t n = htonl(mon_int);     /* convertir en big-endian */
write(fd, &n, 4);                /* écrire exactement 4 octets */

/* Désérialiser : lire champ par champ */
uint32_t n;
read(fd, &n, 4);
int mon_int = ntohl(n);          /* convertir depuis big-endian */
```

### TCP et les sockets TCP

TCP est fiable mais nécessite d'établir une connexion avant d'échanger des données.

```
SERVEUR                          CLIENT
  socket()                         socket()
  bind()
  listen()          ←SYN→          connect()
  accept()          →SYN-ACK←
  (bloque)          ←ACK→
  ↓ connexion établie ↓
  read()/write()                   read()/write()
  close()                          close()
```

```c
/* Côté SERVEUR */
int sock = socket(AF_INET, SOCK_STREAM, 0); /* TCP */
bind(sock, &addr, sizeof(addr));
listen(sock, 5);  /* file d'attente de 5 connexions max */

while (1) {
    int client = accept(sock, &addr_client, &len); /* bloquant */
    /* client est le descripteur pour parler à CE client */
    read(client, buf, sizeof(buf));
    write(client, "OK\n", 3);
    close(client);
}
```

> **Pas de bords en TCP !**
> TCP est un flux continu — il ne préserve pas les frontières entre messages. Si vous envoyez "Hello" puis "World" avec deux `write()`, le destinataire pourrait recevoir "Hel" puis "loWorld". Il faut définir un protocole applicatif pour savoir où un message se termine.

### poll() — attendre plusieurs descripteurs

`poll()` permet de gérer plusieurs clients TCP sans créer un thread par client. Il attend que l'un des descripteurs spécifiés soit prêt.

```c
#include <poll.h>

struct pollfd fds[2];
fds[0].fd = sock_serveur;  fds[0].events = POLLIN;
fds[1].fd = sock_client;   fds[1].events = POLLIN;

int ret = poll(fds, 2, -1); /* -1 = attendre indéfiniment */

if (fds[0].revents & POLLIN) {
    /* sock_serveur a une nouvelle connexion à accepter */
    accept(...);
}
if (fds[1].revents & POLLIN) {
    /* sock_client a des données à lire */
    read(sock_client, ...);
}
```

---

## CM11 — DNS, IPv6 et getaddrinfo

### Le problème : IP vs noms humains

On retient facilement "google.com" mais difficilement "142.250.74.110". Le **DNS** (Domain Name System) est l'annuaire d'Internet : il traduit les noms de domaine en adresses IP.

### Fonctionnement du DNS

Le DNS est une base de données **distribuée et hiérarchique** :

```
Résolution de "galilee.univ-paris13.fr"

  Ta machine → Résolveur local (box internet / serveur DNS)
       │
       ├→ Serveur RACINE (.)
       │    "Je ne sais pas, mais les serveurs pour .fr sont : e.ext.nic.fr..."
       │
       ├→ Serveur TLD .fr  (e.ext.nic.fr)
       │    "Je ne sais pas, mais les serveurs pour univ-paris13.fr sont : dns1.univ-paris13.fr..."
       │
       └→ Serveur autoritaire (dns1.univ-paris13.fr)
            "galilee.univ-paris13.fr = 81.194.43.211"
```

Il y a 13 serveurs racines dans le monde (répliqués des centaines de fois). Chaque étape est mise en cache pour éviter de répéter la même résolution.

### Structure d'un nom de domaine

```
galilee.univ-paris13.fr

  galilee      → étiquette (sous-domaine)
  univ-paris13 → étiquette (sous-domaine)
  fr           → TLD (Top Level Domain = domaine de 1er niveau)

Lecture de droite à gauche : fr → univ-paris13 → galilee
```

### IPv6

IPv4 a des adresses sur 32 bits (4 milliards d'adresses). Avec l'explosion des appareils connectés, c'est insuffisant. IPv6 utilise des adresses sur **128 bits** :

```
IPv4 : 192.168.1.42
IPv6 : 2001:0db8:85a3:0000:0000:8a2e:0370:7334
       (les groupes de 0000 peuvent être abrégés)
       2001:db8:85a3::8a2e:370:7334
```

### getaddrinfo() — la fonction universelle

Plutôt que d'écrire du code différent pour IPv4 et IPv6, on utilise `getaddrinfo()` qui résout un nom et retourne une liste de `struct addrinfo` exploitables directement avec `socket()`, `bind()`, `connect()`.

```c
#include <netdb.h>

struct addrinfo hints = {0};
struct addrinfo *res;

hints.ai_family   = AF_UNSPEC;    /* IPv4 ou IPv6 */
hints.ai_socktype = SOCK_STREAM;  /* TCP */

int err = getaddrinfo("galilee.univ-paris13.fr", "80", &hints, &res);
if (err != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
    exit(1);
}

/* Essayer chaque résultat jusqu'à ce que ça marche */
for (struct addrinfo *p = res; p != NULL; p = p->ai_next) {
    int sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (connect(sock, p->ai_addr, p->ai_addrlen) == 0)
        break;  /* connexion réussie ! */
    close(sock);
}

freeaddrinfo(res); /* toujours libérer ! */
```

---

## Récapitulatif pour les partiels

### Les fonctions indispensables à maîtriser

| Domaine | Fonctions clés |
|---|---|
| Processus | `fork()`, `exit()`, `wait()`, `waitpid()`, `execvp()` |
| Threads | `pthread_create()`, `pthread_join()` |
| Sémaphores | `sem_init()`, `sem_wait()`, `sem_post()`, `sem_destroy()` |
| Mutex | `pthread_mutex_init()`, `pthread_mutex_lock()`, `pthread_mutex_unlock()` |
| I/O bas niveau | `open()`, `read()`, `write()`, `close()` |
| stdio.h | `fopen()`, `fclose()`, `fgetc()`, `fgets()`, `fprintf()` |
| Tubes | `pipe()`, `dup2()` |
| Sockets UDP | `socket()`, `bind()`, `sendto()`, `recvfrom()` |
| Sockets TCP | `socket()`, `bind()`, `listen()`, `accept()`, `connect()` |
| DNS / IPv6 | `getaddrinfo()`, `freeaddrinfo()` |

### Les pièges classiques aux partiels

> 🚨 **À ne JAMAIS oublier**
>
> 1. Toujours tester la valeur de retour des appels système (`-1` = erreur → `perror()` + `exit(1)`)
> 2. Après `fork()`, le fils hérite des descripteurs ouverts → les fermer si inutiles
> 3. Dans un tube, fermer les extrémités inutilisées dans chaque processus
> 4. Ne jamais envoyer une `struct` directement sur le réseau → sérialiser
> 5. Convertir les entiers en big-endian pour le réseau : `htons()`, `htonl()`
> 6. Les sections critiques doivent être les plus courtes possibles
> 7. Compiler avec `-pthread` pour les threads
> 8. TCP ne préserve pas les bords : toujours boucler sur `read()`

### Mémo : fork() en une image

```
           fork()
              │
    ┌─────────┴──────────┐
    │                    │
  PÈRE                 FILS
pid = [PID du fils]  pid = 0
(valeur > 0)
    │                    │
  continue             continue
  (ou wait)           (ou exec)
```

### Mémo : mutex vs sémaphore

```
MUTEX                          SÉMAPHORE
─────────────────────────────────────────────
lock/unlock par le MÊME        wait et post peuvent être
thread                         dans des threads DIFFÉRENTS

Utilisé pour protéger          Utilisé pour signaler qu'une
une section critique           ressource est disponible

Initialisé à 1 (libre)        Initialisé à 0 (attendre)
                               ou N (N ressources disponibles)
```

### Mémo : I/O bas niveau vs stdio.h

```
BAS NIVEAU (Unix)          stdio.h (standard)
───────────────────────────────────────────────
open()                     fopen()
read()                     fread(), fgetc(), fgets(), fscanf()
write()                    fwrite(), fputc(), fputs(), fprintf()
close()                    fclose()
descripteur de fichier     FILE * (pointeur de flux)
pas de buffer              buffer automatique
```
