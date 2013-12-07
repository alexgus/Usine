#include "tourniquet.h"

void init_tourniquet()
{
	pthread_create(&th_tourne, NULL, &tourneMain, NULL);
	pthread_mutex_init(&mutex_tourne, NULL);
}

void* tourneMain()
{
	while(1)
	{
		if(nbObjectsIn > 0)
		{
			rotate();
			sleep(TIME_WAIT);
		}
		else
			printf("Pas d'objet dans le tourniquet");
	}
}

void rotate()
{
	pthread_mutex_lock(&mutex_tourne);
	printf("Tourniquet : Rotation démarée");
	sleep(TIME_TOURNE);
	printf("Tourniquet : Rotation finis");
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
