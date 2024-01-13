/* Si legga il file di testo eventi_unif.txt:
 * si calcoli la media dei numeri contenuti nel file di testo;
 * si calcoli la varianza dei numeri contenuti nel file di testo;
 * si calcoli la deviazione standard dei numeri contenuti nel file di testo;
 * si calcoli la deviazione standard della media dei numeri contenuti nel file di testo; */

#include <iostream>
#include <cmath>
#include <fstream>

double sampleMean(double * arr, int dim)
{
	double sum = 0.0;

	for(int i = 0; i < dim; i++)
	{
		sum += arr[i];
	}

	return sum / static_cast<double>(dim);
}

double sampleVariance(double * arr, int dim)
{
	double mean = sampleMean(arr, dim);
	double sqsum = 0.0;

	for(int i = 0; i < dim; i++)
	{
		sqsum += pow(mean - arr[i], 2);
	}

	return sqsum / static_cast<double>(dim);
}

double sampleStd(double * arr, int dim)
{
	return sqrt(sampleVariance(arr, dim));
}

double sampleMeanStd(double * arr, int dim)
{
	return (sampleStd(arr, dim))/(sqrt(dim));
}

int main(int argc, char ** argv)
{
	// Dichiarazione variabili
	int N = 0; // Numero eventi
	double value = 0.0; // Variabile ausiliaria

	// Dichiarazione oggetti
	std::ifstream f;

	// Apre il file
	f.open("eventi_unif.txt", std::ios::in);

	// Determina la dimensione del file
	while(true)
	{
		f >> value;
		++N;

		if(f.eof() == true)
		{
			--N;
			break;
		}
	}

	f.close(); // Chiude il file
			   
	// Dichiarazione array dinamico
	double * array = new double[N];

	// Apre il file
	f.open("eventi_unif.txt", std::ios::in);

	// Riempimento array
	for(int i = 0; i < N; ++i)
	{
		f >> array[i];
	}

	f.close(); // Chiude il file
	
	// Stampa a schermo le grandezze richieste
	std::cout << "Media: " << sampleMean(array, N) << std::endl;
	std::cout << "Varianza: " << sampleVariance(array, N) << std::endl;
	std::cout << "Deviazione standard: " << sampleStd(array, N) << std::endl;
	std::cout << "Deviazione standard della media: " << sampleMeanStd(array, N) << std::endl;
	
	delete[] array; // Deallocazione memoria
	return 0;
}
