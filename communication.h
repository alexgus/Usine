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


#define TAILLE_MSG 500

typedef struct {
	long mtype;
	char mtext[TAILLE_MSG];
} tmessage;

//initialise une file de message
int init();

//supprime la file de message
void removeFile(int msgid);

//envoie le message sur la file de messages
void ecrire(tmessage message, int msgid);

//lit le message sur la file
tmessage lire(int msgid);


#endif

