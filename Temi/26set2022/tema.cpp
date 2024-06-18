/* COMPILAZIONE */
#include <iostream>
#include <fstream>
#include <vector>
#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include "funzioniutili.h"

int main(int argc, char ** argv)
{
    // Definizione variabili e oggetti
    double input_val_x = 0.0; // Variabile temporanea
    double input_val_y = 0.0; // Variabile temporanea
    double xmin = 0.0;
    double xmax = 0.0;
    double a = 0.0;
    double b = 0.0;
    double sigma_a = 0.0;
    double sigma_b = 0.0;
    double gittata = 0.0;
    double sigma_gittata = 0.0;
    double sigma_gittata_rel = 0.0;
    std::ifstream file_coordinate;
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> par_fit = {-0.5, 1.0, 0.0};

    // Definizione oggetti ROOT
    TApplication app("app", &argc, argv);
    TCanvas canvas;

    file_coordinate.open("coordinate.txt", std::ios::in); // Apre il file

    // Riempimento dei vector
    while(true)
    {
        file_coordinate >> input_val_x >> input_val_y;
        x.push_back(input_val_x);
        y.push_back(input_val_y);

        if(file_coordinate.eof() == true)
        {
            x.pop_back();
            y.pop_back();
            break;
        }
    }

    file_coordinate.close(); // Chiude il file

    // Determina estremi xmin e xmax dai dati
    xmin = minimoVec(x) - 1;
    xmax = massimoVec(x) + 1;

    // Definizione TGraph
    TGraph grafico(x.size(), &x[0], &y[0]);

    // Fit dei dati
    TF1 f_fit("f_fit", "[0] * x[0] * x[0] + [1] * x[0] + [2]", xmin, xmax);

    f_fit.SetParameters(&par_fit[0]);
    f_fit.FixParameter(2, 0.0);

    TFitResultPtr fit_res = grafico.Fit("f_fit", "S");

    // Determinazione della gittata
    a = f_fit.GetParameter(0);
    sigma_a = f_fit.GetParError(0);
    b = f_fit.GetParameter(1);
    sigma_b = f_fit.GetParError(1);

    gittata = -(b / a);
    sigma_gittata_rel = sqrt(pow(sigma_b/b, 2.0) + pow((-1.0/pow(a, 2.0)) * sigma_a * a, 2.0)); // Incertezza relativa come somma in quadratura delle incertezze relative
    sigma_gittata = sigma_gittata_rel * gittata;

    // Stampa a schermo il risultato
    std::cout << "Gittata: " << gittata << " +/- " << sigma_gittata << std::endl;

    // Styling
    grafico.GetHistogram()->GetXaxis()->SetTitle("x_i");
    grafico.GetHistogram()->GetYaxis()->SetTitle("y_i");
    grafico.SetMarkerColor(kBlue);
    grafico.SetMarkerStyle(20);
    grafico.SetMarkerSize(1);
    grafico.GetFunction("f_fit")->SetLineColor(kOrange + 1);
    grafico.GetFunction("f_fit")->SetLineWidth(3);

    // Disegno del grafico su canvas
    grafico.Draw("AP");
    app.Run();

    return 0; 
}