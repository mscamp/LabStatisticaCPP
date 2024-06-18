#include "montecarlo.h"
#include <cmath>
#include <cstdlib>
#include "TF1.h"

double rand_range(double min, double max)
{
	return min + (max-min)*(rand() / static_cast<float>(RAND_MAX));
}

double rand_TAC(TF1 func, double xmin, double xmax, double ymax)
{
    double x = 0.0;
    double y = 0.0; 

    do {
      x = rand_range(xmin, xmax);
      y = rand_range(0.0, ymax);
    } while(y > func.Eval(x));

    return x; 
}

