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
	while(tabRobot[id].state)
	{
		switch(tabRobot[id].state)
		{
			case 1:
				printf("Robot en marche\n");
				robot_waitOp();
				// Do op
				// Switch on op
				break;
			case 2:
				printf("Robot en panne\n");
				break;
			case 3:
				printf("Robot en mode dégradé\n");
				break;
			default:
				printf("Robot %d : Illegal State\n",id);
		}
	sleep(1);
	}
	return NULL;
}

int robot_waitOp()
{
	// Recv msg
	// Struct msg O:1:2 -> operation 1 sur objet type d'objet 2
	// Struct msg G:3:2 -> recupère 3 objet de type 2
	return 0;
}

void robot_op(int idR, int opId)
{
	printf("Robot %d : Effectue l'operation %d\n",idR,opId);
}
