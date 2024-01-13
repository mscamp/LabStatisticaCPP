#ifndef dynamicarray_h
#define dynamicarray_h

#include <iostream>
#include <string>

template <typename T>
class DynamicArray
{
    public:
        // Template del costruttore
        DynamicArray(std::string name):
            initial_size_m(0),
            size_m(0),
            last_index_m(0),
            nome_array_m(name)
        {
            array_m = new T[size_m];
        }

        // Template del distruttore
        ~DynamicArray()
        {
            delete[] array_m;
        }

        // Accedere all'elemento i-esimo
        T elemento(int i) const
		{
		    if(i > last_index_m || i < 0)
		    {
		    	std::cout << "L'indice eccede la dimensione del vettore, oppure è negativo, quindi ritorno il primo elemento." << std::endl;        	
		        return array_m[0];
		 	} 
    
		    else
		 	{
		    	return array_m[i];
			}
		}

        // Override di []
        T operator[](int index)
        {
            return this -> elemento(index);
        }

        void print()
        {
            if(size_m > 0)
            {
                std::cout << "--- Contenuto dell'array " << nome_array_m << " ---" << std::endl;

                for(int i = 0; i < last_index_m; ++i)
                {
                    std::cout << "Elemento " << i << ": " << array_m[i] << std::endl;
                }

                std::cout << std::endl;
            }
            
            else
            {
                std::cout << "L'array non ha elementi. Riempilo con push_back()." << std::endl;
                std::cout << std::endl;
            }
        }

        // PUSH BACK
        void push_back(T element)
        {
            if(last_index_m >= size_m)
            {
                ++size_m;
                T * tmp = new T[size_m];

                for(int i = 0; i < last_index_m; ++i)
                {
                    tmp[i] = array_m[i];
                }

                delete[] array_m;
                array_m = tmp;
            }

            array_m[last_index_m] = element;
            ++last_index_m;
        }

        // RESET
        void reset()
        {
            size_m = initial_size_m;
            delete[] array_m;
            T * tmp = new T[initial_size_m];
            array_m = tmp;
        }

    private:
        int initial_size_m; // Dimensione iniziale array
        int size_m; // Dimensione array
        T * array_m; // Puntatore all'array dinamico
        int last_index_m; // Ultimo indice
        std::string nome_array_m; // Nome array
};

#endif