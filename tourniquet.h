#ifndef __TOURNIQUET_H
#define __TOURNIQUET_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NBCASE 16

// TODO ref to objects or objetcs ?
int tourne[NBCASE];

pthread_t th_tourne;			// Thread tourniquet

void init_tourniquet();

void* tourneMain();

#endif
