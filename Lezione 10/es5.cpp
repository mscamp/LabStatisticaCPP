/* Utilizzando il generatore di numeri pseudo-casuali secondo una pdf esponenziale sviluppato nelle lezioni passate, si disegni la distribuzione di probabilita’ dello stimatore di τ in funzione del numero di eventi a disposizione per la stima. */

#include <iostream>
#include <vector>
#include "funzioniutili.h"
#include "loglikelihood.h"
#include "vectorstatistiche.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"

int main(int argc, char ** argv)
{
    // Seed casuale
	srand(time(NULL));

	// Controllo sugli argomenti passati da riga di comando
	if(argc != 4)
	{
		std::cout << "Utilizzo: ./es5 t_0 numero_toys numero_eventi" << std::endl;
		return 1;
	}

	// Definizione variabili
	double t_0 = atof(argv[1]); // Valore aspettato di t_0
    int n_toys = atoi(argv[2]); // Numero di toy experiment
	int n_eventi = atoi(argv[3]); // Numero di eventi da generare per ogni toy
    int n_bin = floor(static_cast<double>(n_toys) / 100); // Numero di bin
	std::vector<double> dati; // Vettore di numeri pseudo-casuali esponenziali
	double media = 0.0; // Media dei dati (stimatore di t_0)
	double max_l = 0.0; // Massimo della likelihood
    double min_hist = t_0 - 3 * t_0 / sqrt(n_eventi);
    double max_hist = t_0 + 3 * t_0 / sqrt(n_eventi);

    // Definizione oggetti ROOT
    TApplication app("app", &argc, argv);
    TCanvas canvas;
    TH1F hist("hist", "Distribuzione dello stimatore di t_0", n_bin, min_hist, max_hist);

    // Ciclo sui toy experiment
    for(int i = 0; i < n_toys; ++i)
    {
        // Popola il vector delle misure
	    for(int j = 0; j < n_eventi; ++j)
	    {
		    dati.push_back(rand_exp_tzero(t_0));
	    }

	    // Calcola la media dei valori nel vector
        media = sampleMean(dati);

        // Determina il massimo della likelihood
        max_l = find_max_likelihood(loglikelihood, 0.5 * media, 1.5 * media, dati);

        // Riempie l'istogramma
        hist.Fill(max_l);

        // Svuota il vector
        for(int j = 0; j < n_eventi; ++j)
        {
            dati.pop_back();
        }
    }

    // Styling
    hist.GetXaxis() -> SetTitle("Stimatore di t_0");
    hist.GetYaxis() -> SetTitle("Conteggi per bin");
    hist.SetFillColor(kTeal);
    hist.SetLineColor(kBlack);
    
    // Disegna l'istogramma
    hist.Draw();
    app.Run();

    return 0;
}