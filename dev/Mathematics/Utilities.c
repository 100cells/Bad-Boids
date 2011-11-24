#include "Utilities.h"

// restituisce un valore (double) compreso tra "-max/2" e "max/2"
double drandom(double max)
{
	double value;
	//srand(time(NULL));
	value = max*rand();
	value /= (RAND_MAX+1);
	value -= max/2;
	//srand(1);
	return value;
}