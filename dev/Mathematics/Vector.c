#include "Vector.h"

/*
*********************************************
*           inline declaration              *
*********************************************
*/
// inizializza a 0 un vettore
void initVector(Vector *v){ memset(v, 0, sizeof(Vector)); };
void copyVector(const Vector *inputVector, Vector *outputVector){ memmove(outputVector, inputVector, sizeof(Vector)); };
void subVector(Vector *v1, Vector *v2, Vector *v1minusv2)
{
	v1minusv2->x = v1->x - v2->x;
	v1minusv2->y = v1->y - v2->y;
	v1minusv2->z = v1->z - v2->z;
}
void addVector(Vector *v1, Vector *v2, Vector *v1plusv2)
{
	v1plusv2->x = v1->x + v2->x;
	v1plusv2->y = v1->y + v2->y;
	v1plusv2->z = v1->z + v2->z;
}
double magnitude(const Vector *v)
{
	double value = v->x * v->x + v->y * v->y + v->z * v->z;
	return sqrt(value);
}
void multiply(Vector *vettore, double m, Vector *outputVector)
{
	outputVector->x = vettore->x * m;
	outputVector->y = vettore->y * m;
	outputVector->z = vettore->z * m;
}
void normalize(Vector *v)
{
	double mag = magnitude(v);
	if (mag==0)
		return;
	multiply(v, 1/mag, v);
}






void crossProduct(const Vector *v1, const Vector *v2, Vector *outputVector)
{
        outputVector->x = v1->y * v2->z - v1->z * v2->y;
        outputVector->y = v1->z * v2->x - v1->x * v2->z;
        outputVector->z = v1->x * v2->y - v1->y * v2->x;
}

double dotProduct(const Vector *v1, const Vector *v2){ return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z ); }

double length(const Vector *v){ return magnitude(v); }

void direction(const Vector *v, Vector *oVector)
{
    copyVector(v, oVector);
    normalize(oVector);
}

double angleBetween(const Vector *v1, const Vector *v2)
{
    double p1 = dotProduct(v1, v2);
    double p2 = magnitude(v1) * magnitude(v2);
    double p3 = acos(p1/p2);
    return p3;
}

BOOL isNotEqual(const Vector *v1, const Vector *v2){ return(v1->x != v2->x || v1->y != v2->y || v1->z != v2->z); }

BOOL isEqual(const Vector *v1, const Vector *v2){ return(v1->x == v2->x && v1->y == v2->y && v1->z == v2->z); }

void setMagnitude(Vector *v, double magnitude)
{
    normalize(v);
    multiply(v, magnitude, v);
}

void setDirection(Vector *v)
{
    double m = magnitude(v);
    Vector *d = v;
    normalize(d);
    multiply(d, m, d);
    copyVector(d, v);
}

void copyDirection(const Vector *inputVector, Vector *outputVector)
{
    double m = magnitude(outputVector);
    Vector copyV;
    copyVector(inputVector, &copyV);
    normalize(&copyV);
    multiply(&copyV, m, outputVector);
}

void copyMagnitude(const Vector *inputVector, Vector *outputVector)
{
    double mag = magnitude(inputVector);
    setMagnitude(outputVector, mag);
}

void randomVector(Vector *v, double xR, double yR, double zR)
{
    v->x = drandom(xR);
    v->y = drandom(yR);
    v->z = drandom(zR);
}


void limitation(Vector *inputVector, double limit)
{
	if(magnitude(inputVector)>limit)
	{
		normalize(inputVector);
		multiply(inputVector,limit,inputVector);
	}
}

void printVector(char * name,Vector *output)
{
	printf("%s=[%f][%f][%f]\n",name,output->x,output->y,output->z);
}




