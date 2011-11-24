// management of boids caching
#ifndef _DATASAVING_H_
#define _DATASAVING_H_

// mayancache dll project
#include "../MayaCache/MayaNCache.h"//<MayaNCache.h>	// mayancache file
//#include <XMLWriter.h>// mayancache xml file
#include <Boid.h>
#include "Definition.h"

//#include "TextDataFile.h"	// Example: saving data to txt data file format
//#include "XMLDataFile.h"	// Example: saving data to xml data file format 

void (*initMethod)(char *particleSysName,char *fileName, CACHEFORMAT cacheFormat, CACHEOPTION option, unsigned int fps, double start, double end);
void (*saveMethod)(int frame,  Channel *channels);
void (*writeHeaderMethod)();
void (*closeMethod)();
void (*deleteMethod)();

void _DataSaving(InfoCache *cache);
void _write(int frame, Channel * channels);
void _delete();
void _close();
#endif 