all: code_cercle 

gestion_fenetre.o: gestion_fenetre.c gestion_fenetre.h
	gcc -Wall -c gestion_fenetre.c

code_cercle.o: code_cercle.c gestion_fenetre.h
	gcc -Wall -c code_cercle.c

code_cercle: code_cercle.o gestion_fenetre.o
	gcc -Wall -o code_cercle code_cercle.o gestion_fenetre.o -lSDL2 -lm

clean:
	rm -fr *.o code_cercle 
