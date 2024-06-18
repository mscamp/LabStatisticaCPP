#ifndef parabola_h
#define parabola_h
#include <cstdlib>
#include <utility>

class parabola
{
    public:
        parabola(double x0); // Costruttore
        ~parabola(); // Distruttore
        double eval(double x);

    private:
        double m_x0;
};

double rand_range(double a, double b);
double rand_TAC(double x0);
std::pair<double, double> integral_hitormiss(double x0, int trials);
















#endif