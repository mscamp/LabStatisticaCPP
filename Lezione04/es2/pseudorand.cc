#include <iostream>
#include "pseudorand.h"
#include <cstdlib>

pseudorand::pseudorand (long int m, long int a, long int c, int n):
	M(m),
	A(a),
	C(c),
	N(n)
{
	array = new long int[N];
}

pseudorand::~pseudorand() 
{
	delete[] array;
}

void pseudorand::changeseed(long int s)
{
	this->S = s;
}

long int * pseudorand::linear_gen()
{
        array[0] = S;

        for(int i = 1; i < N; i++)
        {
                array[i] = (A * array[i-1] + C) % M;
        }
		
        return array;
}

