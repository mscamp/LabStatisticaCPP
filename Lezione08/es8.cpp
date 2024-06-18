/* Si inserisca il calcolo dell’integrale dell’esercizio precedente in un ciclo che, al variare del numero N di punti generati, mostri il valore dell’integrale e della sua incertezza.
* Si utilizzi un TGraph per disegnare gli andamenti del valore dell’integrale e della sua incertezza, al variare di N con ragione logaritmica.
* Si sovrapponga questo TGraph a quello ottenuto dallo svolgimento dell’Esercizio 8.6.
*/

#include <iostream>
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
    double a = 0.0;
    double b = PI;
    double yMin = 0.0;
    double yMax = PI;  
    std::pair<double, double> integrale_f_hitOrMiss;
    std::pair<double, double> integrale_f_crudeMC;
    std::vector<int> N_points; // Vettore del numero di punti
    std::vector<double> integrali_hitOrMiss; // Vettore degli integrali hit or miss
    std::vector<double> incertezze_hitOrMiss; // Vettore delle incertezze sugli integrali hit or miss
    std::vector<double> integrali_crudeMC; // Vettore degli integrali crude MC
    std::vector<double> incertezze_crudeMC; // Vettore delle incertezze sugli integrali crude MC

    // Definizione oggetti ROOT
    TCanvas canvas;
    TGraph g_integrali_hitOrMiss;
    TGraph g_incertezze_hitOrMiss;
    TGraph g_integrali_crudeMC;
    TGraph g_incertezze_crudeMC;

    // Riempimento del vector con il numero di punti
    for(int i = 1; i <= DIM; ++i)
    {
        N_points.push_back(pow(10, i));
    }

    // Riempimento del vector con i valori degli integrali
    for(int i = 0; i < DIM; ++i)
    {
        // Hit or miss
        integrale_f_hitOrMiss = integral_hitOrMiss(f, a, b, yMin, yMax, N_points.at(i));
        integrali_hitOrMiss.push_back(integrale_f_hitOrMiss.first);
        incertezze_hitOrMiss.push_back(integrale_f_hitOrMiss.second);

        // Crude MC
        integrale_f_crudeMC = integral_crudeMC(f, a, b,N_points.at(i));
        integrali_crudeMC.push_back(integrale_f_crudeMC.first);
        incertezze_crudeMC.push_back(integrale_f_crudeMC.second);
    }

    // Riempimento dei TGraph
    for(int i = 0; i < DIM; ++i)
    {
        // Hit or miss
        g_integrali_hitOrMiss.SetPoint(g_integrali_hitOrMiss.GetN(), N_points.at(i), integrali_hitOrMiss.at(i));
        g_incertezze_hitOrMiss.SetPoint(g_incertezze_hitOrMiss.GetN(), N_points.at(i), incertezze_hitOrMiss.at(i));
        
        // Crude MC
        g_integrali_crudeMC.SetPoint(g_integrali_crudeMC.GetN(), N_points.at(i), integrali_crudeMC.at(i));
        g_incertezze_crudeMC.SetPoint(g_incertezze_crudeMC.GetN(), N_points.at(i), incertezze_crudeMC.at(i));
    }

    // Styling
    g_integrali_hitOrMiss.SetMarkerColor(kBlue);
    g_integrali_hitOrMiss.SetMarkerStyle(20);
    g_integrali_hitOrMiss.SetMarkerSize(1);
    g_integrali_hitOrMiss.SetLineColor(kOrange + 1);
    
    g_incertezze_hitOrMiss.SetMarkerColor(kBlue);
    g_incertezze_hitOrMiss.SetMarkerStyle(20);
    g_incertezze_hitOrMiss.SetMarkerSize(1);
    g_incertezze_hitOrMiss.SetLineColor(kOrange + 1);

    g_integrali_crudeMC.SetMarkerColor(kRed);
    g_integrali_crudeMC.SetMarkerStyle(20);
    g_integrali_crudeMC.SetMarkerSize(1);
    g_integrali_crudeMC.SetLineColor(kBlack);
    
    g_incertezze_crudeMC.SetMarkerColor(kRed);
    g_incertezze_crudeMC.SetMarkerStyle(20);
    g_incertezze_crudeMC.SetMarkerSize(1);
    g_incertezze_crudeMC.SetLineColor(kBlack);
    
    // Stampa i MultiTGraph su una canvas
    canvas.SetLogx();
    g_integrali_hitOrMiss.Draw("ALP");
    g_integrali_crudeMC.Draw("LPSAME");
    canvas.Print("integrali.png", "png");
    
    canvas.SetLogx();
    g_incertezze_hitOrMiss.Draw("ALP");
    g_incertezze_crudeMC.Draw("LPSAME");
    canvas.Print("incertezze.png", "png");

    return 0;
}