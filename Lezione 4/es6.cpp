/* Si implementi un generatore di numeri pseduo-casuali che utilizzi il metodo della funzione inversa per generare eventi distribuiti secondo distribuzione di probabilita’ esponenziale.
Si utilizzi un oggetto di tipo TH1F di ROOT per visualizzare la distribuzione dei numeri generati.
*/

#include <iostream>
#include <cmath>
#include <math.h>
#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "funzioniutili.h"

int main(int argc, char ** argv)
{
    // Impostazione seed
	srand(time(NULL));

    // Oggetti ROOT
	TApplication app ("theApp", &argc, argv);
	TCanvas canvas;

    // Definizione variabili
	int N = 100000; // Numero di eventi
	int n_bin = floor(sqrt(N)) + 1; // Numero di bin
    float lambda = 5; // Parametro di decadimento

    // Definizione istogramma
	TH1F hist("hist", "Distribuzione di numeri pseudo-random esponenziali", n_bin, 0, 1);

    // Algoritmo della funzione inversa
    for(int i = 0; i < N; ++i)
    {
        hist.Fill(rand_exp(lambda));
    }

    // Styling 
    hist.GetXaxis() -> SetTitle("Eventi");
	hist.GetYaxis() -> SetTitle("Conteggi");
	hist.SetFillColor (kGreen);
    hist.Draw();

    app.Run();	

    return 0;
}
