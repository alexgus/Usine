#ifndef __OBJET_H
#define __OBJET_H

#include <stdio.h>
#include <stdlib.h>

#define MATERIAL	1
#define PRODUCT	2

#define NOMP_1 1
#define NOMP_2 2
#define NOMP_3 3
#define NOMP_4 4

#define NOMC_1 NOMP_1
#define NOMC_2 NOMP_2
#define NOMC_3 NOMP_3
#define NOMC_4 NOMP_4

/**************************************
 * Object's type (MATERIAL, PRODUCT)
 *************************************/
typedef int type_t;

/**************************************
 * Manufacturing object's structure
 *************************************/
typedef struct
{
	type_t type;
	int numP;
} object_t;


object_t* getNewObject(type_t type, int name);

int isMaterial(object_t obj);

#endif
