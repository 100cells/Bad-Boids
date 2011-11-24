#include <stdio.h>
#include "../MayaBoids/RulesSetup.h"
#include "../MayaBoids/Definition.h"
#include "../MayaBoids/Boids.h"

void main()
{

	InfoCache infoCache;
	SimulationParameters simParams;
	RulesParameters *applyingRules;
	double *progressBar=NULL;
	double aov=pi/3;
	int i,numberOfDesires=3;	

	// parametri della simulazione
	simParams.fps=25;
	simParams.lenght=10;
	simParams.numberOfBoids=50;
	simParams.maxAcceleration=0.1;
	simParams.maxVelocity=4;
	simParams.simplifiedLocomotion=TRUE;


	applyingRules=(RulesParameters *)malloc(numberOfDesires*sizeof(RulesParameters));
	
	for(i=0;i<numberOfDesires;i++)
	{
		applyingRules[i].enabled=TRUE;
		applyingRules[i].precedence=9-i;
		applyingRules[i].ruleWeight=1;
		applyingRules[i].aov=aov;
		applyingRules[i].visibilityOption=FALSE;
	}

	applyingRules[COHESIONRULE].ruleName=COHESIONRULE;
	applyingRules[COHESIONRULE].ruleRadius=10;
	applyingRules[COHESIONRULE].ruleFactor=1;

	applyingRules[ALIGNMENTRULE].ruleName=ALIGNMENTRULE;
	applyingRules[ALIGNMENTRULE].ruleRadius=7;
	applyingRules[ALIGNMENTRULE].ruleFactor=1;

	applyingRules[SEPARATIONRULE].ruleName=SEPARATIONRULE;
	applyingRules[SEPARATIONRULE].ruleRadius=5;
	applyingRules[SEPARATIONRULE].ruleFactor=1;

	/*applyingRules[FOLLOWRULE].ruleName=FOLLOWRULE;
	applyingRules[FOLLOWRULE].ruleRadius=1;
	applyingRules[FOLLOWRULE].ruleFactor=1;*/
	
	
	

	infoCache.cacheFormat=ONEFILE;
	infoCache.start=0;
	infoCache.end=infoCache.start + (long )simParams.lenght;
	infoCache.fileName="d:\\temp\\BdirectCacheSimulationFile";
	infoCache.fps=25;
	infoCache.loging=FALSE;
	infoCache.option=POSITIONVELOCITY;
	infoCache.particleSysName="BoidsNParticles";
	infoCache.saveMethod=MAYANCACHE;

	boidSim(numberOfDesires, applyingRules, simParams,infoCache);
	getchar();
}