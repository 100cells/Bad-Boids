#include "boidsBrain.h"

// attributes' declaration
// simulation params
declareAttr(simulationLength)	// [int] in seconds
declareAttr(framesPerSecond)	// [int]
declareAttr(startFrame)		// [int]

declareAttr(particleSystem)		// [mess]
declareAttr(boidsNumber)		// [int]
// export params
declareAttr(logFilePath)		// [char *]
declareAttr(logFileName)		// [char *]
declareAttr(logFileType)		// [double] 0 = txt log file; 1 = XML
// desire params
declareRuleAttributes(alignment)
declareRuleAttributes(cohesion)
declareRuleAttributes(separation)
declareRuleAttributes(follow)
/*
declareAttr(distance)			// [double] max dependency distance for boids (boids at greater distances are ignored)
declareAttr(repulsionFactor)	// [double]
declareAttr(cohesionFactor)		// [double]
declareAttr(separationFactor)	// [double]
declareAttr(approachFactor)		// [double]
*/
// locomotion params
declareAttr(locomotionMode)
declareAttr(maxSpeed)			// [double]
declareAttr(maxForce)	// [double]
// declareAttr(mass)			// [double] unused by now

// attributes defaults macros

#define BDZ_SIMLEN			10
#define BDZ_FPS				24
#define BDZ_STF				1
#define BDZ_NUM				30

#define BDZ_LOGNAME			""
#define BDZ_LOGTYPE			0

#define BDZ_DIST			7
#define BDZ_REPULSION		1.5
#define BDZ_COHESION		0.2
#define BDZ_SEPARATION		0.09
#define BDZ_APPROACH		0

#define BDZ_LOCMODE			1
#define BDZ_MAXSPEED		5
#define BDZ_MAXACCEL		2

// #define BDZ_MASS			1

/*
boidsBrain::boidsBrain()
{
	// simulation params
	simulationLengthValue = BDZ_SIMLEN;		// [int] in seconds
	framesPerSecondValue = BDZ_FPS;			// [int]
	boidsNumberValue = BDZ_NUM;				// [int]
	// export params
	logFileNameValue = BDZ_LOGNAME;			// [char *]
	logFileTypeValue = BDZ_LOGTYPE;			// [double] 0 = txt log file; 1 = XML; 2 = nCache
	// boids params
	distanceValue = BDZ_DIST;				// [double] max dependency distance for boids (boids at greater distances are ignored)
	repulsionFactorValue = BDZ_REPULSION;	// [double]
	cohesionFactorValue = BDZ_COHESION;		// [double]
	separationFactorValue = BDZ_SEPARATION;	// [double]
	approachFactorValue = BDZ_APPROACH;		// [double]
	maxSpeedValue = BDZ_MAXSPEED;			// [double]
	maxForceValue = BDZ_MAXACCEL;	// [double]
}
boidsBrain::~boidsBrain(){}
*/

void boidsBrain::postConstructor()
{
	MFnDependencyNode nodeFn(thisMObject());
	nodeFn.setName("boidsBrainShape#");
}

void * boidsBrain::creator(){ return new boidsBrain(); }

MStatus boidsBrain::initialize()
{
	MStatus status;
	
	MFnNumericAttribute		nAttr;
	MFnTypedAttribute		tAttr;
	MFnEnumAttribute		eAttr;
	MFnMessageAttribute		mAttr;
	// MFnUnitAttribute		uAttr;

	// MString				attrOpt;
	
	printf("initializing Boidz Locator node\n");
	MGlobal:: displayInfo("initializing Boidz Locator node");

	nodeCreateAttrNum(simulationLength, sl, kInt, BDZ_SIMLEN );
	nodeCreateAttrNum(framesPerSecond, fps, kInt, BDZ_FPS );
	nodeCreateAttrNum(startFrame, stf, kInt, BDZ_STF );
	particleSystem = mAttr.create("particleSystem", "ps");
	nodeAddAttribute(particleSystem);
	nodeCreateAttrNum(boidsNumber, bn, kInt, BDZ_NUM );
	
	nodeCreateAttrTyp(logFilePath, lp);
	nodeCreateAttrTyp(logFileName, ln);
	// inputSurface = tAttr.create( "inputSurface", "is",MFnData::kNurbsSurface,&stat );
	// nodeCreateAttrTyped(logFileName, ln, BDZ_LOGNAME);
	logFileType = eAttr.create("logFileType", "lt", BDZ_LOGTYPE);
	eAttr.addField("nCache file", 0);
	eAttr.addField("log file", 1);
	eAttr.addField("XML file", 2);
	// eAttr.setStorable(true);
	// nodeCreateAttrNum(logFileType, lt, kDouble, BDZ_LOGTYPE);
	nodeAddAttribute(logFileType);
	
	nodeCreateRuleAttributes(alignment, a)
	nodeCreateRuleAttributes(cohesion, c)
	nodeCreateRuleAttributes(separation, s)
	nodeCreateRuleAttributes(follow, f)
	/*
	nodeCreateAttrNum(distance, d, kDouble, BDZ_DIST)
	nodeCreateAttrNum(repulsionFactor, rf, kDouble, BDZ_REPULSION)
	nodeCreateAttrNum(cohesionFactor, cf, kDouble, BDZ_COHESION)
	nodeCreateAttrNum(separationFactor, sf, kDouble, BDZ_SEPARATION)
	nodeCreateAttrNum(approachFactor, af, kDouble, BDZ_APPROACH)
	*/
	locomotionMode = eAttr.create("locomotionMode", "lm", BDZ_LOCMODE);
	eAttr.addField("physical", 0);
	eAttr.addField("simple", 1);
	nodeAddAttribute(locomotionMode);
	// nodeCreateAttrNum(locomotionMode, lm, kInt, BDZ_LOCMODE)
	nodeCreateAttrNum(maxSpeed, ms, kDouble, BDZ_MAXSPEED)
	nodeCreateAttrNum(maxForce, mf, kDouble, BDZ_MAXACCEL)
	// nodeCreateAttrNum(mass, mss, kDouble, BDZ_MASS)

	// check for error
	if( status != MS::kSuccess ) {
		status.perror("Unable to attach one or more attributes to the boidsBrain node");
		return status;
	}
	
	MGlobal:: displayInfo("boidsBrain node attributes applied");

	return MS::kSuccess;
}

const MString boidsBrain::typeName("boidsBrain");
const MTypeId boidsBrain::typeId(0x00112E01);