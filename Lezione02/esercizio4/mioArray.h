#ifndef mioArray_h
#define mioArray_h

class mioArray 
{
	public:
		mioArray(int N); // costruttore
		mioArray(const mioArray & orig); // copy constructor
		~mioArray(); // distruttore
		void print() const; // stampa array
		double elemento(int index) const;	// accesso agli elementi
		void modifica_elemento(int index, double value); // modifica elementi

	private:
		int m_dim; // dimensione array
		double * m_ptr; // puntatore al primo elemento dell'array
};

#endif
