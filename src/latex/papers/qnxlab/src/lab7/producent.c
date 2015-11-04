/* producent .c */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <process.h>

#define BUFSIZE 1024
#define MIN(a,b) ( (a < b) ? a : b)

char *msg = "Hello!Wiadomosc z potoku...Koniec.";

int main(int argc, char *argv[])
{
	int msg_size = strlen(msg);
	int fildes[2];
	int pipe_status, size;
	ssize_t bytes_written;
	ssize_t offset_w = 0;
	pid_t child_pid;
	char fd[BUFSIZE];

	printf("M: Tworze potok nienazwany...\n");
	pipe_status = pipe(fildes);
	/* Utworzenie potoku nie powiodlo sie */
	if (pipe_status == -1)
	{
		perror("M: Nie moge utworzyc potoku.\n");
		return EXIT_FAILURE;
	}

	child_pid = fork();

	if (child_pid != 0)
	{
		/* Proces macierzysty */
		printf("M: Proces macierzysty PID = %d.\n",getpid());
		/* Utworzenie potoku powiodlo sie */
		printf("M: Utworzylem potok.\n");
		size = fpathconf(fildes[1],_PC_PIPE_BUF);
		printf("M: Rozmiar bufora: %d B\n",size);
		printf("M: Zamykam deskryptor odczytu pliku.\n");
		close(fildes[0]);
		printf("M: Zapisuje dane do potoku...\n");
		printf("M: %s\n",msg);
		bytes_written = write(fildes[1],msg,msg_size);
		offset_w += bytes_written;
		printf("M: Zapisalem do potoku %d B.\n", offset_w);
    }
	else if (child_pid == 0)
	{
		/* proces potomny */
		printf("\tP: Proces potomny PID = %d.\n",getpid());
		printf("\tP: Zamykam deskryptor zapisu pliku.\n");
		close(fildes[1]);
		printf("\tP: Deskryptor pliku do odczytu: %d\n",fildes[0]);
		memset(fd,'\0',sizeof(fd));
		sprintf(fd,"%d",fildes[0]);
		execl("konsument", "konsument", fd, (char *)0);
		printf("\tP: Blad uruchomienia procesu\n");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == -1)
	{
		perror("M: Nie udalo sie utworzyc procesu potomnego...\n");
	}

	printf("M: Koniec programu.\n");
	return EXIT_SUCCESS;
}
