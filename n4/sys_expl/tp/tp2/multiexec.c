#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char * argv[]){
    if (argc < 3) {
        fprintf(stderr, "Usage: %s n cmd [arg1 ... argk]\n", argv[0]);
        return 1;
    }

    // nombre de copies
    int n = atoi(argv[1]);

    /*
    * cmd[0] = "ls", cmd[1] = "/usr", ..., cmd[k] = NULL
    * argv + 2 pointe directement sur le sous-tableau
    * argv est déjà terminé par NULL → cmd aussi !
    * 
    * argv :  ["./multiexec"] ["3"] ["ls"] ["/usr"] [NULL]
    *                            ↑
    *                       argv + 2
    *
    * cmd[0] = "ls"     ← nom de la commande pour execvp
    * cmd[1] = "/usr"   ← arguments
    * cmd[2] = NULL     ← sentinelle déjà là (fin de argv)
    */ 
    char **cmd = argv + 2;
    


    for(int i = 0; i < n; i++){
        switch(fork()){
            case -1:
                perror("fork");
                return 1;
            
            case 0:
                execvp(cmd[0], cmd);
                perror("execvp: ");
                return 1;
        }
    }
    
    while (wait(NULL) != -1);

    // Attendre les n fils et garder le statut du DERNIER à terminer
    int status;
    int last_status = 0;
    while (wait(&status) != -1)
        last_status = status;   // écrase à chaque fois → garde le dernier

    // Décoder le statut avec les macros POSIX
    if (WIFEXITED(last_status))
        return WEXITSTATUS(last_status);       // terminaison normale → son code

    if (WIFSIGNALED(last_status))
        return 128 + WTERMSIG(last_status);    // tué par signal → 128 + numéro

    return 0;
}

/*
void usage_and_exit(void);

int main(int argc, char *argv[]){
    int n, status;

    if (argc < 3)
        usage_and_exit();

    n = atoi(argv[1]);

    for (; n > 0; --n) {
        switch (fork()) {
            case -1:
                perror("fork");
                return 1;
            case 0:
                execvp(argv[2], argv + 2);
                perror("exec");
                return 127;
        }
    }

    while (wait(&status) != -1)
        ;
    
    return WIFEXITED(status) ? WEXITSTATUS(status) : 128 + WTERMSIG(status);
}
    
void usage_and_exit(void){
    puts("Usage: lance NUM CMD_NAME [ARG]...");
    exit(1);
}
*/