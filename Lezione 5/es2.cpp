/* Si testi la funzione somma sviluppata nell’esercizio precedente sulla classe dei numeri complessi sviluppata durante la Lezione 3, aggiungendo anche una specializzazione per un tipo a piacere. */

#include <iostream>
#include "complesso.h"
#include "TLorentzVector.h"

// Somma tra due oggetti di una classe C
template <class C>
C somma(C c1, C c2)
{
	return (c1 + c2);
}

// Specializzazione del template per oggetti TLorentzVector
template <>
TLorentzVector somma(TLorentzVector v1, TLorentzVector v2)
{    	
	std::cout << "Somma di TLorentzVector: " << std::endl;
	return (v1 + v2);
}

int main(int argc, char ** argv)
{
	// Definizione oggetti
	complesso c1(7,29);
	complesso c2(12.67, 72.47);
	TLorentzVector v1(0, 1, 2, 3);
	TLorentzVector v2(5, 7, 4, 3);

	// Test della funzione somma
	std::cout << "Somma di complessi: " << std::endl;
	somma(c1, c2).prop();
	somma(v1, v2).Print(); // Somma di TLorentzVector

	return 0;
}
