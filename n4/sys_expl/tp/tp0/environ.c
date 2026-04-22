#include <stdio.h>
#include <stdlib.h>

int main(){
    extern char ** environ;

    while(*environ != NULL){
        while(**environ != '\0'){
            putchar(**environ);
            (*environ)++;
        }

        putchar(' ');
        environ++;
    }

    putchar('\n');

    return 0;
}