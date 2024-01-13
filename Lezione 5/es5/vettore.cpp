#include <iostream>
#include "vettore.h"

int main(int argc, char ** argv)
{
    // Definizione vettori 3D
    const int N = 3;
    vettore<N> v1;
    vettore<N> v2;
    vettore<N> somma;
    vettore<N> scaled;

    // Riempimento vettori
    for(int i = 0; i < N; ++i)
    {
       v1.setCoord(i, i + 1);
       v2.setCoord(i, i + 2);
    }

    // Stampa a schermo i vettori
    v1.print();
    v2.print();

    // Stampa a schermo le norme
    std::cout << "Norma v1: " << v1.norm() << std::endl;
    std::cout << "Norma v2: " << v2.norm() << std::endl;
    std::cout << std::endl;

    // Test operatori
    somma = v1 + v2;
    scaled = v1 * 2;

    somma.print();
    scaled.print();
    std::cout << "Norma somma: " << somma.norm() << std::endl;
    std::cout << "Norma scaled: " << scaled.norm() << std::endl;

    return 0;
}