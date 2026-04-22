#include <stdio.h>
#include <stdlib.h>

int main(void){
    int c;
    int taille_max = 80;
    int index = 0;

    char * buffer = malloc(sizeof(char) * taille_max);
    if(!buffer){
        perror("Erreur malloc");
        return 1;
    }

    while((c = getchar()) != EOF){
        if(c == '\n'){
            for(int i = index - 1; i >= 0; i--){
                putchar(buffer[i]);
            }

            putchar('\n');
            index = 0; 
        } else {
            if(index >= taille_max){
                taille_max *= 2;
                char * nouveau_buffer = realloc(buffer, taille_max * sizeof(char));

                if(!nouveau_buffer){
                    perror("Erreur realloc");
                    free(buffer);
                    return 1;
                }

                buffer = nouveau_buffer;
            }

            buffer[index++] = c;
        }
    }

    if(index > 0){
        for(int i = index - 1; i >= 0; i--){
            putchar(buffer[i]);
        }

        putchar('\n');
    }

    fprintf(stderr, "Taille finale du tableau : %d\n", taille_max);

    free(buffer);

    return 0;
}