#include "simCmd.h"

// DLL includes
#include "../MayaBoids/Boids.h"

// static attributes recall
MCallbackId simulateBoids::idcb;

typedef struct dllData
{
	int nD;
	RulesParameters *applyingRules;
	SimulationParameters *simParams;
	InfoCache *infoCache;
	int	*progressBarValue;
}DLLData;

// creating threads tasks
void ThreadsCreator(void *data, MThreadRootTask *root);

// threaded progress bar function
MThreadRetVal tProgressBar(void *data);

// threaded dll simulation
MThreadRetVal tBoidsDll(void *data);


void * simulateBoids::creator() { return new simulateBoids; }

bool simulateBoids::isUndoable() const {return false;}

/*
// TO DO
MSyntax simulateBoids::newSyntax()
{
	MSyntax syntax;
	// syntax.addFlag(kFlagDist, kFlagDistLong, MSyntax::kDouble);
	return syntax;
}
*/


MStatus simulateBoids::doIt( const MArgList& args )
{
	
	//	Description: implements the MEL boids command
	//	Arguments: args - the argument list that was passes to the command from MEL

	MStatus status = MS::kSuccess;

	
    /****************************************
	*	costruzione strutture di passaggio  *
	****************************************/

	InfoCache infoCache;
	SimulationParameters simParams;
	RulesParameters *applyingRules;
	double progressBar=0;
	double aov=pi/3;
	int i,numberOfDesires=4;

	// params retrievement
	MSelectionList sel;
	MObject node;
	MFnDependencyNode nodeFn;
	MPlug plug;

	// simulation params
	int simulationLengthValue;		// [int] in seconds
	int framesPerSecondValue;		// [int]
	int startFrameValue;			// [int]
	int boidsNumberValue;			// [int]
	// export params
	MString logFilePathValue;		// [char *]
	MString logFileNameValue;		// [char *]
	//char * logFilePathValue;		// [char *]
	//char * logFileNameValue;		// [char *]
	int logFileTypeValue;			// 0 = nCache; 1 = log file; 2 = XML; 
	// rules params
	setRuleVariables(alignment);
	setRuleVariables(cohesion);
	setRuleVariables(separation);
	setRuleVariables(follow);
	
	// locomotion params
	int locomotionModeValue;				// [int]
	double maxSpeedValue;			// [double]
	double maxForceValue;	// [double]
	// double mass=1;					// [double]

	MGlobal::getActiveSelectionList(sel);
	for ( MItSelectionList listIter(sel); !listIter.isDone(); listIter.next() )
	{
		listIter.getDependNode(node);
		nodeFn.setObject(node);
	}
	cout << nodeFn.name().asChar() << " is selected" << endl;
	
	// plug = nodeFn.findPlug("simulationLength");
	// plug.getValue(dblValue);
	getPlugValue(simulationLength);
	getPlugValue(framesPerSecond);
	getPlugValue(startFrame);
	getPlugValue(boidsNumber);
	getPlugValue(logFileType);
	getRulePlugValue(alignment);
	getRulePlugValue(cohesion);
	getRulePlugValue(separation);
	getRulePlugValue(follow);
	getPlugValue(locomotionMode);
	getPlugValue(maxSpeed);
	getPlugValue(maxForce);
	getTypePlugValue(logFilePath);
	getTypePlugValue(logFileName);

	MGlobal::displayInfo(logFilePathValue);

	simParams.fps=framesPerSecondValue;
	simParams.lenght=simulationLengthValue;
	simParams.numberOfBoids=boidsNumberValue;
	simParams.maxAcceleration=maxForceValue;
	simParams.maxVelocity=maxSpeedValue;
	simParams.simplifiedLocomotion=TRUE;

	applyingRules=(RulesParameters *)malloc(numberOfDesires*sizeof(RulesParameters));

	printf("Number of desires = %d\n",numberOfDesires);

	MString saveString;
	saveString = logFilePathValue+"/"+logFileNameValue;

	for(i=0;i<numberOfDesires;i++)
	{
		applyingRules[i].enabled=TRUE;
		applyingRules[i].precedence=1;
		applyingRules[i].aov=aov;
		applyingRules[i].visibilityOption=FALSE;
	}	

	if(cohesionActiveValue==0)
		applyingRules[COHESIONRULE].enabled=FALSE;
	else
	{
		applyingRules[COHESIONRULE].ruleName=COHESIONRULE;
		applyingRules[COHESIONRULE].ruleFactor=cohesionFactorValue;
		applyingRules[COHESIONRULE].ruleRadius=cohesionRadiusValue;
		applyingRules[COHESIONRULE].ruleWeight=cohesionWeightValue;
	}

	if(separationActiveValue==0)
		applyingRules[SEPARATIONRULE].enabled=FALSE;
	else
	{
		applyingRules[SEPARATIONRULE].ruleName=SEPARATIONRULE;
		applyingRules[SEPARATIONRULE].ruleFactor=separationFactorValue;
		applyingRules[SEPARATIONRULE].ruleRadius=separationRadiusValue;
		applyingRules[SEPARATIONRULE].ruleWeight=separationWeightValue;
	}

	if(alignmentActiveValue==0)
		applyingRules[ALIGNMENTRULE].enabled=FALSE;
	else
	{
		applyingRules[ALIGNMENTRULE].ruleName=ALIGNMENTRULE;
		applyingRules[ALIGNMENTRULE].ruleFactor=alignmentFactorValue;
		applyingRules[ALIGNMENTRULE].ruleRadius=alignmentRadiusValue;
		applyingRules[ALIGNMENTRULE].ruleWeight=alignmentWeightValue;
	}
	
	if(followActiveValue==0)
		applyingRules[FOLLOWRULE].enabled=FALSE;
	else
	{
		applyingRules[FOLLOWRULE].ruleName=FOLLOWRULE;
		applyingRules[FOLLOWRULE].ruleRadius=followRadiusValue;
		applyingRules[FOLLOWRULE].ruleFactor=followFactorValue;
		applyingRules[FOLLOWRULE].ruleWeight=followWeightValue;
	}
	

	infoCache.cacheFormat=ONEFILE;
	infoCache.fps=framesPerSecondValue;
	infoCache.start=startFrameValue/framesPerSecondValue;
	infoCache.end=simulationLengthValue+infoCache.start;	
	infoCache.loging=FALSE;
	infoCache.option=POSITIONVELOCITY;
	infoCache.particleSysName="BoidsNParticles";
	infoCache.saveMethod=MAYANCACHE;

	infoCache.fileName=(char*)malloc(sizeof(char)*(saveString.length()+1));
	for(unsigned int j=0;j<saveString.length()+1;j++)
		infoCache.fileName[j]=saveString.asChar()[j];

	DLLData data;
	data.nD=numberOfDesires;
	data.infoCache=&infoCache;
	data.simParams=&simParams;
	data.applyingRules=applyingRules;
	
	status = MThreadPool::init();
	
	
	if (status==MStatus::kSuccess)
	{
		MThreadPool::newParallelRegion(ThreadsCreator, &data);
		setResult( "Command executed!\n" );
		CHECK_MSTATUS(MProgressWindow::endProgress());
		MThreadPool::release();
	}
	
	free(infoCache.fileName);
	free(applyingRules);
	MThreadPool::release();
	

	return status;
}


