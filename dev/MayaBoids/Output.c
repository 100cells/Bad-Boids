#include "Output.h"

//initialization, at the moment "output will drive DataSaving only
void _Output(InfoCache *cache)
{
	printf("Output initialization...\n");
	_DataSaving(cache);
}

void writeData(int frame,Channel *channels)
{
	_write(frame,channels);
}

void deleteData()
{
	_delete();
}

void closeData()
{
	_close();
}