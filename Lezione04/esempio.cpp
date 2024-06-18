#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char ** argv)
{
	float min = 15;
	float max = 89;
	srand(time(NULL));
	cout << "Numero casuale: " << rand() << endl;
	cout << "Numero casuale tra 0 e 1: " << rand() / static_cast<float>(RAND_MAX) << endl;
	cout << "Numero casuale tra " <<  min << " e " << max << ": " << (max-min)*(rand() / static_cast<float>(RAND_MAX)) << endl;
	cout << "RAND_MAX: " << RAND_MAX << endl;
	return 0;
}
