/* Si scriva una libreria di funzioni per determinare il parametro τ della distribuzione esponenziale a partire da un vector di numeri riempito con numeri pseudo-casuali distribuiti secondo una distribuzione di densità di probabilità esponenziale.
* Si implementino i prototipi delle funzioni presentate a lezione.
* Si confronti il risultato ottenuto con la media dei numeri salvati nel vector.
* Come dipende il risultato dall’intervallo inziale passato alla funzione sezione_aurea_max?
*/

#include <iostream>
#include <vector>
#include "funzioniutili.h"
#include "loglikelihood.h"
#include "vectorstatistiche.h"

int main(int argc, char ** argv)
{
	// Seed casuale
	srand(time(NULL));

	// Controllo sugli argomenti passati da riga di comando
	if(argc != 3)
	{
		std::cout << "Utilizzo: ./es1 t_0 numero_eventi" << std::endl;
		return 1;
	}

	// Definizione variabili
	double t_0 = atof(argv[1]); // Valore aspettato di t_0
	int n_eventi = atoi(argv[2]); // Numero di eventi da generare
	std::vector<double> dati; // Vettore di numeri pseudo-casuali esponenziali
	double media = 0.0; // Media dei dati (stimatore di t_0)
	double max_l = 0.0; // Massimo della likelihood

	// Popola il vector delle misure
	for(int i = 0; i < n_eventi; ++i)
	{
		dati.push_back(rand_exp_tzero(t_0));
	}

	// Calcola la media dei valori nel vector
	media = sampleMean(dati);

	// Determina il massimo della loglikelihood (stima di t_0)
	max_l = find_max_likelihood(loglikelihood, 0.5 * media, 1.5 * media, dati);

	// Stampa a schermo il risultato
	std::cout << "Numero di eventi generati: " << n_eventi << std::endl;
	std::cout << "Media del vettore (valore aspettato di t_0): " << media << std::endl;
	std::cout << "Stima di t_0: " << max_l << std::endl;

	return 0;
}
