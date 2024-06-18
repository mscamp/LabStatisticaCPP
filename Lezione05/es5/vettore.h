/* Si implementi la classe templata vettore definita nella lezione.
* Si ricordi di controllare che gli indici passati ai metodi della classe siano entro i limiti della memoria occupata dagli oggetti di tipo vettore
* Si aggiungano gli operatori algebrici necessari per la definizione di uno spazio vettoriale
*/

#ifndef vettore_h
#define vettore_h

#include <iostream>
#include <cmath>

template <int N>
class vettore
{
  public:
    // Costruttore
    vettore(){}

    // Distruttore
    ~vettore(){}

    // Operatori
    double operator* (vettore<N> & v2);

    // Modifica la componente i-esima
    void setCoord (int i, double val) 
    {  
        elementi[i] = val;
    }

    // Norma euclidea
    double norm()
    {
        double sum = 0.0;

        for(int i = 0; i < N; ++i)
        {
            sum += pow(elementi[i], 2);
        }

        return sqrt(sum);
    }

    // Stampa il contenuto
    void print()
    {
        std::cout << "( ";

        for(int i = 0; i < N; ++i)
        {
            std::cout << elementi[i] << " ";
        }

        std::cout << ")" << std::endl << std::endl;
    }

    // Override di []
    double operator[] (int index)
    {
        return elementi[index];
    }

    // Somma vettoriale
    vettore operator+ (vettore & addendo)
    {
        vettore sum;

        for(int i = 0; i < N; ++i)
        {
            sum.setCoord(i, elementi[i]+addendo[i]);
        }

        return sum;
    }

    // Prodotto per uno scalare
    vettore operator* (const double & coeff)
    {
        vettore v;

        for(int i = 0; i < N; ++i)
        {
            v.setCoord(i, elementi[i] * coeff);
        }

        return v;
    }

      private:
    double elementi[N];
};

#endif