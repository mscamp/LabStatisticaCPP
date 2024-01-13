/* ES1) Dopo aver definito, in un’apposita libreria, una funzione ϕ(x,θ) lineare in due parametri θ, si scriva un programma che generi un insieme di 10 coppie (xi,yi)
tali per cui i punti xi siano disposti casualmente sull’asse orizzontale fra 0 e 10 ed i punti yi siano costruiti a partire dalla formula yi=ϕ(xi,θ)+ϵi.

ES2) Si aggiunga al programma precedente la trasposizione dei punti generati in un TGraphErrors di ROOT.

ES3) Si aggiunga al programma precendente la costruzione di una TF1 di ROOT che contenga il medesimo modello ϕ(x,θ) utilizzato per la generazione pseudo-casuale delle coppie di punti e si utilizzi questa TF1 per fare un fit del TGraphErrors.
Si controlli che il fit abbia avuto successo e si stampi a schermo il valore dei parametri determinati e la loro sigma.

ES7) Si aggiunga all’esercizio 11.3 la scrittura a schermo dell’intera matrice di covarianza dei parametri del fit.
*/

#include <iostream>
#include <ctime>
#include "minimiquadrati.h"
#include "funzioniutili.h"
#include "TApplication.h"
#include "TCanvas.h"
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

	// Modello
	TF1 f_fit("f_fit", phi, 0., 2. * (static_cast<double>(N)/2), 2);
	f_fit.SetLineColor(kViolet);

	// Impostazione dei parametri del modello
	f_fit.SetParameter(0, par0); // Quota
	f_fit.SetParameter(1, par1); // Coefficiente angolare

	// Riempimento dei vector
	for (int i = 0; i < N; ++i)
	{
		x.push_back(rand_range(xmin, xmax));
		y.push_back(f_fit.Eval(x.at(i)) + rand_TCL_minimiquadrati(0, epsilon)); // Viene aggiunta un'incertezza gaussiana sulle yi
	}

	// Definizione del TGraph
	TGraphErrors grafico(N, &x[0], &y[0], &x_err[0], &y_err[0]);

	// Fit con il metodo dei minimi quadrati
	TFitResultPtr fit = grafico.Fit(&f_fit, "S");

	// Stampa a schermo il successo del fit e i parametri ricavati
	std::cout << std::endl;
	std::cout << "Fit andato a buon fine? Status: " << fit->Status() << std::endl;
	std::cout << "Quota: " << f_fit.GetParameter(0) << " +/- " << f_fit.GetParError(0) << std::endl;
	std::cout << "Coefficiente angolare: " << f_fit.GetParameter(1) << " +/- " << f_fit.GetParError(1) << std::endl;

	// Stampa la matrice di covarianza
	fit -> PrintCovMatrix(std::cout);

	// Rappresentazione dei dati con errori associati
	grafico.SetMarkerColor(kTeal);
	grafico.SetMarkerStyle(20);
	grafico.Draw("AP");
	app.Run();

	return 0;
}
