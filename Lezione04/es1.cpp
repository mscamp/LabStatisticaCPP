/* Si scriva una funzione che implementi il generatore lineare congruenziale di numeri pseudo-casuali, utilizzando questi parametri:
M = 2147483647
A = 214013
C = 2531011 
*/

#include <iostream>

// Generatore lineare congruenziale
long int * linear_gen(long int seed, long int M, long int A, long int C, int N)
{
	long int * array = new long int[N];
	array[0] = seed; // Il seed è il primo numero della sequenza
	for(int i = 1; i < N; i++)
	{
		array[i] = (A * array[i-1] + C) % M;
	}
	return array;
}


int main(int argc, char ** argv)
{
	long int S = time(NULL); // Seed

	// Parametri generatore lineare
	long int M = 2147483647; 
	long int A = 214013;
	long int C = 2531011;

	int N = 10; // Dimensione della successione
	long int * p = linear_gen(S, M, A, C, N); // Successione di numeri casuali

	// Stampa a schermo la successione
	for (long int i = 0; i < N; ++i)
	{
		std::cout << "Numero " << i << ": " << p[i] << std::endl;
	}

	delete[] p; // Deallocazione memoria
	return 0;
}
