#include "statistiche.h"
#include <Rtypes.h>
#include <cmath>

// Costruttore
statistiche::statistiche(int N): 
    size_m(N),
    last_index_m(0)
{
    array_m = new double[size_m];
}

// Distruttore
statistiche::~statistiche()
{
    delete[] array_m;
}

// Metodi
void statistiche::addEvent(double value)
{
    if(last_index_m >= size_m)
    {
        double * tmp = new double[2 * size_m]; // Crea array temporaneo di dimensione doppia
        
        // Copia gli elementi del vecchio array nel nuovo
        for(int i = 0; i < size_m; ++i)
        {
            tmp[i] = array_m[i];
        }

        delete[] array_m; // Deallocazione memoria
        array_m = tmp; // Riassegna lo spazio allocato a array_m
    }

    array_m[last_index_m] = value;
    ++last_index_m;
}

double statistiche::sampleMean() const
{
    double sum = 0.0;

    for(int i = 0; i < last_index_m; ++i)
    {
        sum += array_m[i];
    }

    if(last_index_m != 0)
    {
        return (sum)/(last_index_m);
    }

    else 
    {
        return 0;
    }
}

double statistiche::sampleVariance(bool bessel) const
{
    double sumsq = 0.0; // Somma scarti quadratici
    double mean = sampleMean();

    for(int i = 0; i < last_index_m; ++i)
    {
        sumsq += pow((array_m[i] - mean), 2);
    }

    if(last_index_m != 0 && bessel == false)
    {
        return (sumsq)/(last_index_m);
    }
    
    // Correzione di Bessel
    else if(last_index_m != 0 && bessel == true)
    {
        return (sumsq)/(last_index_m - 1);
    }

    else  
    {
        return 0;
    }
}

double statistiche::sampleStd(bool bessel) const
{
    return sqrt(sampleVariance(bessel));
}

double statistiche::sampleMeanStd(bool bessel) const
{
    if (last_index_m != 0) {
        return sampleStd(bessel)/sqrt(last_index_m);
    }

    else   
    {
        return 0;
    }
}

double statistiche::sampleSize() const
{
    return last_index_m;
}

double statistiche::element(int index) const
{
    if(index >= 0 && index < last_index_m)
    {
        return array_m[index];
    }

    else
    {
        return 0;
    }
}

double statistiche::minimumValue() const
{
    double min = array_m[0];

	for(int i = 0; i < last_index_m; ++i)
	{
		if(array_m[i] < min)
		{
			min = array_m[i];
		}
	}

	return min;
}

double statistiche::maximumValue() const
{
    double max = array_m[0];

	for(int i = 0; i < last_index_m; ++i)
	{
		if(array_m[i] > max)
		{
			max = array_m[i];
		}
	}

	return max;
}

void statistiche::reset()
{
    // Riempie array con zeri
    for(int i = 0; i < last_index_m; ++i)
    {
        array_m[i] = 0.0;
    }

    last_index_m = 0;
}