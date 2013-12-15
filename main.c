#include <stdio.h>
#include <stdlib.h>
#include "robot.h"
#include "tapis.h"
#include "tourniquet.h"
#include "objet.h"

int main(void)
{
	// TODO Construct 10,p1;15,p2;12,p3;8,p4
	// TODO Diagramme de communication
	// TODO Reseau de petri

	int r1 = robot_init(1);
	object_t* o1 = getNewObject(C1);
	
	tapis_init();
	init_tourniquet();

	sleep(3);

	stopRobot(r1);
	tapis_finish();
	stop_tourne();

	return EXIT_SUCCESS;
}
