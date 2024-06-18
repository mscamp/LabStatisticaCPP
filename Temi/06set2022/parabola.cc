#include "parabola.h"
#include <math.h>
#include <utility>

// Costruttore
parabola::parabola(double x0):
    m_x0(x0)
{};

// Distruttore
parabola::~parabola() {};

// Metodo eval
double parabola::eval(double x)
{
    if(-m_x0 < x < m_x0)
    {
        return (3/(4 * m_x0) * (-(pow(x, 2) / pow(m_x0, 2)) + 1));
    }
    
    else
    {
        return 0;
    }
}

double rand_range(double a, double b)
{
    return a + ((b - a) * (rand() / static_cast<double>(RAND_MAX)));
}

double rand_TAC(double x0)
{
    parabola f(x0);
    double x = 0.0;
    double y = 0.0;

    do 
    {
        x = rand_range(-x0, x0);
        y = rand_range(0.0, f.eval(0.0));

    } while(y > f.eval(x));

    return x;
}

std::pair<double, double> integral_hitormiss(double x0, int trials)
{
    parabola f(x0);
    std::pair<double, double> integral;
    double x = 0.0;
    double y = 0.0;
    int hits = 0;
    double A = 2 * x0 * f.eval(0);

    for(int i = 0; i < trials; ++i)
    {
        x = rand_range(-x0, x0);
        y = rand_range(0.0, f.eval(0));

        if(y < f.eval(x))
        {
           ++hits; 
        }
    }

    double p = hits / static_cast<double>(trials);

    integral.first = A * p;
    integral.second = (A / sqrt(static_cast<double>(trials))) * sqrt(p * (1 - p));

    return integral;
}