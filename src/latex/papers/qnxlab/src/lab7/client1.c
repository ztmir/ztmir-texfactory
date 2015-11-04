/* klient.c */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_FILE "/tmp/my_fifo_com"
#define BUFSIZE 256

int main(int argc, char *argv[])
{
	int fd;
	int open_mode = O_WRONLY;
	char buffer[BUFSIZE];
	int bytes_written;
	pid_t PID = getpid();

	printf("Klient (%d): otwieram plik FIFO w trybie %s.\n",PID,"O_WRONLY");
	fd = open(FIFO_FILE, open_mode);

	if (fd == -1)
	{
		printf("Klient (%d): nie udalo sie otworzyc pliku FIFO.\n",PID);
		exit(EXIT_FAILURE);
	}
	printf("Klient (%d): deskryptor pliku: %d.\n",PID,fd);
	printf("Klient (%d): wysylam komunikat...\n",PID);

	while(feof(stdin) == 0)
	{
		printf("Klient (%d): ",PID);
		fgets(buffer, BUFSIZE, stdin);
//		fprintf(stdout, "K: %s\n", buffer);
		bytes_written = write(fd,buffer,sizeof(buffer));
		if (bytes_written == -1)
		{
			printf("Klient (%d): nie udalo sie zapisac do pliku FIFO.\n",PID);
			exit(EXIT_FAILURE);
		}
	}

	return EXIT_SUCCESS;
}
