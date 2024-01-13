/* Si determini con il metodo della bisezione lo zero della funzione g(x) = cos(x) nell’intervallo (0, 4).
* Quali controlli sono stati omessi, nell’implementazione dell’algoritmo descritta nel testo della lezione, che potrebbero accelerare il risultato?
*/

#include "TCanvas.h"
#include "TF1.h"
#include "TMarker.h"
#include "funzioniutili.h"

double f(double x)
{
	return cos(x);
}

int main(int argc, char ** argv)
{
	// Definizione variabili
	double x_0 = 0;
	double x_1 = 4;
	double zero = find_zeros(f, x_0, x_1);

	// Definizione oggetti ROOT
	TCanvas grafico;
	TF1 funzione("funzione", "cos(x)", x_0, x_1);
	TMarker P(zero, 0.0, 20);

	// Stampa a schermo il risultato
	std::cout << "Zero della funzione tra " << x_0 << " e " << x_1 << ": " << zero << std::endl;

	// Stampa il grafico su una canvas
	funzione.Draw();
	P.Draw();
	grafico.Print("es1.png", "png");

	return 0;
}	
