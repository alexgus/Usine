##################################
# Variables
##################################
EXEC=Usine.out
LIB=-lpthread
CC=gcc -Wall -c
LD=gcc $(LIB)
ALL=main


all: $(ALL)

#Main
main: main.o robot.o objet.o tapis.o tourniquet.o
	$(LD) -o $(EXEC) main.o robot.o objet.o tapis.o tourniquet.o

main.o: main.c
	$(CC) main.c

#Robot
robot.o: robot.c robot.h
	$(CC) robot.c

#Objet
objet.o: objet.c objet.h
	$(CC) objet.c

#Tapis
tapis.o: tapis.h tapis.c
	$(CC) tapis.c

#Tourniquet
tourniquet.o: tourniquet.h tourniquet.c
	$(CC) tourniquet.c

########
# Util
########
clean:
	/usr/bin/rm *.o *~ $(EXEC) -rf

exec:
	./$(EXEC)


