/* Si utilizzi il metodo hit-or-miss per stimare l’integrale sotteso ad una distribuzione di probabilita’ Gaussiana con μ=0 e σ=1 in un generico intervallo [a,b].
* Si calcoli l’integrale contenuto entro gli intervalli [-kσ,kσ] al variare di k da 1 a 5.
*/

#include <iostream>
#include <cmath>
#include "funzioniutili.h"

double pdf_gauss_standardizzata(double x)
{
    double media = 0.0;
    double sigma = 1.0;
    
	return (1/(sqrt(2*3.14)*sigma))*pow(2.71, -pow((x-media),2)/2*pow(sigma, 2));
}

int main(int argc, char ** argv)
{
    // Definizione variabili
    double a = 0.0;
    double b = 5.0;
    double yMin = 0.0;
    double yMax = pdf_gauss_standard(0.0);
    int N_points = 1000000;

    // Calcolo dell'integrale della gaussiana 
    std::pair<double, double> integrale_gauss = integral_hitOrMiss(pdf_gauss_standardizzata, a, b, yMin, yMax, N_points);

    // Stampa a schermo il risultato
    std::cout << "Integrale della gaussiana standard tra " << a << " e " << b << ": " << integrale_gauss.first << " +/- " << integrale_gauss.second << std::endl << std::endl;

    // Calcolo integrale tra [-k,k] per k da 1 a 5
    for(int k = 1; k <= 5; ++k)
    {
        a = -k;
        b = k;

        integrale_gauss = integral_hitOrMiss(pdf_gauss_standardizzata, a, b, yMin, yMax, N_points);

        std::cout << "Integrale della gaussiana standard tra " << a << " e " << b << ": " << integrale_gauss.first << " +/- " << integrale_gauss.second << std::endl;
    }
    
    return 0;
}