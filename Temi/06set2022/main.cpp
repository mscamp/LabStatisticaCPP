#include "parabola.h"
#include <TH1.h>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <math.h>
#include <vector>
#include "TH1F.h"
#include "TCanvas.h"

int main(int argc, char ** argv)
{
    // Seed
    srand(time(NULL));

    // Controllo argomenti
    if(argc != 3)
    {
        std::cout << "Utilizzo: ./c.out x0 N" << std::endl;
        return 1;
    }

    // Dichiarazione variabili
    double x0 = fabs(atof(argv[1]));
    int N = atoi(argv[2]);

    // Controllo sulle variabili
    if(x0 < 0 || N <= 0)
    {
        std::cout << "Errore." << std::endl;
        return 1;
    }

    // Vector
    std::vector<double> campione;

    // Generazione numeri casuali
    for(int i = 0; i < N; ++i)
    {
        campione.push_back(rand_TAC(x0));
    }

    // Oggetti Root
    TCanvas canvas;
    TH1F hist("hist", "Parabola", sqrt(N), -x0, x0);

    // Riempie istogramma
    for(int i = 0; i < campione.size(); ++i)
    {
        hist.Fill(campione.at(i));
    }

    // Disegna istogramma
    hist.SetFillColor(kOrange + 1);
    hist.Draw();
    canvas.Print("parabola.png", "png");

    // Stampa integrale
    std::pair<double, double> integrale = integral_hitormiss(x0, 100000);
    std::cout << "Integrale: " << integrale.first << " +/- " << integrale.second << std::endl;

    return 0;
}