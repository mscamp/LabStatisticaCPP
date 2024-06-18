/* Si legga il file di testo eventi_gauss.txt:
 * si riempia un istogramma di tipo TH1F con i primi N numeri contenuti nel file, dove N è un parametro passato a linea di comando in fase di esecuzione del programma;
 * si scelga l’intervallo di definizione dell’istogramma ed il suo numero di bin in funzione dei numeri da rappresentare. */

#include <iostream>
#include <fstream>
#include <cmath>
#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"

double minimoArray(double * array, int N)
{
	double min = array[0];

	for(int i = 0; i < N; ++i)
	{
		if(array[i] < min)
		{
			min = array[i];
		}
	}

	return min;
}

double massimoArray(double * array, int N)
{
	double max = array[0];

	for(int i = 0; i < N; ++i)
	{
		if(array[i] > max)
		{
			max = array[i];
		}
	}

	return max;
}

int main(int argc, char ** argv)
{
	//Definizione oggetti
	std::ifstream f;
	TApplication app("app", &argc, argv);
	TCanvas canvas;
	f.open("eventi_gauss.txt", std::ios::in); // Apre il file

	// Definizione variabili
	double value = 0.0; // Variabile ausiliaria
	int n_bin = 0; // Numero di bin dell'istogramma
	int N = 0; // Dimensione array
	int dim_file = 0; // Numero di eventi nel file
	double min = 0.0; // Valore minimo
	double max = 0.0; // Valore massimo

	// Determina la dimensione del file
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

	f.close(); // Chiude il file
		
	// Array dinamico
	std::cout << "Inserire il numero di valori che devono essere presi dal file -> ";
	std::cin >> N;
	
	// Controllo sul valore inserito
	if(N > dim_file)
	{
		std::cout << "Il valore inserito deve essere inferiore al numero di eventi, cioe' " << dim_file << std::endl;
		return 1;
	}

	if(N < 0)
	{
		std::cout << "Il valore inserito non puo' essere negativo." << std::endl;
		return 1;
	}
	
	double * array = new double[N]; // Dichiarazione array

	// Numero di bin
	n_bin = floor(sqrt(N)) + 1;

	// Riapre il file
	f.open("eventi_gauss.txt", std::ios::in);

	// Popola array con i valori del file
	for(int i = 0; i < N; ++i)
  	{
		f >> value;
		array[i] = value;
  	}
	
	f.close(); // Chiude il file

	// Determina minimo e massimo
	min = minimoArray(array, N);
	max = massimoArray(array, N);

	// Istanzia istogramma
	TH1F hist("hist", "Gauss", n_bin, min, max);
	
	// Riempie istogramma
	for(int i = 0; i < N; ++i)
	{
		hist.Fill(array[i]);
	}

	// Styling
	hist.GetXaxis() -> SetTitle("x");
	hist.GetYaxis() -> SetTitle("conteggi");
	hist.SetFillColor(kGreen);
	hist.SetLineColor(kBlack);

	// Disegna istogramma
	hist.Draw();
	canvas.Print("es4.png", "png");
	app.Run(); 

	delete[] array;
	return 0;
}
