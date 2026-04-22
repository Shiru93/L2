CC=gcc

CFLAGS=-Wall -std=c99 -Wfatal-errors

OBJETS=fonctions.o main.o 
PROG=main

all : $(OBJETS)
	gcc $(OBJETS) -o $(PROG) -lm

fonctions.o : fonctions.c fonctions.h
	gcc -c $(CFLAGS) fonctions.c

main.o : main.c fonctions.c

clean :
	rm $(PROG) $(OBJETS)