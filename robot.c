#include "robot.h"

char* infoRobot(char *string, robot_t *r)
{
	char infoO[256];
	infoObject(infoO, r->work);
	sprintf(string, "Robot [num : %d, Working on %s, accepted object [type : %d]]",
		r->id, infoO, r->acceptedObjects);
	return string;
}
