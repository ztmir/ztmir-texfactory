#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFSIZE 32
#define MIN(a,b) ( (a < b) ? a : b)

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
  char buffer[BUFSIZE];
  ssize_t bytes_written, bytes_read;
  ssize_t offset_w = 0;
  ssize_t offset_r = 0;
  pid_t child_pid;
  int status;

  printf("M: Tworze potok nienazwany...\n");
  pipe_status = pipe(fildes);
  /* Utworzenie potoku nie powiodlo sie */
  if (pipe_status == -1)
    {
      perror("M: Nie moge utworzyc potoku.\n");
      return EXIT_FAILURE;
    }

  child_pid = fork();

  if (child_pid == -1)
    {
      perror("M: Nie udalo sie utworzyc procesu potomnego...\n");
    }
  else if (child_pid == 0)
    {
      /* proces potomny */
      printf("\tP: Proces potomny PID = %d.\n",getpid());
      printf("\tP: Pracuje...\n");
      printf("\tP: Zamykam deskryptor zapisu pliku.\n");
      close(fildes[1]);
      printf("\tP: Odczytuje dane z potoku...\n");
      bytes_read = read(fildes[0],buffer,MIN(size1,BUFSIZE));
      offset_r += bytes_read;
      printf("\tP: %.*s\n",MIN(size1,BUFSIZE),buffer);
      bytes_read = read(fildes[0],buffer,MIN(size2,BUFSIZE));
      offset_r += bytes_read;
      printf("\tP: %.*s\n",MIN(size2,BUFSIZE),buffer);
      bytes_read = read(fildes[0],buffer,MIN(size3,BUFSIZE));
      offset_r += bytes_read;
      printf("\tP: %.*s\n",MIN(size3,BUFSIZE),buffer);
      printf("\tP: Odczytalem z potoku %d B.\n", (int)offset_r);
      printf("P: Zakonczenie procesu potomnego.\n");
      exit(EXIT_SUCCESS);
    }
  else
    {
      /* Proces macierzysty */
      printf("M: Proces macierzysty PID = %d.\n",getpid());
      printf("M: Pracuje ...\n");
      /* Utworzenie potoku powiodlo sie */
      printf("M: Utworzylem potok.\n");
      size = fpathconf(fildes[1],_PC_PIPE_BUF);
      printf("M: Rozmiar bufora: %d B\n",size);
      printf("M: Zamykam deskryptor odczytu pliku.\n");
      close(fildes[0]);
      printf("M: Zapisuje dane do potoku...\n");
      printf("M: %s\n",msg1);
      bytes_written = write(fildes[1],msg1,size1);
      offset_w += bytes_written;
      printf("M: %s\n",msg2);
      bytes_written = write(fildes[1],msg2,size2);
      offset_w += bytes_written;
      printf("M: %s\n",msg3);
      bytes_written = write(fildes[1],msg3,size3);
      offset_w += bytes_written;
      printf("M: Zapisalem do potoku %d B.\n", (int)offset_w);
      printf("M: Czekam na potomny...\n");
      child_pid = wait(&status);
      printf("M: Proces potomny o PID=%d zakonczony; status: %d.\n", child_pid, WEXITSTATUS(status));
    }

  printf("M: Koniec programu.\n");
  return EXIT_SUCCESS;
}
