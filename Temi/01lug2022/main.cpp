#include "lib.h"
#include <Rtypes.h>
#include <cstdlib>
#include <time.h>
#include <vector>
#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include "TGraph.h"
#include "TMath.h"


int main(int argc, char ** argv)
{
    // Impostazione seed
    srand(time(NULL));

    // Dichiarazione variabili
    double min = 0.0;
    double max = 15.0;
    double media = 5.0;
    double sigma = 2.0;
    double stima_media_ML = 0.0;
    double stima_sigma_ML = 0.0;
    double stima_media_MQ = 0.0;
    double stima_sigma_MQ = 0.0;

    // Oggetti ROOT
    TCanvas canvas;
    TF1 gauss_fit("gauss_fit", "gaus(0)", min, max);
    TGraph grafico_media_ML;
    TGraph grafico_sigma_ML;
    TGraph grafico_media_MQ;
    TGraph grafico_sigma_MQ;

    for(int k = 4.0; k <= 200; ++k)
    {
        std::vector<double> campione;

        // Generazione eventi gaussiani
        for(int i = 0; i < k; ++i)
        {
            campione.push_back(gauss_TAC(media, sigma, min, max));
        }

        // Definizione istogramma
        TH1F istogramma(generate_hist(campione, sqrt(k), min, max));

        // Setting dei parametri
        gauss_fit.SetParameter(0, istogramma.GetMean());
        gauss_fit.SetParameter(1, istogramma.GetRMS());

        // Fit con maximum likelihood
        TFitResultPtr fit_ML = istogramma.Fit(&gauss_fit, "SQL");
        stima_media_ML = gauss_fit.GetParameter(0);
        stima_sigma_ML = gauss_fit.GetParameter(1);

        // Setting dei parametri
        gauss_fit.SetParameter(0, istogramma.GetMean());
        gauss_fit.SetParameter(1, istogramma.GetRMS());

        // Fit con minimi quadrati
        TFitResultPtr fit_MQ = istogramma.Fit(&gauss_fit, "SQ");
        stima_media_MQ = gauss_fit.GetParameter(0);
        stima_sigma_MQ = gauss_fit.GetParameter(1);

        // Riempimento TGraph
        grafico_media_ML.SetPoint(grafico_media_ML.GetN(), k, (stima_media_ML - media));
        grafico_sigma_ML.SetPoint(grafico_sigma_ML.GetN(), k, (stima_sigma_ML - sigma));

        grafico_media_MQ.SetPoint(grafico_media_MQ.GetN(), k, (stima_media_MQ - media));
        grafico_sigma_MQ.SetPoint(grafico_sigma_MQ.GetN(), k, (stima_sigma_MQ - sigma));

    }

    // Disegna TGraph
    grafico_media_ML.SetLineColor(kRed);
    grafico_media_MQ.SetLineColor(kGreen);
    grafico_media_ML.Draw("alp");
    grafico_media_MQ.Draw("lp same");
    canvas.Print("media.png", "png");
    canvas.Clear();

    grafico_sigma_ML.SetLineColor(kRed);
    grafico_sigma_MQ.SetLineColor(kGreen);
    grafico_sigma_ML.Draw("alp");
    grafico_sigma_MQ.Draw("lp same");
    canvas.Print("sigma.png", "png");

    return 0;
}