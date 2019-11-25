/* klient.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_FILE "/tmp/my_fifo_com"
#define BUFSIZE 256

int main(void)
{
	int fd;
	int bytes_written;
	char buffer[BUFSIZE] = { '\x0' };
	pid_t pid = getpid();

	printf("Klient (%d): otwieram plik FIFO w trybie %s.\n", pid, "O_WRONLY");
	fd = open(FIFO_FILE, O_WRONLY);

	if(fd == -1)
    {
      printf("Klient (%d): nie udalo sie otworzyc pliku FIFO.\n", pid);
      exit(EXIT_FAILURE);
    }
	printf("Klient (%d): deskryptor pliku: %d.\n", pid, fd);
	printf("Klient (%d): wpisz komunikat\n", pid);

	while(feof(stdin) == 0)
    {
      printf("Klient (%d): ", pid);
      fgets(buffer, BUFSIZE - 1, stdin);
      /* fprintf(stdout, "K: %s\n", buffer); */
      bytes_written = write(fd, buffer, strlen(buffer));
      if (bytes_written == -1)
        {
          printf("Klient (%d): nie udalo sie zapisac do pliku FIFO.\n", pid);
          exit(EXIT_FAILURE);
        }
    }

	return EXIT_SUCCESS;
}
