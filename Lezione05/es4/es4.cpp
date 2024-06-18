/* Si implementi una classe templata dal nome DynamicArray che inizialmente non contenga alcun elemento ed abbia un metodo push_back() che permetta di aggiungere un elemento in fondo all’array degli elementi già esistenti.
* Si progetti un meccanismo che rimpiazzi l’array che contiene gli elementi quando è pieno, sostituendolo con uno più capiente.
* Si aggiunga un metodo che permetta anche di svuotare l’oggetto di tipo DynamicArray.
*/

#include <iostream>
#include "DynamicArray.h"
#include "funzioniutili.h"

int main(int argc, char ** argv)
{
    DynamicArray<float> array("rand_range"); // Array di dimensione 5

    // Array vuoto 
    array.print();

    // Aggiunge 10 elementi all'array
    for(int i = 0; i < 10; ++i)
    {
        array.push_back(rand_range(0, 1));
    }

    // Stampa a schermo il contenuto dell'array
    array.print();

    // Stampa a schermo l'elemento 5
    std::cout << "Elemento 5: " << array[5] << std::endl;
    std::cout << "Elemento 5: " << array.elemento(5) << std::endl;
    std::cout << std::endl;


    // Reset (array vuoto)
    array.reset();
    array.print();

    return 0;
}
