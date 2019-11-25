/* konsument.c */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 1024

int main(int argc, char *argv[])
{
  int offset_r = 0;
  int bytes_read, fildes;
  char buffer[BUFSIZE];

  printf("\tK: Konsument...\n");
  if (argc < 2)
    {
      printf("\tK: Podaj deskrytpor pliku jako argument wywolania.\n");
      return EXIT_FAILURE;
    }
  /* Pobierz deskryptor pliku */
  sscanf(argv[1], "%d", &fildes);
  printf("\tK: Proces PID = %d.\n", getpid());
  printf("\tK: Deskrytptor pliku do odczytu: %d\n", fildes);
  printf("\tK: Odczytuje dane z potoku...\n");
  memset(buffer, '\0', BUFSIZE);
  bytes_read = read(fildes, buffer, BUFSIZE);
  offset_r += bytes_read;
  printf("\tK: *** %s ***\n", buffer);
  printf("\tK: Odczytalem z potoku %d B.\n", offset_r);
  printf("\tK: Zakonczenie procesu konsumenta.\n");

  return EXIT_SUCCESS;
}
