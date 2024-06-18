/* Si mostri che inizializzare il seed di un generatore di numeri pseudo-casuali equivale ad inserirsi in una sequenza di numeri pseudo-casuali ad un qualunque punto. */

#include <iostream>
#include "pseudorand.h"

int main(int argc, char ** argv)
{
	// Parametri del generatore
	long int M = 2147483647;
	long int A = 214013;
	long int C = 2531011;
	long int N = 10;
	long int S = time(NULL); // Seed
	long int * p1; // Puntatore alla prima sequenza
	long int * p2; // Puntatore alla seconda sequenza
	long int * p3; // Puntatore alla terza sequenza

	pseudorand r(M,A,C,N); // Oggetto pseudorand
	r.changeseed(S); // Imposta il seed
	p1 = r.linear_gen(); // Genera sequenza

	// Stampa a schermo la prima sequenza
	for(int i = 0; i < N; ++i)
	{
		std::cout << "Numero " << i << ": " << p1[i] << std::endl;

		// Salva il quarto elemento come seed per riutilizzarlo in un'altra sequenza
		if(i == 4)
		{
			S = p1[i];	
		}
	}

	std::cout << std::endl;
	std::cout << "Scelgo come seed l'elemento 4 dell'array ( " << S << " ) " << std::endl;

	r.changeseed(S); // Modifica il seed

	p2 = r.linear_gen(); // Genera la sequenza con il nuovo seed

	// Stampa a schermo la seconda sequenza
	for(int i = 0; i < N; ++i)
	{
		std::cout << "Numero " << i << ": " << p2[i] << std::endl;

		// Salva il settimo elemento come seed per riutilizzarlo in un'altra sequenza
		if(i == 7)
		{
			S = p2[i];
		}
	}
	
	std::cout << "\n";
	std::cout << "Scelgo come seed l'elemento 7 dell'array ( " << S << " ) " << std::endl;

	r.changeseed(S); // Modifica il seed

	p3 = r.linear_gen(); // Genera la sequenza con il nuovo seed
	
	// Stampa a schermo la terza sequenza
	for(int i = 0; i < N; ++i)
	{
		std::cout << "Numero " << i << ": " << p3[i] << std::endl;
	}

	return 0;

}

	
