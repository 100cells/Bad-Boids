#include "Decisions.h"


void decisionComputation(Vector *desiresVector,Boid *currentBoid, Vector *decisionVector)
{	
	int i;
	initVector(decisionVector);
	for(i=0;i<nDesires;i++)
	{
		multiply(&(desiresVector[i]), rParameters[i]->ruleWeight ,&(desiresVector[i]));
		addVector(&(desiresVector[i]),decisionVector,decisionVector);
	}
	// acceleration's limit
	limitation(decisionVector,currentBoid->maxAcceleration);
}
