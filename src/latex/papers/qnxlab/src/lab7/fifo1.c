/* fifo.c */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_FILE "/tmp/my_fifo"

int main(int argc, char *argv[])
{
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
  int res, open_mode = 0;

  if (argc < 2 )
    {
      printf("Jako argument wywolania podaj flagi:\nO_RDONLY, O_WRONLY lub O_RDWR.\n");
      printf("Np.: ./fifo O_RDONLY\n");
      printf("Np.: ./fifo O_WRONLY\n");
      exit(EXIT_FAILURE);
    }

  if (strncmp(argv[1], "O_RDONLY", 8) == 0)
    open_mode = O_RDONLY;
  else if (strncmp(argv[1], "O_WRONLY", 8) == 0)
    open_mode = O_WRONLY;
  else if (strncmp(argv[1], "O_RDWR", 6) == 0)
    open_mode = O_RDWR;
  else
    {
      fprintf(stderr, "error: nieprawidlowa wartosc argv[1]: %s\n", argv[1]);
      exit(EXIT_FAILURE);
    }
  /* open_mode |= O_NONBLOCK; */

  /* Jesli plik FIFO nie istnieje, to go utworz */
  if (access(FIFO_FILE, F_OK) == -1)
    {
      res = mkfifo(FIFO_FILE, mode);
      /* Nie udalo sie utworzyc pliku FIFO */
      if (res == -1)
        {
          fprintf(stderr, "error: nie udalo sie utworzyc pliku FIFO.\n");
          exit(EXIT_FAILURE);
        }
    }
  printf("Proces %d: otwiera plik FIFO w trybie %s.\n", getpid(), argv[1]);
  res = open(FIFO_FILE, open_mode);
  printf("Proces %d: deskryptor pliku: %d.\n", getpid(), res);
  printf("Proces %d: pracuje...\n", getpid());
  sleep(5);
  if (res != -1)
    close(res);
  printf("Proces %d: zakonczyl swoje dzialanie.\n", getpid());

  return EXIT_SUCCESS;
}
