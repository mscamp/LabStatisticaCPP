/* Si crei una std::map vuota e la si riempia con una sequenza di numeri complessi, utilizzando la norma dei numeri stessi come chiave di ordinamento della mappa.
* Si stampino quindi a schermo i numeri, ordinati per norma.
*/

#include <iostream>
#include <map>
#include "complesso.h"

int main(int argc, char ** argv)
{
    // Definizione dei numeri complessi
    complesso c1(7, 8);
    complesso c2(9, 17.2);
    complesso c3(28, 10);
    complesso c4(0, 12);
    complesso c5(10, 0);

    // Definizione std::map
    std::map<double, complesso> mappa;

    // Mappatura
    mappa[c1.modulo()] = c1;
    mappa[c2.modulo()] = c2;
    mappa[c3.modulo()] = c3;
    mappa[c4.modulo()] = c4;
    mappa[c5.modulo()] = c5;

    // Stampa dei numeri ordinati per norma
    for(std::map<double, complesso>::iterator it = mappa.begin(); it != mappa.end(); ++it)
    {
        std::cout << "Chiave: " << it -> first << std::endl;

        (it -> second).prop();
    }

    return 0;
}