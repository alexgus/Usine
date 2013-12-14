#include "robot.h"

robot_t* robot_init(int id, int place)
{
	robot_t* r = malloc(sizeof(robot_t));
	r->id = id;
	r->place = place;
	r->stock = 0;
	
	pthread_mutex_init(&mutex_robot, NULL);
	pthread_create(&th_robot[nbRobot],NULL,&robotMain,NULL);
	nbRobot++;

	return r;
}

void *robotMain()
{
	int op;

	while(1)
	{
		op = waitOp();
		// Do op
		// Switch on op
	}
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
