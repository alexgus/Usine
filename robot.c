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
		tabRobot[id].idMsg = com_init(id);

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
	while(r.state)
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
	int i = 0;
	object_t *o;
	tcom* t = com_getOrger(r.idMsg);

	switch(t->order)
	{
		case GET:
			while(i < t->qte)
			{
				o = ring_lookObject(r.place, t->obj);
				while(o == NULL || (o != NULL && o->type != t->obj))
					o = ring_lookObject(r.place,t->obj);	
					// TODO Suppr attente active avec semaphore

				r.tabObj[r.stock] = ring_getObject(r.place);
				r.stock++;

				i++;
			}
			break;
		case OP:
			robot_op(r.id,t);
			break;
		case LAST_OP:
			robot_op(r.id,t);
			// obj.etat = FINISH
			break;
	}

	// return ack finish. ready for next operation

	return 0;
}

object_t *robot_op(int idR, tcom *op)
{
	printf("Robot %d : Effectue l'operation %d sur l'objet : %d\n",idR,op->operation, op->obj);
	switch(op->obj)
	{
		case C1:
			printf("Coucou\n");
			break;
		case C2:
			break;
		case C3:
			break;
		case C4:
			break;
		case P1:
			break;
		case P2:
			break;
		case P3:
			break;
		case P4:
			break;
	}
	return NULL;
}
