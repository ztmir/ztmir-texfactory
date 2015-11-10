#include <stdio.h>
#include <process.h>
#include <unistd.h>
#include <stdlib.h>

#define CHILD 4
#define PARENT 8

int main()
{
  int child_pid;
  int i, j;

  child_pid = fork();

  if (child_pid == -1)
    {
      perror("M: Nie udalo sie utworzyc procesu potomnego...\n");
    }
  else if (child_pid == 0)
    {
      /* proces potomny */
      printf("P: Proces potomny PID = %d\n",getpid());
      for(j = 0; j < CHILD; j++)
      {
        printf("P: pracuje %d sek. ...\n", j);
        sleep(1);
      }
      printf("P: Zakonczenie procesu potomnego\n");
    }
  else
    {
      /* Proces macierzysty */
      printf("M: Proces macierzysty PID = %d\n",getpid());
      for(i = 0; i < PARENT; i++)
      {
        printf("M: pracuje %d sek. ...\n", i);
        sleep(1);
      }
      printf("M: Proces macierzysty o PID=%d zakonczony\n", child_pid);
    }
  return 0;
}
