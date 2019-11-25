#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 5

char* timenow(void);
char* timenow(void)
{
  /* Pobierz biezacy czas */
  time_t now = time(NULL);
  /* Przekonwertuj na string */
  return asctime(localtime(&now));
}

int main (int argc, char* argv[])
{
  int i, fd, offset = 0;
  const char* mytime;
  const char* path;
  ssize_t bytes_written;
  /* Atrybuty dostepu do pliku. */
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

  if (argc < 2)
    {
      printf("Podaj nazwe pliku jako argument wywolania.\n");
      return EXIT_FAILURE;
    }
  path = argv[1];
  printf("Tworze plik o nazwie: %s\n", path);
  /* Utworz plik */
  fd = open (path, O_WRONLY | O_CREAT, mode);
  /* fd = creat( path, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH ); */

  printf("Zapisuje dane do pliku");
  /* Zapisz do pliku */
  for(i = 0; i < SIZE; i++)
    {
      /* Pobierz czas */
      mytime = timenow();
      bytes_written = write (fd, mytime, strlen (mytime));
      offset = offset + bytes_written;
      printf(".\n");
      sleep(1);
    }

  printf("Zapisano %d bajtow\n", offset);
  printf("Zamkniecie pliku.\n");
  /* Zamknij plik. */
  close(fd);
  return EXIT_SUCCESS;
}
