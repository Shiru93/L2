# Système & Réseaux — Fiches de révision
**L2 Informatique — Université Sorbonne Paris Nord | Pierre Rousselin**

---

## Table des matières

- [AE0 — C, Binaire, Mémoire et Pointeurs](#ae0--c-binaire-mémoire-et-pointeurs)
- [AE1 — Noyau, Processus et fork()](#ae1--noyau-processus-et-fork)
- [AE2 — Signaux, wait() et exec()](#ae2--signaux-wait-et-exec)
- [AE3 — void\*, Pointeurs de fonctions et Threads](#ae3--void-pointeurs-de-fonctions-et-threads)
- [AE4 — Structures, Concurrence et Sémaphores](#ae4--structures-concurrence-et-sémaphores)
- [AE5 — Mutex, Deadlocks et Problèmes classiques](#ae5--mutex-deadlocks-et-problèmes-classiques)
- [AE6 — Entrées/Sorties Unix](#ae6--entréessorties-unix)
- [Résumé de cours par thème](#résumé-de-cours-par-thème)

---

## AE0 — C, Binaire, Mémoire et Pointeurs
*Après le CM0 et avant le TP0*

### Q1 — Comment écrire en C, compiler et exécuter un Hello, World! ?

1. Créer un fichier `hello.c` :

```c
#include <stdio.h>

int main(void) {
    printf("Hello, World!\n");
    return 0;
}
```

2. Compiler :

```bash
gcc -Wall -Wextra -o hello hello.c
```

3. Exécuter :

```bash
./hello
```

> **Prérequis :** GCC installé. Sur Ubuntu/Debian : `sudo apt install gcc`. Sur macOS : `xcode-select --install`.

---

### Q2 — Quel éditeur de texte utiliser ?

Pas de mauvaise réponse. L'important est d'en connaître un.

- **Sur sa propre machine :** VS Code (recommandé), CLion, Eclipse, Vim/Neovim, Emacs…
- **En salle TP :** VS Code, `nano` (simple), `gedit` (graphique)

---

### Q3 — Drapeaux de compilation indispensables et conseillés ?

**Indispensables :**

```bash
gcc -std=c99 -o mon_prog mon_prog.c
```

- `-std=c99` (ou `-std=c11`) : impose le standard C99/C11, requis pour les types `int32_t` etc.

**Fortement conseillés :**

```bash
gcc -Wall -Wextra -g -std=c99 -o mon_prog mon_prog.c
```

| Drapeau | Rôle |
|---------|------|
| `-Wall` | Active la plupart des avertissements utiles |
| `-Wextra` | Avertissements supplémentaires |
| `-g` | Infos de débogage (GDB, Valgrind) |
| `-Werror` | (Optionnel) Traite les warnings comme des erreurs |

> **Règle d'or :** Compiler toujours avec `-Wall -Wextra -g`. Les warnings sont presque toujours des bugs.

---

### Q4 — Comment utiliser Valgrind ?

**Rôle :** Détection dynamique d'erreurs mémoire — fuites, accès hors limites, lecture de mémoire non initialisée, double free.

```bash
# Compiler avec -g d'abord
gcc -Wall -Wextra -g -o mon_prog mon_prog.c

# Lancer avec valgrind
valgrind --leak-check=full ./mon_prog [arguments]
```

> **Note :** Valgrind ralentit l'exécution d'un facteur 10 à 50×, c'est normal.

---

### Q5 — Bit et octet ?

- **Bit :** unité d'information la plus petite, vaut 0 ou 1.
- **Octet (byte) :** groupe de 8 bits. Unité d'adressage standard en mémoire.

---

### Q6 — Que signifie « la machine est byte addressable » ?

Chaque octet en mémoire possède une **adresse unique**. Le plus petit élément adressable est l'octet (pas le bit, pas un mot de 4 octets).

---

### Q7 — Entiers signés vs non signés ?

| Type | Valeurs | Sur 32 bits |
|------|---------|-------------|
| **Signé** | Positifs ET négatifs (complément à 2) | −2 147 483 648 à +2 147 483 647 |
| **Non signé** | Positifs uniquement | 0 à 4 294 967 295 |

En C, les entiers sont signés par défaut (sauf `char` qui dépend de la machine).

---

### Q8 — Taille d'un char ? Signé ou non signé ?

- **Taille :** toujours **1 octet (8 bits)** — garanti par la norme C.
- **Signe :** **dépend de la machine et du compilateur**. Sur x86/x86-64 avec GCC, `char` est signé. Sur certains ARM, non signé.

Pour lever l'ambiguïté : utiliser `signed char` ou `unsigned char` explicitement.

---

### Q9 — Taille d'un int ? Signé ou non signé ?

- **Taille :** généralement **4 octets (32 bits)** sur les architectures modernes. La norme garantit seulement ≥ 16 bits.
- **Signe :** `int` est **signé par défaut**. Pour non signé : `unsigned int`.

> Pour une taille garantie : utiliser `int32_t`, `uint32_t` depuis `<stdint.h>`.

---

### Q10 — Nombre de valeurs sur 8, 16, 32 bits ?

| Bits | Valeurs | Détail |
|------|---------|--------|
| 8 bits | **256** | 2⁸ |
| 16 bits | **65 536** | 2¹⁶ |
| 32 bits | **4 294 967 296 ≈ 4 milliards** | 2³² |
| 64 bits | ≈ 1,8 × 10¹⁹ | 2⁶⁴ |

---

### Q11 — Puissances de 2 jusqu'à 2¹⁰ ?

```
2⁰ = 1      2¹ = 2      2² = 4      2³ = 8
2⁴ = 16     2⁵ = 32     2⁶ = 64     2⁷ = 128
2⁸ = 256    2⁹ = 512    2¹⁰ = 1024 ≈ 10³
```

---

### Q12 — Estimer une grande puissance de 2 ?

Utiliser l'approximation **2¹⁰ ≈ 10³** :

```
2³² = (2¹⁰)³ × 2² ≈ (10³)³ × 4 = 4 × 10⁹  (4 milliards)
2²⁰ = (2¹⁰)² ≈ (10³)² = 10⁶                 (1 million = 1 méga)
2³⁰ ≈ (10³)³ = 10⁹                            (1 giga)
```

---

### Q13 — Convertir décimal → binaire / hexadécimal ?

**Décimal → Binaire :** divisions euclidiennes par 2, lire les restes de bas en haut.

```
13 ÷ 2 = 6  reste 1
 6 ÷ 2 = 3  reste 0
 3 ÷ 2 = 1  reste 1
 1 ÷ 2 = 0  reste 1
→ 13 = 0b1101
```

**Décimal → Hexadécimal :** divisions par 16. Restes 10–15 = A–F.

```
255 ÷ 16 = 15  reste 15 (F)
 15 ÷ 16 = 0   reste 15 (F)
→ 255 = 0xFF
```

---

### Q14 — Passage binaire ↔ hexadécimal ?

**Binaire → Hexa :** regrouper par 4 bits en partant de la droite.

```
10110101 = 1011 | 0101 = B | 5 = 0xB5
```

**Hexa → Binaire :** chaque chiffre hexa = 4 bits.

```
0x3F = 0011 1111
```

**Table à mémoriser :**

```
0=0000  1=0001  2=0010  3=0011  4=0100  5=0101  6=0110  7=0111
8=1000  9=1001  A=1010  B=1011  C=1100  D=1101  E=1110  F=1111
```

---

### Q15 — Types entiers à taille fixe en C99 ?

Définis dans `<stdint.h>` :

```c
// Signés
int8_t   int16_t   int32_t   int64_t

// Non signés
uint8_t  uint16_t  uint32_t  uint64_t

// Pour stocker un pointeur
intptr_t   uintptr_t

// Taille maximale disponible
intmax_t   uintmax_t
```

> **Bonne pratique :** préférer `int32_t` à `int` quand la taille exacte compte (protocoles réseau, fichiers binaires).

---

### Q16 — Boutisme (endianness) ?

Le boutisme définit l'ordre dans lequel les octets d'un entier multi-octets sont stockés en mémoire.

Exemple : `0x12345678` stocké à l'adresse 0x1000 :

```
Adresse :       0x1000   0x1001   0x1002   0x1003

Little-endian (x86, x86-64) :
                0x78     0x56     0x34     0x12
                ↑ octet de poids FAIBLE en premier

Big-endian (réseau, certains ARM) :
                0x12     0x34     0x56     0x78
                ↑ octet de poids FORT en premier
```

> **Importance :** crucial lors des communications réseau (réseau = big-endian). Fonctions de conversion : `htons()`, `ntohl()`, etc.

---

### Q17 — Opérateurs `&` et `*` sur les pointeurs ?

- `&x` : opérateur **adresse de** — retourne l'adresse mémoire de `x`.
- `*p` : opérateur de **déréférencement** — accède à la valeur pointée par `p`.

```c
int x = 42;
int *p = &x;   // p contient l'adresse de x
*p = 100;      // modifie x via p → x vaut 100
printf("%d\n", x); // affiche 100
```

> `*` dans une **déclaration** = "pointeur vers". `*` dans une **expression** = "déréférencer".

---

## AE1 — Noyau, Processus et fork()
*Après le CM1*

### Q1 — Rôles principaux du noyau ?

Le noyau (kernel) s'exécute en mode **privilégié**. Ses rôles :

- **Gestion des processus :** création, ordonnancement, terminaison
- **Gestion de la mémoire :** allocation, protection, mémoire virtuelle
- **Gestion des E/S :** pilotes de périphériques, abstraction matérielle
- **Système de fichiers :** organisation, accès, protection
- **Communication inter-processus (IPC) :** signaux, pipes, sockets…
- **Sécurité :** espace utilisateur vs espace noyau, permissions

---

### Q2 — Qu'est-ce qu'un appel système ? Exemples ?

Un **appel système (syscall)** = interface par laquelle un programme demande un service au noyau via une interruption logicielle. Consultables avec `man 2`.

| Catégorie | Exemples |
|-----------|---------|
| Processus | `fork()`, `execve()`, `exit()`, `wait()`, `getpid()` |
| Fichiers | `open()`, `read()`, `write()`, `close()` |
| Mémoire | `mmap()`, `brk()` |
| Signaux | `kill()`, `sigaction()` |
| Réseau | `socket()`, `bind()`, `connect()` |

---

### Q3 — Sections 2 et 3 du manuel ?

- **Section 2 :** appels système (`man 2 fork`, `man 2 open`…)
- **Section 3 :** fonctions de la bibliothèque C standard (`man 3 printf`, `man 3 malloc`…)

```bash
man 2 fork    # appel système
man 3 printf  # fonction stdlib
```

---

### Q4 — Qu'est-ce qu'un processus ? Identifiant ? Attributs ?

Un **processus** = programme en cours d'exécution avec son propre espace mémoire et ses ressources.

**Identifiant :** le **PID** (Process IDentifier), entier unique.

**Attributs principaux :** PID, PPID, UID/GID, espace d'adressage, table des fd ouverts, répertoire courant, variables d'environnement, état (running/sleeping/zombie), priorité.

---

### Q5 — Chercher le PID d'un processus ?

```bash
ps aux              # liste tous les processus
ps aux | grep nom   # filtrer par nom
pgrep nom           # PID par nom de programme
pidof nom           # PID d'un exécutable
top / htop          # vue dynamique
```

Avec le PID : envoyer un signal (`kill -SIGTERM 1234`), attacher un débogueur (`gdb -p 1234`), inspecter via `/proc/1234/`.

---

### Q6 — Instruction switch en C ?

```c
switch (expression) {
    case valeur1:
        // instructions
        break;       // évite le fall-through
    case valeur2:
    case valeur3:    // deux cas pour la même action
        // instructions
        break;
    default:
        // cas par défaut
        break;
}
```

> **Piège :** oublier un `break` provoque un "fall-through" silencieux. Option `-Wimplicit-fallthrough` pour être averti.

---

### Q7 — fork() : valeur de retour et gestion d'erreur ?

```c
pid_t pid = fork();

if (pid == -1) {
    perror("fork");   // ERREUR
} else if (pid == 0) {
    // Code du FILS (fork retourne 0 au fils)
    printf("Fils, mon PID = %d\n", getpid());
} else {
    // Code du PÈRE (fork retourne le PID du fils)
    printf("Père, j'ai créé le fils PID = %d\n", pid);
}
```

**Valeurs de retour :** `0` → fils | PID du fils → père | `−1` → erreur.

---

### Q8 — Arborescence des processus ?

Chaque processus a un parent. `fork()` crée une relation parent-enfant, formant une **arborescence**. Racine : `systemd` / `init` (PID 1). Visualiser avec `pstree`.

---

### Q9 — Arguments d'un processus ?

```c
int main(int argc, char *argv[]) {
    // argc = nombre d'arguments (nom du prog inclus)
    // argv[0] = nom du programme
    // argv[1..argc-1] = arguments
    // argv[argc] = NULL

    for (int i = 0; i < argc; i++)
        printf("argv[%d] = %s\n", i, argv[i]);
}
```

Exemple : `./prog hello 42` → argc=3, argv=`{"./prog", "hello", "42", NULL}`.

---

### Q10 — Environnement d'un processus ?

Ensemble de variables `NOM=valeur` (ex : `PATH`, `HOME`, `USER`).

```c
#include <stdlib.h>

// Méthode 1 : getenv (la plus simple)
char *path = getenv("PATH");

// Méthode 2 : 3ème paramètre de main
int main(int argc, char *argv[], char *envp[]) { ... }

// Méthode 3 : variable globale
extern char **environ;
```

---

### Q11 — Obtenir son PID et celui de son parent ?

```c
#include <unistd.h>

pid_t mon_pid    = getpid();   // PID du processus courant
pid_t pid_parent = getppid();  // PID du processus parent
```

Ces deux fonctions ne retournent jamais d'erreur.

---

## AE2 — Signaux, wait() et exec()
*Après le CM2*

### Q1 — perror et errno ?

- **`errno`** (dans `<errno.h>`) : variable globale contenant le **code d'erreur du dernier appel système échoué**. Significative uniquement si l'appel a retourné −1.
- **`perror(msg)`** : affiche `msg: message_d_erreur` sur stderr en utilisant `errno`.

```c
int fd = open("fichier.txt", O_RDONLY);
if (fd == -1) {
    perror("Erreur open");
    // Affiche : "Erreur open: No such file or directory"
    exit(1);
}
```

> **Règle :** toujours vérifier la valeur de retour des appels système.

---

### Q2 — Pourquoi utiliser des arguments pointeurs ?

En C, les arguments sont passés **par valeur** (copie). Un pointeur en argument permet :

- **Modifier la variable de l'appelant** (passage par référence) :

```c
void incrementer(int *x) { (*x)++; }
int n = 5;
incrementer(&n);  // n vaut 6
```

- **Retourner plusieurs valeurs** via plusieurs pointeurs
- **Efficacité** : passer l'adresse d'une grande structure plutôt que de la copier

---

### Q3 — Mot-clé pour argument pointeur en lecture seule ?

Le mot-clé **`const`** :

```c
void afficher(const char *s) {
    printf("%s\n", s);
    // s[0] = 'X'; // ERREUR de compilation
}
```

Avantages : documentation de l'intention, détection d'erreurs à la compilation, compatibilité avec les chaînes littérales.

---

### Q4 — Qui peut envoyer un signal ?

- Le processus lui-même (`raise(SIGTERM)`)
- Un autre processus du même utilisateur (`kill()`)
- Le superutilisateur (root) — peut envoyer à n'importe quel processus
- Le noyau (SIGSEGV, SIGFPE, SIGCHLD…)
- Le terminal (Ctrl+C → SIGINT, Ctrl+Z → SIGTSTP, Ctrl+\ → SIGQUIT)

---

### Q5 — Actions possibles à la réception d'un signal ?

- **Terminer** le processus (action par défaut de nombreux signaux)
- **Ignorer** le signal (`SIG_IGN`) — impossible pour SIGKILL et SIGSTOP
- **Exécuter un handler personnalisé** (via `signal()` ou `sigaction()`)
- **Suspendre** le processus (SIGSTOP, SIGTSTP)
- **Reprendre** un processus suspendu (SIGCONT)
- **Générer un core dump** (SIGQUIT, SIGSEGV…)

---

### Q6 — Prototype de kill ?

```c
#include <signal.h>

int kill(pid_t pid, int sig);
```

- `pid` : PID du processus destinataire
- `sig` : signal à envoyer (SIGTERM, SIGKILL, SIGUSR1…)
- **Retour :** 0 si succès, −1 si erreur

```c
kill(pid_fils, SIGTERM);  // terminaison douce
kill(pid_fils, SIGKILL);  // terminaison forcée (ne peut être bloquée)
kill(pid_fils, 0);        // vérifie l'existence du processus
```

---

### Q7 — waitpid : utilisation et valeur de retour ?

```c
#include <sys/wait.h>

pid_t waitpid(pid_t pid, int *status, int options);
```

- `pid = -1` : attendre n'importe quel enfant
- `options = 0` : bloquant | `WNOHANG` : non bloquant
- **Retour :** PID de l'enfant terminé, ou −1 si erreur

```c
int status;
pid_t mort = waitpid(-1, &status, 0);

if (WIFEXITED(status))
    printf("Code de sortie: %d\n", WEXITSTATUS(status));
if (WIFSIGNALED(status))
    printf("Tué par signal: %d\n", WTERMSIG(status));
```

`wait(&status)` ≡ `waitpid(-1, &status, 0)`.

---

### Q8 — exec : comment l'utiliser ? Qu'arrive-t-il à l'ancien programme ?

`exec()` **remplace l'image mémoire** du processus courant par un nouveau programme (même PID, nouveau code/données/pile).

```c
execl("/bin/ls", "ls", "-l", NULL);
// Si succès → cette ligne n'est JAMAIS atteinte
perror("execl a échoué");
```

**Conservé :** PID, PPID, descripteurs de fichiers, environnement.  
**Remplacé :** tout le programme précédent.

---

### Q9 — PATH ? Différence execlp vs execl ?

**PATH :** variable d'environnement listant les répertoires où chercher les exécutables (`/usr/bin:/bin:/usr/local/bin`…).

| Fonction | Recherche dans PATH ? | Syntaxe arguments |
|----------|----------------------|-------------------|
| `execl` | ❌ chemin absolu requis | individuels |
| `execlp` | ✅ oui | individuels |
| `execv` | ❌ chemin absolu requis | tableau |
| `execvp` | ✅ oui | tableau |

---

### Q10 — Différence execv vs execl ?

```c
// execl : arguments listés un par un
execl("/bin/ls", "ls", "-l", "-a", NULL);

// execv : arguments dans un tableau
char *args[] = {"ls", "-l", "-a", NULL};
execv("/bin/ls", args);
```

`execv` est plus pratique quand le nombre d'arguments est variable.

---

### Q11 — Raisons d'échec d'un exec ?

- Fichier inexistant (`ENOENT`)
- Pas les droits d'exécution (`EACCES`)
- Format d'exécutable invalide (`ENOEXEC`)
- Trop d'arguments (`E2BIG`)
- Manque de mémoire (`ENOMEM`)
- Chemin trop long (`ENAMETOOLONG`)

---

### Q12 — Processus zombie ?

Un **zombie** = processus terminé dont le père n'a pas encore appelé `wait()`. Il ne consomme plus de CPU ni de mémoire significative, mais son entrée dans la table des processus persiste.

```c
// Pour éviter les zombies :
signal(SIGCHLD, SIG_IGN);             // ignorer SIGCHLD
// ou appeler waitpid() dans un gestionnaire de SIGCHLD
```

> Si le père meurt sans `wait()`, les enfants zombies sont adoptés par `init` (PID 1) qui les nettoie.

---

## AE3 — void*, Pointeurs de fonctions et Threads
*Après le CM3*

### Q1 — Qu'est-ce qu'un void* ? 3 exemples ?

`void *` = **pointeur générique** pouvant pointer vers n'importe quel type.

**3 exemples dans la stdlib :**

```c
void *malloc(size_t size);
void *memcpy(void *dest, const void *src, size_t n);
void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void*, const void*));
```

---

### Q2 — Quand utiliser void* ?

- Écrire une **fonction générique** indépendante du type
- Passer des données à un thread (`pthread_create`)
- Stocker des pointeurs de types différents dans une même structure
- Implémenter des structures de données génériques (liste, arbre…)

---

### Q3 — Ce qu'on NE peut PAS faire avec void* ?

- ❌ **Déréférencer** : `*p` interdit (taille inconnue)
- ❌ **Arithmétique de pointeur** : `p + 1` interdit
- ❌ **Accès à des champs** : `p->champ` interdit

Il faut d'abord caster :

```c
void *p = malloc(sizeof(int));
*(int *)p = 42;    // cast puis déréférencement : OK
```

---

### Q4 — Quand écrire explicitement un cast entre pointeurs ?

**En C :**
- `void *` ↔ tout autre pointeur : **implicite** (pas de cast nécessaire)
- Pointeur type A → pointeur type B différent : **cast explicite obligatoire**

```c
int *p = malloc(sizeof(int));   // implicite : OK en C

int x = 42;
char *c = (char *)&x;   // cast explicite nécessaire
```

> **Attention :** caster des types incompatibles peut violer les règles d'aliasing strict → comportement indéfini.

---

### Q5 — Déclarer un paramètre de type pointeur de fonction ?

Syntaxe : `type_retour (*nom)(type_param1, type_param2)`

```c
// Paramètre pointeur de fonction
void trier(int *tab, int n, int (*comparer)(int, int));

// Avec typedef (plus lisible)
typedef int (*t_comparateur)(int, int);
void trier(int *tab, int n, t_comparateur comparer);
```

---

### Q6 — (Bonus) Fonction retournant un pointeur de fonction ?

```c
// Sans typedef (difficile à lire)
int (*get_operation(char op))(int, int);

// Avec typedef (recommandé)
typedef int (*t_op)(int, int);
t_op get_operation(char op) {
    if (op == '+') return addition;
    if (op == '*') return multiplication;
    return NULL;
}
```

---

### Q7 — Appeler une fonction via un pointeur (2 syntaxes) ?

```c
int (*f)(int, int) = addition;

int r1 = (*f)(3, 4);  // Syntaxe 1 : déréférencement explicite
int r2 = f(3, 4);     // Syntaxe 2 : appel direct (plus courante)
```

---

### Q8 — Affecter l'adresse d'une fonction (2 syntaxes) ?

```c
int (*f)(int, int);

f = &addition;   // Syntaxe 1 : avec &
f = addition;    // Syntaxe 2 : sans & (implicite, préférée)
```

---

### Q9 — Créer un thread ?

```c
#include <pthread.h>

int pthread_create(pthread_t *tid,
                   const pthread_attr_t *attr,
                   void *(*start_routine)(void *),
                   void *arg);
```

- `tid` : identifiant du thread (sortie)
- `attr` : attributs (`NULL` = défaut)
- `start_routine` : fonction du thread, type `void *(*)(void *)`
- `arg` : argument passé à la fonction (`void *`)
- **Retour :** 0 si succès

```c
void *ma_fonction(void *arg) {
    int n = *(int *)arg;
    printf("Reçoit : %d\n", n);
    return NULL;
}

pthread_t tid;
int valeur = 42;
pthread_create(&tid, NULL, ma_fonction, &valeur);
// Compiler avec : gcc ... -lpthread
```

---

### Q10 — Attendre la fin d'un thread ?

```c
int pthread_join(pthread_t tid, void **retval);
```

```c
void *retour;
pthread_join(tid, &retour);  // bloque jusqu'à la fin du thread
```

---

### Q11 — Différence processus fils vs thread (mémoire) ?

| | Processus fils (fork) | Thread |
|---|---|---|
| **Mémoire** | Copie **indépendante** (COW) | **Partagée** avec le créateur |
| **Variables globales** | Modifications isolées | Visibles par tous les threads |
| **Synchronisation** | Non nécessaire pour sa mémoire | **Obligatoire** (mutex, sémaphores) |
| **Coût création** | Plus élevé | Plus faible |

---

## AE4 — Structures, Concurrence et Sémaphores
*Après le CM4*

### Q1 — Initialiser une structure (C90 et C99) ?

```c
struct Point { int x; int y; float z; };

// C90 : positional (ordre obligatoire)
struct Point p1 = {1, 2, 3.0f};

// C99 : designated initializers (recommandé)
struct Point p2 = {.x = 1, .y = 2, .z = 3.0f};

// Partielle : champs non mentionnés → zéro-initialisés
struct Point p3 = {.x = 5};  // y=0, z=0.0f
```

---

### Q2 — (Optionnel) Passer une structure sans variable intermédiaire ?

Avec les **littéraux composés (compound literals)** de C99 :

```c
void afficher(struct Point p) { ... }

// Sans compound literal
struct Point tmp = {3, 4};
afficher(tmp);

// Avec compound literal C99
afficher((struct Point){.x = 3, .y = 4});
```

---

### Q3 — Qu'est-ce que l'indéterminisme ?

Un programme est **indéterministe** si son résultat peut **varier d'une exécution à l'autre** pour les mêmes entrées.

**Sources :** ordonnancement des threads, interruptions matérielles, variables non initialisées, accès concurrents non synchronisés.

---

### Q4 — Race condition ?

Survient quand deux tâches accèdent à une ressource partagée de façon concurrente et que le **résultat dépend de l'ordre d'exécution**.

```c
int compteur = 0;

void *incrementer(void *arg) {
    for (int i = 0; i < 100000; i++)
        compteur++;   // race condition ! (non atomique)
    return NULL;
}
```

**Entre processus :** fichiers partagés, mémoire partagée.  
**Entre threads :** toute variable globale ou sur le tas accessible sans synchronisation.

---

### Q5 — Appel système bloquant ? Exemples ?

Un **appel bloquant** suspend le processus jusqu'à ce que l'opération soit possible (état "sleeping", CPU libéré).

**Exemples :** `read()` sur terminal/pipe vide, `wait()`/`waitpid()`, `sem_wait()`, `accept()`, `pthread_join()`, `sleep()`.

---

### Q6 — Instruction atomique ?

Une instruction **atomique** est indivisible : s'exécute entièrement ou pas du tout, sans interruption.

```c
x++;  // NON atomique ! Compile en :
      // 1. LOAD  x → registre
      // 2. ADD   registre + 1
      // 3. STORE registre → x
```

Solutions : mutex, sémaphores, ou `<stdatomic.h>` (C11).

---

### Q7 — Initialiser un sémaphore anonyme ?

```c
#include <semaphore.h>

int sem_init(sem_t *sem, int pshared, unsigned int value);
```

- `pshared = 0` : entre threads du même processus
- `pshared ≠ 0` : entre processus (mémoire partagée requise)
- `value` : valeur initiale du compteur

```c
sem_t s;
sem_init(&s, 0, 1);  // sémaphore binaire pour threads
```

---

### Q8 — Détruire un sémaphore ?

```c
int sem_destroy(sem_t *sem);
```

> **Attention :** détruire un sémaphore sur lequel des threads sont bloqués = comportement indéfini.

---

### Q9 — sem_wait et sem_post ?

```c
// P(s) — "prendre" / attendre
int sem_wait(sem_t *sem);
// compteur > 0 : décrémente et continue
// compteur == 0 : BLOQUE

// V(s) — "libérer" / signaler
int sem_post(sem_t *sem);
// Incrémente et réveille un thread bloqué (s'il y en a)
```

---

## AE5 — Mutex, Deadlocks et Problèmes classiques
*Après le CM5*

### Q1 — Section critique ?

Portion de code accédant à une **ressource partagée** qui **ne peut être exécutée que par un thread à la fois**.

```c
pthread_mutex_lock(&mutex);
/* --- DÉBUT section critique --- */
compteur++;
/* --- FIN section critique --- */
pthread_mutex_unlock(&mutex);
```

Propriétés souhaitées : exclusion mutuelle, absence de deadlock, absence de famine, efficacité.

---

### Q2 — Mutex : créer, verrouiller, déverrouiller, détruire ?

```c
#include <pthread.h>

pthread_mutex_t m;

// Initialiser
pthread_mutex_init(&m, NULL);
// Ou statiquement :
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_lock(&m);     // Verrouiller (bloque si pris)
/* section critique */
pthread_mutex_unlock(&m);   // Déverrouiller

pthread_mutex_destroy(&m);  // Détruire
```

---

### Q3 — Contraintes mutex vs sémaphore binaire ?

Contrainte supplémentaire : le mutex **doit être déverrouillé par le même thread qui l'a verrouillé**.

De plus, un mutex est **non récursif par défaut** : re-verrouiller un mutex déjà tenu par le même thread = deadlock (sauf `PTHREAD_MUTEX_RECURSIVE`).

---

### Q4 — Transmettre l'adresse d'un mutex à un thread (3 cas) ?

**a) Mutex global :**
```c
pthread_mutex_t mutex_global;  // accessible directement
```

**b) Mutex dans la pile de main :**
```c
int main() {
    pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
    pthread_create(&tid, NULL, thread_fn, &m);  // passer &m
}
```

**c) Mutex sur le tas dans une structure :**
```c
typedef struct {
    pthread_mutex_t mutex;
    int compteur;
} t_shared;

t_shared *d = malloc(sizeof(*d));
pthread_mutex_init(&d->mutex, NULL);
pthread_create(&tid, NULL, thread_fn, d);
```

---

### Q5 — Problème des philosophes ?

5 philosophes autour d'une table, 5 fourchettes (une entre chaque paire). Pour manger, un philosophe a besoin des **deux fourchettes adjacentes**.

Si chacun prend la fourchette à sa gauche et attend celle à droite → **deadlock !**

**Solutions :** numéroter les fourchettes et les prendre dans l'ordre croissant, ou limiter à N−1 philosophes pouvant tenter de manger simultanément.

---

### Q6 — Deadlock (étreinte mortelle) ?

Situation où deux threads (ou plus) se bloquent **mutuellement** en attendant des ressources que l'autre détient.

```c
// Thread A          // Thread B
lock(mutex1);       lock(mutex2);
lock(mutex2); ←→   lock(mutex1);
// Deadlock !
```

**4 conditions de Coffman** (toutes nécessaires) :
1. Exclusion mutuelle
2. Rétention et attente
3. Non-préemption
4. Attente circulaire

**Prévention :** imposer un **ordre total** sur l'acquisition des ressources.

---

### Q7 — Problème producteurs-consommateurs ?

Producteurs ajoutent dans un buffer borné, consommateurs en retirent. Contraintes : ne pas lire si vide, ne pas écrire si plein.

```c
#define N 10
sem_t vide;   // places libres (init: N)
sem_t plein;  // éléments disponibles (init: 0)
pthread_mutex_t mutex;

// Producteur
void *produire(void *arg) {
    while (1) {
        int item = produire_item();
        sem_wait(&vide);
        pthread_mutex_lock(&mutex);
        inserer(item);
        pthread_mutex_unlock(&mutex);
        sem_post(&plein);
    }
}

// Consommateur
void *consommer(void *arg) {
    while (1) {
        sem_wait(&plein);
        pthread_mutex_lock(&mutex);
        int item = retirer();
        pthread_mutex_unlock(&mutex);
        sem_post(&vide);
        utiliser(item);
    }
}
```

---

### Q8 — Problème lecteurs-écrivains ?

Plusieurs lecteurs peuvent lire **simultanément**, mais un écrivain doit avoir l'accès **exclusif**.

```c
int nb_lecteurs = 0;
pthread_mutex_t mutex_lecteurs;
sem_t acces_ecriture;  // init: 1

// Lecteur
void *lire(void *arg) {
    pthread_mutex_lock(&mutex_lecteurs);
    nb_lecteurs++;
    if (nb_lecteurs == 1) sem_wait(&acces_ecriture);
    pthread_mutex_unlock(&mutex_lecteurs);

    /* lecture */

    pthread_mutex_lock(&mutex_lecteurs);
    nb_lecteurs--;
    if (nb_lecteurs == 0) sem_post(&acces_ecriture);
    pthread_mutex_unlock(&mutex_lecteurs);
}

// Écrivain
void *ecrire(void *arg) {
    sem_wait(&acces_ecriture);
    /* écriture */
    sem_post(&acces_ecriture);
}
```

> **Attention :** cette solution favorise les lecteurs → risque de famine pour les écrivains.

---

### Q9 — Famine (starvation) ?

Un thread attend **indéfiniment** parce que d'autres sont toujours prioritaires.

| | Deadlock | Famine |
|---|---|---|
| **Description** | Blocage mutuel, personne ne progresse | Certains progressent, un thread jamais |
| **Cause** | Attente circulaire de ressources | Politique d'ordonnancement injuste |
| **Solution** | Ordre d'acquisition des ressources | Files FIFO, aging (priorité croissante avec le temps d'attente) |

---

## AE6 — Entrées/Sorties Unix
*Après le CM6*

### Q1 — Les 4 syscalls fondamentaux pour les E/S ?

| Appel système | Rôle |
|---|---|
| `open()` | Ouvre ou crée un fichier → retourne un fd |
| `read()` | Lit des octets depuis un fd |
| `write()` | Écrit des octets vers un fd |
| `close()` | Ferme un fd |

Fonctionnent sur **tout** ce qui est représenté comme fichier Unix : fichiers, pipes, sockets, terminaux…

---

### Q2 — Descripteur de fichier (file descriptor) ?

**Entier non négatif** identifiant un fichier ouvert dans le processus.

| fd | Canal |
|---|---|
| 0 | stdin |
| 1 | stdout |
| 2 | stderr |
| ≥ 3 | fichiers ouverts par le programme |

`open()` retourne le plus petit fd libre ≥ 3.

---

### Q3 — size_t et ssize_t ?

- **`size_t`** : entier **non signé** pour les tailles (`sizeof`, compteurs, `malloc`). Défini dans `<stddef.h>`.
- **`ssize_t`** : entier **signé**, même taille. Permet de retourner une taille OU une erreur (−1). Utilisé par `read()` et `write()`.

---

### Q4 — open : valeur de retour, lecture seule, écriture ?

```c
#include <fcntl.h>

int open(const char *pathname, int flags, .../* mode */);
// Succès : fd ≥ 0
// Échec : -1 (errno mis à jour)

int fd_lecture = open("f.txt", O_RDONLY);
int fd_ecriture = open("f.txt", O_WRONLY);
int fd_les_deux = open("f.txt", O_RDWR);
```

---

### Q5 — Créer, tronquer, ou écrire à la fin ?

```c
// Créer si n'existe pas (avec mode de permissions)
int fd = open("f.txt", O_WRONLY | O_CREAT, 0644);

// Tronquer (vider) si le fichier existe
int fd = open("f.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

// Écrire à la fin (append)
int fd = open("f.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
```

| Combinaison | Équivalent stdio |
|---|---|
| `O_WRONLY | O_CREAT | O_TRUNC` | `fopen("f", "w")` |
| `O_WRONLY | O_CREAT | O_APPEND` | `fopen("f", "a")` |

---

### Q6 — 3ème argument de open lors de la création ?

Les **permissions du fichier créé**, en octal. Ignoré si `O_CREAT` absent.

Permissions réelles = `mode & ~umask`.

---

### Q7 & 8 — Permissions Unix : signification et octal ?

```
Permissions : r w x | r w x | r w x
              proprio  groupe  autres
              
r = 4,  w = 2,  x = 1

0755 = rwxr-xr-x  (proprio: tout ; groupe+autres: r+x)
0644 = rw-r--r--  (proprio: r+w ; groupe+autres: r seul)
0600 = rw-------  (proprio seul)
0777 = rwxrwxrwx  (tout le monde)
```

---

### Q9 — Utiliser read ?

```c
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
```

- **> 0 :** nombre d'octets lus (peut être < count)
- **= 0 :** fin de fichier (EOF)
- **= -1 :** erreur

```c
char buf[1024];
ssize_t n;
while ((n = read(fd, buf, sizeof(buf))) > 0)
    write(STDOUT_FILENO, buf, n);
if (n == -1) perror("read");
```

---

### Q10 — Cas où read est bloquant ?

- Terminal ou stdin (attente saisie clavier)
- Pipe vide (attente d'écriture)
- Socket réseau (attente de données)
- Fichier réseau NFS (serveur lent)

---

### Q11 — Utiliser write ?

```c
ssize_t write(int fd, const void *buf, size_t count);
```

- **> 0 :** octets écrits (peut être < count)
- **= -1 :** erreur

```c
const char *msg = "Hello!\n";
write(STDOUT_FILENO, msg, 7);
```

---

### Q12 — Les octets nuls ont-ils un sens pour read/write ?

**Non.** `read` et `write` traitent les octets nuls (`'\0'`) comme n'importe quel autre octet. Ils travaillent sur des **séquences d'octets brutes**, pas des chaînes C. Cela permet de lire/écrire des données binaires (images, exécutables…).

---

### Q13 — Les trois canaux standards ?

| fd | Macro | Flux stdio | Description |
|---|---|---|---|
| 0 | `STDIN_FILENO` | `stdin` | Entrée standard |
| 1 | `STDOUT_FILENO` | `stdout` | Sortie standard |
| 2 | `STDERR_FILENO` | `stderr` | Sortie erreur |

---

### Q14 — E/S standard : lire ligne, caractère, données formatées ?

```c
// Lire/écrire une ligne
fgets(buf, sizeof(buf), stdin);
fputs("Ligne\n", fichier);

// Lire/écrire un caractère
int c = fgetc(stdin);     // ou getchar()
fputc('A', stdout);       // ou putchar('A')

// Lire/écrire formaté
fscanf(stdin, "%d", &n);  // ou scanf()
fprintf(stdout, "%d\n", n); // ou printf()
```

---

### Q15 — Pourquoi getchar retourne int et pas char ?

Pour distinguer **EOF** (valeur −1) des octets valides (0 à 255). Un `char` non signé ne peut représenter −1 (serait 255). Un `char` signé créerait une ambiguïté avec l'octet 0xFF.

```c
int c = getchar();
if (c == EOF) { ... }        // fin de fichier
else { putchar((char)c); }   // octet valide
```

> **Piège :** `char c = getchar()` est incorrect — la comparaison `c == EOF` peut toujours être fausse si `char` est non signé.

---

### Q16 — Flux associés aux canaux standards ?

```c
stdin   // FILE* associé à fd 0
stdout  // FILE* associé à fd 1
stderr  // FILE* associé à fd 2
```

Variables globales de type `FILE *` déclarées dans `<stdio.h>`.

---

### Q17 — Bufferisation : 3 modes, comportements par défaut ?

| Mode | Constante | Comportement | Par défaut pour |
|---|---|---|---|
| Non bufferisé | `_IONBF` | Chaque write = syscall immédiat | `stderr` |
| Par ligne | `_IOLBF` | Vidé à `'\n'` ou quand plein | `stdout` connecté à un terminal |
| En blocs | `_IOFBF` | Vidé quand plein ou `fflush()` | Fichiers sur disque |

Forcer le vidage : `fflush(stdout)`.

> **Piège :** `printf("msg")` sans `\n` peut ne pas s'afficher immédiatement si bufferisation par ligne.

---

## Résumé de cours par thème

### Thème 1 — Bases C et Représentation des données

Le cycle compilation : préprocesseur → compilateur → éditeur de liens. Drapeaux essentiels : `-Wall -Wextra -g -std=c99`. **Valgrind** pour les erreurs mémoire.

La mémoire est **byte addressable**. Sur n bits : 2ⁿ valeurs. Approximation : **2¹⁰ ≈ 10³**.

Entiers **signés** (complément à 2) vs **non signés**. `<stdint.h>` fournit des types à taille garantie (`int32_t`, `uint64_t`…).

**Endianness :** little-endian (x86, octet poids faible en premier) vs big-endian (réseau, octet poids fort en premier).

---

### Thème 2 — Système d'exploitation et Processus

Le **noyau** gère processus, mémoire, E/S, système de fichiers, IPC et sécurité. Accès via **syscalls** (`man 2`).

Un **processus** = programme en cours d'exécution, identifié par son PID. **fork()** crée un fils (copie du père). **exec()** remplace l'image du processus. **waitpid()** attend la fin d'un fils et évite les zombies.

Les **signaux** sont des notifications asynchrones. Envoi via `kill()`. Les terminaux génèrent SIGINT (Ctrl+C), SIGTSTP (Ctrl+Z).

---

### Thème 3 — Généricité en C

**`void *`** = pointeur générique pour les fonctions indépendantes du type. Ne peut pas être déréférencé directement.

**Pointeurs de fonctions** permettent de passer des callbacks : `int (*f)(int, int)`. Deux syntaxes pour affecter (`f = fn` ou `f = &fn`) et appeler (`f(args)` ou `(*f)(args)`). `typedef` améliore la lisibilité.

---

### Thème 4 — Threads POSIX

`pthread_create` crée un thread exécutant `void *(*)(void *)`. `pthread_join` attend sa fin. Compiler avec `-lpthread`.

**Différence fondamentale vs fork :** les threads partagent la mémoire → nécessitent synchronisation. Les processus fils ont des copies indépendantes.

---

### Thème 5 — Synchronisation

**Race conditions** : accès concurrents non protégés → indéterminisme. Même `x++` n'est pas atomique.

**Sémaphores POSIX :** `sem_wait` (décrémente/bloque) et `sem_post` (incrémente/réveille). Initialisés avec `sem_init`.

**Mutex :** verrou avec propriété (déverrouillé par le même thread qui l'a verrouillé).

**Deadlock :** attente circulaire. Prévention : ordre total d'acquisition. **Famine :** thread indéfiniment ignoré. Solution : politiques équitables.

Problèmes classiques : **philosophes** (deadlock), **producteurs-consommateurs** (sémaphores vide/plein + mutex), **lecteurs-écrivains** (compteur lecteurs + mutex + sémaphore écriture).

---

### Thème 6 — Entrées/Sorties Unix

Les 4 syscalls fondamentaux : `open`, `read`, `write`, `close`. Fonctionnent sur tout (fichiers, pipes, sockets). Travaillent sur des **octets bruts** (pas de sens particulier au `'\0'`).

Un **fd** = entier indexant les fichiers ouverts (0=stdin, 1=stdout, 2=stderr). `ssize_t` permet de distinguer données (≥0) et erreur (−1).

**Permissions Unix :** 9 bits rwx×3. r=4, w=2, x=1. `0644`=rw-r--r--, `0755`=rwxr-xr-x.

**Bufferisation :** non bufferisé (stderr), par ligne (stdout terminal), en blocs (fichiers). `fflush()` pour forcer le vidage. `getchar()` retourne `int` pour distinguer EOF (−1) des octets valides.

---

### Récapitulatif des appels système essentiels

```c
// PROCESSUS
pid_t fork()
pid_t getpid(), getppid()
pid_t waitpid(pid_t pid, int *status, int options)
int execl/execv/execlp/execvp(...)
void exit(int status)

// SIGNAUX
int kill(pid_t pid, int sig)
int raise(int sig)

// THREADS (compiler avec -lpthread)
int pthread_create(pthread_t *tid, NULL, void*(*fn)(void*), void *arg)
int pthread_join(pthread_t tid, void **retval)
int pthread_mutex_lock/unlock(pthread_mutex_t *m)
int sem_wait/sem_post(sem_t *s)

// FICHIERS
int open(const char *path, int flags [, mode_t mode])
ssize_t read(int fd, void *buf, size_t count)
ssize_t write(int fd, const void *buf, size_t count)
int close(int fd)
```
