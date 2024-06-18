#ifndef complesso_h
#define complesso_h

class complesso
{
	public:
		complesso(double r, double i); // Costruttore
		complesso(double r); // Costruttore numeri reali
		complesso(const complesso & orig); // Costruttore di copia
		complesso(); // Costruttore di default
		~complesso(); // Distruttore

		// Metodi
		double modulo() const;
		double phase() const;
		double realp() const;
		double impart() const;
		void prop();
		complesso conj() const;

		// Operatori
		complesso & operator= (const complesso & orig);
		complesso operator+ (const complesso & addendo);
		complesso operator- (const complesso & sottraendo);
		complesso operator* (const complesso & fattore); 
		complesso operator* (const double & fattore);
		complesso & operator+= (const complesso & addendo);
		complesso & operator+= (const double & addendo);
		complesso & operator-= (const complesso & sottraendo);
		complesso & operator-= (const double & sottraendo);
		complesso & operator*= (const complesso & fattore);
		complesso & operator*= (const double & fattore);
		complesso & operator/= (const complesso & divisore);
		complesso & operator/= (const double & divisore);

	private:
		// Membri
		double m_reale;
		double m_immaginario;
};

#endif
