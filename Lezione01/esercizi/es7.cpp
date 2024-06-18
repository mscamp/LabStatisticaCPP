/* Scrivere una funzione creaArray() che prenda in input un numero intero, crei un array di tipo float lungo quando il numero intero di input e restituisca il puntatore al primo elemento dell’array. */

float * creaArray(int dim)
{
	float * arr = new float[dim];
	return arr;
}

int main(int argc, char ** argv)
{
	int N = 5;
	float * array = creaArray(N);	
	delete[] array;

	return 0;
}
