#include "lib.h"
#include <vector>
#include <cstdlib>
#include "TF1.h"

double rand_range(double a, double b)
{
    return a + (b - a) * (rand()/static_cast<double>(RAND_MAX));
}

std::vector<double> genera_Random(int iterazioni)
{
    std::vector<double> vec;

    for(int i = 0; i < iterazioni; ++i)
    {
        vec.push_back(rand_range(0.0, 10.0));
    }

    return vec;
}

double y(TF1 f, double x)
{
    return f.Eval(x);
}
