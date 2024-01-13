#include <iostream>
#include "mioArray.h"

// Costruttore
mioArray::mioArray (int N):

	m_dim(N)
	{
		m_ptr = new double[m_dim];
	}

// Copy constructor
mioArray::mioArray (const mioArray & orig):
	
	m_dim(orig.m_dim)
	{
		m_ptr = new double[m_dim];

		for(int i = 0; i < m_dim; i++)
		{
			m_ptr[i] = orig.m_ptr[i];
		}
	}

// Distruttore
mioArray::~mioArray()
{
	delete[] m_ptr;
}

// Stampa mioArray
void mioArray::print() const
{
	for(int i = 0; i < m_dim; i++)
	{
		std::cout << "Elemento " << i << ": " << m_ptr[i] << std::endl;
	}
}

// Accesso agli elementi
double mioArray::elemento(int index) const
{
	if(index >= m_dim)
	{
		throw std::out_of_range("L'indice inserito è più grande della dimensione dell'array.\n");
	}

	else if(index < 0)
	{
		throw std::out_of_range("L'indice inserito non puo' essere negativo.\n");
	}

	return m_ptr[index];
}

void mioArray::modifica_elemento(int index, double value)
{
	if(index >= m_dim)
	{
		throw std::out_of_range("L'indice inserito è più grande della dimensione dell'array.\n");
	}

	else if(index < 0)
	{
		throw std::out_of_range("L'indice inserito non puo' essere negativo.\n");
	}

	m_ptr[index] = value;
}


