#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
	switch (fork()) {
	case -1:
		perror("fork");
		return 1;
	case 0:
		execlp("ls", "ls", "-l", "/usr", NULL);
		perror("exec: ");
		return 1;
	}
	wait(NULL);
	printf("Commande ls terminée.\n");
	return 0;
}