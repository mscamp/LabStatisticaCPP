/* Si collaudi la classe statistiche con ciascuono degli agoritmi di generazione implementati. In particolare, poi:
* si verifichi che il valore della varianza della distribuzione uniforme corrisponde alle attese (quale è l’incertezza associata al numero ottenuto?)
* si verifichi che il valore della varianza ottenuta con la tecnica del teorema centrale del limite corrisponda a quello atteso
*/

#include <iostream>
#include <cmath>
#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "statistiche.h"
#include "funzioniutili.h"

float gauss(float x)
{
	float media = 0;
	float sigma = 1;
	
	return (1/(sqrt(2*3.14)*sigma))*pow(2.71, -pow((x-media),2)/2*pow(sigma, 2));
}

// Inversa della CDF esponenziale
float inverseCDF(float y, float lambda)
{	
	return ((-1)/lambda) * log(1 - y);
}

int main(int argc, char ** argv)
{
    // Definizione variabili
    int dimensione_campione = 100000;
    float lambda = 5;

    statistiche campione_unif(dimensione_campione);
    statistiche campione_TAC(dimensione_campione);
    statistiche campione_TCL(dimensione_campione);
    statistiche campione_INV(dimensione_campione);

    float * array_TCL = rand_TCL(0, 1, dimensione_campione, 10);

    // Riempimento dei campioni
    for(int i = 0; i < dimensione_campione; ++i)    
    {
        campione_unif.addEvent(rand_range(0,1));
        campione_TAC.addEvent(rand_TAC(gauss, 0, 1, gauss(0)));
        campione_TCL.addEvent(array_TCL[i]);
        campione_INV.addEvent(inverseCDF(rand_range(0, 1), lambda));
    }

    delete[] array_TCL; // Deallocazione memoria

    // Test generatore uniforme
    std::cout << "--- Generatore uniforme ---" << std::endl;

    std::cout << "Media: " << campione_unif.sampleMean() << std::endl;
    std::cout << "Varianza: " << campione_unif.sampleVariance() << std::endl;
    std::cout << "Varianza corretta: " << campione_unif.sampleVariance(true) << std::endl;
    std::cout << "Deviazione standard: " << campione_unif.sampleStd() << std::endl;
    std::cout << "Deviazione standard corretta: " << campione_unif.sampleStd(true) << std::endl;
    std::cout << "Deviazione standard della media: " << campione_unif.sampleMeanStd() << std::endl;
    std::cout << "Deviazione standard della media corretta: " << campione_unif.sampleMeanStd(true) << std::endl;

    std::cout << std::endl;

    // Test try-and-catch
    std::cout << "--- Generatore Try And Catch ---" << std::endl;

    std::cout << "Media: " << campione_TAC.sampleMean() << std::endl;
    std::cout << "Varianza: " << campione_TAC.sampleVariance() << std::endl;
    std::cout << "Varianza corretta: " << campione_TAC.sampleVariance(true) << std::endl;
    std::cout << "Deviazione standard: " << campione_TAC.sampleStd() << std::endl;
    std::cout << "Deviazione standard corretta: " << campione_TAC.sampleStd(true) << std::endl;
    std::cout << "Deviazione standard della media: " << campione_TAC.sampleMeanStd() << std::endl;
    std::cout << "Deviazione standard della media corretta: " << campione_TAC.sampleMeanStd(true) << std::endl;

    std::cout << std::endl;

    // Test teorema centrale del limite
    std::cout << "--- Generatore Teorema Centrale del Limite ---" << std::endl;

    std::cout << "Media: " << campione_TCL.sampleMean() << std::endl;
    std::cout << "Varianza: " << campione_TCL.sampleVariance() << std::endl;
    std::cout << "Varianza corretta: " << campione_TCL.sampleVariance(true) << std::endl;
    std::cout << "Deviazione standard: " << campione_TCL.sampleStd() << std::endl;
    std::cout << "Deviazione standard corretta: " << campione_TCL.sampleStd(true) << std::endl;
    std::cout << "Deviazione standard della media: " << campione_TCL.sampleMeanStd() << std::endl;
    std::cout << "Deviazione standard della media corretta: " << campione_TCL.sampleMeanStd(true) << std::endl;

    std::cout << std::endl;

    // Test Funzione inversa
    std::cout << "--- Generatore Funzione Inversa ---" << std::endl;

    std::cout << "Media: " << campione_INV.sampleMean() << std::endl;
    std::cout << "Varianza: " << campione_INV.sampleVariance() << std::endl;
    std::cout << "Varianza corretta: " << campione_INV.sampleVariance(true) << std::endl;
    std::cout << "Deviazione standard: " << campione_INV.sampleStd() << std::endl;
    std::cout << "Deviazione standard corretta: " << campione_INV.sampleStd(true) << std::endl;
    std::cout << "Deviazione standard della media: " << campione_INV.sampleMeanStd() << std::endl;
    std::cout << "Deviazione standard della media corretta: " << campione_INV.sampleMeanStd(true) << std::endl;

    std::cout << std::endl;

    return 0;
}