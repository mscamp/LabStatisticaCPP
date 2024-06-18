/* Dichiarare un puntatore e poi cercare di assegnargli direttamente un valore numerico. Cosa succede? Perché? */

#include <iostream>

int main(int argc, char ** argv)
{
	int * ptr = 4;

	/* Il compilatore restituisce un errore relativo al casting quando si cerca di compilare il codice: 
	si sta assegnando un valore intero ad una variabile di tipo puntatore ad intero. */

	return 0;
}
