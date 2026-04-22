#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void casser_chocolat(void);
void faire_fondre_chocolat(void);
void separer_blanc_jaune(void);
void melanger_jaunes_choco(void);
void battre_blancs_neige(void);
void incorporer_blancs_neige(void);

int main(void)
{
	int i;
    
    switch(fork()){
        case -1 :
            perror("fork");
            return 1;

        case 0 :
            for(i = 0; i < 6; ++i){
                switch(fork()){
                    case -1:
                        perror("fork");
                        return 1;

                    case 0:
                        separer_blanc_jaune();
                        return 0;
                }
            }

            while(wait(NULL) != -1){
                ;
            }

            battre_blancs_neige();
            return 0;

            default:
                switch(fork()){
                    case -1:
                        perror("fork");
                        return 1;

                    case 0:
                        casser_chocolat();
                        faire_fondre_chocolat();
                        return 0;
                }
    }

    while(wait(NULL) != -1){
        ;
    }

    melanger_jaunes_choco();
    incorporer_blancs_neige();

    printf("PID %d : la mousse est terminée !\n", getpid());

    return 0;
}

void casser_chocolat(void)
{
	printf("PID %d : je casse le chocolat.\n", getpid());
	usleep(200000);
	printf("PID %d : le chocolat est cassé !\n", getpid());
}

void faire_fondre_chocolat(void)
{
	printf("PID %d : je fais fondre le chocolat.\n", getpid());
	usleep(1000000);
	printf("PID %d : le chocolat est fondu !\n", getpid());
}

void separer_blanc_jaune(void)
{
	printf("PID %d : je sépare le blanc d'un jaune.\n", getpid());
	usleep(200000);
	printf("PID %d : un blanc est séparé d'un jaune !\n", getpid());
}

void melanger_jaunes_choco(void)
{
	printf("PID %d : je mélange les jaunes et le chocolat.\n", getpid());
	usleep(200000);
	printf("PID %d : le chocolat est mélangé avec les jaunes !\n", getpid());
}

void battre_blancs_neige(void)
{
	printf("PID %d : je bas les blancs en neige.\n", getpid());
	usleep(600000);
	printf("PID %d : les blancs sont battus en neige !\n", getpid());
}

void incorporer_blancs_neige(void)
{
	printf("PID %d : j'incorpore les blancs en neige.\n", getpid());
	usleep(1000000);
	printf("PID %d : les blancs sont incorporés !\n", getpid());
}
