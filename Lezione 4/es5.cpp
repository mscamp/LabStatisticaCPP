/* Si implementi un generatore di numeri pseudo-casuali che utilizzi il metodo try-and-catch per generare numeri casuali secondo un distribuzione di probabilita’ arbitraria
* si prenda come parametro di ingresso la pdf da utilizzare per la generazione di numeri casuali
* si utilizzi un oggetto di tipo TH1F di ROOT per visualizzare la distribuzione dei numeri generati. */

#include <iostream>
#include <cmath>
#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"

// Punto nel piano R^2
struct punto2D
{
	float x = 0;
	float y = 0;
};

// PDF Gaussiana
float pdf(float x)
{
	float media = 0;
	float sigma = 1;
	
	return (1/(sqrt(2*3.14)*sigma))*pow(2.71, -pow((x-media),2)/2*pow(sigma, 2));
}

float rand_range(float min, float max)
{
	return min + (max-min)*(rand() / static_cast<float>(RAND_MAX));
}

int main(int argc, char ** argv)
{
	// Impostazione seed
	srand(time(NULL));
	
	// Oggetti ROOT
	TApplication app ("theApp", &argc, argv);
	TCanvas canvas;

	// Definizione variabili
	int N = 100000; // Numero di eventi
	float min = -10;
	float max = 10;
	float yMax = pdf(0); // Massimo della PDF
	int n_bin = floor(sqrt(N)) + 1; // Numero di bin
	struct punto2D array[N]; // Array di punti di R^2

	// Definizione istogramma
	TH1F hist("hist", "Distribuzione di numeri pseudo-random gaussiani", n_bin, min, max);	
	
	// Algoritmo Try-And-Catch
	for(int i = 0; i < N; ++i)
	{
		array[i].x = rand_range(min, max);
		array[i].y = rand_range(0, yMax);

		// Gli eventi vengono contati solo se il punto cade nell'area sottesa dal grafico della PDF
		if(array[i].y <= pdf(array[i].x))
		{
			hist.Fill(array[i].x);
		}
	}

	// Styling
	hist.GetXaxis() -> SetTitle("Eventi");
	hist.GetYaxis() -> SetTitle("Conteggi");
	hist.SetFillColor (kOrange + 1);
    hist.Draw();

    app.Run();	

	return 0;
}
