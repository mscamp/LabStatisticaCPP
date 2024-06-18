/* Si disegnino in due TGraph gli andamenti della precisione del calcolo dell’integrale, per i due algoritmi di hit-or-miss e crude-MC, in funzione del tempo di calcolo corrispondente alle varie scelte del numero totale N di eventi pseudo-casuali generati. */

#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <cstdlib>
#include "funzioniutili.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"

#define PI 3.14159
#define DIM 8

// Funzione da integrare
double f(double x)
{
    return sin(x) + 1;
}

int main(int argc, char ** argv)
{
    // Definizione variabili e oggetti
    int N_points_max = 1000000; // Numero di punti massimo
    double a = 0.0;
    double b = PI;
    double yMin = 0.0;
    double yMax = PI;  
    double time_exec = 0.0; // Tempo di esecuzione
    std::pair<double, double> integrale_f_hitOrMiss;
    std::pair<double, double> integrale_f_crudeMC;

    // Definizione oggetti ROOT
    TCanvas canvas;
    TGraph g_incertezze_hitOrMiss;
    TGraph g_incertezze_crudeMC;

    // Riempimento del vector con i valori degli integrali
    for(int iN = 10; iN < N_points_max; iN *= 2) // Numero dei punti raddoppia ad ogni ciclo
    {
        // Calcolo integrali
        integrale_f_hitOrMiss = integral_hitOrMiss(f, a, b, yMin, yMax, iN);
        integrale_f_crudeMC = integral_crudeMC(f, a, b, iN);

        // Tempo di calcolo
        time_exec = clock();

        // Riempimento TGraph
        g_incertezze_hitOrMiss.SetPoint(g_incertezze_hitOrMiss.GetN(), iN, integrale_f_hitOrMiss.second);
        g_incertezze_crudeMC.SetPoint(g_incertezze_crudeMC.GetN(), iN, integrale_f_crudeMC.second);
    }

    // Styling
    g_incertezze_hitOrMiss.SetMarkerColor(kBlue);
    g_incertezze_hitOrMiss.SetMarkerStyle(20);
    g_incertezze_hitOrMiss.SetMarkerSize(1);
    g_incertezze_hitOrMiss.SetLineColor(kOrange + 1);

    g_incertezze_crudeMC.SetMarkerColor(kRed);
    g_incertezze_crudeMC.SetMarkerStyle(20);
    g_incertezze_crudeMC.SetMarkerSize(1);
    g_incertezze_crudeMC.SetLineColor(kBlack);
    
    // Stampa i MultiTGraph su una canvas
    canvas.SetLogx();
    g_incertezze_hitOrMiss.Draw("ALP");
    g_incertezze_crudeMC.Draw("LPSAME");
    canvas.Print("incertezze.png", "png");

    return 0;
}