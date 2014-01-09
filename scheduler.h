#ifndef __TAPIS_H
#define __TAPIS_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "robot.h"
#include "ring.h"

#define PUT 	1
#define TAKE	2

pthread_t th_tapis; 				// Thread tapis
pthread_mutex_t etat_mutex;	// Mutex etat tapis

int nbP1,nbP2,nbP3,nbP4;
int nbP1f,nbP2f,nbP3f,nbP4f;
pthread_t *op;

/************************
 Etat du tapis :
	0 : Arret
	1 : Marche
	2 : Finis
*************************/
int etat_tapis;

/**
 * Initialize the conveyor belt
 */
void scheduler_init(int p1in, int p2in, int p3in, int p4in);

/**
 * Add and remove objects from the conveyor belt
 */
void* scheduler_main();

/**
 * Wait the scheduler finish its jobs
 */
void scheduler_wait();

/**
 * Stop the conveyor belt
 */
void scheduler_stop();

/**
 * Start the conveyor belt
 */
void scheduler_start();

/**
 * Finish the thread
 */
void scheduler_finish();

/**
 * Ask robot to stock product
 */
void stock(typeObject t, int nb, int idRobot);

/**
 * Ask Robot to do op on object
 */
void operation(typeObject t, oper tOp,int nb, int idRobot,int lastOp);

// products
void* p1();
void* p2();
void* p3();
void* p4();

#endif
