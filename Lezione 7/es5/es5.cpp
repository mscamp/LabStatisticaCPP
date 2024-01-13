/* Si utilizzi il risultato dell’esercizio precedente per calcolare le statistiche di una distribuzione di Poisson al variare della media, fra 1 e 20.
* Si disegni l’andamento ottenuto di ciascuna statistica in funzione della media con quattro TGraph di ROOT;
* si disegnino i quattro TGraph in quattro TCanvas e si crei per ciascuno un’immagine salvata su disco.
*/

#include <iostream>
#include "vectorstatistiche.h"
#include "funzioniutili.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1F.h"

int main(int argc, char ** argv)
{
    // Definizione variabili
    int N_esperimenti = 100000; // Numero di pseudo-esperimenti
    std::vector<float> medie; // Vettore delle medie
    std::vector<float> campione_poisson;
    std::vector<float> varianze;
    std::vector<float> asimmetrie;
    std::vector<float> curtosi;

    // Definizione oggetti ROOT
    TCanvas canvas;
    TGraph g_varianza;
    TGraph g_asimmetria;
    TGraph g_curtosi;

    // Riempimento del vector con le medie
    for(int i = 1; i <= 20; ++i)
    {
        medie.push_back(static_cast<float>(i));
    }

    // Riempimento del vector per ogni valore della media
    for(int i = 0; i < 20; ++i)
    {
        for(int j = 0; j < N_esperimenti; ++j)
        {
            campione_poisson.push_back(rand_poisson(medie.at(i)));
        }

        varianze.push_back(sampleVariance(campione_poisson, false));
        asimmetrie.push_back(sampleSkewness(campione_poisson, false));
        curtosi.push_back(sampleKurtosis(campione_poisson, false));
    }

    // Riempimento dei grafici
    for(int i = 0; i < 20; ++i)
    {
        g_varianza.SetPoint(g_varianza.GetN(), medie.at(i), varianze.at(i));
        g_asimmetria.SetPoint(g_asimmetria.GetN(), medie.at(i), asimmetrie.at(i));
        g_curtosi.SetPoint(g_curtosi.GetN(), medie.at(i), curtosi.at(i));
    }

    // Styling e stampa canvas

    // Varianza
    g_varianza.GetHistogram() -> GetXaxis() -> SetTitle("Media");
    g_varianza.GetHistogram() -> GetYaxis() -> SetTitle("Varianza");
    g_varianza.SetMarkerStyle(20);
    g_varianza.SetMarkerColor(kBlue);
    g_varianza.SetMarkerSize(2);
    g_varianza.SetLineColor(kRed);
    g_varianza.Draw("ALP");
    canvas.Print("varianza.gif", "gif");

    // Skewness
    g_asimmetria.GetHistogram() -> GetXaxis() -> SetTitle("Media");
    g_asimmetria.GetHistogram() -> GetYaxis() -> SetTitle("Asimmetria");
    g_asimmetria.SetMarkerStyle(20);
    g_asimmetria.SetMarkerColor(kBlue);
    g_asimmetria.SetMarkerSize(2);
    g_asimmetria.SetLineColor(kRed);
    g_asimmetria.Draw("ALP");
    canvas.Print("asimmetria.gif", "gif");

    // Curtosi
    g_curtosi.GetHistogram() -> GetXaxis() -> SetTitle("Media");
    g_curtosi.GetHistogram() -> GetYaxis() -> SetTitle("Curtosi");
    g_curtosi.SetMarkerStyle(20);
    g_curtosi.SetMarkerColor(kBlue);
    g_curtosi.SetMarkerSize(2);
    g_curtosi.SetLineColor(kRed);
    g_curtosi.Draw("ALP");
    canvas.Print("curtosi.gif", "gif");

    return 0;
}