#ifndef lib_h
#define lib_h
#include <vector>
#include <utility>
#include <string>
#include "funzioniutili.h"

std::pair<std::vector<double>, std::vector<double>> read_file(std::string file_name);
double f(double * x, double * par);
double determina_ampiezza(std::vector<double> w);
double determina_omega(std::vector<double> v, std::vector<double> w);

#endif