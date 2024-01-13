/* In regime asintotico, la distribuzione degli scarti (τ - τvero) / στ ha forma Normale
* Si utilizzi il metodo dei toy experiment per riempire l’istogramma degli scarti, dato un numero di eventi per toy experiment.
* Si calcoli la media e la sigma della distribuzione degli scarti e se ne disegni il valore al variare del numero di eventi a disposizione per la stima, riempiendo un TGraph con il numero di eventi a disposizione sull’asse orizziontale ed il valore del parametro sull’asse verticale.
*/

#include <iostream>
#include <string>
#include <vector>
#include "funzioniutili.h"
#include "loglikelihood.h"
#include "vectorstatistiche.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"

int main(int argc, char ** argv)
{
    // Seed casuale
	srand(time(NULL));

	// Controllo sugli argomenti passati da riga di comando
	if(argc != 2)
	{
		std::cout << "Utilizzo: ./es5 t_0" << std::endl;
		return 1;
	}

	// Definizione variabili
	double t_0 = atof(argv[1]); // Valore aspettato di t_0
    std::vector<int> n_toys = {100, 1000, 10000, 1000000}; // Numero di toy experiment
	int n_eventi = 10000; // Numero di eventi da generare per ogni toy
    int n_bin = 0; 
	std::vector<double> dati; // Vettore di numeri pseudo-casuali esponenziali
    std::vector<double> scarti; // Vettore degli scarti
	double media = 0.0; // Media dei dati (stimatore di t_0)
	double sigma_aspettato = 0.0; 
    double scarto = 0.0;

    // Definizione oggetti ROOT
    TApplication app("app", &argc, argv);
    std::vector<TH1F> hist_vec; // Vettore degli istogrammi
    TGraph grafico;

    // Ciclo sul numero di toys
    for(int r = 0; r < n_toys.size(); ++r)
    {
        // Crea istogramma r-esimo
        n_bin = floor(sqrt(n_toys.at(r))) + 1;// Numero di bin
        std::string hist_name = "TOY_NUM " + std::to_string(n_toys.at(r));
        TH1F hist(hist_name.c_str(), "Distribuzione degli scarti", n_bin, -2, 2);

        // Styling
        hist.GetXaxis() -> SetTitle("Stimatore di t_0");
        hist.GetYaxis() -> SetTitle("Conteggi per bin");
        hist.SetFillColor(kTeal);
        hist.SetLineColor(kBlack);

        // Ciclo sui toy experiment
        for(int i = 0; i < n_toys.at(r); ++i)
        {
            if(i % 1000 == 0)
            {
                std::cout << "Running Toy " << r << "..." << std::endl;
            }

            // Popola il vector delle misure
	        for(int j = 0; j < n_eventi; ++j)
	        {
		        dati.push_back(rand_exp_tzero(t_0));
	        }

	        // Calcola media e deviazione standard dello stimatore
            media = sampleMean(dati);
	        sigma_aspettato = media / sqrt(n_eventi);

            // Scarto (τ - τvero) / στ
            scarto = (media - t_0) / sigma_aspettato;

            // Riempie l'istogramma
            scarti.push_back(scarto);
            hist.Fill(scarto);

            // Svuota il vector dei dati
            for(int j = 0; j < n_eventi; ++j)
            {
                dati.pop_back();
            }
        }
        
        // Riempie vettore degli istogrammi e grafico
        hist_vec.push_back(hist);
        grafico.SetPoint(grafico.GetN(), n_toys.at(r), sampleMean(scarti));

        // Svuota il vector degli scarti
        for(int i = 0; i < n_toys.at(r); ++i)
        {
            scarti.pop_back();
        }
    }

    // Disegna l'istogramma e il TGraph
    TCanvas canvas1;
    canvas1.Divide(2,2 , 0.0001, 0.0001);
    canvas1.SetLeftMargin(0.10);

    for(int r = 0; r < n_toys.size(); ++r)
    {
        canvas1.cd(r + 1);
        hist_vec.at(r).Draw("hist");
    }

    canvas1.Update();
    
    TCanvas canvas2;
    canvas2.SetLogx();
    canvas2.SetLogy();
    canvas2.SetLeftMargin(0.10);
    grafico.SetMarkerStyle(20);
    grafico.SetMarkerSize(1);
    grafico.SetMarkerColor(kRed);
    grafico.Draw("APL");
    canvas2.Update();

    // TApplication
    app.Run();

    return 0;
}