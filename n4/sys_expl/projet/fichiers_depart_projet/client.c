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
#include <poll.h>
#include <string.h>
#include "buffer/buffer.h"
#include "utils.h"

#define PORT_FREESCORD 4321

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while(0);

/** se connecter au serveur TCP d'adresse donnée en argument sous forme de
 * chaîne de caractère et au port donné en argument
 * retourne le descripteur de fichier de la socket obtenue ou -1 en cas
 * d'erreur. */
int connect_serveur_tcp(char *adresse, uint16_t port);

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "Usage: %s <adresse>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	int sfd = connect_serveur_tcp(argv[1], PORT_FREESCORD);
	char buf[4097];
	struct pollfd fds[2];
	buffer * b = buff_create(sfd, 4096);
	
	fds[0].fd = STDIN_FILENO; 	// L'entrée clavier
	fds[0].events = POLLIN;
	fds[1].fd = sfd; 	// La socket serveur
	fds[1].events = POLLIN;

	while(buff_fgets_crlf(b, buf, sizeof(buf)) != NULL){
		crlf_to_lf(buf);
		if(strcmp(buf, "\n") == 0) break;	// Ligne vide -> fin du message
		write(STDOUT_FILENO, buf, strlen(buf));
	}

	while(1){
		// Demander le pseudo à l'utilisateur
		write(STDOUT_FILENO, "Entrez votre pseudo : ", 22);
		if(fgets(buf, sizeof(buf), stdin) == NULL) break;

		// Construire "nickname <pseudo>\r\n"
		char msg[4200];
		snprintf(msg, sizeof(msg), "nickname %s", buf);
		lf_to_crlf(msg);
		write(sfd, msg, strlen(msg));

		// Lire la réponse du serveur
		if(buff_fgets_crlf(b, buf, sizeof(buf)) == NULL) break;
		if(buf[0] == '0') break; 	// Pseudonyme accepté

		// Sinon afficher l'erreur et recommencer
		crlf_to_lf(buf);
		write(STDOUT_FILENO, buf, strlen(buf));
	}

	while(1){
		// poll(fds, 2, -1); 	// Bloque jusqu'à ce que l'un soit prêt

		if(!buff_ready((b)))	// Rien dans le buffer -> on poll
			poll(fds, 2, -1);

		// stdin a une ligne -> lire et envoyer
		if(fds[0].revents & POLLIN){
			if(fgets(buf, sizeof(buf), stdin) == NULL)
				break; 	// Ctrl-D -> on quitte

			lf_to_crlf(buf); 	// Convertir \n -> \r\n avant d'envoyer
			write(sfd, buf, strlen(buf));
		}

		// socket a un message -> lire et afficher
		if(fds[1].revents & POLLIN || buff_ready(b)){
			// ssize_t n = read(sfd, buf, sizeof(buf));
			// ssize_t n = buff_fgets_crlf(b, buf, sizeof(buf));
			// if(n <= 0) break;
			// write(STDOUT_FILENO, buf, n);
			
			if(buff_fgets_crlf(b, buf, sizeof(buf)) == NULL) break;
			crlf_to_lf(buf); 	// Convertir \r\n -> \n avant d'afficher
			write(STDOUT_FILENO, buf, strlen(buf));
		}
	}

	// while(fgets(buf, sizeof(buf), stdin)){
	// 	write(sfd, buf, strlen(buf));
	// 	ssize_t n = read(sfd, buf, sizeof(buf));
	// 	write(STDOUT_FILENO, buf,n);
	// }

	buff_free(b);
	close(sfd);

	return 0;
}

int connect_serveur_tcp(char *adresse, uint16_t port)
{
	int sfd;
	struct sockaddr_in my_addr;

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd == -1)
		handle_error("socket");

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port);

	if(inet_pton(AF_INET, adresse, &my_addr.sin_addr) != 1)
		handle_error("inet_aton");

	if(connect(sfd, (struct sockaddr *) &my_addr, sizeof(my_addr)) == -1)
		handle_error("connect");

	/* pour éviter les warnings de variable non utilisée */
	return sfd;
}
