/* Si svolgano i due esercizi precedenti cercando il massimo di una funzione a scelta. */
#include "TCanvas.h"
#include "TF1.h"
#include "TMarker.h"
#include <iostream>
#include <cmath>
#include "funzioniutili.h"

double f(double x)
{
	return -pow(x, 2) + 7.3 * x + 4;
}

int main(int argc, char ** argv)
{
	// Definizione variabili
	double x_0 = -10;
	double x_1 = 10;
	double massimo = find_max(f, x_0, x_1);

	// Definizione oggetti ROOT
	TCanvas grafico;
	TF1 func("func", "-x*x + 7.3*x + 4", x_0, x_1);
	TMarker p_max(massimo, f(massimo), 20);

    // Stampa a schermo il risultato
	std::cout << "Il massimo della funzione e' in x = " << massimo << " e la funzione in quel punto vale f(x) = " << f(massimo) << std::endl;

	// Disegna il grafico della funzione
	func.Draw();
	p_max.Draw("SAME");
	grafico.Print("es6-1.png", "png");

	return 0;
}

