/* Si scriva un programma che generi numeri pseudo-casuali distribuiti secondo una funzione esponenziale e li scriva in un vector<double>.
* Si faccia in modo che il tempo caratteristico dell’esponenziale ed numero di eventi da generare sia passato a linea di comando come parametro del programma eseguibile.
*/

#include <iostream>
#include <vector>
#include "funzioniutili.h"

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
	double t_0 = atof(argv[1]); // Tempo caratteristico dell'esponenziale
	int n_eventi = atoi(argv[2]); // Numero di eventi da generare
	std::vector<double> dati; // Vettore delle misure
	
	// Popola il vector con numeri casuali esponenziali
	for(int i = 0; i < n_eventi; ++i)
	{
		dati.push_back(rand_exp_tzero(t_0));
	}
	
	// Stampa il contenuto dell'array
	for(int i = 0; i < dati.size(); ++i)
	{
		std::cout << "Valore " << i + 1 << ": " << dati.at(i) << std::endl;
	}

	return 0;
}
