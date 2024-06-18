/* Si crei una std::string riempita con un periodo scelto a piacere.
* Si contino il numero di parole ed il numero di lettere (spazi esclusi) che compongono il periodo.
* Si divida la stringa in singole parole, ciascuna salvata con una stringa all’interno di un std::vector.
*/

#include <iostream>
#include <vector>
#include <string>

int letterCount(std::string s)
{
    int counter = 0;
    char c;

    for(int i = 0; i < s.length(); ++i)
    {   
        c = s[i];

        if(c != ' ' && c != ',' && c != '.' && c != ';' && c != '!' && c != '?' && c != ':' && c != '"' && c != '\'')
        {
            ++counter;
        }
    }

    return counter;
}

int wordCount(std::string s)
{
    int counter = 0;
    char c;

    for(int i = 0; i <= s.length(); ++i)
    {
        c = s[i];

        if(c == ' ' || c == '\0')
        {
            ++counter;
        }
    }

    return counter;
}

void split(std::string s, std::vector<std::string> * v)
{
    char c;
    std::string tmp;
    std::string tmptmp;

    for(int i = 0; i <= s.length(); ++i)
    {
        c = s[i];

        if(c != ' ' && c != '\0')
        {
            tmp += c;
        }

        else  
        {
            for(int j = 0; j < tmp.length(); ++j)
            {
                c = tmp[j];

                if(c != ',' && c != '.' && c != ';' && c != '!' && c != '?' && c != ':' && c != '"')
                {
                    tmptmp += c;
                }
            }

            v->push_back(tmptmp);
            tmp = "";
            tmptmp = "";
        }       
    }
}

int main(int argc, char ** argv)
{
    // Definizione variabili e oggetti
    std::string periodo = "Sono and,ato al mercato ?a fare la spesa. Dopo vuoi venire con me al bow,,l!!ing??,";
    int n_lettere = letterCount(periodo);
    int n_parole = wordCount(periodo);

    std::vector<std::string> * parole = new std::vector<std::string>[n_parole];

    // Stampa il numero di lettere nel periodo
    std::cout << "Numero di lettere: " << n_lettere << std::endl;

    // Salva le parole in un vector e stampa a schermo
    split(periodo, parole);

    std::cout << "Numero di parole: " << n_parole << std::endl << std::endl;
    
    for(int i = 0; i < n_parole; ++i)
    {
        std::cout << "Parola " << i << ": " << parole->at(i) << std::endl;
    }

    // Parola 3
    std::cout << std::endl;
    std::cout << parole->at(3) << std::endl;

    delete[] parole; 
    return 0;
}