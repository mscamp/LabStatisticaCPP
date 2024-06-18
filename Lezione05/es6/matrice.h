/* Si implementi la classe templata matrice delle matrici quadrate di dimensione N, templata sulla dimensione delle matrici, definendo anche le operazioni fra matrici.

* Si definiscano gli operatori di moltiplicazione fra matrici e vettori, utilizzando anche la classe vettore.
* Si verifichi il funzionamento dell’algoritmo creato costruendo un esempio basato sulle rotazioni nel piano.
* Si scriva un metodo per il calcolo del determinante di una matrice nel caso sia quadrata, sfruttando la formula di Laplace ed una funzione ricorsiva.

Si ricordi che, in ogni caso di ricorsività, oltre alla formula iterativa va aggiunto anche il metodo che restituisce il determinate nel caso della matrice più piccola possibile, cioè quella composta da un unico numero. Quindi, oltre al metodo:

double determinante () 
  {
    // implementazione
  }

è necessario anche aggiungere, al di fuori della definizione della classe matrice, la specializzazione al caso di dimensione 1:

template<>
double matrice<1,1>::determinante () { return elementi[0][0] ; }

* Si scriva un metodo che calcola la matrice inversa, nel caso di una matrice quadrata e che ritorna una matrice nulla se la matrice orginale non è quadrata o ha determinante nullo. */

#ifndef matrice_h
#define matrice_h

#include <iostream>
#include "vettore.h"

template <int M, int N>
class matrice
{
    public:
        // Costruttore
        matrice() {};

        // Distruttore
        ~matrice() {};

        // Definizione di metodi e operatori
        vettore<M> operator*(vettore<N> v_colonna);

        // Modifica la componente ij
        void setComponent(int i, int j, double val)
        {
            matrix[i][j] = val;
        }

        // Stampa il contenuto
        void print()
        {
            for(int i = 0; i < M; ++i)
            {
                std::cout << "( ";

                for(int j = 0; j < N; ++j)
                {
                    std::cout << matrix[i][j] << " ";
                }

                std::cout << ")" << std::endl;
            }

            std::cout << std::endl;
        }

        // Restituisce il numero di righe
        int righe()
        {
            return M;
        }

        // Restituisce il numero di colonne
        int colonne()
        {
            return N;
        }

        // Elemento ij
        double element(int i, int j)
        {
            return matrix[i][j];
        }

        // Controlla se la matrice è quadrata
        bool quadrata()
        {
            if(M == N)
            {
                return true;
            }

            else
            {
                return false;
            }
        }


        matrice<M-1, N-1> minore (const int r, const int c)
        {
            matrice<M-1, N-1> min;
            int i_new = 0; 

            for (int i = 0 ; i < M ; ++i)
            {
                if (i == r) 
                {
                    continue;
                }
                
                int j_new = 0 ;

                for (int j = 0 ; j < N ; ++j)
                {
                    if (j == c) continue;
                    min.setComponent(i_new, j_new, element(i,j));
                    ++j_new ;
                }

                ++i_new ;
            }

            return min;
        }


        double determinante ()
        {
            double det = 0.0;

            // Controlla che la matrice sia quadrata
            if (!(quadrata()))
            {
                std::cout << "La matrice non è quadrata. Viene restituito 0." << std::endl;
                return -1;
            }

            for(int i = 0 ; i < M ; ++i)
            {
                det += matrix[0][i] * pow(-1, i + 2) * minore(0,i).determinante();
            }

            return det; 
        }

        matrice<N, M> inversa() 
        {
            matrice<N, M> inv;

            double det = determinante(); 
            double value = 0.0;
            
            if (det < 0.000001) 
            {
                return inv;
            }

            for (int i = 0 ; i < M ; ++i)
            {
                for (int j = 0 ; j < N ; ++j)
                {
                    value = minore(i,j).determinante() * pow(-1, i+j+2) * det;

                    if(value > 0 && value < 0.000001)
                    {
                        inv.setComponent(j, i, 0);
                    }
                    else  
                    {
                        inv.setComponent(j, i, value);
                    }
                }
            }

            return inv;
        }        

        private:
        double matrix[M][N];
};

// Prodotto righe per colonne
template <int P, int Q, int R>
matrice<P,R> operator*(matrice<P,Q> A, matrice<Q,R> B)
{
    matrice<P,R> prodotto;
    double sum = 0.0;

    for(int i = 0; i < P; ++i)
    {
        for(int j = 0; j < R; ++j)
        {
            sum = 0.0;

            for(int k = 0; k < Q; ++k)
            {
                sum += A.element(i, k) * B.element(k, j);
            }

            prodotto.setComponent(i, j, sum);
        }
    }

    return prodotto;
}

// Prodotto matrice * vettore
template <int P, int Q>
vettore<P> matrice<P,Q>::operator*(vettore<Q> v_colonna)
{
    vettore<P> prodotto;
    double sum = 0.0;

    for(int i = 0; i < P; ++i)
    {
        sum = 0.0;

        for(int j = 0; j < Q; ++j)
        {
            sum += element(i, j) * v_colonna[j];
        }

        prodotto.setCoord(i, sum);
    }

    return prodotto;
}

template<>
inline double matrice<1,1>::determinante() { return matrix[0][0]; }

#endif