/*
 * Ziya EMRE 12212738
 * Je déclare qu'il s'agit de mon propre travail
 * Ce travail a été réalisé intégralement par un être humain
 */

#ifndef USER_H
#define USER_H
#include <sys/socket.h>
#include <netinet/in.h>

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while(0);

struct user {
	struct sockaddr_in address;
	socklen_t addr_len;
	int sock;
	char nickname[17];	// 16 caractères max + '\0'
};

struct user *user_accept(int sl);
void user_free(struct user *user);

#endif /* ifndef USER_H */
