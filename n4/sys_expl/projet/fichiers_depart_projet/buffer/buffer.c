/*
 * Ziya EMRE 12212738
 * Je déclare qu'il s'agit de mon propre travail
 * Ce travail a été réalisé intégralement par un être humain
 */

#include "buffer.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct buffer {
	int fd;		// Le fichier à lire
	char * buf;		// Le tableau de caractère
	size_t buffsz;		// Taille du tableau
	size_t pos;		// Position courante dans le tableau
	size_t len; 	// Nombre d'octets valide dans le tableau
	int eof;	// 1 si fin de fichier atteint
};

buffer *buff_create(int fd, size_t buffsz)
{
	struct buffer * bf = malloc(sizeof(struct buffer));
	bf->buf = malloc(sizeof(char) * buffsz);
	
	bf->buffsz = buffsz;
	bf->fd = fd;
	bf->pos = 0;
	bf->len = 0;
	bf->eof = 0;

	return bf;
}

int buff_getc(buffer *b)
{
	if(buff_ready(b)){
		return b->buf[b->pos++];
	}

	ssize_t n = read(b->fd, b->buf, b->buffsz);

	switch(n){
		case 0:
			b->eof = 1;
			return EOF;

		case -1:
			return EOF;

		default:
			b->len = n;
			b->pos = 0;

			return b->buf[b->pos++];
	}
}

int buff_ungetc(buffer *b, int c)
{
	if(!b) return EOF;
	if(b->pos == 0) return EOF;

	b->buf[--b->pos] = c;
	return c;
}

void buff_free(buffer *b)
{
	free(b->buf);
	free(b);

	/* pour éviter les warnings de variable non utilisée */
	b = NULL;
}

int buff_eof(const buffer *buff)
{
	return buff->eof;
}

int buff_ready(const buffer *buff)
{
	return buff->pos < buff->len;
}

char *buff_fgets(buffer *b, char *dest, size_t size)
{
	char c;

	int i = 0;
	while(i < size - 1){
		c = buff_getc(b);
		if(c == EOF){
			if(i == 0) return NULL;
			else break;
		}

		dest[i++] = c;
		if(c == '\n') break;
	}

	dest[i] = '\0';

	return dest;
}

char *buff_fgets_crlf(buffer *b, char *dest, size_t size)
{
	char c, c2;

	int i = 0;
	while(i < size - 1){
		c = buff_getc(b);
		if(c == '\r'){
			c2 = buff_getc(b);
			if(c2 == '\n'){
				dest[i++] = '\r';
				dest[i++] = '\n';
				break;
			} else {
				buff_ungetc(b, c2);
			}
		}

		if(c == EOF){
			if(i == 0) return NULL;
			else break;
		}

		dest[i++] = c;
		if(c == '\n') break;
	}

	dest[i] = '\0';

	return dest;
}
