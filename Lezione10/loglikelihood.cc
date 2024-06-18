#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include "funzioniutili.h"

double loglikelihood(const std::vector<double> & x, double par)
{
	double sum = 0.;

	for(int i = 0; i < x.size(); ++i)
	{
		sum += log(pdf_esponenziale(x.at(i), par));
	}

	return sum;
}

double find_max_likelihood
( double f(const std::vector<double> &, double),
  double xmin, 
  double xmax, 
  const std::vector<double> & data,
  double precision = 0.0001 )

{
	double r = 0.618;
	double x2 = 0;
	double x3 = 0;
	double larghezza = fabs(xmax - xmin);

	while (larghezza > precision)
	{
		x2 = xmin + r * (xmax - xmin);
		x3 = xmin + (1 - r) * (xmax - xmin);

		if (f(data, x3) < f(data, x2))
		{  
			xmin = x3;
			xmax = xmax;
		}
		
		else
		{
			xmax = x2;
			xmin = xmin;
		}

		larghezza = fabs(xmax - xmin);
	}

	return (xmin + xmax)/2;
}

double h(const std::vector<double> & x, double par, double tau_max)
{
	return (loglikelihood(x, par) - loglikelihood(x, tau_max) + 0.5);
}

double find_zeros_likelihood
( double g(const std::vector<double> &, double, double),
  double a, 
  double b, 
  const std::vector<double> & data, 
  double par_max,
  double precision = 0.0001 )

{
	double x_m;

	if(g(data, a, par_max) * g(data, b, par_max) < 0)
	{
		while(b-a > precision)
		{
			x_m = (a+b)/2;

			if(g(data, x_m, par_max) * g(data, b, par_max) < 0)
			{
				a = x_m;
			}

			else if(g(data, a, par_max) * g(data, x_m, par_max) < 0)
			{
				b = x_m;
			}

			else if(g(data, x_m, par_max) == 0)
			{
				return x_m;
			}
		}
	}

	else
	{
		std::cout << "La funzione non rispetta le ipotesi del teorema degli zeri nell'intervallo dato. " << std::endl;
		return 1;
	}

	return x_m;
}

