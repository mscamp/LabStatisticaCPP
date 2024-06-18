/* Realizzare una funzione che risolva un’equazione di secondo grado: ax2 + bx + c = 0. La funzione deve rendere disponibile il risultato al programma che la chiama. */

#include <iostream>
#include <cmath>

// La funzione deve essere di tipo bool e restituire true/false, a seconda che esistano o meno soluzioni reali
bool solve2ndDegree (double * par, double * x)
{
	// Definizione parametri e delta
	double a = par[0];
	double b = par[1];
	double c = par[2];
	double delta = (pow(b,2)-(4*a*c));

	// Verifica se esistono soluzioni, in tal caso le calcola utilizzando la formula quadratica
	if(delta >= 0)
	{
		x[0] = (-b+sqrt(delta))/(2*a);
		x[1] = (-b-sqrt(delta))/(2*a);
		return true;
	}
	
	// Se non ci sono soluzioni, la funzione ritorna 'false'
	else
	{ 
		return false;
	}
	
}

int main(int argc, char ** argv)
{
	// Definizione array dei coefficienti, array delle soluzioni e lettere corrispondenti ai nomi dei coefficienti
	double coeff[3] = { 0, 0, 0 };
	double soluz[2] = { 0, 0 };
	char lettere[3] = { 'a', 'b', 'c' };
	
	// Inserimento dei coefficienti
	for (int i = 0; i < 3; ++i)
	{
		std::cout << "Inserire coefficiente " << lettere[i] << " -> ";
		std::cin >> coeff[i];

		// Controlla che a sia non nullo
		while(lettere[i] == 'a' && coeff[i] == 0)
		{
			std::cout << "a deve essere diverso da zero." << std::endl;
			std::cout << "Inserire coefficiente " << lettere[i] << " -> ";
			std::cin >> coeff[i];
		}

		std::cout << "\n";
	}

	// Stampa le soluzioni nel caso esistano
	if(solve2ndDegree(coeff, soluz))
	{
		std::cout << "Le soluzioni dell'equazione sono: x1 = " << soluz[0] << " e x2 = " << soluz[1] << std::endl;
	}

	// Avvisa l'utente della non esistenza delle soluzioni
	else
	{ 
		std::cout << "L'equazione non ha soluzioni reali." << std::endl;
	}

	return 0;
}
