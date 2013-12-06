#include "tapis.h"

void tapis_init()
{
	pthread_create(&th_tapis,NULL,&life,NULL);
}

void *life()
{
	while(etat_tapis != 2)
	{
		switch(etat_tapis)
		{
			case 0:
				printf("Tapis : Not in work !");
				break;
			case 1:
				printf("Tapis : In work !");
				break;
		}
	}
}

void tapis_stop()
{
	// TODO to protect with mutex
	etat_tapis = 0;
}

void tapis_start()
{
	etat_tapis = 1;
}

void tapis_finish()
{
	etat_tapis = 2;
}
