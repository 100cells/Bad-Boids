#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Utilities.h"
#include "../MayaBoids/Boolean.h"


/*
*********************************************
*     "Vector" struct definition            *
*********************************************
*/

// Vector struct definition
typedef struct
{
    double x;
    double y;
    double z;
} Vector;

// Vector operations
void initVector(Vector *v);
// copia un vettore
void copyVector(const Vector *inputVector, Vector *outputVector);
// somma tra vettori
void addVector(Vector *v1,Vector *v2,Vector *v1plusv2);
// differenza tra vettori
void subVector(Vector *v1,Vector *v2,Vector *v1minusv2);
// moltiplicazione tra vettori
void multiply(Vector *vettore, double m,Vector *outputVector);
// calcolo del modulo del vettore
double magnitude(const Vector *v);
// normalizzazione del vettore
void normalize(Vector *v);




/*
*********************************************
*           standard declaration            *
*********************************************
*/

double dotProduct(const Vector *v1,const Vector *v2);
double angleBetween(const Vector *v1, const Vector *v2);
BOOL isNotEqual(const Vector *v1,const Vector *v2);
BOOL isEqual(const Vector *v1,const Vector *v2);
double length(const Vector*v);
void randomVector(Vector *v, double xR, double yR, double zR);
void crossProduct(const Vector *v1,const Vector *v2, Vector *outputVector);
void direction(const Vector *v, Vector *oVector);
void copyMagnitude(const Vector *inputVector, Vector *outputVector);
void setMagnitude(Vector *v, double magnitude);
void setDirection(Vector *v);
void copyDirection(const Vector *inputVector, Vector *outputVector);
void limitation(Vector *inputVector, double limit);
void printVector(char * name,Vector *output);
#endif // VECTOR_H_INCLUDED
