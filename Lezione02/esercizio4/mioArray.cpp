/* Scrivete una classe chiamata mioArray che implementi un array di numeri double con dimensione impostata dall’utente al momento della creazione degli oggetti, utilizzando l’allocazione dinamica della memoria e ripulisca la memoria nel distruttore.

Scrivete inoltre un programma di test che verifichi le funzionalità della classe.

La classe mioArray deve contenere un metodo per accedere ai suoi elementi che operi un controllo sul valore dell’indice, che avverta con un messaggio a schermo nel caso in cui si cerchi di accedere ad un indice che non sta nell’array

Si faccia in modo che sia possibile utilizzare questa funzione sia nel caso in cui si voglia modificare il contenuto delle celle dell’array, sia nel caso in cui l’oggetto di tipo mioArray sia const */

#include <iostream>
#include "mioArray.h"

int main(int argc, char ** argv)
{
	// Definizione dimensione e array tramite la classe mioArray
	int dim = 10;
	mioArray arr1(dim);

	// Riempimento array
    for(int i = 0; i < dim; ++i)
	{
			arr1.modifica_elemento(i, i+1);	
	}

	// Stampa a schermo l'array 1
	std::cout << "Array 1: " << std::endl;
	arr1.print();
	std::cout << std::endl;

	// Copia arr1 in arr2
	mioArray arr2(arr1);

	// Stampa a schermo l'array 2
	std::cout << "Array 2: " << std::endl;
	arr2.print();
	std::cout << std::endl;
	
	// Test del metodo elemento()
	std::cout << "Elemento 3 del secondo array: " << arr2.elemento(3) << std::endl;
	arr2.elemento(500); // Restituisce un errore out_of_range

	return 0; 
}
