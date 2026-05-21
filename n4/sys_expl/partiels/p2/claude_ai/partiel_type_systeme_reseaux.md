# Partiel Type — Système & Réseaux
> **L2 Informatique — Université Sorbonne Paris Nord**
> Durée : 2h — Documents interdits — Calculatrice interdite

---

> **Barème indicatif :** Exercice 1 (10 pts) · Exercice 2 (8 pts) · Exercice 3 (12 pts) · Exercice 4 (10 pts)

---

## Exercice 1 — Arbres de processus (10 points)

On considère le programme suivant :

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int n;
    if (argc != 2 || sscanf(argv[1], "%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid == -1) { perror("fork"); return 1; }
        if (pid == 0) {
            printf("enfant niveau %d\n", i);
            n = i;  // ← modifier n dans l'enfant !
        } else {
            printf("parent niveau %d\n", i);
            wait(NULL);
        }
    }
    printf("fin %d\n", getpid());
    return 0;
}
```

**Question 1 (3 pts)** — Dessiner l'arbre de création des processus pour l'appel `./a.out 3`.
Identifier chaque processus (P0, P1, P2, ...) et préciser, pour chaque processus, quelle valeur de `n` il a lors de l'appel à `fork()`.

**Question 2 (3 pts)** — Pour l'appel `./a.out 3`, lister **toutes** les chaînes affichées (avec leur nombre d'occurrences). Justifier brièvement.

**Question 3 (2 pts)** — Sans la ligne `n = i;` dans le fils, quel serait le nombre total de processus créés pour `./a.out n` quelconque ? Donner la formule en fonction de `n` et la justifier.

**Question 4 (2 pts)** — Le programme tel qu'écrit attend-il les processus fils correctement ? Y a-t-il un risque de zombies ? Justifier.

---

## Exercice 2 — Threads et parallélisation (8 points)

On veut calculer la somme `S = ∑ f(i)` pour `i` allant de `0` à `N-1`, en utilisant `T` threads, où `f` est une fonction donnée qui peut être longue à exécuter.

```c
double f(int i);  // donnée, longue à calculer, sans effet de bord
```

**Question 1 (4 pts)** — Écrire la fonction thread `void *worker(void *arg)` et la structure `struct worker_arg` associée, tels que chaque thread calcule sa part de la somme selon un découpage **interleaved** (le thread `k` calcule `f(k)`, `f(k+T)`, `f(k+2T)`, ...).

Préciser comment chaque thread renvoie son résultat partiel au thread principal via `pthread_join`.

**Question 2 (2 pts)** — Écrire la fonction `main` qui crée les `T` threads, attend leur fin, puis affiche la somme totale. Traiter correctement les erreurs de `pthread_create`.

**Question 3 (2 pts)** — Quel piège classique y a-t-il si on passe `&k` (l'adresse de l'indice de boucle) comme argument à `pthread_create` au lieu d'un struct alloué sur le tas ? Expliquer avec précision pourquoi c'est une race condition.

---

## Exercice 3 — Synchronisation : Le boulanger et les clients (12 points)

Une boulangerie est modélisée par les règles suivantes :

- Il y a **1 boulanger** et **N clients**.
- Le boulanger peut préparer au maximum **CAPACITE** pains à la fois dans son four. Quand le four est plein, il **attend** que tous les pains soient vendus avant d'en préparer d'autres.
- Les clients prennent les pains **un par un** dans le four.
- Plusieurs clients peuvent prendre un pain **simultanément**.
- Le dernier client qui prend le dernier pain du four **réveille** le boulanger.

Le squelette du programme est fourni :

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define CAPACITE 5
#define N 10

int nb_pains = 0;   // nombre de pains actuellement dans le four

// === ZONE D'AJOUT 1 : variables de synchronisation (globales) ===

void *boulanger(void *arg) {
    for (;;) {
        // === ZONE D'AJOUT 2 : attendre que le four soit vide ===
        nb_pains = CAPACITE;
        printf("Boulanger : four rempli (%d pains)\n", nb_pains);
        // === ZONE D'AJOUT 3 : signaler que les pains sont prêts ===
    }
    return NULL;
}

void *client(void *arg) {
    int id = *(int *)arg;
    for (;;) {
        // === ZONE D'AJOUT 4 : prendre un pain ===
        printf("Client %d prend un pain\n", id);
    }
    return NULL;
}

int main(void) {
    // === ZONE D'AJOUT 5 : init des primitives, création des threads ===
    return 0;
}
```

