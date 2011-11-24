// management of simulation's steps and output 

#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include "Decisions.h"
#include "Desires.h"
#include "Locomotion.h"
#include "Definition.h"
#include "Output.h"

SimulationParameters simParameters;
int simulationProgress;
double dt;
Boid *boidSet;
Boid *leader;
Kdtree * k3;
BOOL firstTime;
BOOL abortSimulation;
InfoCache cacheFileOption;

float *position,*velocity;
double *id, *birthtime,*lifespanPP,*finalLifespanPP;
double count;

void simulationInit(SimulationParameters *simParams, RulesParameters *applyingRules,InfoCache *cache, int numberOfDesires);

// call "Desires" "Decision" Locomotion" "SimFinalization" procedures
void update();



#endif

