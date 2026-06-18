#include <stdio.h>
#include <stdlib.h>

double compute(int k);

int main(int argc, char * argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return 1;
    }

    int n;

    if(sscanf(argv[1], "%d", &n) != 1){
        fprintf(stderr, "Argument invalide : '%s'\n", argv[1]);
        return 1;
    }
    
    double * results = malloc(sizeof(double) * n);

    for(int i = 0; i < n; i++)
        results[i] = compute(i);

    for(int i = 0; i < n; i++)
        printf("%lg ", results[i]);

    printf("\n");

    free(results);

    return 0;
}