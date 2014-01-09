#include "scheduler.h"

void scheduler_init(int p1in, int p2in, int p3in, int p4in)
{
	int i;

	// NB of objects
	nbP1 = p1in;
	nbP2 = p2in;
	nbP3 = p3in;
	nbP4 = p4in;
	
	// Initialize robots
	for(i=0; i < NB_ROBOT; i++)
		robot_init((i * 2) + 1);

	// start ring
	ring_init();

	// Start scheduler
	etat_tapis = 1;
	pthread_mutex_init(&etat_mutex, NULL);
	pthread_create(&th_tapis,NULL,&scheduler_main,NULL);
}

void *scheduler_main()
{
	int i;

	op = malloc(sizeof(pthread_t)*(nbP1 + nbP2 + nbP3 + nbP4));
	for(i=0;i < 1 ; i++)
		pthread_create(&op[i],NULL,&p1,NULL);

	while(etat_tapis != 2)
	{
		switch(etat_tapis)
		{
			case 0:
				for(i=0; i < NB_ROBOT; i++)
					robot_stop(i);
				
				// TODO free memory
				printf("scheduler : Not in work !\n");
				break;
			case 1:
				printf("scheduler : In work !\n");
				break;
		}
		sleep(10);
	}
	return 0;
}

void scheduler_stop()
{
	pthread_mutex_lock(&etat_mutex);
	etat_tapis = 0;
	pthread_mutex_unlock(&etat_mutex);
	
	pthread_join(th_tapis,NULL);
}

void scheduler_start()
{
	pthread_mutex_lock(&etat_mutex);
	etat_tapis = 1;
	pthread_mutex_unlock(&etat_mutex);
}

void scheduler_finish()
{
	int i;

	pthread_mutex_lock(&etat_mutex);
	etat_tapis = 2;
	pthread_mutex_unlock(&etat_mutex);

	for(i=0;i<(nbP1 + nbP2 + nbP3 + nbP4);i++)
		pthread_join(op[i],NULL);
}

void stock(typeObject t, int nb, int idRobot)
{
	int i = 0;
	tcom *msg;
	object_t *o;

	// Send msg
	msg = malloc(sizeof(tcom));
	msg->order = GET;
	msg->qte = nb;
	msg->obj = t;

	com_sendOrder(tabRobot[idRobot].idMsg, msg);

	// Put objects
	while(i < nb)
	{
		o = malloc(sizeof(object_t));
		o->type = t;
		if(isMaterial(*o))
			o->etat = MATERIAL;
		else
			o->etat = PRODUCT;
		while(ring_putObject(PUT,o) == NULL)
			; // TODO Suppr attente active
		i++;
	}
	com_waitACK(tabRobot[idRobot].idMsg);
}

void operation(typeObject t, oper tOp,int nb, int idRobot)
{
	tcom *msg;

	// Send msg
	msg = malloc(sizeof(tcom));
	msg->order = OP;
	msg->qte = nb;
	msg->obj = t;
	msg->operation = tOp;

	com_sendOrder(tabRobot[idRobot].idMsg, msg);
	com_waitACK(tabRobot[idRobot].idMsg);
}

void *p1()
{
// TODO	describe the process
	stock(C3,3,2);
	operation(C3,OP1,3,2);
	return 0;
}

void *p2()
{
	return 0;
}

void *p3()
{
	return 0;
}

void *p4()
{
	return 0;
}
