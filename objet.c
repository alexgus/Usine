#include "objet.h"

void infoObject(char* string, object_t *o)
{
	sprintf(string, "Object [id : %d, type : %d]", o->id, o->type);
}
