CC=gcc

CFLAGS=-Wall -std=c99 -Wfatal-errors

OBJETS=chemin.o fichier.o main.o
PROG=main

all : $(OBJETS)
	gcc $(OBJETS) -o $(PROG) -lncurses

chemin.o : chemin.c chemin.h
	gcc -c $(CFLAGS) chemin.c

fichier.o : fichier.c fichier.h
	gcc -c $(CFLAGS) fichier.c

main.o : main.c fichier.h chemin.h

clean : 
	rm $(PROG) $(OBJETS)