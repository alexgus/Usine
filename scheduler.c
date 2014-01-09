#include "scheduler.h"

void scheduler_init(int p1in, int p2in, int p3in, int p4in)
{
	int i;

	// NB of objects
	nbP1 = p1in;
	nbP2 = p2in;
	nbP3 = p3in;
	nbP4 = p4in;

	nbP1f = 0;
	nbP2f = 0;
	nbP3f = 0;
	nbP4f = 0;	
	
	// Initialize robots
	for(i=0; i < NB_ROBOT; i++)
		robot_init((i * 2) + 1);

	// start ring
	ring_init();

	// Start scheduler
	etat_tapis = 1;
	pthread_mutex_init(&etat_mutex, NULL);
	pthread_mutex_init(&comtex, NULL);
	pthread_mutex_init(&mutexRobot, NULL); // TODO ...
	pthread_create(&th_tapis,NULL,&scheduler_main,NULL);
}

void *scheduler_main()
{
	int i;
	object_t* o;

	op = malloc(sizeof(pthread_t)*(nbP1 + nbP2 + nbP3 + nbP4));
	for(i=0;i < nbP1 ; i++)
		pthread_create(&op[i],NULL,&p1,NULL);
	for(i=0;i < nbP2 ; i++)
		pthread_create(&op[i],NULL,&p2,NULL);
	for(i=0;i < nbP3 ; i++)
		pthread_create(&op[i],NULL,&p3,NULL);
	for(i=0;i < nbP4 ; i++)
		pthread_create(&op[i],NULL,&p4,NULL);

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
				while((o = ring_lookFinish(TAKE)) == NULL)
					; // TODO Suppr attente active
				
				switch(o->type)
				{	
					case P1:
						nbP1f++;
						break;
					case P2:
						nbP2f++;
						break;
					case P3:
						nbP3f++;
						break;
					case P4:
						nbP4f++;
						break;
				}
				printf("Nombre de produit finis :\n"
							"\tP1 : %d/%d\n"
							"\tP2 : %d/%d\n"
							"\tP3 : %d/%d\n"
							"\tP4 : %d/%d\n",
							nbP1f,nbP1,nbP2f,nbP2,nbP3f,nbP3,nbP4f,nbP4);
				break;
		}
	}
	return 0;
}

void scheduler_wait()
{
	pthread_join(th_tapis,NULL);
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
	
	idRobot--;

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

	// Send msg
	msg = malloc(sizeof(tcom));
	msg->order = GET;
	msg->qte = nb;
	msg->obj = t;

	pthread_mutex_lock(&comtex);
	pthread_mutex_lock(&mutexRobot);
	com_sendOrder(tabRobot[idRobot].idMsg, msg);
	pthread_mutex_unlock(&mutexRobot);
	pthread_mutex_unlock(&comtex);

	pthread_mutex_lock(&comtex);
	pthread_mutex_lock(&mutexRobot);
	com_waitACK(tabRobot[idRobot].idMsg);
	pthread_mutex_unlock(&mutexRobot);
	pthread_mutex_unlock(&comtex);
}

void operation(typeObject t, oper tOp,int nb, int idRobot,int lastOp)
{
	tcom *msg;

	idRobot--;

	// Send msg
	msg = malloc(sizeof(tcom));
	if(lastOp)
		msg->order = LAST_OP;
	else	
		msg->order = OP;
	msg->qte = nb;
	msg->obj = t;
	msg->operation = tOp;

	pthread_mutex_lock(&comtex);
	pthread_mutex_lock(&mutexRobot);
	com_sendOrder(tabRobot[idRobot].idMsg, msg);
	pthread_mutex_unlock(&mutexRobot);
	pthread_mutex_unlock(&comtex);

	pthread_mutex_lock(&comtex);
	pthread_mutex_lock(&mutexRobot);
	com_waitACK(tabRobot[idRobot].idMsg);
	pthread_mutex_unlock(&mutexRobot);
	pthread_mutex_unlock(&comtex);
}

void *p1()
{
	stock(C1,3,1);
	operation(C1,OP1,3,1,0);
	operation(P1,OP2,1,2,0);
	operation(P1,OP3,1,3,0);
	operation(P1,OP5,1,5,1); // Final
	return 0;
}

void *p2()
{
	stock(C2,3,1);
	operation(C2,OP2,3,2,0);
	operation(P2,OP4,1,4,0);
	operation(P2,OP1,1,1,0);
	operation(P2,OP6,1,6,1); // Final
	return 0;
}

void *p3()
{
	stock(C3,1,1);
	operation(C3,OP1,1,1,0);
	operation(P3,OP3,1,3,0);
	operation(P3,OP5,1,5,0);
	operation(P3,OP1,1,1,0);
	operation(P3,OP3,1,3,1); // Final
	return 0;
}

void *p4()
{
	stock(C4,2,1);
	operation(C4,OP4,2,4,0);
	operation(P4,OP6,1,6,0);
	operation(P4,OP1,1,1,1); // Final
	return 0;
}
