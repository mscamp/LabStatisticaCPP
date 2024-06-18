/* Rifare l’esercizio su media/varianza della lezione di ripasso realizzando un’unica funzione che le calcoli entrambe, facendo opportuno uso puntatori o referenze. */

#include <iostream>
#include <cmath>

void MediaVarianza (double array[], double * m, double * v, int N)
{
	double somma = 0.0;
	double sumsq = 0.0;

	// Calcola la somma
	for(int i = 0; i < N; ++i)
	{
		somma += array[i];
	}
	
	// Determina la media e la assegna a media utilizzando il puntatore m
	*m = somma / N;

	// Determina la somma degli scarti quadratici
	for(int i = 0; i < N; ++i)
	{
		sumsq += pow((array[i] - *m), 2);
	}

	// Calcola la varianza e la assegna a varianza utilizzando il puntatore v
	*v = sumsq / N;		
}

int main(int argc, char ** argv)
{
	// Definizione array dati, media, varianza
	double arr[10] = { 0.0 };
	double media = 0.0;
	double varianza = 0.0;
	
	// Popola array
	for(int i = 0; i < 10; ++i)
	{
		std::cout << "Inserire elemento " << i << " -> ";
		std::cin >> arr[i];
	}

	// Determina media e varianza e le stampa a schermo
	MediaVarianza(arr, &media, &varianza, 10); // Alla funzione vengono passate le variabili per referenza
	std::cout << "Media: " << media << std::endl;
	std::cout << "Varianza: " << varianza << std::endl;

	return 0;
}
