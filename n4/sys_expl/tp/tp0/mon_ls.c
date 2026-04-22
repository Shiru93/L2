#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

void ls(const char * chemin, int options);

int main(int argc, char *argv[]){
    int options = 0;

    if(argc > 1) {
        if(argc > 2 && ((strcmp(argv[1], "-a") == 0 && strcmp(argv[2], "-i") == 0) || 
                        (strcmp(argv[1], "-i") == 0 && strcmp(argv[2], "-a") == 0))) {
            // Options -a et -i séparées
            options = 3;
            argv += 3;
            argc -= 3;
        } 
        else if(strcmp(argv[1], "-ai") == 0 || strcmp(argv[1], "-ia") == 0) {
            // Options groupées
            options = 3;
            argv += 2;
            argc -= 2;
        } 
        else if(strcmp(argv[1], "-a") == 0) {
            options = 2;
            argv += 2;
            argc -= 2;
        } 
        else if(strcmp(argv[1], "-i") == 0) {
            options = 1;
            argv += 2;
            argc -= 2;
        }
        else {
            // Pas d'option, juste des dossiers
            argv++;
            argc--;
        }
    } else {
        // Zéro argument (argc == 1)
        argv++;
        argc--;
    }

    // Affichage en fonction des dossiers restants
    if(argc == 0){
        ls(".", options); // Aucun dossier spécifié, on liste le dossier courant
    } 
    else if(argc == 1){
        ls(*argv, options); // Un seul dossier
    } 
    else {
        // Plusieurs dossiers
        while(*argv){
            printf("%s :\n", *argv);
            ls(*argv, options);
            printf("\n");
            argv++;
        }
    }

    return 0;
}

void ls(const char * chemin, int options){
    DIR * d = opendir(chemin);
    struct dirent * ent;

    if(!d){
        perror("opendir");
        return;
    }

    while((ent = readdir(d))){
        switch (options) {
        case 3: // -a et -i
            printf("%lu : %s\n", (unsigned long)ent->d_ino, ent->d_name);
            break;

        case 2: // -a
            printf("%s\n", ent->d_name);
            break;

        case 1: // -i (masque les fichiers cachés)
            if(ent->d_name[0] != '.')
                printf("%lu : %s\n", (unsigned long)ent->d_ino, ent->d_name);
            break;

        case 0: // rien (masque les fichiers cachés)
            if(ent->d_name[0] != '.')
                printf("%s\n", ent->d_name);
            break;
        
        default:
            break;
        }
    }

    closedir(d);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h> // Indispensable pour getopt

void ls(const char * chemin, int options);

int main(int argc, char *argv[]) {
    int opt;
    int opt_a = 0;
    int opt_i = 0;

    // getopt parcourt argv à la recherche des options "a" et "i"
    while ((opt = getopt(argc, argv, "ai")) != -1) {
        switch (opt) {
            case 'a':
                opt_a = 1;
                break;
            case 'i':
                opt_i = 1;
                break;
            default: // Si l'utilisateur tape une option non reconnue (ex: -x)
                fprintf(stderr, "Usage: %s [-a] [-i] [dossier...]\n", argv[0]);
                return 1;
        }
    }

    // On recalcule ton entier "options" (0, 1, 2 ou 3)
    int options = (opt_a ? 2 : 0) + (opt_i ? 1 : 0);

    // MAGIE DE GETOPT : La variable 'optind' contient maintenant l'index 
    // du premier argument qui n'est PAS une option (c'est-à-dire le premier dossier).
    
    if (optind == argc) {
        // Aucun dossier spécifié, on liste le dossier courant
        ls(".", options);
    } 
    else if (optind == argc - 1) {
        // Un seul dossier spécifié
        ls(argv[optind], options);
    } 
    else {
        // Plusieurs dossiers spécifiés
        for (int i = optind; i < argc; i++) {
            printf("%s :\n", argv[i]);
            ls(argv[i], options);
            if (i < argc - 1) printf("\n");
        }
    }

    return 0;
}

void ls(const char * chemin, int options) {
    DIR * d = opendir(chemin);
    struct dirent * ent;

    if (!d) {
        perror("opendir");
        return;
    }

    while ((ent = readdir(d))) {
        switch (options) {
            case 3: // -a et -i
                printf("%lu : %s\n", (unsigned long)ent->d_ino, ent->d_name);
                break;
            case 2: // -a
                printf("%s\n", ent->d_name);
                break;
            case 1: // -i (sans -a)
                if (ent->d_name[0] != '.')
                    printf("%lu : %s\n", (unsigned long)ent->d_ino, ent->d_name);
                break;
            case 0: // rien du tout
                if (ent->d_name[0] != '.')
                    printf("%s\n", ent->d_name);
                break;
        }
    }

    closedir(d);
}
*/