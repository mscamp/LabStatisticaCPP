/* Si implementi il metodo di integrazione hit-or-miss con la funzione di esempio f(x) = sin (x) + 1.
* Si scriva l’algoritmo che calcola l’integrale come una funzione esterna al programma main, facendo in modo che prenda come parametri di ingresso, oltre agli estremi lungo l’asse x e l’asse y, anche il numero di punti pseudo-casuali da generare.
* Si faccia in modo che l’algoritmo ritorni un contenitore contenente due elementi: il primo elemento sia il valore dell’integrale, il secondo sia la sua incertezza.
*/

#include <Rtypes.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "funzioniutili.h"

#define PI 3.14159

// Funzione da integrare
double f(double x)
{
    return sin(x) + 1;
}

int main(int argc, char ** argv)
{
    // Definizione intervallo e numero di punti
    double a = 0.0;
    double b = PI;
    double yMin = 0.0;
    double yMax = 2.0;
    int N_points = 1000000;

    // Calcolo dell'integrale: il primo elemento della coppia è la stima, il secondo è l'incertezza su tale stima
    std::pair<double, double> integrale_f = integral_hitOrMiss(f, a, b, yMin, yMax, N_points);

    // Stampa a schermo il risultato
    std::cout << "Integrale di f tra " << a << " e " << b << ": " << integrale_f.first << " +/- " << integrale_f.second << std::endl;

   return 0;
}