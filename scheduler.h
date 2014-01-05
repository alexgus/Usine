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

// products
void* p1();
void* p2();
void* p3();
void* p4();

#endif