**Question 1 (3 pts)** — Identifier les problèmes de synchronisation à résoudre. Proposer les primitives (mutex, sémaphores) nécessaires avec leurs valeurs initiales et leur rôle exact.

**Question 2 (5 pts)** — Compléter toutes les ZONES D'AJOUT pour obtenir un programme correct. S'assurer que :
- Le boulanger attend que le four soit complètement vide avant de refournir.
- Les clients attendent qu'il y ait des pains disponibles.
- Plusieurs clients peuvent accéder au four en même temps pour prendre leur pain, mais `nb_pains` doit être décrémenté de façon atomique.
- Un seul client réveille le boulanger (le dernier à prendre un pain).

**Question 3 (2 pts)** — Y a-t-il un risque de deadlock dans votre solution ? Justifier.

**Question 4 (2 pts)** — Si on modifie le code pour que le boulanger prépare un seul pain à la fois (CAPACITE = 1), quelle simplification peut-on apporter à la synchronisation ? Réécrire les fonctions `boulanger` et `client` pour ce cas simplifié.

---

## Exercice 4 — Tubes, sérialisation et réseau (10 points)

### Partie A — Tubes et redirections (4 pts)

On donne le code suivant :

```c
int tube[2];
pipe(tube);

pid_t pid = fork();
if (pid == 0) {
    // code fils
    dup2(tube[1], 1);
    // ligne X : close(tube[1]);
    // ligne Y : close(tube[0]);
    execlp("echo", "echo", "hello world", NULL);
    perror("execlp"); exit(1);
}
// code père
close(tube[1]);
char buf[128];
ssize_t n;
while ((n = read(tube[0], buf, sizeof(buf))) > 0)
    write(1, buf, n);
close(tube[0]);
wait(NULL);
```

**Question 1 (2 pts)** — Les lignes X et Y sont-elles nécessaires ? Que se passe-t-il si on les omet (analyser séparément chaque cas) ?

**Question 2 (2 pts)** — Qu'affiche ce programme ? Est-ce que l'affichage est déterministe ? Justifier.

### Partie B — Sérialisation et UDP (6 pts)

On veut envoyer en UDP la structure suivante :

```c
struct message {
    uint8_t  type;       // 1 octet : type du message
    uint16_t longueur;   // 2 octets : longueur du texte qui suit
    char     texte[64];  // jusqu'à 64 caractères
};
```

**Question 3 (2 pts)** — Quel est le `sizeof(struct message)` probable sur une machine x86-64 ? Détailler le calcul du padding. Pourquoi ne peut-on pas envoyer cette struct directement avec `sendto(&msg, sizeof(msg), ...)` ?

**Question 4 (2 pts)** — Écrire la fonction `size_t serialiser(const struct message *msg, uint8_t *buf)` qui sérialise le message dans `buf` (ordre réseau) et retourne le nombre d'octets écrits. Le champ `texte` contient exactement `msg->longueur` caractères (pas de `\0`).

**Question 5 (2 pts)** — Écrire la fonction `void deserialiser(const uint8_t *buf, struct message *msg)` qui effectue l'opération inverse. Traiter correctement l'endianness.

---

## Corrigé

### Exercice 1

**Q1 — Arbre pour `./a.out 3`** (n=3 initialement)

```
P0 (n=3)
  ├─ i=0 : fork() → P1 (fils, n=0 après "n=i")
  │         P1 : sa boucle for ne s'exécute pas (n=0, i<0 faux dès i=0)
  │         P1 affiche : "enfant niveau 0", "fin PID_P1"
  │
  │  P0 (père) attend P1, affiche "parent niveau 0"
  │
  ├─ i=1 : fork() → P2 (fils, n=1 après "n=i")
  │         P2 : boucle avec n=1, i=0 seulement
  │           → fork() → P3 (n=0, n'entre pas dans la boucle)
  │             P3 affiche : "enfant niveau 0", "fin PID_P3"
  │           P2 affiche : "parent niveau 0" puis wait(P3)
  │           P2 affiche : "fin PID_P2"
  │
  │  P0 attend P2, affiche "parent niveau 1"
  │
  └─ i=2 : fork() → P4 (fils, n=2)
            P4 : boucle avec n=2, i=0 puis i=1
              i=0 → fork() → P5 (n=0) → affiche "enfant niveau 0", "fin P5"
              P4 attend P5, affiche "parent niveau 0"
              i=1 → fork() → P6 (n=1) → 1 fork interne (P7), similaire à P2
              P4 attend P6, affiche "parent niveau 1"
              P4 affiche "fin P4"
  P0 attend P4, affiche "parent niveau 2"
  P0 affiche "fin P0"
```

