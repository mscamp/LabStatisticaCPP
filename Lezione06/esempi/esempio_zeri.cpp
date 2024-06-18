#include <iostream>
#include <cmath>

double funzione(double x)
{
	return x;
}

double bisezione (
  double g(double),
  double xMin,
  double xMax,
  double precision = 0.0000000000000000000001
)
{
  double xAve = xMin ;
  while ((xMax - xMin) > precision)
    {
      xAve = 0.5 * (xMax + xMin) ;
      if (g(xAve) * g(xMin) > 0.) 
      {
	      xMin = xAve;
      }
      else               
      {
	      xMax = xAve;
      }
    }
  return xAve ;
}  

int main(int argc, char ** argv)
{

	double x_0 = -1;
	double x_1 = 1;
	
	double zero = bisezione(funzione, x_0, x_1);

	std::cout << "Zero della funzione tra " << x_0 << " e " << x_1 << ": " << zero << std::endl;
		


	return 0;
}
