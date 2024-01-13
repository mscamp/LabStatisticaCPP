/* Si crei un std::vector vuoto e, tramite un ciclo for, lo si riempia con i primi 10 numeri della successione di Fibonacci.
* E’ conveniente, dal punto di vista dell’esecuzione di questo esercizio, utilizzare una funzione esterna al ciclo per il calcolo dei numeri di Fibonacci?
* Si stampi a schermo il suo contenuto utilizzando un ciclo su un numero intero, oppure utilizzando un iteratore.
*/

#include <iostream>
#include <vector>

int main(int argc, char ** argv)
{
    // Variabili
    const int N = 10;
    int f = 1;
    
    // Definizione del vector
    std::vector<int> fibonacci;

    for(int i = 0; i < N; ++i)
    {
        if(i == 0)
        {
            fibonacci.push_back(1);
        }
        fibonacci.push_back(f);
        f += fibonacci.at(i);
    }

    // Stampa del contenuto con counter
    for(int i = 0; i < N; ++i)
    {
        std::cout << "Elemento " << i << ": " << fibonacci.at(i) << std::endl;
    }

    std::cout << std::endl;

    // Stampa del contenuto con iteratore
    for(std::vector<int>::iterator it = fibonacci.begin(); it != fibonacci.end() - 1; ++it)
    {
        std::cout << "Elemento " << it - fibonacci.begin() << ": " << *it << std::endl;
    }

    return 0;
}