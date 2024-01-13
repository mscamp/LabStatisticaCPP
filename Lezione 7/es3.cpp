/* Si utilizzi il codice sorgente scritto nell’esercizio precedente per aggiungere alla libreria sviluppata per l’esercizio 1 una funzione che generi numeri casuali secondo la distribuzione di Poisson, avendo la media di eventi attesi come parametro in ingresso. Si riscriva l’esercizio precedente facendo uso di questa funzione, disegnando anche l’istogramma della densità di probabilità. */

#include "TH1F.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "funzioniutili.h"

int main(int argc, char ** argv)
{
    // Definizione variabili
    int N_esperimenti = 1000000; // Numero di pseudo-esperimenti
    float media = 20; // Media della distribuzione di Poisson
    int n_bin = 3 * media; // Numero di bin

    // Definizione oggetti ROOT
    TApplication app("app", &argc, argv);
    TCanvas canvas;
    TH1F hist("hist", "Distribuzione poissoniana", n_bin, 0, n_bin);

    // Ciclo sugli pseudo-esperimenti
    for(int i = 0; i < N_esperimenti; ++i)
    {
        hist.Fill(rand_poisson(media));
    }
    
    // Styling
    hist.GetXaxis() -> SetTitle("Eventi");
    hist.GetYaxis() -> SetTitle("Conteggi");
    hist.SetFillColor(kOrange + 1);
    hist.SetLineColor(kBlack);

    // Disegno istogramma
    hist.Draw();
    app.Run();

    return 0;
}