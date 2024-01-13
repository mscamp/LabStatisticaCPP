/* Si implementi un generatore di numeri pseudo-casuali secondo una distribuzione uniforme fra due estremi arbitrari. Si utilizzi un oggetto di tipo TH1F di ROOT per visualizzare la distribuzione dei numeri generati. */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"

float rand_range(float min, float max)
{
	return min + (max-min)*(rand() / static_cast<float>(RAND_MAX));
}

int main(int argc, char ** argv)
{
	// Impostazione seed
	srand(time(NULL));
	
	// Oggetti ROOT 
	TApplication app ("app", &argc, argv);
	TCanvas canvas;

	// Definizione variabili
	int N = 100000; // Numero di eventi
	float min = 15; 
    float max = 89;
	int n_bin = floor(sqrt(N)) + 1; // Numero di bin

	// Definizione istogramma
	TH1F hist("hist", "Distribuzione Uniforme", n_bin, min, max);
	
	// Riempimento istogramma con N numeri pseudo-casuali uniformi tra 15 e 89
	for(int i = 0; i < N; ++i)
	{
		hist.Fill(rand_range(min, max));	
	}

	// Styling
	hist.GetXaxis() -> SetTitle("Eventi");
	hist.GetYaxis() -> SetTitle("Conteggi");
	hist.SetFillColor(kOrange + 1);
	hist.SetLineColor(kBlack);
	hist.Draw();

	app.Run();

    return 0 ;
}


