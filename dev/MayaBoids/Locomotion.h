// turning decision into movement
#ifndef _LOCOMOTION_H_
#define _LOCOMOTION_H_

#include "RulesSetup.h"

// input vector, output vector
void locomotionComputation(Vector *decisionVector,Boid *currentBoid, double dt);
void locomotionComputationSimplified(Vector *decisionVector,Boid *currentBoid, double dt);

#endif