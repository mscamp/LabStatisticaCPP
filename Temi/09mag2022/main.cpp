#include "lib.h"
#include <Rtypes.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "TCanvas.h"
#include "TGraph.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include "funzioniutili.h"
#include "TH1F.h"


int main(int argc, char ** argv)
{
    // Controllo argomenti
    if(argc != 3) 
    {
        std::cout << "Utilizzo: ./c.out nome_file nome_immagine" << std::endl;
        return 1;
    }

    // Oggetti ROOT
    TCanvas canvas;
    
    // Legge il file e riempie i vector
    std::pair<std::vector<double>, std::vector<double>> xy_pair = read_file(argv[1]);
    std::vector<double> x = xy_pair.first;
    std::vector<double> y = xy_pair.second;

    // Stampa a schermo le coordinate
    for(int i = 0; i < x.size(); ++i)
    {
        std::cout << "x: " << x.at(i) << " " << "y: " << y.at(i) << std::endl;
    }

    // Definizione TGraph
    TGraph grafico(x.size(), &x[0], &y[0]);

    // Definizione TF1 per il fit
    TF1 f_fit("f_fit", f, minimoVec(x), massimoVec(x), 3);

    f_fit.SetParameter(0, determina_ampiezza(y));
    f_fit.SetParameter(1, determina_omega(x, y));
    f_fit.SetParameter(2, 0.5);

    TFitResultPtr fit_result = grafico.Fit(&f_fit, "S");

    // Istogramma
    std::vector<double> residui;

    for(int i = 0; i < y.size(); ++i)
    {
        residui.push_back(y.at(i) - f_fit.Eval(x.at(i)));
    }

    TH1F hist("hist", "Residui", floor(sqrt(x.size())), minimoVec(residui), massimoVec(residui));

    for(int i = 0; i < y.size(); ++i)
    {
        hist.Fill(residui.at(i));
    }

    // Stampa TGraph
    grafico.SetMarkerColor(kGreen);
    grafico.SetMarkerStyle(20);
    grafico.SetMarkerSize(1);
    grafico.Draw("ap");

    std::cout << "Status: " << fit_result -> Status() << std::endl;
    canvas.Print(argv[2]);

    hist.SetFillColor(kOrange + 1);
    hist.Draw();
    canvas.Print("istogramma.png");

    return 0;
}