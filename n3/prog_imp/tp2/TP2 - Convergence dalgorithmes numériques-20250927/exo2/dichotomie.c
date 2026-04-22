#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x){
    return x*x*x - 3*x + 1;
}

double dichotomie(double a, double b, double precision){
    double milieu;

    if(f(a) * f(b) > 0){
        printf("Erreur : f(a) et f(b) doivent être de signes opposés\n");
        return 0;
    }

    while(fabs(b - a) > precision){
        milieu = (a + b) / 2.0;

        if(f(milieu) == 0.0) return milieu;

        if(f(a) * f(milieu) < 0) b = milieu;
        else a = milieu;
    }

    return (a + b) / 2.0;
}