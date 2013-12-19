#include "objet.h"

object_t* getNewObject(typeObject t)
{
	object_t* obj = malloc(sizeof(object_t));

	obj->type = t;

	if(t == C1 || 
		t == C2 || 
		t == C3 ||
		t == C4)
		obj->etat = MATERIAL;
	else
		obj->etat = PRODUCT;

	return obj;
}

int isMaterial(object_t obj)
{
	if(obj.etat == MATERIAL)
		return 1;
	return 0;
}

int isProduct(object_t obj)
{
	if(obj.etat == PRODUCT)
		return 1;
	return 0;
}

int isFinish(object_t obj)
{
	if(obj.etat == FINISH)
		return 1;
	return 0;
}

void finishObj(object_t* obj)
{
	if(obj->etat != MATERIAL)
		obj->etat = FINISH;
}
