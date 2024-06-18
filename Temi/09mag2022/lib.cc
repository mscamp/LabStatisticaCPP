#include "lib.h"
#include "funzioniutili.h"
#include <fstream>
#include <math.h>
#define PI 3.14159

std::pair<std::vector<double>, std::vector<double>> read_file(std::string file_name)
{
    // Definizione oggetti
    std::vector<double> x;
    std::vector<double> y;  
    std::ifstream file; 
    std::pair<std::vector<double>, std::vector<double>> xy;

    // Variabili temporanee
    double tmp1 = 0.0;
    double tmp2 = 0.0;

    // Apre il file
    file.open(file_name, std::ios::in);

    // Lettura file
    while(true)
    {
        file >> tmp1 >> tmp2;

        if(file.eof() == true)
        {
            break;
        }

        x.push_back(tmp1);
        y.push_back(tmp2);
    }

    // Chiude il file
    file.close();

    // Aggiunge i vector ad un pair
    xy.first = x;
    xy.second = y;

    return xy;
}

double f(double * x, double * par)
{
    return par[0] * sin(par[1] * x[0] + par[2]);
}

double determina_ampiezza(std::vector<double> w)
{
    return 0.5 * (massimoVec(w) - minimoVec(w));
}

double determina_omega(std::vector<double> v, std::vector<double> w)
{
    double min_w = minimoVec(w);
    double max_w = massimoVec(w);
    int n_min = 0;
    int n_max = 0;

    for(int i = 0; i < w.size(); ++i)
    {
        if(w.at(i) == min_w) {n_min = i;}
        if(w.at(i) == max_w) {n_max = i;}
    }

    return PI / fabs(v.at(n_max) - v.at(n_min));
}
