#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 32
#define MIN(a, b) ( (a < b) ? a : b)

char *msg1 = "Hello!";
char *msg2 = "Wiadomosc z potoku...";
char *msg3 = "Koniec.";

int main(void)
{
  int size1 = strlen(msg1);
  int size2 = strlen(msg2);
  int size3 = strlen(msg3);
  int fildes[2];
  int pipe_status, size;
  char buffer[BUFSIZE] = { '\x0' };
  ssize_t bytes_written, bytes_read;
  ssize_t offset_w = 0;
  ssize_t offset_r = 0;

  printf("Tworze potok nienazwany...\n");
  pipe_status = pipe(fildes);
  /* Utworzenie potoku nie powiodlo sie */
  if (pipe_status == -1)
    {
      perror("Nie moge utworzyc potoku\n");
      return EXIT_FAILURE;
    }
  /* Utworzenie potoku powiodlo sie */
  printf("Utworzylem potok.\n");
  size = fpathconf(fildes[1], _PC_PIPE_BUF);
  printf("Rozmiar bufora: %d B\n", size);
  printf("Zapisuje dane do potoku...\n");
  printf("\t%s\n", msg1);
  bytes_written = write(fildes[1], msg1, size1);
  offset_w += bytes_written;
  printf("\t%s\n", msg2);
  bytes_written = write(fildes[1], msg2, size2);
  offset_w += bytes_written;
  printf("\t%s\n", msg3);
  bytes_written = write(fildes[1], msg3, size3);
  offset_w += bytes_written;
  printf("Zapisalem do potoku %d B\n", (int)offset_w);
  printf("Odczytuje dane z potoku...\n");
  bytes_read = read(fildes[0], buffer, MIN(size1, BUFSIZE));
  offset_r += bytes_read;
  printf("\t%.*s\n", MIN(size1, BUFSIZE), buffer);
  bytes_read = read(fildes[0], buffer, MIN(size2, BUFSIZE));
  offset_r += bytes_read;
  printf("\t%.*s\n", MIN(size2, BUFSIZE), buffer);
  bytes_read = read(fildes[0], buffer, MIN(size3, BUFSIZE));
  offset_r += bytes_read;
  printf("\t%.*s\n", MIN(size3, BUFSIZE), buffer);
  printf("Odczytalem z potoku %d B\n", (int)offset_r);
  printf("Koniec programu\n");
  return EXIT_SUCCESS;
}
