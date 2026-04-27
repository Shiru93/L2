#include <stdio.h>
#include <time.h>
#include <math.h>

#ifndef N
#define N (1 << 27) /* 1 décalé gauche de 27, donc 2^27 */
#endif
#define PAS (1. / N)

double calculer_pi(long n);
double f(double x);

int main(int argc, char *argv[])
{
	struct timespec tic, toc;
	double duree, pi;

	clock_gettime(CLOCK_REALTIME, &tic);

	pi = calculer_pi(N);

	clock_gettime(CLOCK_REALTIME, &toc);
	duree = (toc.tv_sec - tic.tv_sec);
	duree += (toc.tv_nsec - tic.tv_nsec) / 1000000000.0;

	printf("pi = %.10f\n", pi);
	printf("PI = %.10f\n", atan(1.) * 4.);
	printf("durée : %g\n", duree);
	return 0;
}

double f(double x)
{
	return sqrt(1 - x * x);
}

double calculer_pi(long n)
{
	double x = 0.,  res = 0.;
	for (; x < 1 - PAS; x += PAS)
		res += (f(x) + f(x + PAS)) / 2.;
	return 4. * res * PAS;
}
