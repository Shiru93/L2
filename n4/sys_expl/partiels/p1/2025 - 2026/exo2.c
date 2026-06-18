#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <unistd.h>    // For fork(), getpid(), and execlp()
#include <sys/wait.h>  // For wait()
#include <signal.h>    // For kill() and SIGKILL

#define N_DFT 3

int main(int argc, char *argv[]){
    int n = argc > 1 ? atoi(argv[1]) : N_DFT;
    if(n <= 0){
        printf("def !\n");
        return 0;
    }

    printf("prem's !\n");
    for(; n > 0; n--){
        pid_t p = getpid();
        printf("lol\n");
        if(fork() != 0){
            wait(NULL);
            printf("plop\n");
        }

        kill(p, SIGKILL);
    }

    execlp("./a.out", "./a.out", "0", NULL);
    printf("haha\n");

    return 0;
}