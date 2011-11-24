#include "macros.h"
#include <maya/MPxNode.h>
#include <maya/MTypeId.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnMessageAttribute.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MObject.h>
#include <maya/MGlobal.h>

class boidsBrain : public MPxNode
{
	public:

		static const MString typeName;
		static const MTypeId typeId;
		
		// simulation params
		static MObject simulationLength;	// [int] in seconds
		static MObject framesPerSecond;		// [int]
		static MObject startFrame;		// [int]

		static MObject particleSystem;		// [mess]
		static MObject boidsNumber;			// [int]
		// export params
		static MObject logFilePath;			// [char *]
		static MObject logFileName;			// [char *]
		static MObject logFileType;			// [double] 0 = txt log file; 1 = XML; 2 = nCache
		// desire params
		setRuleAttributes(alignment)
		setRuleAttributes(cohesion)
		setRuleAttributes(separation)
		setRuleAttributes(follow)

		// locomotion params
		static MObject locomotionMode;		// [bool]
		static MObject maxSpeed;			// [double]
		static MObject maxForce;		// [double]
		// static MObject mass;				// [double] unused by now

		// boidsBrain();
		// virtual ~boidsBrain();
		virtual void  postConstructor();
		
		static void * creator();
		static MStatus initialize();

		// virtual MStatus boidsBrain::compute( const MPlug& plug, MDataBlock& data );

	 //private:
};