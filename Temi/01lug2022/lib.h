#ifndef lib_h
#define lib_h
#include "TH1F.h"

double rand_range(double a, double b);
double gauss(double x, double media, double sigma);
double gauss_TAC(double media, double sigma, double x_min, double x_max);
TH1F generate_hist(std::vector<double> sample, int N, double min, double max);

#endif