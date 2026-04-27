/* fichiers de la bibliothèque standard */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
/* bibliothèque standard unix */
#include <unistd.h> /* close, read, write */
#include <sys/types.h>
#include <sys/socket.h>
/* spécifique à internet */
#include <arpa/inet.h> /* inet_pton */

#include "sys_utils.h"
#define PORT_QUIZZP 6666

void usage(char *nom_prog)
{
	fprintf(stderr, "Usage: %s addr_ipv4\n"
			"client pour QUIZZP (Quizz Protocol)\n"
			"Exemple: %s 127.0.0.1 \n", nom_prog, nom_prog);
}

/** Essayer de se connecter en TCP à l'adresse IPv4 donnée en argument, au port
 * associé au Quizz Protocol.
 *
 * En cas de succès, retourne le descripteur de fichier associé à la socket
 * d'échange avec le serveur.
 * En cas d'échec, met fin au programme après avoir affiché un message d'erreur
 * sur la sortie standard des erreurs. */
int connection_au_serveur(const char *addr_ipv4);

/** Échanger avec le serveur connecté via la socket sock ainsi que spécifié par
 * le protocole Quizz Protocol, tout en menant les échanges avec l'utilisateur.
 *
 * - Imprimer sur la sortie standard la question et les propositions envoyées
 *   par le serveur
 * - Demander à l'utilisateur un entier entre 1 et le nombre de propositions
 * - Envoyer le numéro de la réponse choisie au serveur
 * - Recevoir le message final du serveur (réponse correcte ou incorrecte)
 * - Dire à l'utilisateur si sa réponse est correcte ou non
 */
void echanger_avec_serveur(int sock);
void echanger_avec_serveur_test(int sock);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		usage(argv[0]);
		return 1;
	}
	int sock = connection_au_serveur(argv[1]);
	echanger_avec_serveur(sock);
	close(sock);
	return 0;
}

int connection_au_serveur(const char *addr_ipv4)
{
	return 0;
}

void echanger_avec_serveur(int sock)
{
}
