/* ES2) Utilizzando il programma main_03.cpp, si generi un file dati_2.txt contenente 10,000 eventi distribuiti secondo una distribuzione di probabilità modello. 

ES3) Si scriva un programma che effettui il fit degli eventi salvati nel file dati_2.txt con il metodo della massima verosimiglianza e con il metodo dei minimi quadrati e si confronti il risultato delle due tecniche, comparando i valori studiati nell’esercizio 12.1 per i parametri e per la bontà del fit.
*/

#include <iostream>
#include <fstream>
#include "funzioniutili.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"

int main(int argc, char ** argv)
{
    // Definzione variabili
    double input_value = 0.0; // Variabile temporanea
    int n_bin = 0; // Numero di bin
    double xmin = 0.0; // Estremo inferiore dell'istogramma
    double xmax = 0.0; // Estremo superiore dell'istogramma
    std::vector<double> eventi; // Vettore degli eventi
    std::ifstream file_dati; // Oggetto ifstream

    // Definizione oggetti ROOT 
    TApplication app("app", &argc, argv);
    TCanvas canvas;

    // Parametri del modello
    double p0 = 0.0; // Normalizzazione modello (numero di eventi)
    double p1 = 0.0; // Media
    double p2 = 0.0; // Deviazione standard

    // Lettura del file di testo e riempimento del vettore con gli eventi
    file_dati.open("dati_2.txt", std::ios::in);

    while(true)
    {
        file_dati >> input_value;

        if(file_dati.eof() == true)
        {
            break;
        }

        eventi.push_back(input_value);
    }

    file_dati.close(); // Chiusura del file

    // Definizione istogramma
    xmin = floor(minimoVec(eventi));
    xmax = ceil(massimoVec(eventi));
    n_bin = round(sqrt(eventi.size()));
    n_bin = massimoTra(n_bin, 10.0);
    TH1F hist("hist", "Fit della distribuzione normale", n_bin, xmin, xmax);

    // Riempimento istogramma
    for(int i = 0; i < eventi.size(); ++i)
    {
        hist.Fill(eventi.at(i));
    }

    // Impostazione ragionevole dei parametri
    p0 = eventi.size(); // Fattore di normalizzazione
    p1 = 0.5 * (xmax - xmin); // Media
    p2 = hist.GetRMS(); // Deviazione standard

    // Definizione TF1
    TF1 * modello = new TF1("modello", "gaus(0)", xmin, xmax);

    // Impostazione dei parametri del modello
    modello -> SetParameter(0, p0);
    modello -> SetParameter(1, p1);
    modello -> SetParameter(2, p2);

    // Fit con metodo dei minimi quadrati
    TFitResultPtr fit_result_LS = hist.Fit("modello", "S+");
    hist.GetFunction("modello") -> SetLineColor(kRed);
    hist.GetFunction("modello") -> SetLineWidth(3);
    
    // Stampa a schermo il risultato del fit e i parametri determinati
    std::cout << std::endl << std::endl;
    std::cout << "--- LEAST SQUARES ---" << std::endl;
    std::cout << "Status del fit: " << fit_result_LS -> Status() << std::endl;
    std::cout << "Parametro p0 (integrale): " << modello -> GetParameter(0) << " +/- " << modello -> GetParError(0) << std::endl;
    std::cout << "Parametro p1 (media): " << modello -> GetParameter(1) << " +/- " << modello -> GetParError(1) << std::endl;
    std::cout << "Parametro p2 (deviazione standard): " << modello -> GetParameter(2) << " +/- " << modello -> GetParError(2) << std::endl;

    // Test di bontà del fit
    std::cout << std::endl;
    std::cout << "Integrale di Chi2: " << fit_result_LS -> Prob() << std::endl;
    std::cout << "Numero di gradi di libertà: " << fit_result_LS -> Ndf() << std::endl;
    std::cout << std::endl << std::endl;

    // Fit con metodo della ML
    TFitResultPtr fit_result_ML = hist.Fit("modello", "SL+");
    hist.GetFunction("modello") -> SetLineColor(kBlue);
    hist.GetFunction("modello") -> SetLineWidth(3);

    // Stampa a schermo il risultato del fit e i parametri determinati
    std::cout << std::endl << std::endl;
    std::cout << "--- MAXIMUM LIKELIHOOD ---" << std::endl;
    std::cout << "Status del fit: " << fit_result_ML -> Status() << std::endl;
    std::cout << "Parametro p0 (integrale): " << modello -> GetParameter(0) << " +/- " << modello -> GetParError(0) << std::endl;
    std::cout << "Parametro p1 (media): " << modello -> GetParameter(1) << " +/- " << modello->GetParError(1) << std::endl;
    std::cout << "Parametro p2 (deviazione standard): " << modello -> GetParameter(2) << " +/- " << modello -> GetParError(2) << std::endl;

    // Test di bontà del fit
    std::cout << std::endl;
    std::cout << "Integrale di Chi2: " << fit_result_ML -> Prob() << std::endl;
    std::cout << "Numero di gradi di libertà: " << fit_result_ML -> Ndf() << std::endl;

    // Styling 
    hist.SetFillColor(kOrange + 1);
    hist.SetLineColor(kBlack);

    // Rappresentazione del risultato del fit
    hist.Draw();
    app.Run();

    delete modello; // Deallocazione memoria

    return 0;
}