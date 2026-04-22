#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    argv++;

    while(*argv != NULL){
        while(**argv != '\0'){
            putchar(**argv);
            (*argv)++;
        }

        putchar(' ');
        argv++;
    }
    
    putchar('\n');

    return 0;
}