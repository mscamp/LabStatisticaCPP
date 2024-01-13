/* Si modifichi il programma precedente alterando volutamente l’incertezza sperimentale associata ai punti yi nei TGraphErrors e si verifichi che si possa risalire alla incertezza utilizzata nella generazione dei punti tramite il valore di aspettazione della variabile Q2. */

#include <iostream>
#include <ctime>
#include "minimiquadrati.h"
#include "funzioniutili.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"

int main(int argc, char ** argv)
{
	// Seed casuale
	srand(time(NULL));

	// Definizione variabili 
	int N = 10; // Numero di coppie di valori
	int n_toys = 10000; // Numero di toy experiment
	int n_bin = 20 * N; // Numero di bin
	double epsilon = 0.15; // Incertezza sulle yi
	double xmin = 0.0; // Range di valori delle xi
	double xmax = 10.0;
	double par0 = 0.4; // Quota
	double par1 = 1.5; // Coefficiente angolare
    double alt = 0.23; // Alteratore dell'incertezza
    double ndf = 0.0;
    double aspettazione_Q2 = 0.0;
	std::vector<double> x; // Vettore delle x
	std::vector<double> y; // Vettore delle y
	std::vector<double> x_err(N,0.); // Vettore delle incertezze su x
	std::vector<double> y_err(N, epsilon); // Vettore delle incertezze su y

	// Definizione oggetti di ROOT
	TApplication app("app", &argc, argv);
	TCanvas canvas;
	TH1F hist("hist", "Distribuzione dei Q^2", n_bin, 0, static_cast<double>(N)/5);

	// Modello
	TF1 f_fit("f_fit", phi, 0, 2 * (static_cast<double>(N)/2), 2);

	// Setting dei parametri aspettati
	f_fit.SetParameter(0, par0);
	f_fit.SetParameter(1, par1);

	// 10000 toy experiment
	for (int k = 0; k < n_toys; ++k)
	{
		// Singolo toy experiment

		// Riempimento dei vector
		for (int i = 0; i < N; ++i)
		{
			x.push_back(rand_range(xmin, xmax));
			y.push_back(f_fit.Eval(x.at(i)) + rand_TCL_minimiquadrati(0, epsilon * alt));
		}
	
		// Definizione del grafico
		TGraphErrors grafico(N, &x[0], &y[0], &x_err[0], &y_err[0]);
	
		// Fit con il metodo dei minimi quadrati
		TFitResultPtr fit = grafico.Fit(&f_fit, "SQ");

		// Riempie istogramma con i valori di Q2
		hist.Fill(fit->Chi2());

        // Salva il numero di gradi di libertà
        if(k == 0)
        {
            ndf = fit->Ndf();
        }

		// Reset dei vector
		for (int j = 0; j < N; ++j)
		{
			x.pop_back();
			y.pop_back();
		}
	}

    // Determina incertezza
    aspettazione_Q2 = sqrt(hist.GetMean() / ndf) * epsilon;
    std::cout << "Sigma modificata: " << epsilon * alt << std::endl;
    std::cout << "Stima mediante l'aspettazione di Q^2: " << aspettazione_Q2 << std::endl;
	
	// Rappresentazione istogramma (distribuzione CHI2)
	hist.SetFillColor(kOrange + 1);
	hist.SetLineColor(kBlack);
	hist.Draw();
	app.Run();

	return 0;
}