void ThreadsCreator(void *data, MThreadRootTask *root)
{
	MThreadPool::createTask(tProgressBar, NULL, root);
	MThreadPool::createTask(tBoidsDll, data, root);
	MThreadPool::executeAndJoin(root);
}

MThreadRetVal tProgressBar(void *data)
{
	MStatus status=MS::kSuccess;
	//MString statusString;

	if(!MProgressWindow::reserve())
	{
		MGlobal::displayError("Progress window already in use");
		stopSim();
		return (MThreadRetVal)-1;
	}

	// Set up and print progress window state
	CHECK_MSTATUS(MProgressWindow::setProgressRange(PROGRESSBARMINVALUE, PROGRESSBARMAXVALUE));
	CHECK_MSTATUS(MProgressWindow::setTitle("Boids Progress"));
	CHECK_MSTATUS(MProgressWindow::setInterruptable(true));
	MProgressWindow::setProgressStatus("Simulation Progress");
	CHECK_MSTATUS(MProgressWindow::setProgress(PROGRESSBARMINVALUE));
	CHECK_MSTATUS(MProgressWindow::startProgress());

	while((MProgressWindow::progress()<PROGRESSBARMAXVALUE)&&(!MProgressWindow::isCancelled()))
	{	
		/*statusString ="Progress " + MProgressWindow::progress();	
		CHECK_MSTATUS(MProgressWindow::setProgressStatus(statusString));*/

		int prog=getProgression();
		int progV=MProgressWindow::progress();
		while(prog>=progV+PROGRESSBARADVANCEVALUE)
		{
			CHECK_MSTATUS(MProgressWindow::advanceProgress(PROGRESSBARADVANCEVALUE));	
			progV+=PROGRESSBARADVANCEVALUE;
		}
		if(progV>=PROGRESSBARMAXVALUE)
			CHECK_MSTATUS(MProgressWindow::setProgress(PROGRESSBARMAXVALUE));	
		
		Sleep(PROGRESSBARSLEEPTIME);
	}

	if (MProgressWindow::isCancelled()) 
	{
		//CHECK_MSTATUS(MProgressWindow::endProgress());
		MGlobal::displayInfo("Progress interrupted!");
		stopSim();
	}
	//else
		//CHECK_MSTATUS(MProgressWindow::endProgress());

	return (MThreadRetVal)0;
}

MThreadRetVal tBoidsDll(void *data)
{
	DLLData * app=(DLLData*)data;
	SimulationParameters sp;
	InfoCache iC;

	// BUILDING DLL'S PARAMETERS
	sp.fps=app->simParams->fps;
	sp.lenght=app->simParams->lenght;
	sp.maxAcceleration=app->simParams->maxAcceleration;
	sp.maxVelocity=app->simParams->maxVelocity;
	sp.numberOfBoids=app->simParams->numberOfBoids;
	sp.simplifiedLocomotion=app->simParams->simplifiedLocomotion;
	
	iC.cacheFormat=app->infoCache->cacheFormat;
	iC.fps=app->infoCache->fps;
	iC.start=app->infoCache->start;
	iC.end=app->infoCache->end;
	iC.loging=app->infoCache->loging;
	iC.option=app->infoCache->option;
	iC.saveMethod=app->infoCache->saveMethod;
	iC.fileName=app->infoCache->fileName;
	iC.particleSysName=app->infoCache->particleSysName;

	//starting simulation
	boidSim(app->nD, app->applyingRules, sp ,iC);
	return (MThreadRetVal)0;
}