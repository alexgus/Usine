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

		pthread_kill(tabRobot[id].th, SIGTERM);
		com_removeFile(tabRobot[id].idMsg);
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
				//printf("Robot %d en marche\n", r.id+1);
				robot_waitOp(r);
				break;
			case 2:
				printf("Robot %d en panne\n", r.id+1);
				exit(0);
				break;
			case 3:
				printf("Robot %d en mode dégradé\n", r.id+1);
				break;
			default:
				printf("Robot %d : Illegal State\n", r.id+1);
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
			if(t->obj != C1 && t->obj != C2 && t->obj != C3 && t->obj != C4)
			{
				o = ring_lookObject(r.place, t->obj);
				while(o == NULL || (o != NULL && o->type != t->obj))
				{
					o = ring_lookObject(r.place,t->obj);	
					if(o != NULL)
						printf("%d\n",t->obj);
				}
					// TODO Suppr attente active avec semaphore

				r.tabObj[r.stock] = ring_getObject(r.place);
				r.stock++;
			}

			o = robot_op(r,t);

			while(ring_putObject(r.place,o) == NULL)
				; // TODO Suppr attente active
			break;
		case LAST_OP:
			o = ring_lookObject(r.place, t->obj);
			while(o == NULL || (o != NULL && o->type != t->obj))
				o = ring_lookObject(r.place,t->obj);	
				// TODO Suppr attente active avec semaphore

			r.tabObj[r.stock] = ring_getObject(r.place);
			r.stock++;

			o = robot_op(r,t);
			o->etat = FINISH;

			while(ring_putObject(r.place,o) == NULL)
				; // TODO Suppr attente active
			break;
	}
	com_sendACK(r.idMsg);
	return 0;
}

object_t *robot_op(robot_t r, tcom *op)
{
	object_t* o = NULL;
//	printf("Robot %d : Effectue l'operation %d sur un objet %d\n",r.id+1,op->operation+1, op->obj);

	switch(op->obj)
	{
		case C1:
			o = getNewObject(P1);
			break;
		case C2:
			o = getNewObject(P2);
			break;
		case C3:
			o = getNewObject(P3);
			break;
		case C4:
			o = getNewObject(P4);
			break;
		case P1:
			o = getNewObject(P1);
			break;
		case P2:
			o = getNewObject(P2);
			break;
		case P3:
			o = getNewObject(P3);
			break;
		case P4:
			o = getNewObject(P4);
			break;
	}
	r.stock = 0;
	return o;
}
