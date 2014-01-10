#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "robot.h"
#include "scheduler.h"
#include "ring.h"
#include "object.h"


void interupt(int id)
{
	int i;
	printf("Que voulez vous faire :\n"
		"\t	1) Quitter\n"
		"\t	2) Mode degrade\n"
		"\t	3) Ne rien faire\n"
		"\nChoix : ");
	scanf("%d",&i);
	printf("\n");
	switch(i)
	{
		case 1:
			exit(0);
			break;
		case 2:
			printf("\n\n--- Mode dégradé\n"
						"Quel robot tombe en panne [1-6] : ");
			scanf("%d",&i);
			printf("\nLe robot %d est alors en panne\n",i);
			break;
		case 3:
			break;
	}
}

int main(void)
{
	signal(SIGINT,interupt);

	scheduler_init(10,15,12,8);
	scheduler_wait();

	return EXIT_SUCCESS;
}
