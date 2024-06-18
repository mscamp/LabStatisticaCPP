#ifndef loglikelihood_h
#define loglikelihood_h

#include <vector>

double loglikelihood(const std::vector<double> & x, double par);
double find_max_likelihood(double f(const std::vector<double> &, double), double xmin, double xmax, const std::vector<double> & data, double precision = 0.0001); 
double h(const std::vector<double> & x, double par, double tau_max);
double find_zeros_likelihood(double g(const std::vector<double> &, double, double), double a, double b, const std::vector<double> & data, double par_max, double precision = 0.0001);

#endif
