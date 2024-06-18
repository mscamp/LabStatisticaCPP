/* Si calcoli il valore di Q2 a partire dai punti e dalla funzione di fit ottenuta nell’esercizio precedente. (si ricordi che si può calcolare ϕ(x,θ) utilizzando il metodo TF1::Eval(Double_t))
* Si confronti il numero così ottenuto con quello calcolato da ROOT, che si può ottenere dal risultato del fit utilizzando il metodo FitResult::Chi2 ().
* Si stampi a schermo il valore del numero di gradi di libertà del fit, utilizzando il metodo FitResult::Ndf().*/

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
	double Q2 = 0.0; 
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

	// Determinazione di Q^2
	for(int i = 0; i < N; ++i)
	{
		Q2 += pow((y.at(i) - f_fit.Eval(x.at(i))), 2) / pow(epsilon, 2);
	}
	
	// Confronto tra la stima di Q2 e il valore determinato da ROOT
	std::cout << std::endl;
    std::cout << "Valore Q^2: " << Q2 << std::endl;
	std::cout << "Valore di ROOT: " << fit->Chi2() << std::endl;	
	std::cout << "Gradi di libertà: " << fit->Ndf() << std::endl;

	// Rappresentazione dei dati con errori associati
	grafico.SetMarkerColor(kTeal);
	grafico.SetMarkerStyle(20);
	grafico.Draw("AP");
	app.Run();

	return 0;
}

