/* Si legga il file di testo eventi_unif.txt:
 * si riempia un istogramma di tipo TH1F con i primi N numeri contenuti nel file, dove N è un parametro passato a linea di comando in fase di esecuzione del programma;
 * si scelga l’intervallo di definizione dell’istogramma ed il suo numero di bin in funzione dei numeri da rappresentare;
 * Si visualizzino, sovrapposte, le distribuzioni degli eventi contenuti nei due file, trovado il modo di ottenere la migliore visualizzazione per poter effettuare un confronto visivo fra i due istogrammi. */

#include <iostream>
#include <fstream>
#include <cmath>
#include <ostream>
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
	std::ifstream f1; // File eventi gauss
	std::ifstream f2; // File eventi uniformi
	TApplication app("app", &argc, argv);
	TCanvas canvas;

	// Definizione variabili
	int dim_file1 = 0; // Numero di eventi gauss
	int dim_file2 = 0; // Numero di eventi uniformi
	double value = 0.0; // Variabile ausiliaria
	int N = 0; // Dimensione array
	int n_bin = 0; // Numero di bin
	double min1 = 0.0;
	double max1 = 0.0;
	double min2 = 0.0;	
	double max2 = 0.0;
	
	// Apertura dei file
	f1.open("eventi_gauss.txt", std::ios::in); // Apre il file gauss
	f2.open("eventi_unif.txt", std::ios::in); // Apre il file unif

	// Determina la dimensione dei file
	while(true)
	{
		f1 >> value;
		++dim_file1;

		if(f1.eof() == true)
		{
			--dim_file1;
			break;
		}
	}

	while(true)
	{
		f2 >> value;
		++dim_file2;

		if(f2.eof() == true)
		{
			--dim_file2;
			break;
		}
	}

	f1.close(); // Chiude il file
	f2.close(); // Chiude il file
			
	if(dim_file1 != dim_file2)
	{
		std::cout << "Il numero di eventi contenuto nei file deve essere lo stesso." << std::endl;
		return 1;
	}

	// Apertura dei file
	f1.open("eventi_gauss.txt", std::ios::in); // Apre il file gauss
	f2.open("eventi_unif.txt", std::ios::in); // Apre il file unif

	// Array dinamici
	std::cout << "Inserire il numero di valori che devono essere presi dai file -> ";
	std::cin >> N;

	// Controllo valore di N
	if(N > dim_file1)
	{
		std::cout << "Il valore inserito deve essere inferiore al numero di eventi, cioe' " << dim_file1 << std::endl;
		return 1;
	}

	if(N < 0)
	{
		std::cout << "Il valore inserito non puo' essere negativo." << std::endl;
		return 1;
	}
	
	// Definizione array dinamici
	double * array1 = new double[N];
	double * array2 = new double[N];

	// Numero di bin
	n_bin = floor(sqrt(N)) + 1;

	// Popola array con i valori dei file
	for(int i = 0; i < N; ++i)
  	{
		f1 >> value;
		array1[i] = value;

		f2 >> value;
		array2[i] = value;
  	}
	
	f1.close(); // Chiude il file gauss
	f2.close(); // Chiude il file unif

	// Determina minimo e massimo degli array
	min1 = minimoArray(array1, N);
	max1 = massimoArray(array1, N);
	min2 = minimoArray(array2, N);
	max2 = massimoArray(array2, N);

	// Istanzia istogramma
	TH1F hist_gauss("hist_gauss", "Gauss", n_bin, min1, max1);
	TH1F hist_unif("hist_unif", "Uniforme", n_bin, min2, max2);
	
	// Riempie istogramma
	for(int i = 0; i < N; ++i)
	{
		hist_gauss.Fill(array1[i]);
		hist_unif.Fill(array2[i]);
	}

	// Styling
	hist_gauss.SetLineColor(kRed);
	hist_unif.SetLineColor(kOrange);

	// Disegna istogramma
	hist_gauss.Draw();
	hist_unif.Draw("SAME");
	canvas.Print("es5.png", "png");
	app.Run(); 

	// Deallocazione memoria
	delete[] array1;
	delete[] array2;

	return 0;
}
