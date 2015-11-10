/* potomny.c */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  int i;
  for(i=1; i<=atoi(argv[1]); i++)
    {
     printf("Potomny krok: %d\n",i);
     sleep(1);
    }

  exit(EXIT_SUCCESS);
}
