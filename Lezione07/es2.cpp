/* Si utilizzi il risultato del primo esercizio per simulare uno pseudo-esperimento di conteggio con caratteristiche di Poisson:
* si scelga un tempo caratteristico t0 di un processo di decadimento radioattivo;
* si scelga un tempo di misura tM entro cui fare conteggi;
* in un ciclo, si simulino N pseudo-esperimenti di conteggio, in cui, per ciascuno di essi, si simuli una sequenza di eventi casuali con intertempo caratteristico dei fenomeni di Poisson, fino a che il tempo totale trascorso non sia maggiore del tempo di misura, contando il numero di eventi generati che cascano nell’intervallo;
* si riempia un istogramma TH1F con i conteggi simulati per ogni esperimento
*/

#include "TH1F.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "funzioniutili.h"

int main(int argc, char ** argv)
{
    // Definizione variabili
    int N_esperimenti = 1000000; // Numero di pseudo-esperimenti
    int N_eventi_exp = 0.0; // Contatore degli eventi esponenziali che cadono in un intervallo
    float t_0 = 5; // Tempo caratteristico dell'esponenziale
    float t_M = 100; // Tempo di misura in secondi
    float t = 0.0; // Tempo
    int n_bin = 3 * t_M / t_0; // Numero di bin

    // Definizione oggetti ROOT
    TApplication app("app", &argc, argv);
    TCanvas canvas;
    TH1F hist("hist", "Distribuzione poissoniana", n_bin, 0, n_bin);

    // Ciclo sugli pseudo-esperimenti
    for(int i = 0; i < N_esperimenti; ++i)
    {
        t = rand_exp_tzero(t_0);

        while(t < t_M)
        {
            ++N_eventi_exp;
            t += rand_exp_tzero(t_0);
        }

        hist.Fill(N_eventi_exp);
        N_eventi_exp = 0;
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