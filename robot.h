#ifndef __ROBOT_H
#define __ROBOT_H

#include <stdio.h>
#include <pthread.h>
#include "objet.h"

#define NB_ROBOT 6

/**************************************
 * 			Struct Robot
 *************************************/
typedef struct
{
	int id; // Robot's id
	int place; // Robot's place in front of the ring
	int stock; // Robot's stock for Materials or Products
	int state; // State of the robot -> 0 : Arret, 1 : Marche, 2 : Panne, 3 : Dégradé
	pthread_t th;
	pthread_mutex_t mutex; // Mutex of robot
} robot_t;

/**
 * Table for stocking information about robots
 */
robot_t tabRobot[NB_ROBOT];

/**
 * Create e new robot and place it in front of ring's case
 * @return id's robot
 */
int robot_init(int place);

/**
 * Stop the robot, thread exit
 */
void stopRobot(int id);
/**
 * Start normaly the robot
 */
void startRobot(int id);
/**
 * The robot is breakdown
 */
void breakdownRobot(int id);
/** 
 * The robot is in degrade mode
 */
void degradeRobot(int id);

/**
 * Main of the robot thread
 */
void *robotMain(int id);

/**
 * Wait an operation to do
 */
int waitOp();


/**
 * List of operation
 */
void op(int idR, int opId);

#endif
