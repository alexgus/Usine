#include "communication.h"
int init()
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

void removeFile(int msgid)
{
	msgctl(msgid, IPC_RMID,NULL);
}

void ecrire(tcom message, int msgid)
{

	key_t key;
   
	/* Envoie du message sur la file	*/
	if (msgsnd(msgid, &message, sizeof(tcom),0) == -1) 
	{
		perror("Erreur d'ecriture requete \n");
		exit(1);
	}
	printf("Message envoyé\n");
}

tcom lire(int msgid)
{

	tcom message;
	int longMSG;
	
	/* lecture du message sur la file */
	if ((longMSG = msgrcv(msgid, &message, sizeof(tcom), 1, 0)) == -1) 
	{
		perror("Erreur de lecture requete \n");
		exit(1);
	}
	printf("Message lu\n");
	
   return message;
}