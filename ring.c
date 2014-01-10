#include "ring.h"

void ring_init()
{
	nbObjectsIn = 0;
	nbMATERIAL = 0;
	nbPRODUCT = 0;
	nbFINISH = 0;
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
		usleep(1000);
	printf("OBJ : %d\n"
					"\tMATERIAL : %d\n"
					"\tPRODUCT  : %d\n"
					"\tFINISH   : %d\n",nbObjectsIn,nbMATERIAL,nbPRODUCT,nbFINISH);
		int i;
		for(i=0; i < NBCASE; i++)
		{
			if(tourne[i] != NULL)
				printf("%d\n",tourne[i]->type);
		}
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
	int i;
	object_t *t;
	
	pthread_mutex_lock(&mutex_tourne);
	
	t = tourne[0];
	for(i=0;i < NBCASE;i++)
		tourne[i] = tourne[i+1];
	tourne[NBCASE-1] = t;

	pthread_mutex_unlock(&mutex_tourne);
}

object_t* ring_lookObject(int n, typeObject o)
{
	pthread_mutex_lock(&mutex_tourne);
	if(tourne[n] != NULL && tourne[n]->type == o)
	{
		object_t* obj = tourne[n];
		return obj;
	}
	else
	{
		pthread_mutex_unlock(&mutex_tourne);
		return NULL;
	}
}

object_t* ring_getObject(int n)
{
	if(tourne[n] != NULL)
	{
		object_t* obj = tourne[n];
		tourne[n] = NULL;
		nbObjectsIn--;
		
		switch(obj->etat)
		{
			case MATERIAL:
				nbMATERIAL--;
				break;
			case PRODUCT:
				nbPRODUCT--;
				break;
			case FINISH:
				nbFINISH--;
				break;
		}
		pthread_mutex_unlock(&mutex_tourne);
		return obj;
	}
	else
	{
		pthread_mutex_unlock(&mutex_tourne);
		return NULL;
	}
}

object_t* ring_putObject(int n, object_t* obj)
{
	pthread_mutex_lock(&mutex_tourne);
	if(tourne[n] == NULL && nbObjectsIn < NBCASE && nbMATERIAL < 9 && obj->etat == MATERIAL)
	{
		tourne[n] = obj;
		nbObjectsIn++;
		nbMATERIAL++;
		pthread_mutex_unlock(&mutex_tourne);
		return obj;
	}
	else if(tourne[n] == NULL && nbObjectsIn < NBCASE && nbPRODUCT < 5 && obj->etat == PRODUCT)
	{
		tourne[n] = obj;
		nbObjectsIn++;
		nbPRODUCT++;
		pthread_mutex_unlock(&mutex_tourne);
		return obj;
	}
	else if(tourne[n] == NULL && nbObjectsIn < NBCASE && nbFINISH < 1 && obj->etat == FINISH)
	{
		tourne[n] = obj;
		nbObjectsIn++;
		nbFINISH++;
		pthread_mutex_unlock(&mutex_tourne);
		return obj;
	}
	else
	{
		pthread_mutex_unlock(&mutex_tourne);
		return NULL;
	}
	pthread_mutex_unlock(&mutex_tourne);
	return NULL;
}

object_t* ring_lookFinish(int n)
{
	pthread_mutex_lock(&mutex_tourne);
	if(tourne[n] != NULL)
	{
		object_t* obj = tourne[n];
		if(obj->etat == FINISH)
		{
			tourne[n] = NULL;
			nbObjectsIn--;
			nbFINISH--;
			pthread_mutex_unlock(&mutex_tourne);
			return obj;
		}
		else
		{
			pthread_mutex_unlock(&mutex_tourne);
			return NULL;
		}
	}
	else
	{
		pthread_mutex_unlock(&mutex_tourne);
		return NULL;
	}
}
