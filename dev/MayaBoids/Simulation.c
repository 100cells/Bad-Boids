#include "Simulation.h"


// functions declaration
void compute();
void updateBoids();
void sortingRules();

void boidInitialization(Boid *boid, int id,double width, double depth, double high,Vector * startingV,Vector * startingA);
void cachingData(Channel* channels);
void freeChannel(Channel* channels);
void leaderInit(double radius);

/********************************************/
void simulationInit(SimulationParameters *simParams, RulesParameters *applyingRules,InfoCache *cache, int numberOfDesires)
{
	int j;
	unsigned long i;
	Vector acc,vel;
		
	firstTime=TRUE;
	abortSimulation=FALSE;
	nDesires=numberOfDesires;
	dt=1/(double)(simParams->fps);
	simulationProgress = 0;
	leader=NULL;

	memcpy(&cacheFileOption,cache,sizeof(InfoCache));
	rParameters=(RulesParameters**)malloc(nDesires*sizeof(RulesParameters*));
	
	for(j=0;j<nDesires;j++)
	{
		rParameters[j]=(RulesParameters*)malloc(sizeof(RulesParameters));
		memcpy(rParameters[j],&applyingRules[j],sizeof(RulesParameters));
	}

	memcpy(&simParameters,simParams,sizeof(SimulationParameters));
	actions=(Action*)malloc(sizeof(Action)*nDesires);
	boidSet=(Boid *)malloc(sizeof(Boid)*simParameters.numberOfBoids);	
	

	if((nDesires>3) && (applyingRules[FOLLOWRULE].enabled))
	{
		leader=(Boid*)malloc(sizeof(Boid)*(unsigned)(simParameters.fps*simParameters.lenght));
		leaderInit(20);
	}
	
	randomVector(&acc, simParams->maxAcceleration, 0, 0);
	randomVector(&vel, simParams->maxVelocity, 0, 0);
	
	k3=kd_create(3);
	for(i=0; i<simParameters.numberOfBoids; i++)
	{
		boidInitialization(&boidSet[i],i+1, 20, 10, 5, &vel, &acc);
		kd_insert3(k3,boidSet[i].currentPosition.x, boidSet[i].currentPosition.y, boidSet[i].currentPosition.z, &boidSet[i]);
		
	}

	initDesires(leader);
	//sortingRules();
}

// update simulation
void  update()
{
	unsigned int simulationLenght,progress;
	
	progress=0;
	simulationLenght=(unsigned int)ceil(simParameters.fps * simParameters.lenght);

	_Output(&cacheFileOption);
	
	while((!abortSimulation) && (progress<=simulationLenght))
	{
		Channel *channels;
		channels=(Channel*)malloc(sizeof(Channel)*info.option);

		// compute Boids' new positions, velocities, accelerations 
		compute();

		// data management
		cachingData(channels);

		// write data
		writeData(progress,channels);

		// update Boids properties and kdtree 
		updateBoids();

		// update the index job progress 
		simulationProgress = ((int)(100*progress)/simulationLenght);

		//advance to the next frame
		progress++;

		// free channels memory
		freeChannel(channels);
	}

	simulationProgress=100;
	
	closeMethod();
	if(abortSimulation)
	{
		printf("Simulation interrupted\n");
		deleteData();
	}
	// restoring abortSimulation flag
	abortSimulation=FALSE;

	// free resources
	free(boidSet);	
	kd_free(k3);
}

/********************************************/
/********************************************/
void sortingRules()
{
	// sorting from smallest "precedence" value to the bigest one
	int i,j;
	Action temp;

	for(i=0;i<nDesires;i++)
	{
		for (j=0;j<nDesires;j++)
		{
			if(rParameters[i]->precedence<rParameters[j]->precedence)
			{
				memcpy(&temp,actions[i],sizeof(Action));			
				memcpy(actions[i],actions[j],sizeof(Action));
				memcpy(actions[j],&temp,sizeof(Action));
			}
		}
	}
}

void boidInitialization(Boid *boid, int id,double width, double depth, double high,Vector * startingV,Vector * startingA)
{
	double mass, force;
	Vector position, vVelocity, vAcceleration;

	//Vector offsetAcceleration;
	//double accelerationOffset, velocityOffset;

	////vettore accelerazione iniziale (valore base uguale x tutti + leggero offset)
	//initVector(&vAcceleration);
	//accelerationOffset = simParameters.maxAcceleration/100;
	//randomVector(&offsetAcceleration, accelerationOffset, accelerationOffset, accelerationOffset);
	//addVector(&offsetAcceleration,startingA,&vAcceleration);


	////vettore velocità iniziale (valore base uguale x tutti + leggero offset)
	//initVector(&vVelocity);
	//velocityOffset = simParameters.maxVelocity/100;
	//randomVector(&offsetVelocity, velocityOffset, velocityOffset, velocityOffset);
	//addVector(&offsetVelocity,startingV,&vVelocity);

	mass=1;
	force=0.1;

	initVector(&vAcceleration);
	initVector(&vVelocity);

    // vettore posizione
    randomVector(&position, width, depth, high);

    initBoid(&position, &vVelocity, &vAcceleration, simParameters.maxVelocity, simParameters.maxAcceleration, force, mass, id, boid);
}

