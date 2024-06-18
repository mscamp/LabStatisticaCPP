/* COMPILE COMMAND */
#include <Rtypes.h>
#include <iostream>
#include <vector>
#include "TApplication.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "montecarlo.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"

int main(int argc, char ** argv)
{
    // Seed casuale
    srand(time(NULL));

    // Definizione variabili
    int n_eventi = 10000;
    int n_bin = floor(sqrt(n_eventi)) + 1;
    double xmin = 0.0;
    double xmax = 10.0;
    double ymax = 0.0;
    std::vector<double> parabola_pars = {-0.2, 0.8, 1.0};
    std::vector<double> gauss_pars = {2.0, 2.0, 0.25};
    
    // Parametri per il fit
    double p0 = 0.0; // a della parabola
    double p1 = 0.0; // b della parabola
    double p2 = 0.0; // c della parabola
    double p3 = 0.0; // Normalizzazione della gaussiana
    double p4 = 0.0; // Media della gaussiana
    double p5 = 0.0; // Sigma della gaussiana

    // Definizione oggetti ROOT
    TApplication app("app", &argc, argv);
    TCanvas canvas("canvas", "", 800, 800);
    TH1F hist("hist", "parabola + gauss", n_bin, xmin, xmax);

    // Definizione TF1
    TF1 parabola("parabola", "[0] * x[0] * x[0] + [1] * x[0] + [2]", xmin, xmax);
    TF1 gauss("gauss", "gaus(0)", xmin, xmax);
    TF1 f("f", "[0] * x[0] * x[0] + [1] * x[0] + [2] + gaus(3)", xmin, xmax);
    TF1 f_fit("f_fit", "[0] * x[0] * x[0] + [1] * x[0] + [2] + gaus(3)", xmin, xmax);

    // Impostazione dei parametri
    parabola.SetParameters(&parabola_pars[0]);
    gauss.SetParameters(&gauss_pars[0]);

    for(int i = 0; i < parabola_pars.size(); ++i)
    {
        f.SetParameter(i, parabola.GetParameter(i));
        f.SetParameter(i + 3, gauss.GetParameter(i));
    }

    // Riempimento dell'istogramma
    ymax = f.Eval(2.0);
    for(int i = 0; i < n_eventi; ++i)
    {
        hist.Fill(rand_TAC(f, xmin, xmax, ymax));
    }

    // Parametri del fit
    p0 = -0.5; // a della parabola
    p1 = 0.5; // b della parabola
    p2 = 35.0; // c della parabola
    p3 = n_eventi; // Normalizzazione gaussiana
    p4 = 0.5 * (xmax - xmin); // Media gaussiana
    p5 = hist.GetRMS(); // Sigma gaussiana

    // Fit parziale sul fondo
    parabola.SetParameter(0, p0);
    parabola.SetParameter(1, p1);
    parabola.SetParameter(2, p2);

    hist.Fit("parabola", "Q", "", 0.0, 1.5);

    // Fit parziale sul segnale
    gauss.SetParameter(0, p3);
    gauss.SetParameter(1, p4);
    gauss.SetParameter(2, p5);

    hist.Fit("gauss", "Q", "", 1.5, 2.5);

    // Fit finale con f_fit
    f_fit.SetParameter(0, parabola.GetParameter(0));
    f_fit.SetParameter(1, parabola.GetParameter(1));
    f_fit.SetParameter(2, parabola.GetParameter(2));
    f_fit.SetParameter(3, gauss.GetParameter(0));
    f_fit.SetParameter(4, gauss.GetParameter(1));
    f_fit.SetParameter(5, gauss.GetParameter(2));

    TFitResultPtr fit_res = hist.Fit("f_fit", "S");

    // Stampa a schermo il risultato del fit
    std::cout << std::endl << std::endl;
    std::cout << "Status: " << fit_res -> Status() << std::endl;
    std::cout << "Parametro p0: " << f_fit.GetParameter(0) << " +/- " << f_fit.GetParError(0) << std::endl;
    std::cout << "Parametro p1: " << f_fit.GetParameter(1) << " +/- " << f_fit.GetParError(1) << std::endl;
    std::cout << "Parametro p2: " << f_fit.GetParameter(2) << " +/- " << f_fit.GetParError(2) << std::endl;
    std::cout << "Parametro p3: " << f_fit.GetParameter(3) << " +/- " << f_fit.GetParError(3) << std::endl;
    std::cout << "Parametro p4: " << f_fit.GetParameter(4) << " +/- " << f_fit.GetParError(4) << std::endl;
    std::cout << "Parametro p5: " << f_fit.GetParameter(5) << " +/- " << f_fit.GetParError(5) << std::endl;

    // Valuta la bontà del fit
    std::cout << "Q^2 min: " << fit_res -> Chi2() << std::endl;
    std::cout << "Probabilità Chi2: " << fit_res -> Prob() << std::endl;
    std::cout << "Gradi di libertà: " << fit_res -> Ndf() << std::endl;

    // Styling 
    f_fit.SetLineColor(kRed);
    f_fit.SetLineWidth(3);
    hist.SetFillColor(kOrange + 1);
    hist.SetLineColor(kBlack);
    
    // Disegna il grafico di f
    hist.Draw();
    app.Run();

    return 0;
}
