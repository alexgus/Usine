#ifndef __OBJET_H
#define __OBJET_H

#include <stdio.h>

#define TYPE_1 1
#define TYPE_2 2
#define TYPE_3 3
#define TYPE_4 4
#define TYPE_5 5
#define TYPE_6 6

/**************************************
 * Object'type
 *************************************/
typedef int type_t;

/**************************************
 * Manufacturing object's structure
 *************************************/
typedef struct
{
	int id;
	type_t type;
} object_t;

void infoObject(char* string, object_t *o);

#endif
