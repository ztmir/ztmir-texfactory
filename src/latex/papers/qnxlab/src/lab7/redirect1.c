#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int join(char* const com1[], char* const com2[]);

int join(char* const com1[], char* const com2[])
{
  int fd[2], status;

  /* utworz proces Potomny */
  switch(fork())
    {
    case -1:  /* blad */
      perror("Blad przy tworzeniu procesu potomnego 1.\n");
      return EXIT_FAILURE;
    case 0:   /* Potomek */
      break;
    default: /* Rodzic */
      wait(&status);
      return status;
    }
  /* Potomek kontynuuje swoje dzialanie */
  if (pipe(fd) == -1)
    {
      /* Utworzenie potoku nie powiodlo sie */
      perror("M: Nie moge utworzyc potoku.\n");
      return EXIT_FAILURE;
    }
  /* utworz proces Wnuczek */
  switch(fork())
    {
    case -1:  /* blad */
      perror("Blad przy tworzeniu procesu potomnego 2.\n");
      return EXIT_FAILURE;
    case 0:   /* Wnuczek pisze do stdout */
      /* podlacz stdout z wnuczka do wejscia do potoku */
      dup2(fd[1], 1);
      /* zamknij deskryptory */
      close(fd[0]);
      execvp(com1[0], com1);
      perror("Blad uruchomienia procesu\n");
      exit(EXIT_FAILURE);
    default: /* Potomek czyta z stdin */
      /* podlacz stdin z potomka do wyjscia z potoku */
      dup2(fd[0], 0);
      /* zamknij deskryptory */
      close(fd[1]);
      execvp(com2[0], com2);
      perror("Blad uruchomienia procesu\n");
      exit(EXIT_FAILURE);
    }

}

int main(void)
{
  char* const one[] = {"/bin/ls", "-l", "./", (char *)0 };
  char* const two[] = {"/usr/bin/wc", "-w", (char *)0 };

  join(one, two);

  return EXIT_SUCCESS;
}
