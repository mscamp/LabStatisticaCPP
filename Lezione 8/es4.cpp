/* Si utilizzino due TGraph per confrontare l’evoluzione della deviazione standard della media calcolata per ogni singolo toy con la deviazione standard del campione delle medie al variare del numero di eventi generati in un singolo toy experiment. */

#include <iostream>
#include <ctime>
#include "statistiche.h"
#include "funzioniutili.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TH1F.h"
#define NTOYS 10
#define DIM 7

int main(int argc, char ** argv)
{
	// Seed casuale
	srand(time(NULL));

	// Definizione variabili e oggetti
	float t_0 = 5; // Tempo caratteristico dell'esponenziale
	int NMax[DIM] = {10, 50, 100, 500, 1000, 10000, 100000};
	statistiche s_singleToy(NMax[6]);
	statistiche s_allToys(NTOYS);

	// Definizione oggetti ROOT
	TApplication app("app", &argc, argv);
	TCanvas canvas;
	TGraph * grafico1 = new TGraph;
	TGraph * grafico2 = new TGraph;
	TMultiGraph mg; // Oggetto multigraph, permette di rappresentare due TGraph in una stessa canvas

	// Ciclo sulla dimensione dei singoli toy experiment
	for(int r = 0; r < DIM; ++r)
	{
		// Ciclo su tutti i toy experiment di una certa dimensione
		for(int i = 0; i < NTOYS; ++i)
		{
			// Singolo toy experiment
			for(int j = 0; j < NMax[r]; ++j)
			{
				s_singleToy.addEvent(rand_exp_tzero(t_0));
			}

			// Andamento delle deviazioni standard della media per i singoli toy experiment
			grafico1->SetPoint(grafico1->GetN(), NMax[r], s_singleToy.sampleMeanStd());

			s_allToys.addEvent(s_singleToy.sampleMean()); // Distribuzione delle medie
			s_singleToy.reset();
		}

		// Andamento della deviazione standard della distribuzione delle medie
		grafico2->SetPoint(grafico2->GetN(), NMax[r], s_allToys.sampleStd());
		s_allToys.reset();
	}

	// Styling
	grafico1->SetLineColor(kBlue);
	grafico1->SetLineWidth(3);
	grafico1->SetMarkerStyle(20);
	grafico1->SetMarkerSize(1);
	grafico1->SetMarkerColor(kGreen);
	grafico2->SetLineColor(kRed);
	grafico2->SetLineWidth(3);
	grafico2->SetMarkerStyle(20);
	grafico2->SetMarkerSize(1);
	grafico2->SetMarkerColor(kGreen);

	// Aggiunge i graph al multigraph e stampa su canvas
	mg.Add(grafico1);
	mg.Add(grafico2);
	mg.Draw("ALP");
	app.Run();

	// Deallocazione memoria
	delete grafico1;
	delete grafico2;

	return 0;
}
