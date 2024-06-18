/* Si scriva una funzione loglikelihood che calcoli il logaritmo della verosimiglianza al variare del parametro t0, per un campione di eventi pseudo-casuali generati secondo le istruzioni dell’Esercizio 1. Si scriva la funzione in modo che possa essere utilizzata per costruire una TF1 di ROOT che ne disegni l’andamento in funzione di t0. Si utilizzi il seguente prototipo: 

Double_t loglikelihood (Double_t * x, Double_t * par)
{
  // implementazione della funzione
}

dove:
* Double_t * x è la variabile libera nel disegno, dunque t0
* Double_t * par sono le informazioni aggiuntive dal punto di vista del disegno da effettuare, dunque il campione. Si trovi il modo di passare alla funzione il campione di eventi e la sua lunghezza tramite l’argomento par. Si ricordi che il logaritmo della verosimiglianza è definito solamente per il caso in cui la likelihood sia strettamente positiva.
*/

#include <iostream>
#include <cmath>
#include <vector>
#include "TF1.h"
#include "TCanvas.h"
#include "funzioniutili.h"
#include "vectorstatistiche.h"

// I parametri sono le misure, mentre x[0] = t_0 è variabile indipendente
double loglikelihood(double * x, double * par)
{	
	double sum = 0.0;

	// Ciclo sul numero di eventi + 1 (dimensione dell'array). par[0] = n_eventi
	for(int i = 1; i < par[0] + 1; ++i)
	{
		sum += log(pdf_esponenziale(par[i], x[0]));
	}

	return sum;
}

int main(int argc, char ** argv)
{
	// Seed casuale
	srand(time(NULL));

	// Controllo sugli argomenti passati da riga di comando
	if(argc != 3)
	{
		std::cout << "Utilizzo: ./es4 t_0 numero_eventi" << std::endl;
		return 1;
	} 

	// Definizione variabili
	double t_0 = atof(argv[1]); // Tempo caratteristico dell'esponenziale
	int n_eventi = atoi(argv[2]); // Numero di eventi da generare
	std::vector<double> dati; // Vettore dei campioni (contiene anche la propria lunghezza)
	dati.push_back(n_eventi);
	double media = 0.0;
	double sigma = 0.0;
	double min = 0.0; // Minimo dell'intervallo di definizione della loglikelihood
	double max = 0.0; // Massimo dell'intervallo di definizione della loglikelihood
	double * tmp = new double[2]; // Array temporaneo

	// Popola il vector con numeri casuali esponenziali
	for(int i = 1; i < n_eventi + 1; ++i)
	{
		dati.push_back(rand_exp_tzero(t_0));
	}

	// La loglikelihood ha per intervallo di definizione "ottimale" min = max(0.1 * media, media - 3 * sigma) e max = media + 3 * sigma
	media = sampleMean(dati);
	sigma = sampleStd(dati, false);

	tmp[0] = 0.1 * media;
	tmp[1] = media - 3 * sigma;

	min = massimoArray(tmp, 2);
	max = media + 3 * sigma;

	delete[] tmp; // Deallocazione memoria

	// Definizione oggetti ROOT
	TCanvas canvas;
	TF1 f_loglikelihood("f_loglikelihood", loglikelihood, min, max, n_eventi); // La loglikelihood ha per intervallo di definizione "ottimale" min = max(0.1 * media, media - 3 * sigma) e max = media + 3 * sigma

	// Imposta i parametri della funzione likelihood (i parametri sono le misure, mentre t_0 è variabile indipendente)
	f_loglikelihood.SetParameter(0, dati.at(0));

	for(int i = 1; i < n_eventi + 1; ++i)	
	{
		f_loglikelihood.SetParameter(i, dati.at(i)); 
	}

	// Stampa il grafico della funzione likelihood su canvas
	f_loglikelihood.Draw();
	canvas.Print("loglikelihood.png", "png");
	
	return 0;
}
