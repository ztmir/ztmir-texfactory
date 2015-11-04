/* serwer.c */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_FILE "/tmp/my_fifo_com"
#define BUFSIZE 256

int main(int argc, char *argv[])
{
	int fd, res;
	int open_mode = O_RDONLY;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	char buffer[BUFSIZE];
	int bytes_read;
	pid_t PID = getpid();

	/* Jesli plik FIFO nie istnieje, to utworz */
	if (access(FIFO_FILE, F_OK) == -1)
	{
		printf("Serwer (%d): Tworze plik FIFO.\n",PID);
		res = mkfifo(FIFO_FILE, mode);
		/* Nie udalo sie utworzyc pliku FIFO */
		if (res == -1)
		{
			printf("Serwer (%d): Nie udalo sie utworzyc pliku FIFO.\n",PID);
			exit(EXIT_FAILURE);
		}
	}
	printf("Serwer (%d): otwieram plik FIFO w trybie %s.\n",PID,"O_RDONLY");
	fd = open(FIFO_FILE, open_mode);
	if (fd == -1)
	{
		printf("Serwer (%d): nie udalo sie otworzyc pliku FIFO.\n",PID);
		exit(EXIT_FAILURE);
	}

	printf("Serwer (%d): deskryptor pliku: %d.\n",PID,fd);
	printf("Serwer (%d): odbieram komunikat...\n",PID);

	while(1)
	{
		printf("\tSerwer (%d): ",PID);
		bytes_read = read(fd,buffer,sizeof(buffer));
		if (bytes_read == -1)
		{
			printf("Serwer (%d): nie udalo sie odczytac z pliku FIFO.\n",PID);
			exit(EXIT_FAILURE);
		}
		/* Przetworzenie wiadomosci */
		fprintf(stdout,"%s", buffer);
	}

	return EXIT_SUCCESS;
}
