/* Utilizzare new e delete per creare e distruggere una variabile double ed un array di double. */

int main(int argc, char ** argv)
{
	// Crea una variabile double
	double * num = new double(7.9);
	delete num; // Deallocazione memoria

	// Crea un array double
	double * arr = new double[5];
	delete[] arr; // Deallocazione memoria

	return 0;
}
