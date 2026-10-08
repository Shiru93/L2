#include <stdio.h>
#include <stdlib.h>

/*
 * QUESTION 1
 * Un numéro de port permet d'identifier une application spécifique sur une machine (plusieurs services peuvent tourner sur la même adresse IP)
 * Il est codé sur 2 octets non signés (16 bits), donc valeur maximale 65535
 * Son boutisme en réseau est le big-endian (réseau byte order), d'o`u l'utilisation de htons()
 */

int main(int argc, char * argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <adresse_ip>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Création du socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Remplissage de l'adresse du serveur
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    if(inet_pton(AF_INET, argv[1], &addr.sin_addr) <= 0){
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    // Connexion
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1){
        perror("connect");
        exit(EXIT_FAILURE);
    }

    // Réception du numéro de joueur
    uint8_t num_joueur;
    read(sock, &num_joueur, 1);

    // Suite du client 
    close(sock);

    return 0;
}