#include "funzioniutili.h"
#include <fstream>
#include <cmath>
#include <iostream>
#define PHI 0.618

void sortArray(double * array, int N)
{
	double tmp = 0.0;

	for(int i = 0; i < N; ++i) 
	{
		for(int j = 0; j < i; ++j)
		{
			if(array[i] < array[j])
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
}

double minimoArray(double * array, int N)
{
	double min = array[0];

	for(int i = 0; i < N; ++i)
	{
		if(array[i] < min)
		{
			min = array[i];
		}
	}

	return min;
}

double massimoArray(double * array, int N)
{
	double max = array[0];

	for(int i = 0; i < N; ++i)
	{
		if(array[i] > max)
		{
			max = array[i];
		}
	}

	return max;
}

float rand_range(float min, float max)
{
	return min + (max-min)*(rand() / static_cast<float>(RAND_MAX));
}

float rand_TAC(float pdf(float), float min, float max, float yMax)
{
    float x = 0.0;
    float y = 0.0; 

    do {
      x = rand_range(min, max);
      y = rand_range(0, yMax);
    } while(y > pdf(x));

    return x; 
}

float * rand_TCL(float a, float b, int N_distribuzioni, int N)
{
	float sum = 0.0;
	float mean = 0.0;
	float * means = new float[N_distribuzioni];

	for(int i = 0; i < N_distribuzioni; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            sum += rand_range(a, b);
        }
        
        mean = (sum / N);
		means[i] = mean;
        sum = 0.0;
    }

	return means;
}

float rand_exp(float lambda)
{	
	return ((-1)/lambda) * log(1 - rand_range(0,1));
}

float rand_exp_tzero(float t_0)
{	
	return (-1) * t_0 * log(1 - rand_range(0,1));
}

float rand_poisson(float media)
{
	float t = rand_exp(1.);
	int N_eventi = 0;

	while(t < media)
	{
		++N_eventi;
		t += rand_exp(1.);
	}

	return N_eventi;
}

float pdf_gauss(float x, float media, float sigma)
{
	return (1/(sqrt(2*3.14)*sigma))*pow(2.71, -pow((x-media),2)/2*pow(sigma, 2));
}

float pdf_gauss_standard(float x)
{
	float media = 0.0;
	float sigma = 1.0;

	return (1/(sqrt(2*3.14)*sigma))*pow(2.71, -pow((x-media),2)/2*pow(sigma, 2));
}

double find_zeros(double g(double), double a, double b)
{
	double p = 0.0001;
	double x_m;

	if(g(a)*g(b) < 0)
	{
		while(b-a > p)
		{
			x_m = (a+b)/2;

			if(g(x_m)*g(b) < 0)
			{
				a = x_m;	
			}

			else if(g(a)*g(x_m) < 0)
			{
				b = x_m;
			}

			else if(g(x_m) == 0)
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

double find_zeros_recursive(double g(double), double a, double b)
{
	double p = 0.0001;
	double x_m;

	if(g(a)*g(b) < 0)
	{
		x_m = (a+b)/2;

		if(b-a < p)
		{
			return x_m;
		}

		else if(g(x_m)*g(b) < 0)
		{
			return find_zeros_recursive(g, x_m, b);
		}

		else if(g(a)*g(x_m) < 0)
		{
			return find_zeros_recursive(g, a, x_m);
		}
		
	}
	
	else
	{
		std::cout << "La funzione non rispetta le ipotesi del teorema degli zeri nell'intervallo dato. " << std::endl;
		return -1;
	}

	return x_m;
}

double find_min(double g(double), double a, double b)
{
	double p = 0.0001;
	double x_2 = 0.0;
	double x_3 = 0.0;

	while(fabs(b - a) > p)
	{
		x_2 = a + (1. - PHI) * (b - a);
		x_3 = a + PHI * (b - a);

		if(g(x_3) < g(x_2))
		{
			a = x_2;
		}

		else
		{
			b = x_3;
		}
	}

	return (a + b) / 2.0;
}

double find_min_recursive(double g(double), double a, double b)
{
	double p = 0.0001;
	double x_2 = a + (1. - PHI) * (b - a);
	double x_3 = a + PHI * (b - a); 

	if(fabs(b - a) < p)
	{
		return (a + b) / 2.0;
	}
	
	else if(g(x_3) < g(x_2))
	{
		a = x_2;	
		return find_min_recursive(g, a, b);
	}

	else 
	{
		b = x_3;
		return find_min_recursive(g, a, b);
	}
}

double find_max(double g(double), double a, double b)
{
	double p = 0.0001;
	double x_2 = 0.0;
	double x_3 = 0.0;

	while(fabs(b - a) > p)
	{
		x_2 = a + (1. - PHI) * (b - a);
		x_3 = a + PHI * (b - a);

		if(g(x_3) > g(x_2))
		{
			a = x_2;
		}

		else
		{
			b = x_3;
		}
	}

	return (a + b) / 2.0;
}

double find_max_recursive(double g(double), double a, double b)
{
	double p = 0.0001;
	double x_2 = a + (1. - PHI) * (b - a);
	double x_3 = a + PHI * (b - a); 

	if(fabs(b - a) < p)
	{
		return (a + b) / 2.0;
	}
	
	else if(g(x_3) > g(x_2))
	{
		a = x_2;	
		return find_max_recursive(g, a, b);
	}

	else 
	{
		b = x_3;
		return find_max_recursive(g, a, b);
	}
}

int fattoriale(int num)
{
	if (num == 1)
	{
		return 1;
	}

	else
	{
		return num*fattoriale(num-1);
	}
}

std::pair<double, double> integral_hitOrMiss(double g(double), double a, double b, double yMin, double yMax, int N)
{
    std::pair<double, double> integrale;

    int n_hit = 0;
    double x = 0.0;
    double y = 0.0;
    double A = (b - a) * (yMax - yMin);
    double p = 0.0;

    for(int i = 0; i < N; ++i)
    {
        x = rand_range(a, b);
        y = rand_range(yMin, yMax);

        if(y < g(x))
        {
            ++n_hit;
        }
    }

    p = static_cast<double>(n_hit) / N;

    integrale.first = A * (static_cast<double>(n_hit) / static_cast<double>(N));
    integrale.second = (A / sqrt(static_cast<double>(N))) * sqrt(p*(1-p));

    return integrale;
}

std::pair<double, double> integral_crudeMC(double g(double), double a, double b, int N)
{
    std::pair<double, double> integrale;
    double x = 0.0;
    double sum = 0.0;
    double sumsq = 0.0;
    double aspettazione = 0.0; // Valore di aspettazione di g(x) (media dei g(x_i))
    double varianza = 0.0; // Varianza di g(x) (dalla deviazione standard della media dei g(x_i))

    for(int i = 0; i < N; ++i)
    {
        x = rand_range(a, b);
        sum += g(x);
        sumsq += pow(g(x), 2);
    }

    aspettazione = sum / static_cast<double>(N);
    varianza = sumsq / static_cast<double>(N) - pow(aspettazione, 2);

    integrale.first = aspettazione * (b - a);
    integrale.second = sqrt(varianza / static_cast<double>(N)) * (b - a);

    return integrale;
}




