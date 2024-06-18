#include <iostream>
#include <math.h>
#include "complesso.h"

// Costruttore
complesso::complesso(double r, double i): 
	m_reale(r),
	m_immaginario(i)
	{}

// Costruttore numeri reali
complesso::complesso(double r):
	m_reale(r),
	m_immaginario(0.0)
	{}

// Costruttore di copia
complesso::complesso(const complesso & orig):
	m_reale(orig.m_reale),
	m_immaginario(orig.m_immaginario)
	{}

// Costruttore di default
complesso::complesso():
	m_reale(0.0),
	m_immaginario(0.0)
	{}

// Distruttore
complesso::~complesso() {}

// Metodi
double complesso::modulo() const
{
	return sqrt(pow(m_reale, 2) + pow(m_immaginario, 2));
}

double complesso::phase() const
{
	return atan(m_immaginario/m_reale);
}

double complesso::realp() const
{
	return m_reale;
}

double complesso::impart() const
{
	return m_immaginario;
}

void complesso::prop()
{
	std::cout << "MODULO: " << this -> modulo() << std::endl;
    std::cout << "FASE: " << this -> phase() << std::endl;
    std::cout << "PARTE REALE: " << this -> realp() << std::endl;
    std::cout << "PARTE IMMAGINARIA: " << this -> impart() << std::endl;
    std::cout << "\n";
}

complesso complesso::conj() const
{
	complesso coniugato(m_reale, -m_immaginario);
	return coniugato;
}

// Operatori

// Assegnazione
complesso & complesso::operator= (const complesso & orig)
{
	m_reale = orig.m_reale;
	m_immaginario = orig.m_immaginario;
	return *this;
}

// Somma
complesso complesso::operator+ (const complesso & addendo)
{
	complesso somma(m_reale, m_immaginario);
	somma.m_reale = somma.m_reale + addendo.m_reale;
	somma.m_immaginario = somma.m_immaginario + addendo.m_immaginario;
	return somma;
}

// Differenza
complesso complesso::operator- (const complesso & sottraendo)
{
	complesso differenza(m_reale, m_immaginario);
	differenza.m_reale = differenza.m_reale - sottraendo.m_reale;
	differenza.m_immaginario = differenza.m_immaginario - sottraendo.m_immaginario;
	return differenza;
}

// Moltiplicazione per complesso
complesso complesso::operator* (const complesso & fattore)
{
	complesso prodotto(m_reale, m_immaginario);
	prodotto.m_reale = (prodotto.m_reale * fattore.m_reale) - (prodotto.m_immaginario * fattore.m_immaginario);
	prodotto.m_immaginario = (prodotto.m_reale * fattore.m_immaginario) + (prodotto.m_immaginario * fattore.m_reale);
	return prodotto;	
}

// Moltiplicazione per reale
complesso complesso::operator* (const double & fattore)
{
	complesso prodotto(m_reale, m_immaginario);
	prodotto.m_reale = prodotto.m_reale * fattore;
	prodotto.m_immaginario = prodotto.m_immaginario * fattore;
	return prodotto;
}

// Operatore += (complesso)
complesso & complesso::operator+= (const complesso & addendo)
{
	m_reale = m_reale + addendo.m_reale; 
	m_immaginario = m_immaginario + addendo.m_immaginario;
	return *this;
}

// Operatore += (reale)
complesso & complesso::operator+= (const double & addendo)
{
	m_reale = m_reale + addendo;
	return *this;
}

// Operatore -= (complesso)
complesso & complesso::operator-= (const complesso & sottraendo)
{
	m_reale = m_reale - sottraendo.m_reale;
	m_immaginario = m_immaginario - sottraendo.m_immaginario;
	return *this;
}

// Operatore -= (reale)
complesso & complesso::operator-= (const double & sottraendo)
{
	m_reale = m_reale - sottraendo;
	return *this;
}

// Operatore *= (complesso)
complesso & complesso::operator*= (const complesso & fattore)
{
	m_reale = (m_reale * fattore.m_reale) - (m_immaginario * fattore.m_immaginario);
	m_immaginario = (m_reale * fattore.m_immaginario) + (m_immaginario * fattore.m_reale);
	return *this;
}

// Operatore *= (reale)
complesso & complesso::operator*= (const double & fattore)
{
	m_reale = m_reale * fattore;
	m_immaginario = m_immaginario * fattore;
	return *this;
}

// Operatore /= (complesso)
complesso & complesso::operator/= (const complesso & divisore)
{
	if(divisore.modulo() != 0)
	{
		*this *= (divisore.conj()*(1/divisore.modulo()));
		return *this;
	}

	else
	{
		std::cout << "Il divisore non puo' avere modulo nullo. " << std::endl;
		return *this;
	}
}

// Operatore /= (reale)
complesso & complesso::operator/= (const double & divisore)
{
	if (divisore != 0)
	{
		m_reale = m_reale / divisore;
		m_immaginario = m_immaginario / divisore;
		return *this;
	}

	else
	{
		std::cout << "Il divisore non puo' essere zero. " << std::endl;
		return *this;
	}
}
