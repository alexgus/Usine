#include "tapis.h"

void tapis_init()
{
	etat_tapis = 0;
	pthread_mutex_init(&etat_mutex, NULL);
	pthread_create(&th_tapis,NULL,&tapisMain,NULL);
}

void *tapisMain()
{
	while(etat_tapis != 2)
	{
		switch(etat_tapis)
		{
			case 0:
				printf("Tapis : Not in work !\n");
				break;
			case 1:
				printf("Tapis : In work !\n");
				break;
		}
	sleep(1);
	}
	return 0;
}

void tapis_stop()
{
	pthread_mutex_lock(&etat_mutex);
	etat_tapis = 0;
	pthread_mutex_unlock(&etat_mutex);
}

void tapis_start()
{
	pthread_mutex_lock(&etat_mutex);
	etat_tapis = 1;
	pthread_mutex_unlock(&etat_mutex);
}

void tapis_finish()
{
	pthread_mutex_lock(&etat_mutex);
	etat_tapis = 2;
	pthread_mutex_unlock(&etat_mutex);
}
