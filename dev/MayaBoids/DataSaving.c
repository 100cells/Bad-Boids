#include "DataSaving.h"

void _DataSaving(InfoCache *cache)
{
	printf("DataSaving initialization...\n");

	switch(cache->saveMethod)
	{
	case MAYANCACHE:
		initMethod = init;
		saveMethod = writeMayaNCacheBlock;
		writeHeaderMethod = writeMayaNCacheHeader;
		closeMethod = closeMayaNCacheFile;
		deleteMethod = deleteFile;
		printf("MayaNCache library loaded\n");
		break;
	case TEXTDATA:
		/*initMethod=setFileName;
		saveMethod=printSingleBoid;
		writeHeaderMethod=printHeader;
		deleteMethod = delete;
		closeMethod=closeFile;*/
		printf("TextData library loaded\n");
		break;
	case XMLDATA:
		/*initMethod=setFileName;
		saveMethod=printSingleBoid;
		writeHeaderMethod=printHeader;
		deleteMethod = delete;
		closeMethod=closeFile;*/
		printf("XmlData library loaded\n");
		break;
	default:
		break;
	};
	initMethod(cache->particleSysName,cache->fileName,cache->cacheFormat,cache->option,cache->fps,cache->start,cache->end);
	writeHeaderMethod();
}


void _write(int frame, Channel * channels)
{
	saveMethod(frame,channels);
}

void _delete()
{
	deleteMethod();
}

void _close()
{
	closeMethod();
}