/* Si aggiunga al programma precedente il codice sorgente che riempia un istogramma con i numeri presenti nel vector dove sono stati trasferiti e che visualizzi l’istogramma a schermo. */

#include <iostream>
#include <vector>
#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "funzioniutili.h"

int main(int argc, char ** argv)
{
	// Seed casuale
	srand(time(NULL));

	// Controllo sugli argomenti passati da riga di comando
	if(argc != 3)
	{
		std::cout << "Utilizzo: ./es2 t_0 numero_eventi" << std::endl;
		return 1;
	} 

	// Definizione variabili
	double t_0 = atof(argv[1]); // Tempo caratteristico dell'esponenziale
	int n_eventi = atoi(argv[2]); // Numero di eventi da generare
	int n_bin = floor(sqrt(n_eventi)) + 1; // Numero di bin
	std::vector<double> dati; // Vettore delle misure
	
	// Definizione oggetti ROOT
	TApplication app("app", &argc, argv);
	TCanvas canvas;
	TH1F hist("hist", "pdf esponenziale", sqrt(n_bin), 0.0, 5 * t_0);

	// Popola il vector con numeri casuali esponenziali
	for(int i = 0; i < n_eventi; ++i)
	{
		dati.push_back(rand_exp_tzero(t_0));
	}

	// Riempie l'istogramma
	for(int i = 0; i < n_eventi; ++i)
	{
		hist.Fill(dati.at(i));
	}

	// Styling 
	hist.SetFillColor(kOrange + 1);
	hist.SetLineColor(kBlack);

	// Disegna istogramma
	hist.Draw();
	app.Run();

	return 0;
}
