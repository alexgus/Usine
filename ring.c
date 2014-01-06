#include "ring.h"

void ring_init()
{
	nbObjectsIn = 0;
	state_tourne = 1;
	pthread_create(&th_tourne, NULL, &ring_main, NULL);
	pthread_mutex_init(&mutex_tourne, NULL);
}

void* ring_main()
{
	while(state_tourne)
	{
		if(nbObjectsIn > 0)
			ring_spin();
		else
			printf("Pas d'objet dans le tourniquet\n");
		usleep(TIME_WAIT);
	}
	return NULL;
}

void ring_stop()
{
	pthread_mutex_lock(&mutex_tourne);
	state_tourne = 0;
	pthread_mutex_unlock(&mutex_tourne);
}

void ring_spin()
{
	int i = 0;
	object_t *t;
	
	pthread_mutex_lock(&mutex_tourne);
	printf("Ring : Rotation\n");

	t = tourne[0];
	while(i < NBCASE)
		tourne[i] = tourne[i+1];
	tourne[NBCASE-1] = t;

	pthread_mutex_unlock(&mutex_tourne);
}

object_t* ring_lookObject(int n)
{
	pthread_mutex_lock(&mutex_tourne);
	object_t* obj = tourne[n];
	pthread_mutex_unlock(&mutex_tourne);
	return obj;
}


object_t* ring_getObject(int n)
{
	pthread_mutex_lock(&mutex_tourne);
	object_t* obj = tourne[n];
	tourne[n] = NULL;
	nbObjectsIn--;
	pthread_mutex_unlock(&mutex_tourne);
	return obj;
}

void ring_putObject(int n, object_t* obj)
{
	if(tourne[n] == NULL)
	{
		pthread_mutex_lock(&mutex_tourne);
		tourne[n] = obj;
		nbObjectsIn++;
		pthread_mutex_unlock(&mutex_tourne);
	}
}
