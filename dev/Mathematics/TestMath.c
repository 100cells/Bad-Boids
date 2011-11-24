#include "Vector.h"

void main()
{
	Vector v1;

	v1.x=10;
	v1.y=20;
	v1.z=2;
	printf("v1=[%f][%f][%f]\n",v1.x,v1.y,v1.z);
	addVector(&v1,&v1,&v1);
	limitation(&v1,5);
	printf("limit v1 a 5 v1=[%f][%f][%f]\n ",v1.x,v1.y,v1.z);
	getchar();

}