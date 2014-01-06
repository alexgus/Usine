#include "robot.h"

/**
 * Nb of existing robots
 */
int nbRobot = 0;


int robot_init(int place)
{
	if(nbRobot < NB_ROBOT)
	{
		int id = nbRobot;

		tabRobot[id].id = id;
		tabRobot[id].place = place;
		tabRobot[id].stock = 0;
		tabRobot[id].state = 1; // Marche
		tabRobot[id].idMsg = com_init();

		pthread_mutex_init(&tabRobot[id].mutex, NULL);
		pthread_create(&tabRobot[id].th,NULL,&robot_main,(int)id);

		nbRobot++;

		return id;
	}
	return -1;
}

void robot_stop(int id)
{
	if(id < NB_ROBOT)
	{
		pthread_mutex_lock(&tabRobot[id].mutex);
		tabRobot[id].state = 0;
		pthread_mutex_unlock(&tabRobot[id].mutex);

		pthread_join(tabRobot[id].th,NULL);
	}
}

void robot_start(int id)
{
	if(id < NB_ROBOT)
	{
		pthread_mutex_lock(&tabRobot[id].mutex);
		tabRobot[id].state = 1;
		pthread_mutex_unlock(&tabRobot[id].mutex);
	}
}

void robot_breakdown(int id)
{
	if(id < NB_ROBOT)
	{
		pthread_mutex_lock(&tabRobot[id].mutex);
		tabRobot[id].state = 2;
		pthread_mutex_unlock(&tabRobot[id].mutex);
	}
}

void robot_degradeMode(int id)
{
	if(id < NB_ROBOT)
	{
		pthread_mutex_lock(&tabRobot[id].mutex);
		tabRobot[id].state = 3;
		pthread_mutex_unlock(&tabRobot[id].mutex);
	}
}

void *robot_main(int id)
{
	robot_t r = tabRobot[id];
	while(tabRobot[id].state)
	{
		switch(r.state)
		{
			case 1:
				printf("Robot %d en marche\n", r.id);
				robot_waitOp(r);
				break;
			case 2:
				printf("Robot %d en panne\n", r.id);
				break;
			case 3:
				printf("Robot %d en mode dégradé\n", r.id);
				break;
			default:
				printf("Robot %d : Illegal State\n", r.id);
		}
	}
	return NULL;
}

int robot_waitOp(robot_t r)
{
	com* t = com_lire(r.idMsg);
	
	printf("--> %d\n",t->data->qte);

/*
	switch(t->data.order)
	{
		case GET:
			while(ring_lookObject(r.place)->type != t->data.obj)
				; // TODO Suppr attente active avec semaphore
			r.tabObj[r.stock] = ring_getObject(r.place);
			r.stock++;
			break;
		case OP:
			robot_op(r.id,t->data);
			break;
		case LAST_OP:
			robot_op(r.id,t->data);
			// obj.etat = FINISH
			break;
	}*/

	// return ack finish. ready for next operation

	return 0;
}

void robot_op(int idR, tcom op)
{
	printf("Robot %d : Effectue l'operation %d sur l'objet : %d\n",idR,op.operation, op.obj);
	// switch obj type
	// return obj
}
