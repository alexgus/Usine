#ifndef __ROBOT_H
#define __ROBOT_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "object.h"
#include "communication.h"
#include "ring.h"

#define NB_ROBOT 6
#define NB_STOCK 5

/**************************************
 * 			Struct Robot
 *************************************/
typedef struct
{
	int id; // Robot's id
	int place; // Robot's place in front of the ring
	int stock; // Robot's stock for Materials or Products
	object_t* tabObj[NB_STOCK]; // Robot's tab
	int state; // State of the robot -> 0 : Arret, 1 : Marche, 2 : Panne, 3 : Dégradé
	int idMsg; // msg queue for receiving orders
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
void robot_stop(int id);
/**
 * Start normaly the robot
 */
void robot_start(int id);
/**
 * The robot is breakdown
 */
void robot_breakdown(int id);
/** 
 * The robot is in degrade mode
 */
void robot_degradeMode(int id);

/**
 * Main of the robot thread
 */
void *robot_main(int id);

/**
 * Wait an operation to do
 */
int robot_waitOp(robot_t id);

/**
 * List of operation
 */
void robot_op(int idR, tcom op);

#endif
