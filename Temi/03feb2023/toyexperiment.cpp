/* COMPILE COMMAND */
#include <Rtypes.h>
#include <TString.h>
#include <iostream>
#include <string>
#include <vector>
#include "TF1.h"
#include "TH1F.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include "montecarlo.h"
#include "vectorstatistiche.h"

int main(int argc, char ** argv)
{
    // Seed casuale
    srand(time(NULL));

    // Definizione variabili
    int n_eventi = 1000;
    int n_toys = 100;
    int n_bin = floor(sqrt(n_eventi)) + 1;
    double xmin = 0.0;
    double xmax = 10.0;
    double ymax = 0.0;
    std::vector<double> parabola_pars = {-0.2, 0.8, 1.0};
    std::vector<double> gauss_pars = {2.0, 2.0, 0.25};
    std::vector<double> * parametri_vec = new std::vector<double>[6]; // Ciascuno dei sei vector contiene 100 valori dei rispettivi parametri determinati dai toy experiment
    
    // Parametri per il fit
    double p0 = 0.0; // a della parabola
    double p1 = 0.0; // b della parabola
    double p2 = 0.0; // c della parabola
    double p3 = 0.0; // Normalizzazione della gaussiana
    double p4 = 0.0; // Media della gaussiana
    double p5 = 0.0; // Sigma della gaussiana

    // Definizione TF1
    TF1 parabola("parabola", "[0] * x[0] * x[0] + [1] * x[0] + [2]", xmin, xmax);
    TF1 gauss("gauss", "gaus(0)", xmin, xmax);
    TF1 f("f", "[0] * x[0] * x[0] + [1] * x[0] + [2] + gaus(3)", xmin, xmax);

    // Impostazione dei parametri
    parabola.SetParameters(&parabola_pars[0]);
    gauss.SetParameters(&gauss_pars[0]);

    for(int i = 0; i < parabola_pars.size(); ++i)
    {
        f.SetParameter(i, parabola.GetParameter(i));
        f.SetParameter(i + 3, gauss.GetParameter(i));
    }

    for(int i = 0; i < n_toys; ++i)
    {
        TF1 f_fit("f_fit", "[0] * x[0] * x[0] + [1] * x[0] + [2] + gaus(3)", xmin, xmax);
        TH1F hist("hist", "parabola + gauss", n_bin, xmin, xmax);

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

        // Riempie il vector
        for(int j = 0; j < 6; ++j)
        {
            parametri_vec[j].push_back(f_fit.GetParameter(j));
        }

        TFitResultPtr fit_res = hist.Fit("f_fit", "S");

    }

    // Calcola media e deviazione standard dei vector
    std::cout << std::endl << std::endl;
    std::cout << "Media vector p0: " << sampleMean(parametri_vec[0]) << std::endl;
    std::cout << "Media vector p1: " << sampleMean(parametri_vec[1]) << std::endl;
    std::cout << "Media vector p2: " << sampleMean(parametri_vec[2]) << std::endl;
    std::cout << "Media vector p3: " << sampleMean(parametri_vec[3]) << std::endl;
    std::cout << "Media vector p4: " << sampleMean(parametri_vec[4]) << std::endl;
    std::cout << "Media vector p5: " << sampleMean(parametri_vec[5]) << std::endl;
    std::cout << std::endl;
    std::cout << "Sigma vector p0: " << sampleStd(parametri_vec[0], false) << std::endl;
    std::cout << "Sigma vector p1: " << sampleStd(parametri_vec[1], false) << std::endl;
    std::cout << "Sigma vector p2: " << sampleStd(parametri_vec[2], false) << std::endl;
    std::cout << "Sigma vector p3: " << sampleStd(parametri_vec[3], false) << std::endl;
    std::cout << "Sigma vector p4: " << sampleStd(parametri_vec[4], false) << std::endl;
    std::cout << "Sigma vector p5: " << sampleStd(parametri_vec[5], false) << std::endl;
    std::cout << std::endl;
    std::cout << "Media della gaussiana: " << sampleMean(parametri_vec[4]) << " +/- " << sampleStd(parametri_vec[4], false) << std::endl;
    std::cout << "Sigma della gaussiana: " << sampleMean(parametri_vec[5]) << " +/- " << sampleStd(parametri_vec[5], false) << std::endl;

    delete[] parametri_vec; // Deallocazione memoria

    return 0;
}