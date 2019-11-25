/* macierzysty.c */
#include <stdio.h>
#include <process.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
  int pid, i, res, status;
  res = spawnl(P_NOWAIT,"potomny","potomny","10",NULL);
  if (res<0)
    {
      printf("blad wywolania procesu 'potomny'\n");
      exit(0);
    }
  for(i=1;i<=10;i++)
    {
      printf("Macierzysty - krok %d\n",i);
      sleep(1);
    }
  pid = wait(&status);
  printf("Proces %d zakonczony, status %d\n", pid, status);
  return 0;
}
