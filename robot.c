#include "robot.h"

/**
 * Nb of existing robots
 */
int nbRobot = 0;

/**
 * Operations table
 */
void (*tabOp[])(robot_t) = { 
									&op1,
									&op2,
									&op3,
									&op4,
									&op5,
									&op6
								};


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
		pthread_create(&tabRobot[id].th,NULL,&robotMain,(int)id);

		nbRobot++;

		return id;
	}
	return -1;
}

void stopRobot(int id)
{
	if(id < NB_ROBOT)
	{
		pthread_mutex_lock(&tabRobot[id].mutex);
		tabRobot[id].state = 0;
		pthread_mutex_unlock(&tabRobot[id].mutex);

		pthread_join(tabRobot[id].th,NULL);
	}
}

void startRobot(int id)
{
	if(id < NB_ROBOT)
	{
		pthread_mutex_lock(&tabRobot[id].mutex);
		tabRobot[id].state = 1;
		pthread_mutex_unlock(&tabRobot[id].mutex);
	}
}

void breakdownRobot(int id)
{
	if(id < NB_ROBOT)
	{
		pthread_mutex_lock(&tabRobot[id].mutex);
		tabRobot[id].state = 2;
		pthread_mutex_unlock(&tabRobot[id].mutex);
	}
}

void degradeRobot(int id)
{
	if(id < NB_ROBOT)
	{
		pthread_mutex_lock(&tabRobot[id].mutex);
		tabRobot[id].state = 3;
		pthread_mutex_unlock(&tabRobot[id].mutex);
	}
}

void *robotMain(int id)
{
	while(tabRobot[id].state)
	{
		switch(tabRobot[id].state)
		{
			case 1:
				printf("Robot en marche\n");
				op = waitOp();
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
	}
	return NULL;
}

int waitOp()
{
	// Recv msg
	return 0;
}

void op1(robot_t r)
{
	printf("Operation 1\n");
}

void op2(robot_t r)
{
	printf("Operation 2\n");
}

void op3(robot_t r)
{
	printf("Operation 3\n");
}

void op4(robot_t r)
{
	printf("Operation 4\n");
}

void op5(robot_t r)
{
	printf("Operation 5\n");
}

void op6(robot_t r)
{
	printf("Operation 6\n");
}
