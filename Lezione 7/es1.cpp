/* Si generi un campione di numeri pseudo-casuali distribuiti secondo una distribuzione di densità esponenziale con tempo caratteristico t0 di 5 secondi e si visualizzi la distribuzione del campione ottenuto in un TH1F utilizzando il metodo della funzione inversa. Si scrivano tutte le funzioni deputate alla generazione di numeri casuali in una libreria, implementata in file separati rispetto al programma principale. */

#include "TCanvas.h"
#include "TApplication.h"
#include "TH1F.h"
#include "funzioniutili.h"

int main(int argc, char ** argv)
{
    // Definizione parametri
    int N_eventi = 10000;
    int n_bin = floor(sqrt(N_eventi)) + 1;
    float t_0 = 5; // Tempo caratteristico

    // Definizione oggetti ROOT
    TApplication app("app", &argc, argv);
    TCanvas canvas;
    TH1F hist("hist", "Distribuzione esponenziale", n_bin, 0, 10*t_0);

    // Riempimento istogramma
    for(int i = 0; i < N_eventi; ++i)
    {
        hist.Fill(rand_exp_tzero(t_0));
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

