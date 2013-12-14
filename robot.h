#ifndef __ROBOT_H
#define __ROBOT_H

#include <stdio.h>
#include <pthread.h>
#include "objet.h"

#define NB_ROBOT 6

pthread_t th_robot[NB_ROBOT];
pthread_mutex_t mutex_robot;
int nbRobot = 0;

/**************************************
 * Robot
 *************************************/
typedef struct
{
	int id; // Robot's id
	int place; // Robot's place in front of the ring
	int stock; // Robot's stock for Materials or Products
} robot_t;

robot_t* robot_init(int id, int place);
void *robotMain();
int waitOp();

void op1(robot_t r);
void op2(robot_t r);
void op3(robot_t r);
void op4(robot_t r);
void op5(robot_t r);
void op6(robot_t r);

void (*tabOp[])(robot_t) = { 
									&op1,
									&op2,
									&op3,
									&op4,
									&op5,
									&op6
								};
#endif
