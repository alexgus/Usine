#ifndef __TAPIS_H
#define __TAPIS_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_t th_tapis; 				// Thread tapis
pthread_mutex_t etat_mutex;	// Mutex etat tapis

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
void scheduler_init();

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

// TODO Put materials
// TODO Pick up finish products

#endif
