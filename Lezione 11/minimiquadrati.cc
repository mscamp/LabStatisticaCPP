#include <cmath>
#include "minimiquadrati.h"
#include "funzioniutili.h"

double phi(double * x, double * par)
{
	return (par[0] + par[1] * x[0]);
}

float rand_TCL_minimiquadrati(double media, double sigma, int N)
{
    double y = 0;
    double xMin = media - sqrt (3 * N) * sigma;
    double xMax = media + sqrt (3 * N) * sigma;

    for (int i = 0; i < N; ++i)
    {
    	y += rand_range (xMin, xMax);
    }

    y /= N;

    return y;
}