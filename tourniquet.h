#ifndef __TOURNIQUET_H
#define __TOURNIQUET_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include "objet.h"

#define NBCASE			16
#define TIME_TOURNE	2
#define TIME_WAIT		4

object_t* tourne[NBCASE];		// Tourniquet cases
int nbObjectsIn = 0;				// Nb objects in the tourniquet
pthread_t th_tourne;				// Thread tourniquet
pthread_mutex_t mutex_tourne;	// Mutex tourniquet

/**
 * Initialize thread
 */
void init_tourniquet();

/**
 * Main of the thread
 */
void* tourneMain();

/**
 * Rotate conveyor belt
 */
void rotate();

/**
 * Get objetc at position n
 */
object_t* getObject(int n);

/**
 * Put objects at position n
 */
void putObject(int n, object_t* obj);

#endif
