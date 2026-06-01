# Administration Système — Cours Complet
> L2 Informatique · Université Sorbonne Paris Nord

---

## Table des matières

1. [Introduction & Shell](#1-introduction--shell)
2. [Le Manuel (man)](#2-le-manuel-man)
3. [Arborescence des répertoires](#3-arborescence-des-répertoires)
4. [Types de fichiers Unix](#4-types-de-fichiers-unix)
5. [Systèmes de fichiers](#5-systèmes-de-fichiers)
6. [Inodes](#6-inodes)
7. [Périphériques en mode bloc](#7-périphériques-en-mode-bloc)
8. [Utilisateurs & Groupes](#8-utilisateurs--groupes)
9. [Permissions](#9-permissions)
10. [Identification, Authentification, Autorisation](#10-identification-authentification-autorisation)
11. [Concepts Réseau](#11-concepts-réseau)
12. [SSH](#12-ssh)
13. [DNS](#13-dns)
14. [Manipulation de texte & Redirections](#14-manipulation-de-texte--redirections)
15. [Processus & Systemd](#15-processus--systemd)
16. [Gestion des paquets (apt/dpkg)](#16-gestion-des-paquets-aptdpkg)
17. [Git](#17-git)
18. [Dualités clés](#18-dualités-clés)
19. [Fichiers de configuration importants](#19-fichiers-de-configuration-importants)
20. [Programme de l'examen](#20-programme-de-lexamen)

---

## 1. Introduction & Shell

### Qu'est-ce que l'administration système ?

L'expression est polysémique :
- Être **root** sur sa propre machine et l'administrer.
- Administrer des stations de travail, des services (mail, web, annuaires…) ou un réseau local.
- Un **métier** à part entière — avec une dimension politique réelle (autonomie, subordination, rapport au collectif).

### Le Shell

Le shell est simultanément :

| Rôle | Description |
|------|-------------|
| **Interface noyau** | Une coquille (shell) qui entoure le noyau (kernel) — comme dans une noix |
| **REPL** | Read–Eval–Print Loop : interpréteur de commandes interactif |
| **Langage de script** | Un langage de programmation complet (`#!/bin/bash`) |

Variantes principales : `bash`, `zsh`, `dash`, `ksh`, `csh`, `busybox ash`…

### Pourquoi l'anglais ?

La quasi-totalité de la documentation est en anglais, et les noms de commandes viennent de l'anglais :

| Commande | Signification | Commande | Signification |
|----------|--------------|----------|--------------|
| `cp` | CoPy | `rm` | ReMove |
| `mv` | MoVe | `ls` | LiSt directory |
| `cd` | Change Directory | `pwd` | Print Working Dir. |
| `mkdir` | MaKe DIRectory | `mkfs` | MaKe FileSystem |
| `tar` | Tape ARchiver | `lsblk` | LiSt BLocK devices |
| `/etc` | Editable Text Config. | `/usr` | UNIX System Resources |

### Évolutions technologiques à connaître

Mieux vaut comprendre les **concepts** que retenir la syntaxe d'un outil particulier :

| Ancien | Nouveau |
|--------|---------|
| CHS | **LBA** |
| MBR | **GPT** |
| BIOS | **UEFI** |
| sysV init | **systemd** |
| `ifconfig/netstat` | **`ip/ss`** |
| iptables | **nftables** |
| ISO-8859 | **UTF-8** |
| IPv4 | **IPv6** |

> **Principe fondamental** : Il est plus important de comprendre les **concepts** (fichier, port, processus, encapsulation, masque…) que la syntaxe d'un outil particulier, afin de pouvoir s'adapter aux évolutions.

---

## 2. Le Manuel — `man`

### Usage de base

```bash
man <programme>      # manuel d'une commande
man 5 passwd         # section 5 (fichiers de config)
man -k <mot_clef>    # chercher un mot clef (= apropos)
man -a random        # toutes les sections disponibles
```

### Sections du manuel

| Section | Contenu |
|---------|---------|
| 1 | Programmes exécutables |
| 2 | Appels système |
| 3 | Bibliothèques |
| 4 | Fichiers spéciaux (`/dev/`) |
| 5 | Fichiers de configuration |
| 7 | Notions générales |
| 8 | Commandes root |

### Navigation dans `less`

| Touche | Action |
|--------|--------|
| `g` / `G` | Début / Fin |
| `Espace` | Page suivante |
| `q` | Quitter |
| `/motif` | Rechercher |
| `n` / `N` | Occurrence suivante / précédente |

> **Astuce examen** : `man passwd` (section 1, la commande) ≠ `man 5 passwd` (section 5, le fichier de configuration).

---

## 3. Arborescence des répertoires

### Modèle en 4 couches

| Couche | Description | Commandes clés |
|--------|-------------|----------------|
| **1 — Arborescence** | Navigation, liens, droits | `ls`, `cd`, `cp`, `mv`, `find`… |
| **2 — Filesystem** | Inodes, montage | `mkfs`, `mount`, `stat`, `df`… |
| **3 — Block devices** | Disques, partitions, LVM, LUKS | `lsblk`, `parted`, `cryptsetup`… |
| **4 — Matériel** | Le disque physique réel | — |

### Filesystem Hierarchy Standard (FHS)

Consulter avec `man 7 hier` ou `man 7 file-hierarchy`.

| Répertoire | Contenu |
|------------|---------|
| `/` | Racine |
| `/etc` | Fichiers de configuration système |
| `/home` | Répertoires personnels des utilisateurs |
| `/root` | HOME de root |
| `/dev` | Fichiers de périphériques |
| `/tmp` | Fichiers temporaires |
| `/run` | Sockets, PID files (volatil) |
| `/usr` | UNIX System Resources |
| `/var` | Données variables (logs, mail…) |
| `/proc` | Pseudo-fs, infos processus |

### Chemins absolus vs relatifs

- **Absolu** : commence par `/` — ex. `/home/ziya/tp.pdf`
- **Relatif** : par rapport au répertoire courant — ex. `../docs/tp.pdf`
- `.` = répertoire courant, `..` = parent, `~` = HOME de l'user

### Commandes de navigation

```bash
cd /tmp                    # aller dans /tmp
cd ..                      # remonter d'un niveau
cd ~                       # aller dans son HOME
pwd                        # afficher le répertoire courant
ls -ilah /etc              # lister avec inodes, tailles lisibles
tree /etc/ssh              # vue arborescente
find /var -name "*.log"    # chercher fichiers .log
find . -type f -empty      # fichiers réguliers vides
find /home -perm /o+w      # fichiers modifiables par "other"
```

---

## 4. Types de fichiers Unix

**Presque tout est fichier** sous Unix — interface uniforme pour lire, écrire et contrôler l'accès à toute ressource.

### Les 7 types

| Char | Type | Description |
|------|------|-------------|
| `-` | Fichier régulier | Texte, binaire, PDF, image… |
| `d` | Répertoire | Contient des paires (nom, inode) |
| `l` | Lien symbolique | Pointeur vers un chemin (raccourci) |
| `p` | Tube nommé | IPC unidirectionnel |
| `s` | Socket | IPC bidirectionnel |
| `b` | Périphérique bloc | Disque, partition, clef USB… |
| `c` | Périphérique caractère | Souris, terminal, mémoire… |

### Fichiers spéciaux dans `/dev/`

| Fichier | Comportement |
|---------|-------------|
| `/dev/null` | Absorbe tout ce qu'on lui écrit |
| `/dev/zero` | Génère des octets nuls à l'infini |
| `/dev/random` | Octets aléatoires (entropie matérielle) |
| `/dev/urandom` | Aléatoire pseudo (plus rapide) |
| `/dev/full` | Simule un disque plein |

### Liens symboliques vs liens physiques

**Lien symbolique (`ln -s`)** : fichier contenant un chemin. Si la cible est supprimée → **lien cassé** (broken link). Analogue d'un raccourci Windows.

**Lien physique (`cp -l` ou `ln`)** : nouvelle entrée de répertoire pointant vers le **même inode**. Le fichier n'est supprimé que quand le nombre de liens tombe à 0.

```bash
ln -s /etc/nginx/sites-available/mon_site /etc/nginx/sites-enabled/mon_site
# Lien symbolique — activer/désactiver une config

cp -l source dest    # lien physique (même inode)
readlink lien        # afficher la cible d'un lien symbolique
file document.pdf    # déterminer le type par magic number
```

> **Examen** : savoir expliquer la différence entre `cp` (copie → nouvel inode), `cp -l`/`ln` (lien physique → même inode) et `ln -s` (lien symbolique → nouveau fichier de type `l`).

---

## 5. Systèmes de fichiers

### Le montage

L'arborescence Unix est un **assemblage de filesystems montés les uns sur les autres**. À la base il n'existe que `/`. On monte des filesystems sur des répertoires existants de façon récursive.

```bash
mount                            # lister les fs montés
findmnt                          # vue arborescente des montages
mount /dev/sdb1 /mnt/usb         # monter une clef USB
umount /mnt/usb                  # démonter
lsof /mnt/usb                    # voir qui utilise le fs (avant umount)
```

La configuration des montages permanents est dans `/etc/fstab`.

### Créer et vérifier un filesystem

```bash
mkfs -t ext4 /dev/sdb1    # formater en ext4
fsck /dev/sdb1             # vérifier l'intégrité
df -h                      # espace disque des fs montés
df -i                      # inodes utilisés/libres
du -sh ~                   # taille du répertoire HOME
```

**Types de filesystems courants** : `ext4` (Linux standard), `btrfs`, `xfs`, `vfat/fat32` (clefs USB/Windows), `tmpfs` (RAM), `sshfs` (distant via SSH), `iso9660` (CD-ROM).

---

## 6. Inodes

### Qu'est-ce qu'un inode ?

- **1 fichier = 1 inode** (identifiant unique dans le filesystem).
- L'inode contient les *métadonnées* du fichier — mais **pas son nom**.
- Le nom est une info du *répertoire* (qui stocke des paires *nom → numéro d'inode*).
- Un même inode peut avoir plusieurs noms (liens physiques).

### Attributs d'un inode

| Attribut | Description |
|----------|-------------|
| type | -, d, l, c, b, s, p |
| permissions | 12 bits (9 rwx + setuid/setgid/sticky) |
| Nlinks | Nombre de liens physiques |
| uid / gid | User et groupe propriétaires |
| taille | En octets |
| atime | Dernier accès en lecture |
| mtime | Dernière modification du **contenu** |
| ctime | Dernière modification de l'**inode** |
| btime | Date de création |
| pointeurs | Vers les blocs de données |

```bash
stat fichier.txt     # afficher tous les attributs d'inode
ls -i fichier.txt    # afficher le numéro d'inode
```

### Récapitulatif des opérations sur inodes

| Commande | Effet sur les inodes |
|----------|---------------------|
| `cp f1 f2` | Nouvel inode (copie) |
| `cp -l f1 f2` = `ln f1 f2` | Même inode, Nlinks++ |
| `ln -s f1 f2` | Nouvel inode de type `l` |
| `mv f1 f2` | Renomme l'entrée (même inode) |
| `rm f` | Supprime l'entrée, Nlinks-- |

---

## 7. Périphériques en mode bloc

### Concept central : le DAG des block devices

Disques, partitions, volumes LVM, volumes chiffrés LUKS, RAID, images ISO… ne sont que des **block devices obtenus les uns à partir des autres** en formant un DAG (graphe acyclique orienté).

```bash
lsblk       # vue arborescente des block devices
lsblk -f    # avec les filesystems
```

### Partitionnement

```bash
parted /dev/sda       # outil interactif (actions : mklabel, mkpart)
# Alternatives : fdisk, cfdisk, gparted (GUI)
```

| Type | Limites |
|------|---------|
| **MBR (msdos)** | Max 4 partitions primaires, max 2 To |
| **GPT** | Partitions illimitées, grands disques |

### Périphériques boucle (loop devices)

```bash
losetup -f image.img    # promouvoir un fichier en block device
losetup -l              # lister les loop devices actifs
losetup -d /dev/loop0   # détacher
```

Utilisations : accéder à une image ISO, créer un disque virtuel pour s'entraîner, récupérer des données sur une copie.

### Chiffrement LUKS (cryptsetup)

```bash
cryptsetup luksFormat /dev/sdb1          # installer LUKS
cryptsetup open /dev/sdb1 nom_ouvert     # déchiffrer → /dev/mapper/nom_ouvert
cryptsetup close nom_ouvert              # fermer
```

### LVM — Logical Volume Manager

Permet de fusionner/redécouper des block devices, faire des snapshots, redimensionner à chaud. Les volumes apparaissent dans `/dev/mapper/`.

```bash
# Autocomplétion : pv[TAB], vg[TAB], lv[TAB]
pvcreate /dev/sdb1         # créer un Physical Volume
vgcreate myvg /dev/sdb1    # créer un Volume Group
lvcreate -L 10G myvg       # créer un Logical Volume de 10G
```

### RAID (mdadm)

Combine plusieurs block devices pour améliorer performances et/ou tolérance aux pannes. RAID0 (striping), RAID1 (mirroring), RAID5/6 (parité).

### dmsetup — simuler des erreurs

```bash
dmsetup create nom << EOF
0 <taille> flakey <device> 0 10 100   # 10s ok, 100s avec erreurs
EOF
```

> **Empilement logique** : l'ordre d'empilement est important. Exemple typique d'un disque chiffré : disque physique → partition → **LUKS** → **LVM** → `mkfs` → `mount`.

---

## 8. Utilisateurs & Groupes

### Fichiers système

| Fichier | Contenu |
|---------|---------|
| `/etc/passwd` | Comptes utilisateurs : login, UID, GID, HOME, shell |
| `/etc/shadow` | Mots de passe hachés + politique d'expiration |
| `/etc/group` | Groupes et membres |
| `/etc/gshadow` | Mots de passe de groupes |

### Commandes de gestion

```bash
adduser alice                 # créer l'user alice (interactif)
adduser alice sudo            # ajouter alice au groupe sudo
deluser alice                 # supprimer l'user alice
addgroup devteam              # créer le groupe devteam
usermod -aG devteam alice     # ajouter alice à devteam
chage alice                   # gérer l'expiration du mot de passe
id                            # afficher son UID, GID, groupes
who / w                       # utilisateurs connectés
```

### Concepts clés

- **root** (UID 0) a tous les droits — le super-user.
- L'**UID est la référence** (stocké dans les inodes, les processus). Le nom n'est qu'un alias dans `/etc/passwd`.
- Un user ne correspond pas forcément à une personne — beaucoup de services tournent sous un user système dédié (ex. `www-data` pour nginx).
- Les users système ont un UID < 1000 (conventionnel).
- Attention au **champ de commentaires** de `/etc/passwd` (champ 5) — peut contenir des infos personnelles ajoutées à l'insu de l'utilisateur (utiliser `--comment ''`).

### sudo, su, runuser

```bash
sudo commande                       # exécuter en tant que root
su - alice                          # changer d'user (avec son environnement)
runuser -u www-data -- commande     # exécuter en tant qu'user moins privilégié
```

---

## 9. Permissions

### Lecture d'une sortie `ls -l`

```
- r w x r - x r - -   2   alice   devteam   4096   ...
^ ^^^ ^^^ ^^^
|  |   |   └── autres (o)
|  |   └────── groupe (g)
|  └────────── user (u)
└───────────── type de fichier
```

### Modifier les permissions

```bash
# Notation symbolique (modification partielle)
chmod u+x script.sh           # ajouter exécution au user
chmod ug+x,o-x script.sh      # user+group exec, other retire
chmod a=r fichier              # tout le monde : lecture seule

# Notation octale (écrasement complet)
chmod 750 repertoire    # rwxr-x--- (u=7, g=5, o=0)
chmod 644 fichier       # rw-r--r-- (u=6, g=4, o=4)
chmod 600 ~/.ssh/id_rsa # clef privée SSH : rw------- obligatoire
```

### Correspondance octal ↔ symboles

| Octal | Binaire | Symboles |
|-------|---------|----------|
| 7 | 111 | rwx |
| 6 | 110 | rw- |
| 5 | 101 | r-x |
| 4 | 100 | r-- |
| 0 | 000 | --- |

### Signification des permissions sur les répertoires

| Permission | Sur un répertoire signifie… |
|------------|----------------------------|
| `r` | Lire la liste des noms (faire `ls`) |
| `w` | Ajouter ou supprimer des liens (créer/effacer fichiers) |
| `x` | Traverser le répertoire (accéder aux inodes par nom) |

> Pour accéder à un fichier via son chemin absolu, **tous** les répertoires du chemin doivent avoir le bit `x` pour l'utilisateur courant.

### Permissions spéciales (SST)

| Bit | Sur fichier | Sur répertoire | Exemple |
|-----|------------|----------------|---------|
| **setuid** | S'exécute avec les droits du *propriétaire* | — | `passwd`, `sudo` |
| **setgid** | S'exécute avec les droits du *groupe* | Nouveaux fichiers héritent du groupe | Site web `www-data` |
| **sticky** | — | Seul le propriétaire peut supprimer ses fichiers | `/tmp` |

```bash
chmod 700 ~/.ssh           # répertoire .ssh : personne d'autre ne doit y accéder
chmod 600 ~/.ssh/id_rsa    # clef privée trop lisible = SSH refuse de l'utiliser !
chown alice:devteam fichier   # changer user ET groupe propriétaire
chgrp devteam fichier         # changer seulement le groupe
```

### ACL (Access Control Lists)

Permissions plus fines que les 3 entités standard (user, group, other). Attributs étendus stockés dans l'inode.

```bash
setfacl -m u:bob:rx fichier    # donner r-x à bob
getfacl fichier                # afficher les ACL
```

---

## 10. Identification, Authentification, Autorisation

| Concept | Définition | Question posée |
|---------|------------|----------------|
| **Identification** | Déclarer son identité | *Qui êtes-vous ?* |
| **Authentification** | Prouver son identité | *Êtes-vous bien qui vous dites être ?* |
| **Autorisation** | Obtenir des droits selon son identité vérifiée | *Qu'avez-vous le droit de faire ?* |

### SSH (client → serveur)

- **Identification** : donner le nom d'user distant (`ssh alice@serveur` ou option `User` dans `~/.ssh/config`).
- **Authentification** : fournir le mot de passe *ou* prouver la possession de la clef privée correspondant à une clef publique dans `~/.ssh/authorized_keys`.
- **Autorisation** : obtenir un shell (défini dans `/etc/passwd`), éventuellement restreint via `authorized_keys`.

### sudo

- **Identification** : implicite — c'est l'user propriétaire du processus qui lance `sudo`.
- **Authentification** : saisir son propre mot de passe.
- **Autorisation** : si l'user est dans les sudoers (définis dans `/etc/sudoers`), la commande est exécutée en tant que root.

---

## 11. Concepts Réseau

### Architectures

| Rôle | Description | Exemples |
|------|-------------|---------|
| **Client** | Processus qui demande un service | Firefox, `wget`, `ssh` |
| **Serveur** | Processus qui attend et répond | nginx, sshd |
| **Proxy (mandataire)** | Relais côté client | Proxy SOCKS SSH (`DynamicForward`) |
| **Reverse-proxy** | Relais côté serveur | nginx (load balancing) |
| **Pair (P2P)** | Communication symétrique | BitTorrent |

Plusieurs serveurs peuvent tourner sur un même hôte sur des ports différents.

### Commandes réseau essentielles

```bash
ip address                    # interfaces et adresses IP
ip route                      # table de routage
ss -tl                        # ports TCP en écoute
ss -tln                       # avec numéros (pas de résolution)
ping google.com               # tester l'accessibilité
nmap 192.168.1.1             # scanner les ports ouverts
traceroute google.com         # route des paquets
socat TCP:hote:port -         # connexion TCP brute
```

### Encapsulation & Tunnels

Les protocoles réseau s'encapsulent les uns dans les autres (HTTP dans TCP dans IP dans Ethernet). SSH crée des **tunnels** permettant d'encapsuler d'autres protocoles dans une connexion SSH chiffrée.

---

## 12. SSH

### Arborescence côté client

```
/etc/ssh/ssh_config          # config système (tous les users)
~/.ssh/
  config                     # config personnelle (blocs Host)
  id_ed25519                 # clef privée (600 obligatoire !)
  id_ed25519.pub             # clef publique
  known_hosts                # fingerprints des serveurs connus
```

### Arborescence côté serveur

```
/etc/ssh/sshd_config         # config du serveur
/etc/ssh/ssh_host_*_key      # clefs d'hôte (identité du serveur)
/etc/motd                    # message affiché à la connexion
~/.ssh/authorized_keys       # clefs publiques autorisées à se connecter
/var/log/auth.log            # journal des connexions
```

### Commandes SSH essentielles

```bash
# Connexion
ssh alice@serveur.example.com
ssh -p 2222 alice@serveur         # port non standard

# Génération de clef
ssh-keygen -t ed25519 -C "alice@machine"

# Copie de la clef publique sur le serveur
ssh-copy-id alice@serveur

# Tunnel local (accéder à un port distant localement)
ssh -L 8080:localhost:80 alice@serveur

# Tunnel SOCKS (proxy dynamique)
ssh -D 1080 alice@serveur

# Copie de fichiers
scp fichier.txt alice@serveur:/home/alice/
rsync -av dossier/ alice@serveur:/backup/

# Monter un répertoire distant
sshfs alice@serveur:/home/alice /mnt/distant
```

### Fichier `~/.ssh/config`

```
Host mon_conteneur
    HostName conteneur.example.com
    User alice
    Port 22
    IdentityFile ~/.ssh/id_ed25519
    ServerAliveInterval 60
```

> **Clef publique vs clef privée** : la clef privée reste sur le client, ne se partage jamais. La clef publique se dépose sur les serveurs dans `~/.ssh/authorized_keys`.

> **⚠️ Permissions SSH** : SSH refusera d'utiliser une clef privée trop permissive : `chmod 700 ~/.ssh` et `chmod 600 ~/.ssh/id_*` sont obligatoires.

---

## 13. DNS

### Principe

Le DNS (Domain Name System) traduit les noms de domaine (`example.com`) en adresses IP. Système hiérarchique et distribué.

### Fichiers de configuration réseau

| Fichier | Rôle |
|---------|------|
| `/etc/hostname` | Nom de la machine |
| `/etc/hosts` | Résolution locale (DNS local statique) |
| `/etc/resolv.conf` | Serveurs DNS à interroger |

### Types d'enregistrements DNS

| Type | Signification |
|------|--------------|
| `A` | Nom → IPv4 |
| `AAAA` | Nom → IPv6 |
| `CNAME` | Alias → autre nom |
| `MX` | Mail eXchanger |
| `TXT` | Texte libre (SPF, DKIM…) |

---

## 14. Manipulation de texte & Redirections

### Redirections

| Opérateur | Effet |
|-----------|-------|
| `<` | Rediriger stdin depuis un fichier |
| `>` | Rediriger stdout vers un fichier (écrase) |
| `>>` | Ajouter stdout à un fichier |
| `2>` | Rediriger stderr |
| `2>&1` | stderr → stdout |
| `\|` | Pipe : stdout d'une cmd → stdin de la suivante |

### Exemples de pipelines (style examen)

```bash
# Compter les alias commentés dans .bashrc
cat ~/.bashrc | grep '^ *#alias' | wc -l > le_nombre_d_alias_commentes.txt

# Users dont le shell est bash
cat /etc/passwd | grep "^.*:/bin/bash$" | cut -d ':' -f 1

# 3 fichiers avec les plus petits numéros d'inode
ls -i | sort -n | head -n 3
```

### Commandes de traitement de texte

| Commande | Usage |
|----------|-------|
| `grep` | Chercher un motif (`-v` inverser, `-i` insensible, `-c` compter) |
| `cut` | Extraire des colonnes (`-d':'` délimiteur, `-f1` champ) |
| `sort` | Trier (`-n` numérique, `-r` inverse) |
| `uniq` | Éliminer les doublons consécutifs |
| `wc` | Compter (`-l` lignes, `-w` mots, `-c` octets) |
| `head/tail` | Premiers/derniers lignes (`-n N`) |
| `tr` | Translittérer des caractères |
| `sed` | Substitutions/suppressions de lignes |
| `awk` | Traitement de fichiers en colonnes |
| `diff` | Comparer deux fichiers |
| `hexdump -C` | Afficher en hexadécimal |
| `cat` | Afficher/concaténer des fichiers |
| `less` | Visionner un fichier avec navigation |
| `echo` / `printf` | Afficher du texte |
| `tac` / `rev` | Inverser fichier / caractères |

---

## 15. Processus & Systemd

### Gestion des processus

```bash
ps aux                    # lister tous les processus (BSD)
ps -eF                    # lister tous les processus (POSIX)
pstree                    # vue arborescente (PID 1 = systemd)
htop                      # moniteur interactif
kill -15 1234             # SIGTERM (arrêt propre)
kill -9 1234              # SIGKILL (force)
pidof nginx               # PIDs d'un processus par nom
lsof /var/log/syslog      # qui utilise ce fichier
```

### Systemd (gestion des services)

```bash
systemctl start nginx        # démarrer
systemctl stop nginx         # arrêter
systemctl restart nginx      # redémarrer
systemctl reload nginx       # recharger config sans arrêter
systemctl status nginx       # état + fin du journal
systemctl enable nginx       # démarrage automatique au boot
systemctl disable nginx      # désactiver le démarrage auto
systemctl is-enabled nginx   # vérifier si activé
```

### Séquence de boot

```
UEFI/BIOS → bootloader (GRUB) → noyau Linux → initramfs
→ systemd (PID 1) → montage des filesystems → services
```

Tous les processus sont descendants de systemd (PID 1) — arbre de processus.

---

## 16. Gestion des paquets (apt/dpkg)

### apt — gestion à l'échelle de la distribution

```bash
apt update              # récupérer la liste des paquets
apt upgrade             # mettre à jour les paquets installés
apt install nginx       # installer nginx et ses dépendances
apt remove nginx        # désinstaller
apt search web server   # chercher un paquet
apt show nginx          # descriptif d'un paquet
```

### dpkg — gestion à l'échelle d'un paquet

```bash
dpkg -i paquet.deb          # installer un .deb téléchargé
dpkg -L nginx               # lister les fichiers d'un paquet installé
dpkg -S /usr/sbin/nginx     # quel paquet a fourni ce fichier
```

---

## 17. Git

### Les 3 zones

| Zone | Description |
|------|-------------|
| **Worktree** (répertoire de travail) | Les fichiers tels qu'ils sont sur le disque. C'est là qu'on édite. |
| **Staging area** (index) | Le "commit en préparation". On y ajoute les modifications à inclure. |
| **Dépôt local** (`.git/`) | Le DAG des commits — l'historique complet. HEAD pointe vers le commit courant. |

### Boucle de base (solo local)

```bash
git init                            # créer un dépôt
git add fichier.txt                 # ajouter à la staging area
git add .                           # tout ajouter
git commit -m "message"             # créer un commit
git status                          # état des 3 zones
git diff                            # worktree vs staging
git diff --staged                   # staging vs dernier commit
git log --graph --oneline --all     # visualiser le DAG
```

### Annuler des changements

```bash
git restore fichier                       # annuler modifs dans worktree
git restore --staged fichier              # retirer de la staging area
git restore --staged --worktree .         # annuler tout
```

### Branches et remote

```bash
git branch nouvelle-branche     # créer une branche
git checkout nouvelle-branche   # changer de branche
git merge branche               # fusionner
git clone url                   # cloner un dépôt distant
git push origin main            # pousser vers le remote
git pull                        # récupérer + merger
```

> **Comprendre git, pas mémoriser des formules magiques** : si vous comprenez ce qu'est la staging area, un commit (snapshot), une branche (pointeur sur un commit), un DAG, et un remote, vous pouvez toujours vous en sortir avec un petit nombre de commandes atomiques.

---

## 18. Dualités clés

Le programme d'examen demande explicitement d'être clair sur ces dualités :

| Dualité | Explication |
|---------|-------------|
| **Relatif / Absolu** | Chemin depuis la racine vs chemin depuis le répertoire courant |
| **Mutable / Immutable** | Ex. un commit git est immutable ; un répertoire de travail est mutable |
| **Local / Distant** | Fichiers sur la machine courante vs sur un serveur (SSH) |
| **Réel / Virtuel** | Périphérique physique vs loop device, VM vs hôte |
| **Client / Serveur** | Qui demande (`ssh`) vs qui écoute (`sshd`) |
| **Stock / Flux** | Fichier régulier (stocké) vs pipe, socket, périphérique caractère (flux) |
| **Permanent / Temporaire** | `/tmp` (volatil au reboot) vs `/home` |
| **Statique / Dynamique** | HTML statique vs page web générée dynamiquement |
| **Identification / Authentification / Autorisation** | Qui / Preuve / Droits |
| **Clef publique / Clef privée** | Publique = partageable. Privée = secrète, jamais partagée |
| **Système hôte / Système invité** | Machine réelle vs VM (VirtualBox) |
| **Spécifique / Générique** | Ex. une règle sudo précise vs une règle générale |

---

## 19. Fichiers de configuration importants

| Fichier | Rôle |
|---------|------|
| `/etc/passwd` | Comptes utilisateurs |
| `/etc/shadow` | Mots de passe hachés |
| `/etc/group` | Groupes |
| `/etc/gshadow` | Mots de passe de groupes |
| `/etc/hostname` | Nom de la machine |
| `/etc/hosts` | Résolution DNS locale |
| `/etc/resolv.conf` | Serveurs DNS |
| `/etc/fstab` | Montages automatiques au boot |
| `~/.ssh/config` | Configuration client SSH |
| `~/.ssh/authorized_keys` | Clefs autorisées à se connecter |
| `~/.ssh/known_hosts` | Fingerprints des serveurs connus |
| `~/.bashrc` | Config du shell bash (non-login) |
| `~/.inputrc` | Config de readline (autocomplétion) |
| `/etc/nginx/nginx.conf` | Config principale nginx |
| `/etc/nginx/sites-available/` | Virtual hosts disponibles |
| `/etc/nginx/sites-enabled/` | Virtual hosts actifs (liens symboliques) |
| `/etc/sudoers` | Politiques sudo |
| `/proc/` | Pseudo-filesystem, infos noyau/processus |

---

## 20. Programme de l'examen

### Partie non négociable — À maîtriser absolument

Ces points feront l'objet de questions certaines :

- **Manuel** : sections, `man -k`, différence section 1 vs 5
- **Navigation** : `/`, `.`, `..`, `~`, chemins absolus/relatifs
- **`find`** : tests `-name`, `-type`, `-perm`, `-empty`, actions `-exec`…
- **`ls -ila`** : interpréter entièrement — inode, types, liens, user/groupe, permissions, liens symboliques, fichiers cachés
- **Copie vs liens** : différence `cp` / lien physique / lien symbolique
- **Filesystems** : montage, point de montage, inode vs contenu
- **Block devices** : reconnaître, organiser en DAG, construire avec loop/partitionnement/cryptsetup/LVM
- **Permissions** : notation symbolique ET octale, `chmod`, `chown` ; permissions des répertoires (r/w/x)
- **Processus** : séquence de boot, arbre de processus, daemons via `systemctl`
- **Redirections et pipes** : `<`, `>`, `>>`, `2>`, `|`
- **Fichiers de config** : ceux listés au chapitre 19
- **Bases de numération** : binaire, octal, hexadécimal

### Compréhension générale

- SSH : tunnels (réseau) ≠ authentification (clefs)
- Notions de clefs de chiffrement (clef publique, clef privée, vérification)
- DNS, IPv6
- Structures : arborescence, DAG
- Encapsulations, tunnels, proxy SOCKS
- Dualités du chapitre 18

### Exemple de questions pipelines (style examen)

```bash
# Compter les alias commentés dans .bashrc
cat ~/.bashrc | grep '^ *#alias' | wc -l > fichier.txt

# Lister les users dont le shell est /bin/bash
cat /etc/passwd | grep "^.*:/bin/bash$" | cut -d ':' -f 1

# Les 3 fichiers avec les plus petits inodes
ls -i | sort -n | head -n 3 > resultat.txt
```

---

*Cours généré à partir des documents du cours Administration Système 2025–2026.*
