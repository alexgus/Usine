#include "tourniquet.h"

void init_tourniquet()
{
	nbObjectsIn = 0;
	state_tourne = 1;
	pthread_create(&th_tourne, NULL, &tourneMain, NULL);
	pthread_mutex_init(&mutex_tourne, NULL);
}

void* tourneMain()
{
	while(state_tourne)
	{
		if(nbObjectsIn > 0)
		{
			rotate();
			sleep(TIME_WAIT);
		}
		else
		{
			printf("Pas d'objet dans le tourniquet\n");
			sleep(1);
		}
	}
	return NULL;
}

void stop_tourne()
{
	pthread_mutex_lock(&mutex_tourne);
	state_tourne = 0;
	pthread_mutex_unlock(&mutex_tourne);
}

void rotate()
{
	pthread_mutex_lock(&mutex_tourne);
	printf("Tourniquet : Rotation démarée\n");
	usleep(TIME_TOURNE);
	printf("Tourniquet : Rotation finis\n");
	pthread_mutex_unlock(&mutex_tourne);
}

object_t* getObject(int n)
{
	pthread_mutex_lock(&mutex_tourne);
	object_t* obj = tourne[n];
	tourne[n] = NULL;
	nbObjectsIn--;
	pthread_mutex_unlock(&mutex_tourne);
	return obj;
}

void putObject(int n, object_t* obj)
{
	if(tourne[n] == NULL)
	{
		pthread_mutex_lock(&mutex_tourne);
		tourne[n] = obj;
		nbObjectsIn++;
		pthread_mutex_unlock(&mutex_tourne);
	}
}
