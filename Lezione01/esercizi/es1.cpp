/* Scrivere un programma che assegni il valore di una variabile ad un’altra utilizzando un puntatore. Stampare inoltre a terminale i valori e gli indirizzi di ogni variabile prima e dopo l’assegnazione. */

#include <iostream>

int main(int argc, char ** argv)
{
	// Definizione variabili
	int a = 5;
	int b = 0;
	int * ptr_a = &a;
	
	// Stampa valori e indirizzi prima dell'assegnamento
	std::cout << "--- PRIMA DELL'ASSEGNAMENTO ---" << std::endl;
	std::cout << "Valore a: " << a << std::endl;
	std::cout << "Indirizzo a: " << ptr_a << std::endl;
	std::cout << "Valore b: " << b << std::endl;
	std::cout << "Indirizzo b: " << &b << std::endl << std::endl;
	
	// Assegnamento
	b = *(ptr_a); 

	// Stampa valori e indirizzi dopo l'assegnamento
	std::cout << "--- DOPO L'ASSEGNAMENTO ---" << std::endl;
	std::cout << "Valore a: " << a << std::endl;
	std::cout << "Indirizzo a: " << ptr_a << std::endl;
	std::cout << "Valore b: " << b << std::endl;
	std::cout << "Indirizzo b: " << &b << std::endl;
	
	return 0;
}
