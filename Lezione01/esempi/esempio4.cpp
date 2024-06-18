#include <iostream>
using namespace std;

int main(int argc, char ** argv) 
{
	// Creazione di una variabile nella mem heap
	
	int * ptr_int = new int(6); // Alloca la memoria per un intero e lo inizializza con valore 6
	cout << *ptr_int << endl;
	delete ptr_int; // Dealloca la memoria
	return 0;
}
