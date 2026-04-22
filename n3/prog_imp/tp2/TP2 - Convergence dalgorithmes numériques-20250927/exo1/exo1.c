#include <stdio.h>
#include <stdlib.h>
#include "leipniz.h"

int main(){
    int precision; 
    double pi;

    printf("Veuillez taper le nombre de chiffres après la virgule que vous souhaitez avoir : ");
    scanf("%d", &precision);

    pi = suite_leipniz(precision);

    printf("%.*f\n", precision, pi);

    return 0;
}