#ifndef __OBJET_H
#define __OBJET_H

#include <stdio.h>
#include <stdlib.h>

#define MATERIAL	1
#define PRODUCT	2
#define FINISH		3

/**************************************
 * Object's type (MATERIAL, PRODUCT, FINISH)
 *************************************/
typedef int state_t;

/**************************************
 * Manufacturing object's structure
 *************************************/
typedef struct
{
	int idP; // Product's id
	state_t state;
} object_t;


object_t* getNewObject(state_t type, int id);

int isMaterial(object_t obj);
int isProduct(object_t obj);
int isFinish(object_t obj);

#endif
