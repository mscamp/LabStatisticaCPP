/* Si scriva una nuova classe, sotto forma di libreria, che dato in input il nome di un file di testo contenente un campione di eventi, sia in grado di salvare al proprio interno il campione, calcolarne media, varianza, deviazione standard, deviazione standard dalla media, visualizzare il campione in un istogramma con intervallo di definizione e numero di bin scelto appropriatamente. Si scriva un programma di test della classe creata. */

#include <iostream>
#include <fstream>
#include "statistiche.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"
#include <string>

int main(int argc, char ** argv)
{
	// Dichiarazione variabili
	double value = 0.0;
	int dim_file = 0;
	std::string file_name = "eventi_gauss.txt";

	// Oggetti ROOT
	TApplication app("app", &argc, argv);
	TCanvas canvas;

	// Apertura file
	std::ifstream f;
	f.open(file_name, std::ios::in);
	
	// Determina numero di eventi
	while(true)
	{
		f >> value;
		++dim_file;

		if(f.eof() == true)
		{
			--dim_file;
			break;
		}
	}

	// Chiude e apre il file 
	f.close();
	f.open(file_name, std::ios::in);

	// Definisce oggetto statistiche
	statistiche campione(dim_file);

	for(int i = 0; i < dim_file; ++i)
	{
		f >> value;
		campione.addEvent(value);
	}

	f.close(); // Chiude il file

	// Stampa i valori richiesti
	std::cout << "Media: " << campione.sampleMean() << std::endl;
	std::cout << "Varianza: " << campione.sampleVariance() << std::endl;
	std::cout << "Varianza corretta: " << campione.sampleVariance(true) << std::endl;
	std::cout << "Deviazione standard: " << campione.sampleStd() << std::endl;
	std::cout << "Deviazione standard corretta: " << campione.sampleStd(true) << std::endl;
	std::cout << "Deviazione standard della media: " << campione.sampleMeanStd() << std::endl;
	std::cout << "Deviazione standard della media corretta: " << campione.sampleMeanStd(true) << std::endl;
	std::cout << "Grandezza campione: " << campione.sampleSize() << std::endl;
	std::cout << "Elemento 1001: " << campione.element(1001) << std::endl;
	std::cout << "Minimo: " << campione.minimumValue() << std::endl;
	std::cout << "Massimo: " << campione.maximumValue() << std::endl;

	// Plot istogramma
	TH1F istogramma = campione.createHistogram();
	istogramma.Draw();

	app.Run();

	return 0;
}
