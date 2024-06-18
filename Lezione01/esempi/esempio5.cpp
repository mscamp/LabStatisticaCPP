// Per compilare c++ -o a.out es3.cpp
#include <iostream>
using namespace std;

int * creaInteroDoppio(int num) 
{
	int * doppio = new int(num*2);
	return doppio;
}

int main(int argc, char ** argv)
{
	int num = 5;
	int * intDoppio = creaInteroDoppio(num);
	cout << "Numero: " << num << endl;
	cout << "Numero doppio: " << *intDoppio << endl;
	delete intDoppio;

	return 0;
}

