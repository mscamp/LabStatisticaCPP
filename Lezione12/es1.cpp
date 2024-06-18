/* Si scriva un programma che effettui il fit degli eventi salvati nel file dati.txt, utilizzando gli algoritmi di ROOT ed il modello descritto nella Lezione.
* Si abbia cura di determinare l’intervallo di definizione ed il binning dell’istogramma utilizzato per il fit a partire dagli eventi medesimi, scrivendo algoritmi appropriati che determinino il minimo ed il massimo fra i dati ed una stima ragionevole del numero di bin da utilizzare.
* Si determinino i valori iniziali dei parametri del fit con le tecniche descritte a lezione
* Si stampi a schermo il risultato del fit, includendo un test di bontà del fit.
* Si disegni l’istogramma con il modello fittato sovrapposto.
*/

#include <iostream>
#include <fstream>
#include "funzioniutili.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"

int main(int argc, char ** argv)
{
	// Definizione variabili e oggetti
	double input_value = 0.0; // Variabile temporanea
	double xmin = 0.0; // Estremo inferiore dei dati
	double xmax = 0.0; // Estremo superiore dei dati
	int N_bin = 0; // Numero di bin
	double half_eventi = 0.0; // Metà degli eventi
	std::vector<double> eventi;
	std::ifstream file_dati; // Oggetto ifstream

	// Definizione oggetti ROOT
	TApplication app("app", &argc, argv);
	TCanvas canvas;

	// Parametri del modello
	double p0 = 0.0; // Normalizzazione fondo
	double p1 = 0.0; // Pendenza del fondo
	double p2 = 0.0; // Eventi di segnale
	double p3 = 0.0; // Media del segnale
	double p4 = 0.0; // Deviazione standard del segnale

	// Lettura del file con il set di dati
	file_dati.open("dati.txt", std::ifstream::in);

	// Salva i dati letti dal file nel vector
	while(true)
	{
		file_dati >> input_value;

		if(file_dati.eof() == true)
		{
			break;
		}

		eventi.push_back(input_value);
	}

	file_dati.close(); // Chiusura file

	// Definizione istogramma
	half_eventi = eventi.size() / 2.;
	xmin = floor(minimoVec(eventi));
	xmax = ceil(massimoVec(eventi));
	N_bin = round(sqrt(half_eventi));
	TH1F hist("hist", "Sovrapposizione di Gauss e Exp", N_bin, xmin, xmax);

	// Riempimento istogramma
	for(int i = 0; i < eventi.size(); ++i)
	{
		hist.Fill(eventi.at(i));
	}

	// Impostazione ragionevole dei parametri del modello 
	p0 = log(half_eventi); // Eventi di fondo (normalizzazione fondo)
	p1 = -0.5; // Pendenza del fondo
	p2 = half_eventi; // Eventi di segnale (normalizzazione segnale)
	p3 = 0.5 * (xmax - xmin); // Media del segnale	
	p4 = hist.GetRMS(); // Deviazione standard del segnale

	// Definizione delle TF1
	TF1 segnale("segnale", "gaus(0)", xmin, xmax);
	TF1 fondo("fondo", "expo(0)", xmin, xmax);
	TF1 modello("modello", "gaus(2) + expo(0)", xmin, xmax);

	// Setting dei parametri iniziale per fondo e segnale
	fondo.SetParameter(0, p0);
	fondo.SetParameter(1, p1);
	segnale.SetParameter(0, p2);
	segnale.SetParameter(1, p3);
	segnale.SetParameter(2, p4);
	
	// Fit parziale sul fondo
	hist.Fit("fondo", "Q", "", 0., 4.);
	
	// Fit parziale sul segnale
	hist.Fit("segnale", "Q", "", 7., 14.);

	// Fit del modello (metodo dei minimi quadrati) 
	modello.SetParameter(0, fondo.GetParameter(0));
	modello.SetParameter(1, fondo.GetParameter(1));
	modello.SetParameter(2, segnale.GetParameter(0));
	modello.SetParameter(3, segnale.GetParameter(1));
	modello.SetParameter(4, segnale.GetParameter(2));
	
	TFitResultPtr fit_result = hist.Fit("modello", "S");

	// Stampa a schermo il risultato del fit e i parametri determinati
	std::cout << std::endl << std::endl;
	std::cout << "Status del fit: " << fit_result->Status() << std::endl;
	std::cout << "Parametro p0 (eventi di fondo): " << exp(modello.GetParameter(0)) << " +/- " << exp(modello.GetParameter(0)) * modello.GetParError(0) << std::endl;
	std::cout << "Parametro p1 (pendenza del fondo): " << modello.GetParameter(1) << " +/- " << modello.GetParError(1) << std::endl;
	std::cout << "Parametro p2 (eventi di segnale): " << modello.GetParameter(2) << " +/- " << modello.GetParError(2) << std::endl;
	std::cout << "Parametro p3 (media del segnale): " << modello.GetParameter(3) << " +/- " << modello.GetParError(3) << std::endl;
	std::cout << "Parametro p4 (deviazione standard del segnale): " << modello.GetParameter(4) << " +/- " << modello.GetParError(4) << std::endl;

	// Test di bontà del fit
	std::cout << std::endl;
	std::cout << "Integrale di Chi2: " << fit_result->Prob() << std::endl;
	std::cout << "Valore di Q2: " << fit_result->Chi2() << std::endl;
	std::cout << "Numero di gradi di libertà: " << fit_result->Ndf() << std::endl;

	// Styling 
	hist.GetFunction("modello") -> SetLineColor(kRed);
	hist.GetFunction("modello") -> SetLineWidth(4);
	hist.SetFillColor(kOrange + 1);

	// Disegna il grafico fittato
	hist.Draw();
	canvas.Update();
	app.Run();
	
	return 0;
}

