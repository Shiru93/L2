CC=gcc

CFLAGS=-Wall -std=c99 -Wfatal-errors

OBJETS=dichotomie.o main.o
PROG=main

all : $(OBJETS)
	gcc $(OBJETS) -o $(PROG) -lm

dichotomie.o : dichotomie.c dichotomie.h
	gcc -c $(CFLAGS) dichotomie.c

main.o : main.c dichotomie.c

clean : 
	rm $(PROG) $(OBJETS)