/* Si scriva un programma che, fissato un numero NMAX, generi NToys toy experiment, ciascuno contenente un campione di NMAX eventi che seguano una distribuzione a scelta e ne calcoli la media. */

#include <iostream>
#include <ctime>
#include "statistiche.h"
#include "funzioniutili.h"
#define NMAX 500
#define NTOYS 10000

int main(int argc, char ** argv)
{
	// Seed casuale
	srand(time(NULL));

	// Definizione variabili e oggetti
	float t_0 = 5; // Tempo caratteristico dell'esponenziale
	statistiche s_singleToy(NMAX); // Singolo toy experiment
	statistiche s_allToys(NTOYS); // Campione di tutti i toy experiment

	// Ciclo su tutti i toy experiment
	for(int i = 0; i < NTOYS; ++i)
	{
		// Singolo toy experiment
		for(int j = 0; j < NMAX; ++j)
		{
			s_singleToy.addEvent(rand_exp_tzero(t_0));
		}

		s_allToys.addEvent(s_singleToy.sampleMean()); // Distribuzione delle medie
		s_singleToy.reset();
	}

	// Stampa a schermo il risultato
	std::cout << "Media della distribuzione delle medie: " << s_allToys.sampleMean() << std::endl;
	
	return 0;
}
