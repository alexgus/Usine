#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#include "object.h"

typedef enum { GET, OP, LAST_OP } order;
typedef enum { OP1, OP2, OP3, OP4, OP5, OP6 } oper;
typedef enum { ORDER, ACK } msgType;

typedef struct 
{
	order order;
	oper operation;
	typeObject obj;
	int qte;
} tcom;

typedef struct
{
	long type;
	tcom* data;
} com;

tcom* test;

//initialise une file de message
int com_init();

//supprime la file de message
void com_removeFile(int msgid);

//envoie le message sur la file de messages
void com_ecrire(com* message, int msgid);

//lit le message sur la file
com *com_lire(int msgid,msgType m);

/**
 * Envoie un ordre à un robot
 */
void com_sendOrder(int msgid, tcom *t);

/**
 * Le robot recoit un ordre
 */
tcom* com_getOrger(int msgid);

/**
 * Envoie un ACK au scheduler
 */
void com_sendACK(int msgid);

/**
 * Le scheduler recoit un ACK
 */
void com_waitACK(int msgid);

#endif

