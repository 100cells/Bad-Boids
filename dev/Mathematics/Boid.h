#ifndef BOID_H_INCLUDED
#define BOID_H_INCLUDED

#include "Vector.h"

// Boid struct definition
typedef struct boid
{
    long int id;
    Vector currentPosition;
    Vector currentVelocity;
    Vector acceleration;
    Vector nextPosition;
    Vector nextVelocity;

    double maxSpeed;
    double maxAcceleration;
	double wanderTheta;

    // for future implementation
    double maxForce;
    double mass;
	double boundingBoxRadius;
}Boid;


// Boid duplication "boidSource" nel bod destinazione "boidDestination"
void copyBoid(const Boid *boidSource,Boid *boidDestination);

// Boid initialization
void initBoid(const Vector *p, const Vector *v, const Vector *a, double speed, double acceleration, double mForce, double bMass, long int id, Boid *boid);

void printBoid(Boid *output);

#endif // BOID_H_INCLUDED