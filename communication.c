#include "communication.h"

int com_init()
{
	key_t cle;
	int msgid;

	/*  Creation de la clé IPC */
	 if ((cle = ftok(".", "A")) == -1) 
	{
		perror("Erreur de creation de la clé \n");
		exit(1);
	 }

	/* Creation de la file de message 	*/
	if ((msgid = msgget(cle, IPC_CREAT | IPC_EXCL | 0600)) == -1) 
	{
		if ((msgid = msgget (cle,0)) == -1)
		{
			perror("Erreur de creation de la file\n");
			exit(1);
		}
   }

	return msgid;
}

void com_removeFile(int msgid)
{
	msgctl(msgid, IPC_RMID,NULL);
}

void com_ecrire(com message, int msgid)
{
//	key_t key;
   
	/* Envoie du message sur la file	*/
	if (msgsnd(msgid, &message, sizeof(com),0) == -1) 
	{
		perror("Erreur d'ecriture requete : ");
		exit(1);
	}
	printf("Message envoyé\n");
}

com *com_lire(int msgid)
{
	com *message = malloc(sizeof(com));
	int longMSG;
	
	/* lecture du message sur la file */
	if ((longMSG = msgrcv(msgid, message, sizeof(com), 1, 0)) == -1) 
	{
		perror("Erreur de lecture requete : ");
		exit(1);
	}
	printf("Message lu : %d\n", longMSG);
	
   return message;
}
