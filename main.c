#include <stdio.h>
#include <stdlib.h>

#include "robot.h"

int main(void)
{
	char out[512];
	robot_t r1;
	object_t o1;

	o1.id = 1;
	o1.type = TYPE_1;

	r1.work=&o1;
	r1.acceptedObjects = TYPE_1;

	infoRobot(out,&r1);
	printf("%s\n", out);
	
	return EXIT_SUCCESS;
}
