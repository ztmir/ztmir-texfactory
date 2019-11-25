#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <memory.h>

int main (int argc, char* argv[])
{
  int buf_size, offset = 0;
  int fd1, fd2;
  char* buffer;
  ssize_t bytes_read, bytes_written;
  /* Sciezki dostepu i nazwy plikow */
  char const *path1, *path2;
  /* Atrybuty dostepu do pliku. */
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

  if (argc < 4)
    {
      printf("Podaj nazwy plikow jako argument wywolania oraz rozmiar bufora.\n");
      printf("Przyklad wywolania:\n\t./program plik1 plik2 150\n");
      return EXIT_FAILURE;
    }

  path1 = argv[1];
  path2 = argv[2];
  buf_size = atoi(argv[3]);
  buffer = (char*)malloc(buf_size * sizeof(char));

  /* Otworz plik 1 */
  printf("Otwieram plik o nazwie: %s\n", path1);
  fd1 = open (path1, O_RDONLY, mode);
  if (fd1 < 0)
    {
      printf("Nie moge otworzyc pliku.\n");
      return EXIT_FAILURE;
    }

  /* Utworz plik 2 */
  printf("Tworze plik o nazwie: %s\n", path2);
  /* fd2 = open (path2, O_WRONLY | O_CREAT | O_TRUNC, mode); */
  fd2 = creat(path2, mode);
  if (fd2 < 0)
    {
      printf("Nie moge otworzyc pliku.\n");
      return EXIT_FAILURE;
    }

  printf("Czytam dane z pliku %s i zapisuje do pliku %s\n", path1, path2);
  do
    {
      bytes_read = read(fd1, buffer, buf_size);
      bytes_written = write(fd2, buffer, bytes_read);
      offset = offset + bytes_written;
    }
  while (bytes_read == buf_size);

  printf("Zapisano %d bajtow\n", offset);
  printf("Zamkniecie pliku.\n");
  /* Zamknij plik. */
  close(fd1);
  close(fd2);
  /* Zwolnij pamiec bufora */
  free(buffer);
  return EXIT_SUCCESS;
}
