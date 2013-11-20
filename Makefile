##################################
# Variables
##################################
EXEC=Usine.out
#LIB=
CC=gcc -Wall -c
LD=gcc
ALL=main


all: $(ALL)

main: main.o robot.o objet.o
	$(LD) -o $(EXEC) main.o robot.o objet.o

main.o: main.c
	$(CC) main.c

robot.o: robot.c robot.h
	$(CC) robot.c

objet.o: objet.c objet.h
	$(CC) objet.c

clean:
	/usr/bin/rm *.o *~ $(EXEC) -rf

exec:
	./$(EXEC)


