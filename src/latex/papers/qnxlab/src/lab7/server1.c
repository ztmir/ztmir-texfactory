/* serwer.c */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_FILE "/tmp/my_fifo_com"
#define BUFSIZE 256

int main(void)
{
  int fd, res;
  int bytes_read;
  char buffer[BUFSIZE] = { '\x0' };
  pid_t pid = getpid();

  /* Jesli plik FIFO nie istnieje, to utworz */
  if (access(FIFO_FILE, F_OK) == -1)
    {
      printf("Serwer (%d): Tworze plik FIFO.\n", pid);
      res = mkfifo(FIFO_FILE, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
      /* Nie udalo sie utworzyc pliku FIFO */
      if (res == -1)
        {
          printf("Serwer (%d): Nie udalo sie utworzyc pliku FIFO.\n", pid);
          exit(EXIT_FAILURE);
        }
    }
  printf("Serwer (%d): otwieram plik FIFO w trybie %s.\n", pid, "O_RDONLY");
  fd = open(FIFO_FILE, O_RDONLY);
  if (fd == -1)
    {
      printf("Serwer (%d): nie udalo sie otworzyc pliku FIFO.\n", pid);
      exit(EXIT_FAILURE);
    }

  printf("Serwer (%d): deskryptor pliku: %d.\n", pid, fd);
  printf("Serwer (%d): odbieram komunikat...\n", pid);

  do
    {
      printf("\tSerwer (%d): ", pid);
      bytes_read = read(fd, buffer, sizeof(buffer) - 1);
      if (bytes_read == -1)
        {
          printf("Serwer (%d): nie udalo sie odczytac z pliku FIFO.\n", pid);
          exit(EXIT_FAILURE);
        }
      /* Przetworzenie wiadomosci */
      printf("%s", buffer);
    }
  while(bytes_read > 0);

  printf("Serwer (%d): koniec strumienia.\n", pid);

  return EXIT_SUCCESS;
}
