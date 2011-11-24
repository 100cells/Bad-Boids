#define DLL
#include "Boids.h"

#ifdef __cplusplus
extern "C" {
#endif
// it will became the dll entry point

void boidSim(int numberOfDesires, RulesParameters *applyingRules, SimulationParameters simParams,InfoCache infoCache)
{
	simulationInit(&simParams,applyingRules,&infoCache,numberOfDesires);
	update();

	/*
		- retrive parameter from input (rules weight, rules parameter, rules priority ecc ecc)
		- call simulation with parameters
		- simulation updates the "simulation progress" 
		- at the end release the resources
	*/
}

	
int getProgression() { return simulationProgress; }

void stopSim(){ abortSimulation=TRUE; }

void loadParticles(ParticlesParameters *pariclesList, int nParticles)
{
	int i;
	Vector nullVector;
	initVector(&nullVector);
	boidSet=(Boid *)malloc(sizeof(Boid)*nParticles);
	for (i=0;i<nParticles;i++)
		initBoid(&(pariclesList[i].position),&(pariclesList[i].velocity),&nullVector,pariclesList[i].maxSpeed,pariclesList[i].maxAcceleration,pariclesList[i].maxForce,pariclesList[i].mass,i+1,&boidSet[i]);
}


void DLL_EXPORT loadLeader(Vector *leaderPosition, int nFrame)
{
	int i;
	Vector nullVector;
	initVector(&nullVector);
	leader=(Boid *)malloc(sizeof(Boid)*nFrame);
	for (i=0;i<nFrame;i++)
		initBoid(&(leader[i].currentPosition),&nullVector,&nullVector,0,0,0,0,-1,&leader[i]);

}


#ifdef __cplusplus
}
#endif



