#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

#define BUFSZ 4096

void dcopy(int fdin, int fdout);

int main(int argc, char * argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <fichier>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipefd[2];
    pipe(pipefd);   // pipefd[0] = lecture, pipefd[1] = écriture

    // Question 8
    char tmpfilename[] = "/tmp/sponge.XXXXXX";
    int fdtmp = mkstemp(tmpfilename);
    if(fdtmp == -1){
        perror("mkstemp");
        exit(EXIT_FAILURE);
    }

    /*
     * Question 9
     */
    // Etape 1 : lire stdin, écrire danss le fichier temporaire
    dcopy(0, fdtmp);    // 0 = stdin
    //Etape 2 : tenter le renommage
    if(rename(tmpfilename, argv[1]) == -1){
        // Echec (ex: système de fichiers différents -> copie)
        // Ré-ouvrir le temporaire en lecture
        int fdin = open(tmpfilename, O_RDONLY);
        if(fdin == -1){
            perror("open tmpfile for copy");
            unlink(tmpfilename);
            exit(EXIT_FAILURE);
        }
        // Ouvrir le fichier cible en écriture
        int fdout = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
        if(fdout == -1){
            perror(argv[1]);
            close(fdin);
            unlmink(tmpfilename);
            exit(EXIT_FAILURE);
        }
        // Copier
        dcopy(fdin, fdout);
        close(fdin);
        close(fdout);
        // Supprimer le temporaire
        if(unlink(tmpfilename) == -1){
            perror("unlink");
            exit(EXIT_FAILURE);
        }
    }   

    // Processus 1 : sort foo -> écrit dans le pipe
    if(fork() == 0){
        close(pipefd[0]);   // Ferme la lecture
        dup2(pipefd[1], 1); // stdout -> écriture pipe
        close(pipefd[1]);
        execlp("sort", "sort", "foo", NULL);

        // Si execlp échoue
        perror("execlp sort");
        _exit(1);
    }

    // Processus 2 : sponge foo -> lit depuis le pipe, écrit dans foo quand EOF
    if(fork() == 0){
        close(pipefd[1]);   // Ferme l'écriture
        dup2(pipefd[0], 0); // stdin -> lecture pipe
        close(pipefd[0]);
        execlp("sponge", "sponge", "foo", NULL);
        perror("execlp sponge");
        _exit(1);
    }

    // Parent : ferme les deux bouts du pipe et attend
    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}

/*
 * Copier le fichier de descripteur fdin dans le fichier descripteur fdout
 * On suppose que fdin est ouvert au moins en lecture et fdout au moins en écriture
 * La copie utilise un tampon de taille BUFSZ
 */
void dcopy(int fdin, int fdout){
    char buf[BUFSZ];
    ssize_t n;
    while((n = read(fdin, buf, BUFSZ)) > 0){
        ssize_t written = 0;
        while(written < n){
            ssize_t w = write(fdout, buf + written, n - written);
            if(w < 0){
                perror("write");
                return;
            }

            written += w;
        }
    }

    if(n < 0)
        perror("read");
}