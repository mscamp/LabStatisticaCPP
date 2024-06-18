/* Si implementi un generatore di numeri pseudo-casuali che utilizzi il metodo del teorema centrale del limite per generare eventi distribuiti secondo una distribuzione di probabilità Gaussiana.
* Come si fa ad ottenere una distribuzione si probabilita’ Normale, cioè Gaussiana centrata in zero con varianza unitaria?
* Si verifichi visivamente che al crescere del numero di eventi aumenta la somiglianza fra la distribuzione ottenuta e la forma funzionale Gaussiana, sia graficamente che utilizzando i momenti delle distribuzioni calcolati sul campione di eventi generati. */

#include <Rtypes.h>
#include <iostream>
#include <cmath>
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
    int N_distribuzioni = 10000; // Numero di medie
    int N; // Numero di campioni da prendere da ogni distribuzione
	int n_bin = floor(sqrt(N_distribuzioni)) + 1; // Numero di bin
    float a; // Per fare in modo che sigma = 1 e mu = 0 (gauss standardizzata)
    float b;
    float * array_gauss;

    // Definizione istogrammi
    TH1F hist1("hist1", "Distribuzione di numeri pseudo-random gaussiani (TCL)", n_bin, -5, 5);
    TH1F hist2("hist2", "Distribuzione di numeri pseudo-random gaussiani (TCL)", n_bin, -5, 5);
    TH1F hist4("hist4", "Distribuzione di numeri pseudo-random gaussiani (TCL)", n_bin, -5, 5);
	TH1F hist10("hist10", "Distribuzione di numeri pseudo-random gaussiani (TCL)", n_bin, -5, 5);


    // Riempimento istogrammi
    // N = 1
    N = 1;
    a = -0.5 * sqrt(12*N);
    b = 0.5 * sqrt(12*N);
    for(int i = 0; i < N_distribuzioni; ++i)
    {
        hist1.Fill(rand_range(a,b));
    }

    // N = 2
    N = 2;
    a = -0.5 * sqrt(12*N);
    b = 0.5 * sqrt(12*N);

    array_gauss = rand_TCL(a, b, N_distribuzioni, N);

    for(int i = 0; i < N_distribuzioni; ++i)
    {
        hist2.Fill(array_gauss[i]);
    }

    delete[] array_gauss;

    // N = 4
    N = 4;
    a = -0.5 * sqrt(12*N);
    b = 0.5 * sqrt(12*N);

    array_gauss = rand_TCL(a, b, N_distribuzioni, N);

    for(int i = 0; i < N_distribuzioni; ++i)
    {
        hist4.Fill(array_gauss[i]);
    }

    delete[] array_gauss;

    // N = 10
    N = 10;
    a = -0.5 * sqrt(12*N);
    b = 0.5 * sqrt(12*N);

    array_gauss = rand_TCL(a, b, N_distribuzioni, N);

    for(int i = 0; i < N_distribuzioni; ++i)
    {
        hist10.Fill(array_gauss[i]);
    }

    delete[] array_gauss;

    // Styling 
    canvas.SetLogy();

    hist2.SetFillColor(kBlue);
    hist4.SetFillColor(kRed + 1);
    hist10.SetFillColor(kGreen + 1);

    hist2.SetLineColor(kBlack);
    hist4.SetLineColor(kBlack);
    hist10.SetLineColor(kBlack);

    hist2.Draw();
    hist4.Draw("SAME");
    hist10.Draw("SAME");
    
    app.Run();

    return 0;
}