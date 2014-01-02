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

typedef struct 
{
	order order;
	oper operation;
	typeObject obj;
	int qte;
} tcom;

//initialise une file de message
int init();

//supprime la file de message
void removeFile(int msgid);

//envoie le message sur la file de messages
void ecrire(tcom message, int msgid);

//lit le message sur la file
tcom lire(int msgid);


#endif

