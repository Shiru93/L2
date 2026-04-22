#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

void ls(const char * chemin);

int main(int argc, char *argv[]){
    if(argc == 2){
        argv++;
        ls(*argv);
    } else if(argc > 2){
        argv++;
        while(*argv){
            printf("%s :\n", *argv);
            ls(*argv);
            printf("\n");
            argv++;
        }
    } else {
        ls(".");
    }

    return 0;
}

void ls(const char * chemin){
    DIR * d = opendir(chemin);
    struct dirent * ent;

    if(!d){
        perror("opendir");
        return;
    }

    while((ent = readdir(d))){
        if(ent->d_name[0] != '.')
            printf("%s\n", ent->d_name);
    }

    closedir(d);
}