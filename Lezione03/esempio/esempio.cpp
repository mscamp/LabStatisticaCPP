#include <iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"
using namespace std;

int main (int argc, char ** argv)
{
	TH1F istogramma("istogramma", "titolo", 10, -3., 3.);
	TApplication theApp ("theApp", &argc, argv);
	istogramma.Fill (2.2);
	istogramma.Fill (2.1);
	istogramma.Fill (-1.4);
	
	TCanvas cv;
	istogramma.Draw();
	cv.Print("esempio.png", "png");

	cout << "Numero di eventi: " << istogramma.GetEntries();
	cout << "Media: " << istogramma.GetMean();
	cout << "Deviazione std: " << istogramma.GetRMS();

	/*TH2F h2 ("h2", "eventi pseudo-casuali Gaussiani", 200, -1.5, 1.5, 200, -1.5, 1.5);
	h2.Fill (rand_TCL (-1., 1., 10), rand_TCL (-1., 1., 10));*/

	theApp.Run();

	return 0;
}
