/*
 * Ziya EMRE 12212738
 * Je déclare qu'il s'agit de mon propre travail
 * Ce travail a été réalisé intégralement par un être humain
 */

#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list/list.h"
#include "user.h"
#include "buffer/buffer.h"
#include "utils.h"

#define PORT_FREESCORD 4321
#define LISTEN_BACKLOG SOMAXCONN

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while(0);

/*
 * Variables globales (accessible par tous les threads)
 */
int pipe_fd[2];
struct list * users;

/** Gérer toutes les communications avec le client renseigné dans
 * user, qui doit être l'adresse d'une struct user */
void *handle_client(void *user);

/** Créer et configurer une socket d'écoute sur le port donné en argument
 * retourne le descripteur de cette socket, ou -1 en cas d'erreur */
int create_listening_sock(uint16_t port);

void *repeteur(void * arg);

int main(int argc, char *argv[])
{
	// struct sockaddr_in peer_addr;
	// socklen_t peer_addr_size = sizeof(peer_addr);
	int sfd = create_listening_sock(PORT_FREESCORD);
	pthread_t tid;
	// char buf[4096];
	// ssize_t n;
	users = list_create();

	if(pipe(pipe_fd) == -1)
		handle_error("pipe");

	pthread_t rep_tid;
	pthread_create(&rep_tid, NULL, repeteur, NULL);
	pthread_detach(rep_tid);

	while(1){
		// int cfd = accept(sfd, (struct sockaddr *) &peer_addr, &peer_addr_size);
		// if(cfd == -1)
		// 	handle_error("accept");

		struct user *u = user_accept(sfd);

		// Quand read return 0, le client s'est déconnecté -> on sort de la boucle
		// while((n = read(cfd, buf, sizeof(buf))) > 0)
		// 	write(cfd, buf, n); 	// On renvoie exactement ce qu'on a lu

		// close(cfd);

		// Ici on va créer un thread pour gérer cfd
		pthread_create(&tid, NULL, handle_client, (void *) u);
		pthread_detach(tid);
	}

	return 0;
}

void *handle_client(void *clt)
{
	struct user *u = (struct user *) clt;
	char buf[4096];
	struct buffer * b = buff_create(u->sock, 4096);

	list_add(users, u);

	write(u->sock, "Bienvenue sur freescord !\r\n", 27);
	write(u->sock, "Entrez votre pseudonyme.\r\n", 26);
	write(u->sock, "\r\n", 2);	// Ligne vide = fin du message de bienvenue

	while(1){
		if(buff_fgets_crlf(b, buf, sizeof(buf)) == NULL) break;

		if(strncmp(buf, "nickname ", 9) == 0){
			crlf_to_lf(buf);	// Enlever le \r\n
			char *pseudo = buf + 9;		// Sauter "nickname"

			
			// Enlever le \n final
			int plen = strlen(pseudo);
			if(plen > 0 && pseudo[plen - 1] == '\n')
			pseudo[plen - 1] = '\0';
			
			if(strlen(pseudo) > 16 || strchr(pseudo, ':') != NULL){
				write(u->sock, "2 Nickname prohibited\r\n", 23);
				continue;	// Recommencer
			}
			
			// Vérifier si le pseudo est déjà pris
			int already_taken = 0;
			struct node *curr = users->first;
			for(; curr != NULL; curr = curr->next){
				struct user *other = (struct user *) curr->elt;
				if(strcmp(other->nickname, pseudo) == 0){
					already_taken = 1;
					break;
				}
			}

			if(already_taken){
				write(u->sock, "1 Nickname already taken\r\n", 26);
				continue;
			}
			
			strncpy(u->nickname, pseudo, 16);
			u->nickname[16] = '\0';
			write(u->sock, "0 ok\r\n", 6);
			break;

		} else {
			write(u->sock, "3 Don't start with nickname \r\n", 31);
			continue;
		}
	}

	while(buff_fgets_crlf(b, buf, sizeof(buf)) != NULL){
		char prefixed[4096 + 20];
		snprintf(prefixed, sizeof(prefixed), "%s: %s", u->nickname, buf);
		write(pipe_fd[1], prefixed, strlen(prefixed));
	}

	list_remove_element(users, u);
	close(u->sock);
	user_free(u);

	return NULL;
}

int create_listening_sock(uint16_t port)
{
	int sfd;
	struct sockaddr_in my_addr;
	
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd == -1)
	handle_error("socket");
	
	/*
	 * Quand tu arrêtes le serveur avec Ctrl-C, la connexion TCP ne se ferme pas instantanément. 
	 * Le système garde le port en état TIME_WAIT pendant ~30-60 secondes pour s'assurer que tous les paquets en transit sont bien arrivés.
	 * Pendant ce temps, si tu relances ./srv, bind() échoue car le port est encore "occupé". 
	 */
	int opt = 1;

	/*
	 * C'est une option de socket qui dit au système : "même si ce port est en TIME_WAIT, laisse-moi le réutiliser".
	 * Argument					Ce que c'est
	 * sfd						ta socket
	 * SOL_SOCKET				niveau "socket" (pas TCP, pas IP)
	 * SO_REUSEADDR				l'option qu'on veut activer
	 * &opt						la valeur — 1 = activer
	 * sizeof(opt)				taille de la valeur
	 * 
	 * Sans SO_REUSEADDR :
	 * ./srv → Ctrl-C → ./srv → bind: Address already in use ❌
	 * 
	 * Avec SO_REUSEADDR :
	 * ./srv → Ctrl-C → ./srv → fonctionne immédiatement ✅
	 */
	setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	my_addr.sin_family = AF_INET;
	
	/*
	 * Les processeurs stockent les nombres dans un certain ordre d'octets (little-endian sur x86). 
	 * Mais le réseau utilise un ordre différent (big-endian). Il faut convertir :
	 */
	my_addr.sin_port = htons(port);

	/*
	 * INADDR_ANY signifie "accepte les connexions sur toutes les interfaces réseau de la machine" (localhost, WiFi, ethernet...). 
	 * C'est ce qu'on veut pour un serveur.
	 */
	my_addr.sin_addr.s_addr = INADDR_ANY; 	// Adresse internet dans l'ordre des octets réseaux 

	/*
	 * Le cast (struct sockaddr *) est nécessaire car bind est générique — elle accepte plusieurs types d'adresses
	 */
	if(bind(sfd, (struct sockaddr *) &my_addr, sizeof(my_addr)) == -1)
		handle_error("bind");

	if(listen(sfd, LISTEN_BACKLOG) == -1)
		handle_error("listen");

	return sfd;
}

void *repeteur(void * arg){
	char buf[4096];

	while(1){
		ssize_t n = read(pipe_fd[0], buf, sizeof(buf));

		struct node * curr = users->first;
		for(; curr != NULL; curr = curr->next){
			struct user * u = (struct user *) curr->elt;
			write(u->sock, buf, n);
		}
	}

	return NULL;
}