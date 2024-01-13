#include <iostream>
#include "TLorentzVector.h"

template <class T>
T somma (T a, T b)
{
    return a + b ;
}

int main (int argc, char ** argv)
{

    int i_a = 1 ;
    int i_b = 2 ;
    double d_a = 5. ;
    double d_b = 7. ;
    TLorentzVector p1(1,2,3,4);
    TLorentzVector p2(1,2,3,5);

    std::cout << "somma di interi    " << somma (i_a, i_b) << std::endl ;
    std::cout << "somma di interi    " << somma<int> (i_a, i_b) << std::endl ;
    std::cout << "somma di razionali " << somma<double> (i_a, i_b) << std::endl ;
    std::cout << "somma di razionali " << somma (d_a, d_b) << std::endl ;
    std::cout << "somma ibrida       " << somma<double> (i_a, d_b) << std::endl ;
    std::cout << "somma vettoriale   " << std::endl;

    somma(p1, p2).Print();

    return 0 ;

}

