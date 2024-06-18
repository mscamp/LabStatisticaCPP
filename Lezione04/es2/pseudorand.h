#ifndef pseudorand_h
#define pseudorand_h

class pseudorand 
{
	public:
		pseudorand(long int m, long int a, long int c, int n); // Costruttore
		~pseudorand(); // Distruttore
		void changeseed(long int s); // Modifica il seed
		long int * linear_gen(); // Generatore lineare
	private:
		long int * array; // Sequenza
		long int S; // Seed
		long int M; 
		long int A;
		long int C;
		int N; // Numero elementi della sequenza
};

#endif
