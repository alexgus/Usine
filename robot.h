#ifndef __ROBOT_H
#define __ROBOT_H

#include <stdio.h>
#include "objet.h"

/**************************************
 * Robot
 *************************************/
typedef struct
{
	int id;
	object_t *work;
	type_t acceptedObjects;
} robot_t;

char* infoRobot(char *string, robot_t *r);

#endif
