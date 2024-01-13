#include "funzioniutili.h"
#include <fstream>
#include <cmath>

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

float pdf_gauss(float x, float media, float sigma)
{
	return (1/(sqrt(2*3.14)*sigma))*pow(2.71, -pow((x-media),2)/2*pow(sigma, 2));
}