/* COMMENTO PER COMPILATORE */

#include <TFitResult.h>
#include <iostream>
#include "TApplication.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TH1F.h"
#include "lib.h"

#define PI 3.14159

int main(int argc, char ** argv)
{
    // Seed casuale
    srand(time(NULL));

    // Definizione variabili
    double xmin = 0.0;
    double xmax = 10.0;
    std::vector<double> x_i = genera_Random();
    std::vector<double> y_i;

    // Parametri delle TF1
    std::vector<double> par_segnale = {3.0 /*a1*/, 0.2 /*a2*/, 0.2 * PI /*omega_1*/, PI /*omega_2*/};
    std::vector<double> par_modello = {3.0 /*a1*/, 0.2 /*a2*/, 0.2 * PI /*omega_1*/, PI /*omega_2*/, 1.0 /*Norm*/, 0.0 /*Media*/, 0.2 /*Sigma*/};
    std::vector<double> par_g = {1.0 /*A*/, PI /*omega*/}; // In questo caso per stimare omega si fa il minimo comune multiplo tra omega_1 e omega_2 (PI)

    // Definizione oggetti ROOT
    TApplication app("app", &argc, argv);
    TCanvas canvas;

    // Definizione TF1
    TF1 segnale("segnale", "[0] * sin([2] * x[0]) + [1] * sin([3] * x[0])", xmin, xmax);
    TF1 modello("modello", "[0] * sin([2] * x[0]) + [1] * sin([3] * x[0]) + gaus(4)", xmin, xmax);
    TF1 g("g", "[0] * sin([1] * x)"); // Funzione fit
    
    // Impostazione dei parametri
    segnale.SetParameters(&par_segnale[0]);
    modello.SetParameters(&par_modello[0]);

    // Riempimento del vector y_i
    for(int j = 0; j < x_i.size(); ++j)
    {
        y_i.push_back(y(modello, x_i.at(j)));
    }

    // Definizione del TGraph
    TGraph grafico(6, &x_i[0], &y_i[0]);

    // Impostazione dei parametri iniziali del fit
    g.SetParameters(&par_g[0]);

    // Fit
    TFitResultPtr fit_res = grafico.Fit(&g, "S");

    // Styling 
    grafico.GetHistogram()->GetXaxis()->SetTitle("x_i");
    grafico.GetHistogram()->GetYaxis()->SetTitle("y_i");
    grafico.SetMarkerColor(kBlue);
    grafico.SetMarkerStyle(20);
    grafico.SetMarkerSize(1);
    segnale.SetLineColor(kRed);
    segnale.SetLineWidth(3);
    g.SetLineColor(kGreen);
    g.SetLineWidth(3);

    // Disegno su canvas
    grafico.Draw("AP");
    segnale.Draw("SAME");
    app.Run();

    return 0;
}