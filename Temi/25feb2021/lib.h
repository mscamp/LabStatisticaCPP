#ifndef lib_h
#define lib_h

#include <vector>
#include "TF1.h"

double rand_range(double a, double b);
std::vector<double> genera_Random(int iterazioni = 6);
double y(TF1 f, double x);




#endif