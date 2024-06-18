/* Si modifichi la funzione loglikelihood in modo che calcoli il logaritmo del prodotto dei valori della funzione di densità di probabilità, piuttosto che la somma dei singoli logaritmi. Come cambia il comportamento dell’algoritmo? */

#include <iostream>
#include <vector>
#include "funzioniutili.h"
#include "loglikelihood.h"
#include "vectorstatistiche.h"

// Calcola logaritmo del prodotto delle pdf invece della somma dei logaritmi
double loglikelihood_product(const std::vector<double> & x, double par)
{
	double prod = 1.0;

	for(int i = 0; i < x.size(); ++i)
	{
		prod *= pdf_esponenziale(x.at(i), par);
	}

	return log(prod);
}

// x2 e x3 sono invertiti
double find_max_likelihood_modified
( double f(const std::vector<double> &, double),
  double xmin, 
  double xmax, 
  const std::vector<double> & data,
  double precision = 0.0001 )

{
	double r = 0.618;
	double x2 = 0;
	double x3 = 0;
	double larghezza = fabs(xmax - xmin);

	while (larghezza > precision)
	{
		x2 = xmin + r * (xmax - xmin);
		x3 = xmin + (1 - r) * (xmax - xmin);

		if (f(data, x3) < f(data, x2))
		{  
			xmin = x3;
			xmax = xmax;
		}
		
		else
		{
			xmax = x2;
			xmin = xmin;
		}

		larghezza = fabs(xmax - xmin);
		std::cout << "Intervallo: [ " << x3 << " " << x2 << " ]" << std::endl;
	}

	return (xmin + xmax)/2;
}



int main(int argc, char ** argv)
{
	// Seed casuale
	srand(time(NULL));

	// Controllo sugli argomenti passati da riga di comando
	if(argc != 3)
	{
		std::cout << "Utilizzo: ./es3 t_0 numero_eventi" << std::endl;
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
	max_l = find_max_likelihood_modified(loglikelihood_product, 0.97 * media, 1.03 * media, dati);

	// Stampa a schermo il risultato
	std::cout << std::endl;
	std::cout << "Numero di eventi generati: " << n_eventi << std::endl;
	std::cout << "Media del vettore (valore aspettato di t_0): " << media << std::endl;
	std::cout << "Stima di t_0: " << max_l << std::endl;

	return 0;
}

/* RISPOSTA: L'algoritmo è molto meno stabile, converge al valore aspettato solo se l'intervallo di ricerca del massimo è stretto: questo perché il logaritmo di un numero è più piccolo del numero stesso e varia su un intervallo minore */