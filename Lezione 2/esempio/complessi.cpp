#include <iostream>
#include "complessi.h"

int main(int argc, char ** argv) {

	complesso c1(1, 1.7);
	complesso * c2 = new complesso(17, 12.2);

	std::cout << "Modulo 1: " << c1.modulo() << std::endl;
	std::cout << "Modulo 2: " << c2->modulo() << std::endl;

	delete c2;

	return 0;
}
