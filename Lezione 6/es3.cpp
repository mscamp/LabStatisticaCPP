/* Si implementi una funzione che calcola il fattoriale di un numero utilizzando una funzione ricorsiva. */

#include <iostream>

int fattoriale(int num)
{
	if (num == 1)
	{
		return 1;
	}

	else
	{
		return num*fattoriale(num-1);
	}
}

int main(int argc, char ** argv)
{
	// Definizione variabili
	int n = 5;
	int fact = fattoriale(n);

	// Stampa a schermo il risultato
	std::cout << "Il fattoriale di " << n << " e' " << fact << std::endl;

	return 0;
}
