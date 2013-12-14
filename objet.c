#include "objet.h"

object_t* getNewObject(state_t typeO, int id)
{
	object_t* obj = malloc(sizeof(object_t));
	obj->state = typeO;
	obj->idP = id;
	return obj;
}

int isMaterial(object_t obj)
{
	if(obj.state == MATERIAL)
		return 1;
	return 0;
}

int isProduct(object_t obj)
{
	if(obj.state == PRODUCT)
		return 1;
	return 0;
}

int isFinish(object_t obj)
{
	if(obj.state == FINISH)
		return 1;
	return 0;
}
