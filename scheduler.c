#include "scheduler.h"

void scheduler_init()
{
	etat_tapis = 0;
	pthread_mutex_init(&etat_mutex, NULL);
	pthread_create(&th_tapis,NULL,&scheduler_main,NULL);
}

void *scheduler_main()
{
	while(etat_tapis != 2)
	{
		switch(etat_tapis)
		{
			case 0:
				printf("scheduler : Not in work !\n");
				break;
			case 1:
				printf("scheduler : In work !\n");
				break;
		}
	sleep(1);
	}
	return 0;
}

void scheduler_stop()
{
	pthread_mutex_lock(&etat_mutex);
	etat_tapis = 0;
	pthread_mutex_unlock(&etat_mutex);
}

void scheduler_start()
{
	pthread_mutex_lock(&etat_mutex);
	etat_tapis = 1;
	pthread_mutex_unlock(&etat_mutex);
}

void scheduler_finish()
{
	pthread_mutex_lock(&etat_mutex);
	etat_tapis = 2;
	pthread_mutex_unlock(&etat_mutex);
}
