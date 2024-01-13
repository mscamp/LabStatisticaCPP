/* Si utilizzi la classe statistiche sviluppata durante la Lezione 4 per confrontare la deviazione standard della media calcolata per ogni singolo toy con la deviazione standard del campione delle medie. */

#include <iostream>
#include <ctime>
#include "statistiche.h"
#include "funzioniutili.h"
#define NMAX 500
#define NTOYS 10

int main(int argc, char ** argv)
{
	// Seed casuale
	srand(time(NULL));

	// Definizione variabili e oggetti
	float t_0 = 5; // Tempo caratteristico dell'esponenziale
	statistiche s_singleToy(NMAX);
	statistiche s_allToys(NTOYS);

	// Ciclo su tutti i toy experiment
	for(int i = 0; i < NTOYS; ++i)
	{
		// Singolo toy experiment
		for(int j = 0; j < NMAX; ++j)
		{
			s_singleToy.addEvent(rand_exp_tzero(t_0));
		}

		// Stampa la deviazione standard della media per ogni toy experiment
		std::cout << "Deviazione standard della media del toy " << i + 1 << ": " << s_singleToy.sampleMeanStd() << std::endl;

		s_allToys.addEvent(s_singleToy.sampleMean()); // Distribuzione delle medie
		s_singleToy.reset();
	}

	// Stampa la deviazione standard delle medie di tutti i toy
	std::cout << "Deviazione standard del campione delle medie: " << s_allToys.sampleStd() << std::endl;

	return 0;
}
