/* Si svolga l’esercizio precedente utilizzando una funzione ricorsiva.
* Quale delle due implementazioni è più rapida?
*/

#include "TCanvas.h"
#include "TF1.h"
#include "TMarker.h"
#include <iostream>
#include <cmath>
#include "funzioniutili.h"

double f(double x)
{
	return pow(x, 2) + 7.3 * x + 4;
}

int main(int argc, char ** argv)
{
	// Definizione variabili
	double x_0 = -10;
	double x_1 = 10;
	double minimo = find_min_recursive(f, x_0, x_1);

	// Definizione oggetti ROOT
	TCanvas grafico;
	TF1 func("func", "x*x + 7.3*x + 4", x_0, x_1);
	TMarker p_min(minimo, f(minimo), 20);

    // Stampa a schermo il risultato
	std::cout << "Il minimo della funzione e' in x = " << minimo << " e la funzione in quel punto vale f(x) = " << f(minimo) << std::endl;

	// Disegna il grafico della funzione
	func.Draw();
	p_min.Draw("SAME");
	grafico.Print("es5.png", "png");

	return 0;
}

