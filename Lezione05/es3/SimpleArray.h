#ifndef simplearray_h
#define simplearray_h

#include <iostream>

template <typename T>
class SimpleArray 
{
	public:
		// Template del costruttore
		SimpleArray(int N):
			N_m(N)
		{
			pointer_m = new T[N_m];
		}

		// Template del copy constructor
		SimpleArray(const SimpleArray & copy):
			N_m(copy.N_m)
		{
			pointer_m = new T[N_m];
	
		   	for(int i = 0; i < N_m; ++i)
		    {
		   		pointer_m[i] = copy.pointer_m[i];
		   	}
		}

		// Distruttore
		~SimpleArray()
		{
		    delete[] pointer_m;
		}

		// Template ricerca elemento 
		T elemento(int i) const
		{
		    if(i > N_m || i < 0)
		    {
		    	std::cout << "L'indice eccede la dimensione del vettore, oppure è negativo, quindi ritorno il primo elemento." << std::endl;        	
		        return pointer_m[0];
		 	} 
    
		    else
		 	{
		    	return pointer_m[i];
			}
		}

		void modificaElemento(int i, T value)
		{
 		   if(i > N_m || i < 0)
 		   {
 			   	std::cout << "L'indice eccede la dimensione del vettore, oppure è negativo, quindi ritorno il primo elemento." << std::endl;        	
 			} 
    
 		   else
 			{
 		       pointer_m[i] = value;
			}
		}

		T operator[](int i) const
		{
		    return this->elemento(i);
		}

		private:
			// Membri
			int N_m;
 	 		T * pointer_m;
};

#endif
