// Per compilare c++ -o a.out es3.cpp
#include <iostream>
using namespace std;

int raddoppia(int num) 
{
	num *= 2;
	return num;
}

void raddoppia_ref(int * num)
{
	*num *= 2;
}

int main(int argc, char ** argv)
{
	// Per valore
	int numero = 0;
	cout << "Inserisci numero > ";
	cin >> numero;
	cout << "Numero: " << numero << endl;
	cout << "Raddoppia: " << raddoppia(numero) << endl;
	cout << "Numero: " << numero << endl;

	// Per referenza
	int * ptr = &numero;
	raddoppia_ref(&numero);
	cout << "Numero: " << numero << endl;
	return 0;
}

