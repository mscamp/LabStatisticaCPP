/* Si inserisca il calcolo dell’integrale dell’esercizio precedente in un ciclo che, al variare del numero N di punti generati, mostri il valore dell’integrale e della sua incertezza.
* Si utilizzi un TGraph per disegnare gli andamenti del valore dell’integrale e della sua incertezza, al variare di N con ragione logaritmica. */

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include "funzioniutili.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"

#define PI 3.14159
#define DIM 6

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
    std::pair<double, double> integrale_f;
    std::vector<int> N_points; // Vettore del numero di punti
    std::vector<double> integrali; // Vettore degli integrali
    std::vector<double> incertezze; // Vettore delle incertezze sugli integrali

    // Definizione oggetti ROOT
    TCanvas canvas;
    TGraph g_integrali;
    TGraph g_incertezze;

    // Riempimento del vector con il numero di punti
    for(int i = 1; i <= DIM; ++i)
    {
        N_points.push_back(pow(10, i));
    }

    // Riempimento del vector con i valori degli integrali
    for(int i = 0; i < DIM; ++i)
    {
        integrale_f = integral_hitOrMiss(f, a, b, yMin, yMax, N_points.at(i));
        integrali.push_back(integrale_f.first);
        incertezze.push_back(integrale_f.second);
    }

    // Riempimento dei TGraph
    for(int i = 0; i < DIM; ++i)
    {
        g_integrali.SetPoint(g_integrali.GetN(), N_points.at(i), integrali.at(i));
        g_incertezze.SetPoint(g_incertezze.GetN(), N_points.at(i), incertezze.at(i));
    }

    // Styling
    g_integrali.GetHistogram()->GetXaxis()->SetTitle("Numero di punti");
    g_integrali.GetHistogram()->GetYaxis()->SetTitle("Valore dell'integrale");
    g_integrali.SetMarkerColor(kBlue);
    g_integrali.SetMarkerStyle(20);
    g_integrali.SetMarkerSize(1);
    g_integrali.SetLineColor(kOrange + 1);
    
    g_incertezze.GetHistogram()->GetXaxis()->SetTitle("Numero di punti");
    g_incertezze.GetHistogram()->GetYaxis()->SetTitle("Valore dell'incertezza");
    g_incertezze.SetMarkerColor(kGreen);
    g_incertezze.SetMarkerStyle(20);
    g_incertezze.SetMarkerSize(1);
    g_incertezze.SetLineColor(kRed + 1);
    
    // Stampa i TGraph su una canvas
    canvas.SetLogx();
    g_integrali.Draw("ALP");
    canvas.Print("integrali.png", "png");

    g_incertezze.Draw("ALP");
    canvas.Print("incertezze.png", "png");
    
    return 0;
}