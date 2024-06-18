#include "lib.h"
#include <cmath>
#include <cstdlib>
#include <math.h>
#include "TMath.h"
#include "TH1F.h"

double rand_range(double a, double b)
{
    return a + ((b - a) * (rand() / (static_cast<double>(RAND_MAX))));
}

double gauss(double x, double media, double sigma)
{
    return (1.0 / (sigma * sqrt(2 * TMath::Pi()))) * exp(-pow((x - media), 2) / (2 * pow(sigma, 2)));
}

double gauss_TAC(double media, double sigma, double x_min, double x_max)
{
    double x = 0.0;
    double y = 0.0;
    double y_max = gauss(media, media, sigma);

    do 
    {
        x = rand_range(x_min, x_max);
        y = rand_range(0.0, y_max);

    } while (y > gauss(x, media, sigma));

    return x;
}

TH1F generate_hist(std::vector<double> sample, int N, double min, double max)
{
    TH1F hist("hist", "Eventi Gaussiani", N, min, max);

    for(int i = 0; i < sample.size(); ++i)
    {
        hist.Fill(sample.at(i));
    }

    return hist;
}