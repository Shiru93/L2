#include <stdio.h>
#include <stdlib.h>
#include "dichotomie.h"

int main(){
    double a = -1.0, b = 1.0;
    double precision = 1e-4;
    double zero = dichotomie(a, b, precision);

    printf("Zéro trouvé : %.6f\n", zero);
    printf("f(%.6f) = %.6f\n", zero, f(zero));

    return 0;
}