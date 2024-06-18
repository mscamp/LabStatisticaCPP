/* 1) Implementate la classe complesso come descritta nella lezione al paragrafo 2.2.1, includendo anche un programma di test delle sue funzionalità.
 * 2) Aggiungete alla classe complesso i vari tipi di costruttore discussi nella sezione 2.3 della lezione.
 * 3) Aggiungete alla classe complesso le seguenti operazioni:

		somma di due numeri complessi
		differenza fra due numeri complessi
		moltiplicazione per un numero reale
		prodotto fra due numeri complessi
		operatore += con come argomento un numero complesso
		operatore += con come argomento un numero reale
		operatore -= con come argomento un numero complesso
		operatore -= con come argomento un numero reale
		operatore *= con come argomento un numero complesso
		operatore *= con come argomento un numero reale
		operatore /= con come argomento un numero complesso
		operatore /= con come argomento un numero reale

	In quali casi vanno effettuati controlli sul valore dei numeri complessi in input alle funzioni? */

#include <iostream>
#include "complesso.h"

int main (int argc, char ** argv)
{
	// Definisce due numeri complessi
	complesso z1(9,10);
	complesso z2(3,5);

	// Stampa proprietà z1
	z1.prop();	
	// Stampa proprietà z2
	z2.prop();

	// Costruzione di una copia
	complesso z3(z1);
	
	// Stampa proprietà z3
	z3.prop();

	// Definisce un numero reale r
	complesso r(15);
	
	// Stampa proprietà r
	r.prop();

	// Operazioni
	complesso somma = z1 + z2;
	complesso prod = z1 * z2;
	complesso diff = z2 - z1;
	complesso prodreale = z2 * r;
	complesso z4(9,12);
	complesso z5(0,34);
	double c = 17;
	
	
	z1 += z3;
	z3 -= c;
	z5 *= z3 *= z2;
	z4 /= z1 /= z2;
	z5 /= c;

	somma.prop();
	prod.prop();
	diff.prop();
	prodreale.prop();
	
	z4.prop();
	z5.prop();

	return 0;
}
