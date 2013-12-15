#ifndef __OBJET_H
#define __OBJET_H

#include <stdio.h>
#include <stdlib.h>

typedef enum { MATERIAL, PRODUCT, FINISH } state;
typedef enum {C1,C2,C3,C4,P1,P2,P3,P4} typeObject;

/**************************************
 * Manufacturing object's structure
 *************************************/
typedef struct
{
	state etat;
	typeObject type;
} object_t;


object_t* getNewObject(typeObject t);

int isMaterial(object_t obj);
int isProduct(object_t obj);
int isFinish(object_t obj);

void finishObj(object_t* obj);

#endif
