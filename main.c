#include <stdio.h>
#include <stdlib.h>
#include "robot.h"
#include "scheduler.h"
#include "ring.h"
#include "object.h"

int main(void)
{
	// TODO Construct 10,p1;15,p2;12,p3;8,p4
	// TODO Diagramme de communication
	// TODO Reseau de petri

	/*int r1 = robot_init(1);
	object_t* o1 = getNewObject(C1);
	
	scheduler_init();
	ring_init();

	sleep(3);

	robot_stop(r1);
	scheduler_finish();
	ring_stop();*/

	scheduler_init(10,15,12,8);
	scheduler_wait();

	return EXIT_SUCCESS;
}
