#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSZ 256
int main(void)
{
	int fd = open("lol.txt", O_RDONLY);
	ssize_t n; /* signed size type pour pouvoir accueillir -1 */
	char buffer[BUFSZ];

	if (fd < 0) {
		perror("open");
		return 1;
	}

	printf("Descripteur de fichier : %d\n", fd);
	
	n = read(fd, buffer, 1); /* lire au maximum 1 octet */
	printf("n = %ld\n", n);
	printf("octet 0 du fichier : %c\n", buffer[0]);

	n = read(fd, buffer, 1); /* lire au maximum 1 octet */
	printf("n = %ld\n", n);
	printf("octet 1 du fichier : %c\n", buffer[0]);

	close(fd);
	return 0;
}
