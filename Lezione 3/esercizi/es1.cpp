/* Si crei un istogramma monodimensionale di tipo TH1F e lo si riempia con 5 valori compresi nel suo intervallo di definizione.
 * Si salvi l’immagine dell’istogramma in un file di tipo png utilizzando un oggetto di tipo TCanvas ed il suo metodo TCanvas::Print
 * Si visualizzi l’istogramma interattivamente utilizzando un oggetto di tipo TApplication */

#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"

int main(int argc, char ** argv)
{
	TH1F hist("hist", "titolo", 5, -7.5, 7.5); // Istogramma
	TApplication app("app", &argc, argv); // Oggetto TApplication
	TCanvas canvas; // Canvas

	// Si riempie l'istogramma
	hist.Fill(2.0);
	hist.Fill(-7.3);
	hist.Fill(-6.9);
	hist.Fill(3.5);
	hist.Fill(6.8);	

	// Styling
	hist.GetXaxis() -> SetTitle("Asse x");
	hist.GetYaxis() -> SetTitle("Asse y");
	hist.SetFillColor(kOrange + 1);
	hist.SetLineColor(kBlack);
	
	// Disegna istogramma e avvia la TApplication
    hist.Draw();
    canvas.Print("es1.png", "png"); 
	app.Run();

	return 0;
}
