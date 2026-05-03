#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
    switch(fork()){
        case -1:
            perror("fork");
            return 1;

        case 0:
            execlp("cp", "cp", "exemple_execlp.c", "exemple_copie.c", NULL);
            perror("execlp: ");
            return 1;
    }

    wait(NULL);
    printf("Commande cp terminée.\n");
	return 0;
}