##################################
# Variables
##################################
EXEC=Usine.out
CC=gcc -c
LD=gcc
#LIB=
ALL=main


all: $(ALL)

main: main.o
	$(LD) -o $(EXEC) main.o

main.o: main.c
	$(CC) main.c

clean:
	/usr/bin/rm *.o *~ $(EXEC) -rf

exec:
	./$(EXEC)