**Q2 — Chaînes affichées** :

| Chaîne | Occurrences | Par qui |
|--------|-------------|---------|
| `"enfant niveau 0"` | 4 | P1, P3, P5, et P7 (ou similaire) |
| `"enfant niveau 1"` | 2 | P2 (quand il était fils), P4 (quand il était fils)... |
| `"parent niveau 0"` | 4 | P0, P2, P4, P6 |
| `"parent niveau 1"` | 2 | P0, P4 |
| `"parent niveau 2"` | 1 | P0 |
| `"fin PIDx"` | 1 par processus | Chaque processus |

> **Note** : l'ordre exact des lignes est non déterministe (concurrence entre père et fils après le fork), mais le contenu global est fixé.

**Q3 — Sans `n = i;`** : chaque processus créé effectue les mêmes `n` itérations de fork. Le nombre total de processus suit `T(n) = 2^n` (arbre binaire complet).

**Q4** : Oui, le programme gère les zombies correctement. Chaque père appelle `wait(NULL)` après chaque `fork()`, ce qui collecte immédiatement l'état du fils. Pas de risque de zombie.

---

### Exercice 2

**Q1 — Structure et fonction thread :**

```c
struct worker_arg {
    int    id;       // indice du thread (0 à T-1)
    int    n;        // taille totale
    int    t;        // nombre de threads
    double resultat; // résultat partiel (rempli par le thread)
};

void *worker(void *arg) {
    struct worker_arg *wa = (struct worker_arg *)arg;
    wa->resultat = 0.0;
    for (int k = wa->id; k < wa->n; k += wa->t)
        wa->resultat += f(k);
    return NULL;  // la valeur se récupère via wa->resultat après pthread_join
}
```

**Q2 — main :**

```c
int main(void) {
    int n = 1000000, t = 8;
    pthread_t threads[t];
    struct worker_arg args[t];

    for (int i = 0; i < t; i++) {
        args[i] = (struct worker_arg){.id = i, .n = n, .t = t, .resultat = 0.0};
        if (pthread_create(&threads[i], NULL, worker, &args[i]) != 0) {
            perror("pthread_create"); return 1;
        }
    }

    double total = 0.0;
    for (int i = 0; i < t; i++) {
        pthread_join(threads[i], NULL);
        total += args[i].resultat;
    }

    printf("Somme = %g\n", total);
    return 0;
}
```

**Q3 — Piège avec `&k`** : la variable `k` de la boucle est modifiée à chaque itération avant que le thread créé ait eu le temps de lire sa valeur. Si le thread 0 n'a pas encore exécuté `wa->id = *(int*)arg` quand la boucle passe à `k=1`, le thread 0 lira `1` au lieu de `0`. Plusieurs threads peuvent recevoir la même valeur de `k` ou des valeurs incorrectes. C'est une **race condition** car l'accès à `k` depuis le thread et la modification dans main ne sont pas synchronisés.

---

### Exercice 3

**Q1 — Primitives :**

```
sem_t pain_dispo    : init = 0      → clients attendent qu'il y ait des pains
sem_t four_vide     : init = 1      → boulanger attend que le four soit vide (commence libre)
pthread_mutex_t mut : init = libre  → protège nb_pains lors de la décrémentation
```

**Q2 — Solution complète :**

```c
// ZONE D'AJOUT 1
sem_t pain_dispo;
sem_t four_vide;
pthread_mutex_t mut;

// boulanger (ZONE D'AJOUT 2 et 3)
void *boulanger(void *arg) {
    for (;;) {
        sem_wait(&four_vide);           // attend que le four soit complètement vide
        nb_pains = CAPACITE;
        printf("Boulanger : four rempli (%d pains)\n", nb_pains);
        for (int i = 0; i < CAPACITE; i++)
            sem_post(&pain_dispo);      // signale CAPACITE pains disponibles
    }
    return NULL;
}

// client (ZONE D'AJOUT 4)
void *client(void *arg) {
    int id = *(int *)arg;
    for (;;) {
        sem_wait(&pain_dispo);          // attend qu'il y ait un pain
        pthread_mutex_lock(&mut);
        --nb_pains;
        int est_vide = (nb_pains == 0);
        pthread_mutex_unlock(&mut);
        if (est_vide)
            sem_post(&four_vide);       // réveille le boulanger
        printf("Client %d prend un pain\n", id);
    }
    return NULL;
}

// main (ZONE D'AJOUT 5)
int main(void) {
    sem_init(&pain_dispo, 0, 0);
    sem_init(&four_vide,  0, 1);
    pthread_mutex_init(&mut, NULL);

    pthread_t boul, clients[N];
    pthread_create(&boul, NULL, boulanger, NULL);
    int ids[N];
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&clients[i], NULL, client, &ids[i]);
    }
    pthread_join(boul, NULL);
    for (int i = 0; i < N; i++) pthread_join(clients[i], NULL);

    sem_destroy(&pain_dispo);
    sem_destroy(&four_vide);
    pthread_mutex_destroy(&mut);
    return 0;
}
```

