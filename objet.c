#include "objet.h"

object_t* getNewObject(type_t typeO, int nameO)
{
	object_t* obj = malloc(sizeof(object_t));
	obj->type = typeO;
	obj->numP = nameO;
	return obj;
}

int isMaterial(object_t obj)
{
	if(obj.type == MATERIAL)
		return 1;
	return 0;
}

