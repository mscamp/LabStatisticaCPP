/* Si svolga l’esercizio precedente utlizzando l’allocazione dinamica della memoria per creare l’oggetto di tipo TH1F, senza dimenticare di pulire la memoria con l’istruzione delete prima del termine del programma. */

#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"

int main(int argc, char ** argv) {

	TH1F * h_ptr = new TH1F("hist", "titolo", 5, -7.5, 7.5); // Pointer all'istogramma
	TApplication app("app", &argc, argv); // TApplication
	TCanvas canvas; // Canvas

	// Si riempie l'istogramma
	h_ptr -> Fill(2.0);
	h_ptr -> Fill(-7.3);
	h_ptr -> Fill(-6.9);
	h_ptr -> Fill(3.5);
	h_ptr -> Fill(6.8);	

	// Styling 
	h_ptr -> GetXaxis() -> SetTitle("Asse x");
	h_ptr -> GetYaxis() -> SetTitle("Asse y");
	h_ptr -> SetFillColor(kViolet);
	h_ptr -> SetLineColor(kBlack);

	// Disegna istogramma e avvia la TApplication 
    h_ptr -> Draw();
    canvas.Print("es2.png", "png"); 
	app.Run();	

	delete h_ptr; // Deallocazione memoria
	return 0;
}
