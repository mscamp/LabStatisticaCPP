#include "vettore.h"
#include "matrice.h"
#define PI 3.14159265


int main(int argc, char ** argv)
{
    // Definizione dimensioni
    const int N = 2;
    const int M = 3;

    // Definizione matrici e vettori
    matrice<N,N> m1;
    matrice<N,M> m2;
    matrice<N,M> prodotto;
    vettore<N> prodotto1;
    
    vettore<M> v_colonna;
    vettore<N> v_riga;

    matrice<N, N> rotazione;
    vettore<N> prodotto_ruotato;

    // Definizione variabili 
    double alfa = PI/2;
    double sin_alfa = sin(alfa);
    double cos_alfa = cos(alfa);

    // Riempimento m1 e m2
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            if(i == j)
            {
                m1.setComponent(i, j, 1);
            }

            else  
            {
                m1.setComponent(i, j, 3);
            }
        }
    }

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < M; ++j)
        {
            if(i == j)
            {
                m2.setComponent(i, j, 1);
            }

            else  
            {
                m2.setComponent(i, j, 5);
            }
        }
    }

    // Riempimento dei vettori
    for(int i = 0; i < N; ++i)
    {
        v_riga.setCoord(i, i + 1);
    }

    v_colonna.setCoord(0, 1);
    v_colonna.setCoord(1, 2);
    v_colonna.setCoord(2, 6);

    // Riempimento matrice di rotazione
    rotazione.setComponent(0, 0, cos_alfa);
    rotazione.setComponent(0, 1, -sin_alfa);
    rotazione.setComponent(1, 0, sin_alfa);
    rotazione.setComponent(1, 1, cos_alfa);

    // Stampa m1 e m2
    m1.print();
    m2.print();

    // Calcola il prodotto m1 * m2 e stampa a schermo
    prodotto = m1 * m2;
    prodotto.print();

    v_riga.print();
    v_colonna.print();

    // Test prodotto matrice * vettore colonna
    prodotto1 = (m2 * v_colonna); 
    prodotto1.print();

    // Rotazione di 95 gradi in senso antiorario di prodotto1
    prodotto_ruotato = (rotazione * prodotto1);
    prodotto_ruotato.print();
    
    // Determinante di m1
    std::cout << m1.determinante() << std::endl;

    // Determinante di rotazione
    std::cout << rotazione.determinante() << std::endl;
    std::cout << std::endl;

    // Inversa di rotazione
    rotazione.inversa().print();

    return 0;
}