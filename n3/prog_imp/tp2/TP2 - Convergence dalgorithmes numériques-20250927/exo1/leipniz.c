#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double suite_leipniz(int precision){
    double somme = 0.0;
    double p = pow(10, -precision);
    int i = 0;
    double terme;

    do{
        terme = (i % 2 == 0 ? 1.0 : -1.0) / (2.0 * i + 1.0);
        somme += terme;
        i++;
    } while(fabs(4.0 * terme) > p);

    return 4 * somme;
}