#include "tourniquet.h"

void init_tourniquet()
{
	pthread_create(th_tourne, NULL, &tounreMain, NULL);
}

void tourneMain()
{
	while(1) // TODO while there products
		;
}
