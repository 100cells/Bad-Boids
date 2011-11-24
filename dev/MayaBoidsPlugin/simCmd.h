#include "macros.h"
#include <maya/MPxCommand.h>
#include <maya/MSyntax.h>
#include <maya/MGlobal.h>
#include <maya/MSelectionList.h>
#include <maya/MItSelectionList.h>
//#include <maya/MDagPath.h>
#include <maya/MObject.h>
//#include <maya/MFnDagNode.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MPlug.h>
//#include <maya/MDataHandle.h>
#include <maya/MIOStream.h>
#include <maya/MString.h>

#include <maya/MTimerMessage.h>

// pbar
#include <maya/MProgressWindow.h>

// maya thread
#include <winbase.h>
#include <maya/MThreadPool.h>

#define PROGRESSBARADVANCEVALUE 1
#define PROGRESSBARMAXVALUE 100
#define PROGRESSBARMINVALUE 0
#define PROGRESSBARSLEEPTIME 1000
class simulateBoids : public MPxCommand
{
	public:
		/*simulateBoids();
		virtual	~simulateBoids();*/
		static	void * creator();
		bool isUndoable() const;
		// static MSyntax newSyntax();
		MStatus doIt( const MArgList& args );

	private:
		static void cbfProgressBar(float elapsedTime, float lastTime, void * clientData);
		static MCallbackId idcb;
		static bool firstTime;
};