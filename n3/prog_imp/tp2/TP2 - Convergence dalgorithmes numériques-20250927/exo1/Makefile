CC=gcc

CFLAGS=-Wall -std=c99 -Wfatal-errors

OBJETS=leipniz.o exo1.o
PROG=main

all : $(OBJETS)
	gcc $(OBJETS) -o $(PROG) -lm

leipniz.o : leipniz.c leipniz.h
	gcc -c $(CFLAGS) leipniz.c

exo1.o : exo1.c leipniz.c

clean : 
	rm $(PROG) $(OBJETS)