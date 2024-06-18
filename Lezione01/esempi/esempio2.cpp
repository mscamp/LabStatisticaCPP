#include <iostream>
using namespace std;

int main(int argc, char ** argv) 
{
	int num = 0;
	int * pointer = &num;
	cout << "Inserire numero > ";
	cin >> num;
	cout << "Valore: " << num << endl;
	cout << "Indirizzo: " << pointer << endl;
	
	// Dereferenziazione
	cout << "Valore del puntatore dereferenziato: " << *pointer << endl;

	// Cambio del valore
	*pointer = 10;
	cout << "Valore del puntatore dereferenziato 2: " << *pointer << endl;

	return 0;
}
