/* Si implementi il generatore nella forma di una classe, che contenga un metodo di generazione di un numero casuale ed un metodo di impostazione del seed di generazione, utilizzando appropriatamente un membro private della classe per salvare questa informazione.*/

#include <iostream>
#include "pseudorand.h"

int main(int argc, char ** argv)
{
	// Dimensione della successione
	int N = 10;

	// Parametri del generatore lineare
	long int M = 2147483647;
	long int A = 214013;
	long int C = 2531011;
	long int S = time(NULL); // Seed
	long int * p; // Puntatore alla successione

	pseudorand r(M,A,C,N); // Oggetto pseudorand
	r.changeseed(S); // Imposta il seed con il metodo changeseed()
	p = r.linear_gen(); // Genera sequenza 

	// Stampa a schermo la sequenza
	for(int i = 0; i < N; ++i)
	{
		std::cout << "Numero " << i << ": " << p[i] << std::endl;
	}

	return 0;
}
