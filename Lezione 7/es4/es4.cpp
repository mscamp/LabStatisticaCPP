/* A partire dall’esercizio precedente,
* si scriva un nuovo programma che riempia un vector con il campione generato;
* si scriva una libreria che calcola le statistiche del campione (media, varianza, asimmetria, curtosi) a partire dal vector come input;
* si utilizzi il campione generato per fare il test di funzionamento della libreria.
*/

#include <iostream>
#include "vectorstatistiche.h"
#include "funzioniutili.h"

int main(int argc, char ** argv)
{
    // Definizione variabili
    int N_esperimenti = 1000000; // Numero di pseudo-esperimenti
    float media = 20; // Media della distribuzione di Poisson
    std::vector<float> campione_poisson;

    // Riempimento del vector
    for(int i = 0; i < N_esperimenti; ++i)
    {
        campione_poisson.push_back(rand_poisson(media));
    }

    // Statistiche
    std::cout << "Media: " << sampleMean(campione_poisson) << std::endl;
    std::cout << "Varianza: " << sampleVariance(campione_poisson, false) << std::endl;
    std::cout << "Deviazione standard: " << sampleStd(campione_poisson, false) << std::endl;
    std::cout << "Skewness: " << sampleSkewness(campione_poisson, false) << std::endl;
    std::cout << "Kurtosis: " << sampleKurtosis(campione_poisson, false) << std::endl;

    return 0;
}