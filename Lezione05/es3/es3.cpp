/* Si costruisca la classe SimpleArray, templata sul tipo degli oggetti che contiene, implementando le funzioni definite nel prototipo presentato a lezione.
* Si ricordi di utilizzare correttamente l’allocazione dinamica della memoria.
* Si aggiungano alla classe anche metodi che permettano di accedere agli elementi della classe in caso vengano chiamati su un oggetto const.
* Si faccia in modo che i metodi di accesso al contenuto del SimpleArray controllino il valore dell’indice prima di accedere all’array salvato in memoria.
* Si verifichi che la classe SimpleArray può essere templata sulla classe dei numeri complessi sviluppata durante la Lezione 3.
*/

#include <iostream>
#include "SimpleArray.h"
#include "complesso.h"

template <class C>
C somma(C a, C b)
{
	return a + b;
}

int main(int argc, char ** argv)
{
	// Definizione complessi
	complesso c1(0.,0.);
	complesso c2(1., 17.);
	complesso c3(9., 10.8);

	// Definizione SimpleArray
	SimpleArray<complesso> array(3); // Array di complessi
	
	// Riempimento SimpleArray
	array.modificaElemento(0, c1);
	array.modificaElemento(1, c2);
	array.modificaElemento(2, c3);

	// Stampa c3
	std::cout << "Elemento 2: " << std::endl;
	array[2].prop();
	std::cout << std::endl;	

	// Stampa la somma di c1 e c2
	std::cout << "Somma di c1 e c2: " << std::endl;
	somma(array[0], array[1]).prop();
	std::cout << std::endl;	

	return 0;
}
