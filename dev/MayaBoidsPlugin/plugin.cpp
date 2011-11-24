// Copyright (C) 100cells
// File: myCmdCmd.cpp
// MEL Command: myCmd
// Author: 100cells

// Maya includes
#include <maya/MFnPlugin.h>

// Plugin includes
#include "simCmd.h"
#include "boidsBrain.h"


MStatus initializePlugin( MObject obj )
{

	MStatus status;

	MFnPlugin plugin( obj, "100cells", "1.0", "Any" );
	plugin.registerCommand( "simulateBoids", simulateBoids::creator /*, simulateBoids::newSyntax*/ );
	
	// register boids locator node
	status = plugin.registerNode(boidsBrain::typeName, boidsBrain::typeId, &boidsBrain::creator, &boidsBrain::initialize);	  
	if (!status) {
			status.perror("registerNode");
			return status;
	}

	// register ui
    status = plugin.registerUI("boidsCreateUI", "boidsDeleteUI");
    if (!status) {
        status.perror("registerUIScripts");
        return status;
    }	
	return status;
}

MStatus uninitializePlugin( MObject obj )
{
	MStatus status;

	MFnPlugin plugin( obj );

	plugin.deregisterCommand( "simulateBoids" );
	status = plugin.deregisterNode( boidsBrain::typeId );
	
	if (!status) {
			status.perror("deregisterNode");
			return status;
	}
	return status;
}