**Q3 — Deadlock** : Non. Le boulanger n'acquiert jamais le mutex. Les clients acquièrent le mutex brièvement pour décrémenter `nb_pains`, mais ne font jamais `sem_wait` sous mutex. Il ne peut pas y avoir de cycle d'attente.

**Q4 — CAPACITE = 1** : on n'a plus besoin de compter les pains ni du mutex. Un seul sémaphore suffit pour la synchronisation :

```c
sem_t echange;  // init = 0

void *boulanger(void *arg) {
    for (;;) {
        sem_wait(&four_vide_ou_sem);  // simplifié : un seul pain
        printf("Boulanger prépare un pain\n");
        sem_post(&pain_dispo);
    }
}
void *client(void *arg) {
    for (;;) {
        sem_wait(&pain_dispo);
        sem_post(&four_vide_ou_sem);  // four "vide" après 1 pain pris
        printf("Client prend le pain\n");
    }
}
// (avec 2 sémaphores : pain_dispo init=0, four_libre init=1)
```

---

### Exercice 4

**Q1 — Lignes X et Y :**

- **Sans la ligne X** (`close(tube[1])` dans le fils) : après `execlp("echo", ...)`, `echo` hérite du fd `tube[1]` ouvert (via le mapping dup2 : fd 1 = tube[1]). Mais `tube[1]` *en tant que fd original* est aussi ouvert dans le fils. Après `execlp`, le processus a `stdout = tube[1]` (via dup2) et aussi `tube[1]` directement. Quand `echo` ferme stdout (fd 1), `tube[1]` reste ouvert. Cela dit, `echo` se termine et ferme tous ses fd → pas de problème pratique ici. En général c'est une bonne pratique de fermer tube[1] pour éviter des fuites de descripteurs.

- **Sans la ligne Y** (`close(tube[0])`) : le fils garde le côté lecture du tube ouvert. Ce n'est pas catastrophique ici (echo n'écrit pas), mais c'est une fuite de descripteur.

**Q2** : Le programme affiche `hello world\n`. L'affichage est **déterministe** quant au contenu : `echo` écrit exactement `"hello world\n"` dans le tube, le père lit tout et l'écrit sur stdout. L'ordre n'est pas un problème car le père attend d'abord la fin de la lecture avant d'appeler `wait`.

**Q3 — sizeof et padding :**

```
struct message :
  type      : uint8_t  → 1 octet, offset 0
  (padding) : 1 octet  (uint16_t s'aligne sur 2)
  longueur  : uint16_t → 2 octets, offset 2
  texte     : char[64] → 64 octets, offset 4
Total : 1 + 1 (padding) + 2 + 64 = 68 octets

sizeof(struct message) = 68 (pas 67 !)
```

On ne peut pas envoyer directement la struct car le byte de padding (offset 1) contient une valeur indéterminée (donnée aléatoire de la pile). Sur une machine big-endian (ou différente architecture), `uint16_t longueur` serait interprété différemment. De plus, le padding constitue une fuite d'information mémoire.

**Q4 — Sérialisation :**

```c
size_t serialiser(const struct message *msg, uint8_t *buf) {
    uint8_t *p = buf;

    *p++ = msg->type;                         // 1 octet, pas de conversion

    uint16_t lon = htons(msg->longueur);
    memcpy(p, &lon, 2);   p += 2;            // 2 octets big-endian

    memcpy(p, msg->texte, msg->longueur);    // longueur caractères
    p += msg->longueur;

    return (size_t)(p - buf);  // = 3 + longueur octets
}
```

**Q5 — Désérialisation :**

```c
void deserialiser(const uint8_t *buf, struct message *msg) {
    const uint8_t *p = buf;

    msg->type = *p++;                         // 1 octet

    uint16_t lon;
    memcpy(&lon, p, 2);   p += 2;
    msg->longueur = ntohs(lon);               // convertir depuis big-endian

    memcpy(msg->texte, p, msg->longueur);    // copier les caractères
    if (msg->longueur < 64)
        msg->texte[msg->longueur] = '\0';    // ajouter \0 si possible
}
```

---

*Fin du partiel type.*
