/* Si implementi il metodo di integrazione crude-MC con la funzione di esempio f(x) = sin (x).
* Si scriva l’algoritmo che calcola l’integrale come una funzione esterna al programma main, facendo in modo che prenda come parametri di ingresso, oltre agli estremi lungo l’asse x, anche il numero di punti pseudo-casuali da generare.
* Si faccia in modo che l’algoritmo ritorni un contenitore contenente due elementi: il primo elemento sia il valore dell’integrale, il secondo sia la sua incertezza.
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
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
    int N_iterazioni = 1000000;

    // Calcolo dell'integrale: il primo elemento della coppia è la stima, il secondo è l'incertezza su tale stima
    std::pair<double, double> integrale_f = integral_crudeMC(f, a, b, N_iterazioni);

    // Stampa a schermo il risultato
    std::cout << "Integrale di f tra " << a << " e " << b << ": " << integrale_f.first << " +/- " << integrale_f.second << std::endl;

   return 0;
}