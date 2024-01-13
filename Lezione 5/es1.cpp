/* Si scriva una funzione somma che, utilizzando la tecnologia template, sia applicabile a qualunque tipo numerico del C++ */

#include <iostream>

// Funzione somma templata sul tipo T
template <typename T>
T somma(T a, T b)
{
	return a + b;
}

int main(int argc, char ** argv)
{
	int n1 = 4;
	int n2 = 7;
	float f1 = 5.5;
	float f2 = 8.7;

	std::cout << "Somma di interi: " << somma<int> (n1, n2) << std::endl;
	std::cout << "Somma di float: " << somma<float> (f1, f2) << std::endl;

	return 0;
}
