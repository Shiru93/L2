#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s PATHNAME\n", argv[0]);
        return 1;
    }

    // a) Créer fils 1 → ls
    switch (fork()) {
        case -1:
            perror("fork");
            return 1;

        case 0:
            execlp("ls", "ls", argv[1], NULL);
            perror("execlp ls");
            return 1;
    }

    // Père : attendre la fin de fils 1 (ls)
    wait(NULL);

    // b) Créer fils 2 → du
    switch (fork()) {
        case -1:
            perror("fork");
            return 1;

        case 0:
            execlp("du", "du", "-sh", argv[1], NULL);
            perror("execlp du");
            return 1;
    }

    // c) Le père lui-même devient df (pas d'attente de fils 2 !)
    execlp("df", "df", argv[1], NULL);
    perror("execlp df");
    return 1;
}

/*
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s PATHNAME\n", argv[0]);
        return 1;
    }

    switch (fork()) {
        case -1:
            perror("fork 1");
            return 1;
            
        case 0:
            execlp("ls", "ls", argv[1], NULL);

        default:
            wait(NULL);
            switch (fork()) {
                case -1:
                    perror("fork 2");
                    return 1;

                case 0:
                    execlp("du", "du", "-sh", argv[1], NULL);

                default:
                    wait(NULL);
                    execlp("df", "df", argv[1], NULL);
            }
    }
    
    return 0; // Jamais atteint 
}
*/