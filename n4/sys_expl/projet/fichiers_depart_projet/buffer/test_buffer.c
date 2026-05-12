/*
 * Ziya EMRE 12212738
 * Je déclare qu'il s'agit de mon propre travail
 * Ce travail a été réalisé intégralement par un être humain
 */

#include "buffer.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

int main(){
    buffer * buff = buff_create(STDIN_FILENO, 4096);
    char dest[4096];

    while(buff_fgets(buff, dest, sizeof(dest)) != NULL){
        write(STDOUT_FILENO, dest, strlen(dest));
    }

    buff_free(buff);
}