#ifndef funzioniutili_h
#define funzioniutili_h
#include <fstream>

void sortArray(double * array, int N); // Riordina un array di double
double minimoArray(double * array, int N); // Determina il minimo di un array di double
double massimoArray(double * array, int N); // Determina il massimo di un array di double
float rand_range(float min, float max); // Genera un numero pseudo-random uniforme tra min e max
float rand_TAC(float pdf(float), float min, float max, float yMax); // Genera un numero casuale con un algoritmo TAC
float * rand_TCL(float a, float b, int N_distribuzioni, int N); // Genera un set di numeri casuali distribuito normalmente a partire da una distribuzione uniforme, sfruttando il teorema centrale del limite. Per ottenere una distribuzione normalizzata, a = -0.5 * sqrt(12 * N) e b = 0.5 * sqrt(12 * N). N è il numero di campioni presi da ciascuna distribuzione uniforme e N_distribuzioni il numero di distribuzioni uniformi
float pdf_gauss(float x, float media, float sigma); // PDF Gaussiana
float rand_exp(float lambda); // Genera un numero casuale esponenziale con il metodo della funzione inversa









#endif
