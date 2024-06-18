#ifndef statistiche_h
#define statistiche_h
#include "TH1F.h"

class statistiche
{
	public:
		statistiche(int N); // Costruttore
		~statistiche(); // Distruttore

		// Metodi
		void addEvent(double value); // Aggiunge un evento
		double sampleMean() const; // Calcola la media del campione
		double sampleVariance(bool bessel = false) const; // Calcola la varianza del campione
		double sampleStd(bool bessel = false) const; // Calcola la deviazione standard del campione
		double sampleMeanStd(bool bessel = false) const; // Calcola la deviazione std della media
		double sampleSize() const; // Restituisce il numero di eventi
		double element(int index) const; // Restituisce l'elemento di indice index
		double minimumValue() const; // Restituisce il minimo valore del campione
		double maximumValue() const; // Restituisce il massimo valore del campione
		TH1F createHistogram() const; // Restituisce l'istogramma 
		void reset(); // Resetta la classe

	private: 
		// Membri
		int size_m; // Dimensione array
		double * array_m; // Puntatore all'array dei dati
		int last_index_m; // Dimensione campione
};

#endif
