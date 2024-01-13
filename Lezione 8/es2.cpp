/* Si aggiunga al programma precedente un oggetto di tipo TH1F che visualizzi la distribuzione delle medie al variare dei toy experiment. */

#include <Rtypes.h>
#include <iostream>
#include <ctime>
#include "statistiche.h"
#include "funzioniutili.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"
#define NMAX 500
#define NTOYS 1000000

int main(int argc, char ** argv)
{
	// Seed casuale
	srand(time(NULL));

	// Definizione variabili e oggetti
	double singleMean = 0.0;
	float t_0 = 5; // Tempo caratteristico dell'esponenziale
	statistiche s_singleToy(NMAX);
	statistiche s_allToys(NTOYS);

	// Definizione oggetti ROOT
	TApplication app("app", &argc, argv);
	TCanvas canvas;
	TH1F hist("hist", "Distribuzione delle medie", sqrt(NTOYS), 0., 2 * t_0);

	// Ciclo su tutti i toy experiment
	for(int i = 0; i < NTOYS; ++i)
	{
		// Singolo toy experiment
		for(int j = 0; j < NMAX; ++j)
		{
			s_singleToy.addEvent(rand_exp_tzero(t_0));
		}

		singleMean = s_singleToy.sampleMean(); // Media di un toy experiment

		s_allToys.addEvent(singleMean); // Distribuzione delle medie
		hist.Fill(singleMean);
		s_singleToy.reset();
	}

	// Stampa a schermo media e varianza
	std::cout << "Media della distribuzione delle medie: " << s_allToys.sampleMean() << std::endl;
	std::cout << "Deviazione standard della distribuzione delle medie: " << s_allToys.sampleStd() << std::endl;
	
	// Styling
	hist.GetXaxis() -> SetTitle("Medie dei toy experiment");
	hist.GetYaxis() -> SetTitle("PDF");
	hist.SetFillColor(kOrange + 1);
	hist.SetLineColor(kBlack);

	// Disegna istogramma
	hist.Draw();
	app.Run();
	
	return 0;
}
