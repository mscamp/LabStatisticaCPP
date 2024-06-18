/* Si crei un std::vector vuoto e lo si riempia con cinque oggetti del tipo della classe complesso sviluppato durante la Lezione 3.
* Tramite opportuni messaggi a schermo, si verifichi quando vengono chiamati costruttore, copy constructor, operatore di assegnazione e distruttore della classe complesso
*/

#include <iostream>
#include <vector>
#include "complesso.h"

int main(int argc, char ** argv)
{
    // Definizione complessi
    complesso c1(7, 8);
    complesso c2(9, 17.2);
    complesso c3(28, 10);
    complesso c4(0, 12);
    complesso c5(10, 0);

    // Definizione vector
    std::vector<complesso> v;

    // Riempimento vector
    v.push_back(c1);
    v.push_back(c2);
    v.push_back(c3);
    v.push_back(c4);
    v.push_back(c5);

    // Stampa vector
    for(std::vector<complesso>::iterator it = v.begin(); it != v.end(); ++it)
    {
        (*it).prop();
    }

    return 0;
}