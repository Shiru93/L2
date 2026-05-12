/*
 * Ziya EMRE 12212738
 * Je déclare qu'il s'agit de mon propre travail
 * Ce travail a été réalisé intégralement par un être humain
 */

#include "user.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>

/** accepter une connection TCP depuis la socket d'écoute sl et retourner un
 * pointeur vers un struct user, dynamiquement alloué et convenablement
 * initialisé */
struct user *user_accept(int sl)
{
	struct user *u = malloc(sizeof(struct user));
	if(!u){
		fprintf(stderr, "Erreur malloc\n");
		exit(EXIT_FAILURE);
	}

	u->addr_len = sizeof(u->address);

	u->sock = accept(sl, (struct sockaddr *) &u->address, &u->addr_len);
	if(u->sock == -1)
		handle_error("accept");

	return u;
}

/** libérer toute la mémoire associée à user */
void user_free(struct user *user)
{
	free(user);
}
