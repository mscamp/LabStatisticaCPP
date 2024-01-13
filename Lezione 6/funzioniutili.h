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
double find_zeros(double g(double), double a, double b); // Determina gli zeri di una funzione mediante il metodo di bisezione in un intervallo dato
double find_zeros_recursive(double g(double), double a, double b); // Metodo di bisezione ricorsivo
double find_min(double g(double), double a, double b); // Determina il minimo di una funzione mediante il metodo della sezione aurea in un intervallo dato
double find_min_recursive(double g(double), double a, double b); // Sezione aurea ricorsiva per il minimo
double find_max(double g(double), double a, double b); // Determina il massimo di una funzione mediante il metodo della sezione aurea in un intervallo dato
double find_max_recursive(double g(double), double a, double b); // Sezione aurea ricorsiva per il massimo
int fattoriale(int num); // Calcola il fattoriale di un numero dato con una procedura ricorsiva








#endif
