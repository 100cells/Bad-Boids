// management of simulation's functions call
// DLL entry point (main function)
// can receive boids initialization as input 
#ifndef BOIDS_H_INCLUDED
#define BOIDS_H_INCLUDED

#include "RulesSetup.h"
#include "Simulation.h"
#include <stdio.h>


#ifdef DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C" {
#endif
	/*
	int numberOfDesires, number of rules to use for computing the simulation 
	Rules applyingRules, rules' list (e.g. Cohesion, Alignment and so on ) with their parameters . List's lenght= numberOfDesires
	double *progressBarProgress, pointer to a double variable. Storing the simulation progress (%)
	*/
	void DLL_EXPORT boidSim(int numberOfDesires, RulesParameters *applyingRules, SimulationParameters simParams,InfoCache infoCache);
	
	int DLL_EXPORT getProgression();

	void DLL_EXPORT stopSim();

	void DLL_EXPORT loadParticles(ParticlesParameters *pariclesList, int nParticles);

	void DLL_EXPORT loadLeader(Vector *leaderPosition, int nFrame);

#ifdef __cplusplus
}
#endif


#endif // BOIDS_H_INCLUDED


