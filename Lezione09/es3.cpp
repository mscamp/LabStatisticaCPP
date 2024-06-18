/* Si scriva un programma che disegni in un TCanvas di ROOT la distribuzione di probabilità esponenziale avendo fissato il parametro t0 ad un numero passato da linea di comando come parametro del programma eseguibile.*/

#include <iostream>
#include <cmath>
#include "TF1.h"
#include "TCanvas.h"

// PDF esponenziale
double esponenziale(double * t, double * t_0)
{
	if(*t_0 == 0.0)
	{
		return 1;
	}

	return (1 / *(t_0)) * exp(-(*t / *(t_0)));
}

int main(int argc, char ** argv)
{
	// Controllo sugli argomenti passati da riga di comando
	if(argc != 2)
	{
		std::cout << "Utilizzo: ./es3 t_0" << std::endl;
		return 1;
	}

	// Definizione variabili
	double t_0 = atof(argv[1]); // Tempo caratteristico dell'esponenziale

	// Definizione oggetti di ROOT
	TCanvas canvas;
	TF1 pdf_exp("pdf_exp", esponenziale, 0.0, 5 * t_0, 1);

	// Impostazione del parametro t_0
	pdf_exp.SetParameter(0, t_0);
	
	// Disegna la funzione su canvas
	pdf_exp.Draw();
	canvas.Print("exp.png", "png");

	return 0;
}
