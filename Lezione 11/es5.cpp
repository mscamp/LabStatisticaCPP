/* Utilizzando la tecnica dei toy experiment, si generino 10,000 esperimenti di fit con il modello studiato negli esercizi precedenti e si riempia un istogramma dei valori di Q2 ottenuti. */

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
	int n_bin = 20 * (N / 2); // Numero di bin
	double epsilon = 0.15; // Incertezza sulle yi
	double xmin = 0.0; // Range di valori delle xi
	double xmax = 10.0;
	double par0 = 0.4; // Quota
	double par1 = 1.5; // Coefficiente angolare
	std::vector<double> x; // Vettore delle x
	std::vector<double> y; // Vettore delle y
	std::vector<double> x_err(N,0.); // Vettore delle incertezze su x
	std::vector<double> y_err(N, epsilon); // Vettore delle incertezze su y

	// Definizione oggetti di ROOT
	TApplication app("app", &argc, argv);
	TCanvas canvas;
	TH1F hist("hist", "Distribuzione dei Q^2", n_bin, 0, 4 * (static_cast<double>(N)/2));

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
			y.push_back(f_fit.Eval(x.at(i)) + rand_TCL_minimiquadrati(0, epsilon));
		}
	
		// Definizione del grafico
		TGraphErrors grafico(N, &x[0], &y[0], &x_err[0], &y_err[0]);
	
		// Fit con il metodo dei minimi quadrati
		TFitResultPtr fit = grafico.Fit(&f_fit, "SQ");

		// Riempie istogramma con i valori di Q2
		hist.Fill(fit->Chi2());

		// Reset dei vector
		for (int j = 0; j < N; ++j)
		{
			x.pop_back();
			y.pop_back();
		}
	}
	
	// Rappresentazione istogramma (distribuzione CHI2)
	hist.SetFillColor(kOrange + 1);
	hist.SetLineColor(kBlack);
	hist.Draw();
	app.Run();

	return 0;
}
