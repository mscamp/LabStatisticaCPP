/* Scrivere una funzione che, dato un array di N interi, lo ordini dal più piccolo al più grande (suggerimento: creare un array inserendo alcuni numeri a caso per testare che l’ordinamento funzioni). */

#include <iostream>

void SortArray (double * myArray, int dim)
{
	double tmp = 0.0;

	// Riordina l'array con l'ausilio di una variabile temporanea
	for(int i = 0; i < dim; ++i) 
	{
		for(int j = 0; j < i; ++j)
		{
			if(myArray[i] < myArray[j])
			{
				tmp = myArray[i];
				myArray[i] = myArray[j];
				myArray[j] = tmp;
			}
		}
	}
}

int main(int argc, char ** argv)
{
	// Definizione array e dimensione
	int N = 5;
	double * arr = new double[N];
	
	// Riempimento array
	for(int i = 0; i < N; ++i)
	{
		std::cout << "Inserire elemento " << i << " -> ";
		std::cin >> arr[i];
	}

	// Riordina array
	SortArray(arr, N); 
	
	// Stampa a schermo l'array ordinato
	std::cout << std::endl;
	std::cout << "--- ARRAY ORDINATO ---" << std::endl;	
	for (int i = 0; i < N; ++i)
	{
		std::cout << "Elemento " << i << " : " << arr[i] << std::endl;
	}	

	delete[] arr; // Deallocazione memoria
	return 0;
}