void compute()
{
	Vector *desiresVector;
	Vector decisionVector;
	unsigned long  i=0;
	desiresVector=(Vector *)malloc(sizeof(Vector)*nDesires);

	for (i=0;i<simParameters.numberOfBoids;i++)
	{	

		// execute "Desires" 
		desiresComputation(k3, &(boidSet[i]),NULL, desiresVector);

		// execute "Decision"
		decisionComputation(desiresVector, &(boidSet[i]), &decisionVector);

		// execute "Locomotion"
		if(simParameters.simplifiedLocomotion)
			locomotionComputationSimplified(&decisionVector, &(boidSet[i]), dt);
		else
			locomotionComputation(&decisionVector, &(boidSet[i]), dt);
		
		// execute "SimFinalization"
		// ending the procedure
	}
	free(desiresVector);
}

void updateBoids()
{
	unsigned long j;
	kd_clear(k3);
	for( j=0;j<simParameters.numberOfBoids;j++)
	{
		copyVector(&(boidSet[j].nextPosition), &(boidSet[j].currentPosition));
		copyVector(&(boidSet[j].nextVelocity), &(boidSet[j].currentVelocity));
		
		// kdtree update
		kd_insert3(k3,boidSet[j].currentPosition.x, boidSet[j].currentPosition.y, boidSet[j].currentPosition.z, &boidSet[j]);
	}
}



void cachingData(Channel *channels)
{
	int i;
	unsigned long j,totalNumberOfBoids;
	
	totalNumberOfBoids = simParameters.numberOfBoids;
	
	count = (double)totalNumberOfBoids;
	id = (double*)malloc(sizeof(double)*totalNumberOfBoids);
	position = (float*)malloc(3*sizeof(float)*totalNumberOfBoids);
	velocity = (float*)malloc(3*sizeof(float)*totalNumberOfBoids);
	birthtime = (double*)calloc(totalNumberOfBoids, sizeof(double));
	lifespanPP = (double*)calloc(totalNumberOfBoids, sizeof(double));
	finalLifespanPP = (double*)calloc(totalNumberOfBoids, sizeof(double));

	for(i=0;i<POSITIONVELOCITY;i++)
	{
		channels[i].name=cName.names[i];
		channels[i].attribute=aName.names[i];

		if(i==_COUNT)
			channels[i].numberOfElements = 1;
		else
			channels[i].numberOfElements = totalNumberOfBoids;

		switch(i)
		{
			case _COUNT:
			case _ID:
			case _BIRTHTIME:
			case _LIFESPANPP:
			case _FINALLIFESPANPP:
				channels[i].type = DBLA;
				break;
			default:
				channels[i].type = FVCA;
				break;
		};
	}

	for(j=0;j<simParameters.numberOfBoids;j++)
	{
		// id
		id[j] = boidSet[j].id;

		// position
		position[3*j]=(float)(boidSet[j].currentPosition.x);
		position[3*j+1]=(float)(boidSet[j].currentPosition.y);
		position[3*j+2]=(float)(boidSet[j].currentPosition.z);

		// velocity
		velocity[3*j]=(float)(boidSet[j].currentVelocity.x);
		velocity[3*j+1]=(float)(boidSet[j].currentVelocity.y);
		velocity[3*j+2]=(float)(boidSet[j].currentVelocity.z);
	}

	channels[_COUNT].elements = &count;
	channels[_ID].elements = id;
	channels[_VELOCITY].elements = velocity;
	channels[_POSITION].elements = position;
	channels[_BIRTHTIME].elements = birthtime;
	channels[_LIFESPANPP].elements = lifespanPP;
	channels[_FINALLIFESPANPP].elements = finalLifespanPP;
}

void freeChannel(Channel* channels)
{
	// free memory
		if(id!=NULL)
			free(id);
		if(position!=NULL)
			free(position);
		if(velocity!=NULL)
			free(velocity);
		if(birthtime!=NULL)
			free(birthtime);
		if(lifespanPP!=NULL)
			free(lifespanPP);
		if(finalLifespanPP!=NULL)
			free(finalLifespanPP);
		if(channels!=NULL)
			free(channels);
}

void leaderInit(double radius)
{
	double delta,angle, stair,up;
	int j,totalLength;
	totalLength=(int)ceil(simParameters.fps*simParameters.lenght);
	up=10/totalLength;

	stair=0;
	angle=0;
	delta=(double)(360.0/totalLength);

	leader=(Boid *)malloc((unsigned int)ceil(simParameters.fps * simParameters.lenght)* sizeof(Boid));

	for(j=0;j<totalLength;j++)
	{
		leader[j].id=-1;
		leader[j].mass=1;
		leader[j].maxForce=1;
		leader[j].maxAcceleration=1;
		leader[j].maxSpeed=1;
		leader[j].currentPosition.x = radius*sin(3.14*angle/180.0);
		leader[j].currentPosition.y = radius*cos(3.14*angle/180.0);
		leader[j].currentPosition.z = stair;
		angle+=delta;
		stair+=up;
	}
}