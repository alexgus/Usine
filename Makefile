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
main: main.o robot.o object.o scheduler.o ring.o communication.o
	$(LD) -o $(EXEC) main.o robot.o object.o scheduler.o ring.o communication.o

main.o: main.c
	$(CC) main.c

#Robot
robot.o: robot.c robot.h
	$(CC) robot.c

#Object
objet.o: object.c object.h
	$(CC) object.c

#scheduler
scheduler.o: scheduler.h scheduler.c
	$(CC) scheduler.c

#ring
ring.o: ring.h ring.c
	$(CC) ring.c

#com
communication.o: communication.h communication.c
	$(CC) communication.c

########
# Util
########
clean:
	/usr/bin/rm *.o *~ $(EXEC) -rf

exec:
	./$(EXEC)


