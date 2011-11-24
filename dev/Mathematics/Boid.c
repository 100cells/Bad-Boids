#include "Boid.h"

// Boid operations
void copyBoid(const Boid *boidSource, Boid *boidDestination)
{	
	memmove(boidDestination, boidSource, sizeof(Boid)); 
};


// single boid initialization
void initBoid(const Vector *p, const Vector *v, const Vector *a, double speed, double acceleration, double mForce, double bMass, long int id, Boid *boid)
{
	copyVector(p, &(boid->currentPosition));
	copyVector(p, &(boid->nextPosition));
	copyVector(v, &(boid->currentVelocity));
	copyVector(v, &(boid->nextVelocity));
	copyVector(a, &(boid->acceleration));

	boid->id = id;
	boid->maxSpeed = speed;
	boid->maxAcceleration = acceleration;
	// for future implementation
	boid->maxForce = acceleration;
	boid->mass = bMass;
}


void printBoid(Boid *output)
{
	printf("id=%d \t maxSpeed=%f \t maxAcceleration=%f \t maxForce=%f \t mass=%f \n",output->id,output->maxSpeed,output->maxAcceleration,output->maxForce,output->mass);
	printVector("current position",&(output->currentPosition));
	printVector("current velocity",&(output->currentVelocity));
	printVector("current acceleration",&(output->acceleration));
	printVector("next position",&(output->nextPosition));
	printVector("next velocity",&(output->nextVelocity));
}

