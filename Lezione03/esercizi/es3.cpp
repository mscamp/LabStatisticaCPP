/* Si legga il file di testo eventi_unif.txt:
 * si scrivano a schermo i suoi primi 10 elementi positivi;
 * si conti il numero di eventi contenuti nel file;
 * si trascriva il contenuto del file in un array opportunamente dimensionato e se ne scrivano a schermo i primi 10 elementi;
 * si determinino il minimo ed il massimo valore fra i numeri salvati nel file. */

#include <iostream>
#include <fstream>

// Stampa a schermo i primi 10 elementi dell'array
void stampaArray(double * array, int N)
{
	std::cout << "--- Stampa i primi 10 elementi dell'array ---" << std::endl;
	
	for(int i = 0; i < 10; ++i)
	{
		if (i == N)
		{
			break;
		}

		std::cout << "Elemento " << i + 1 << ": " << array[i] << std::endl;
	}
}

// Determina minimo e massimo di un set di valori e li stampa a schermo
void minimoMassimo(double * array, int N)
{
	double min = array[0];
	double max = array[0];

	for(int i = 0; i < N; ++i)
	{
		if(array[i] < min)
		{
			min = array[i];
		}

		if(array[i] > max)
		{
			max = array[i];
		}
	}

	std::cout << std::endl;
	std::cout << "Minimo: " << min << std::endl;
	std::cout << "Massimo: " << max << std::endl;	
}

void fillArrayFromFile(std::ifstream & file, double * array, int counter)
{
	double value = 0.0;
	while (true)
  	{
		file >> value;
		array[counter] = value;
		++counter;
    	if(file.eof () == true) break;
  	}
}

int main(int argc, char ** argv)
{
	// Definizione variabili
	double value = 0.0;
	int i = 0; // Counter valori positivi
	int N = 0; // Counter eventi 

	std::ifstream f; // Oggetto ifstream
	f.open("eventi_unif.txt", std::ios::in); // Apre il file in sola lettura

	// Stampa i primi 10 valori positivi e conta gli eventi
	std::cout << "--- Stampa i primi 10 valori positivi ---" << std::endl;

	while (true)
  	{
		f >> value;

		if (value > 0.0 && i < 10)
		{
			std::cout << "Valore " << i + 1 << ": " << value << std::endl;
			++i; // Counter dei valori positivi
		}

		++N; // Counter degli eventi

		if(f.eof() == true)
		{
			--N; // Viene conteggiato anche il carattere EOF, quindi si toglie 1 dal totale
			break;
		}
  	}

	std::cout << std::endl;
	std::cout << "Numero totale di eventi: " << N << std::endl << std::endl;

	f.close(); // Chiude il file

	double * array = new double[N]; // Array dinamico che conterrà gli eventi
	i = 0; // Azzera il counter per riutilizzarlo

	f.open("eventi_unif.txt", std::ios::in); // Apre nuovamente il file

	// Popola l'array con i valori contenuti nel file
	fillArrayFromFile(f, array, i);

	f.close(); // Chiude il file

	// Stampa il contenuto dell'array, il minimo e il massimo valore
	stampaArray(array, N);
	minimoMassimo(array, N);
	
	delete[] array; // Deallocazione memoria
	return 0;
}

