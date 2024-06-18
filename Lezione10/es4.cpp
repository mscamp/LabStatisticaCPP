/* Si utilizzi il metodo della bisezione per trovare i due punti τ - στ e τ + στ nel caso dell’esercizio precedente. Si confronti il valore di στ ottenuto in questo modo con quello calcolato a partire dalla media aritmetica dei numeri salvati nel vector.
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
		std::cout << "Utilizzo: ./es4 t_0 numero_eventi" << std::endl;
		return 1;
	}

	// Definizione variabili
	double t_0 = atof(argv[1]); // Valore aspettato di t_0
	int n_eventi = atoi(argv[2]); // Numero di eventi da generare
	std::vector<double> dati; // Vettore di numeri pseudo-casuali esponenziali
	double media = 0.0; // Media dei dati (stimatore di t_0)
	double max_l = 0.0; // Massimo della likelihood
	double h_intersect_sx = 0.0; // Zero di h di sinistra
	double h_intersect_dx = 0.0; // Zero di h di destra
	double stima_sigma = 0.0; // Sigma dello stimatore stimata con likelihood
	double sigma_aspettato = 0.0;

	// Popola il vector delle misure
	for(int i = 0; i < n_eventi; ++i)
	{
		dati.push_back(rand_exp_tzero(t_0));
	}

	// Calcola la media dei valori nel vector
	media = sampleMean(dati);
	sigma_aspettato = media / sqrt(n_eventi);

	// Determina il massimo della loglikelihood (stima di t_0)
	max_l = find_max_likelihood(loglikelihood, 0.5 * media, 1.5 * media, dati);

	// Determina gli zeri di h
	h_intersect_sx = find_zeros_likelihood(h, 0.5 * media, max_l, dati, max_l);
	h_intersect_dx = find_zeros_likelihood(h, max_l, 1.5 * media, dati, max_l);
	stima_sigma = 0.5 * (h_intersect_dx - h_intersect_sx);

	// Stampa a schermo il risultato
	std::cout << "Numero di eventi generati: " << n_eventi << std::endl;
	std::cout << "Media del vettore (valore aspettato di t_0): " << media << std::endl;
	std::cout << "Stima di t_0: " << max_l << std::endl;

	std::cout << std::endl;
	std::cout << "Sigma aspettato: " << sigma_aspettato << std::endl;
	std::cout << "Stima di sigma: " << stima_sigma << std::endl;

	return 0;
}
