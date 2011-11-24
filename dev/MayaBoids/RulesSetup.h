#ifndef _RULESETUP_H_
#define _RULESETUP_H_

#include "Boolean.h"
#include <kdtree.h>					// generic kdtree implementation
#include <Boid.h>		// Boid struct and operations

//#include "../KDTree/kdtree.h"			// generic kdtree implementation
//#include "../Mathematics/Boid.h"		// Boid struct and operations
//#include "../Mathematics/Vector.h"		// Vector struct and operations

#define PRECEDENCE int

#define VISIBILITY BOOL
#define VISIBILITYON TRUE
#define VISIBILITYOFF FALSE

#define RULE int
#define RULESAVAILABLE 3
#define COHESIONRULE 0
#define ALIGNMENTRULE 1
#define SEPARATIONRULE 2
#define FOLLOWRULE 3
#define WANDERRULE 4

static const char *rulesName[]={"cohesionRule","alignmentRule","separationRule","wanderRule","followRule"};

typedef struct kdtree Kdtree;
typedef struct kdres Kdres;

typedef void(* Action)(Kdres *, Boid *, Vector *);



typedef struct rulesParameters
{
	BOOL enabled;
	RULE ruleName;
	PRECEDENCE precedence;
	VISIBILITY visibilityOption;
	double aov;						//angle of view
	double ruleRadius;
	double ruleFactor;
	double ruleWeight;
}RulesParameters;


typedef struct simulationParameters
{
	int fps;
	double lenght;
	unsigned long int numberOfBoids;
	double maxVelocity;
	double maxAcceleration;
	BOOL simplifiedLocomotion;
}SimulationParameters;

typedef struct particlesParameters
{
	Vector position;
	Vector velocity;
	double mass;
	double maxSpeed;
	double maxAcceleration;
	double maxForce;

}ParticlesParameters;

Action *actions;
RulesParameters **rParameters;
int nDesires;


#endif