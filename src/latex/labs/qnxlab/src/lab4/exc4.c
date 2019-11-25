#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#define CHILDREN 3

int main()
{
  int i = 0, j, status, t[] =  { 2, 5, 6 };
  pid_t fork_pid, child_pid;

  printf("%d: [i=%d] I'm the root process.\n", getpid(), i);

  for(; i < CHILDREN; ++i)
    {
      fork_pid = fork();
      if(fork_pid != 0)
        {
          /* I'm just become a parent */
          printf("%d: [i=%d] I've just born a child %d.\n", getpid(), i, fork_pid);
          break;
        }
      printf("%d: [i=%d] I'm the new child.\n", getpid(), i);
      /* Expecting my own child in next iteration (if it'll happen) */
    }

  if(i > 0) /* only non-root */
    {
      for(j = 0; j < t[i-1]; ++j)
        {
          printf("%d: [i=%d] starting cycle no. %d\n", getpid(), i, j+1);
          sleep(1);
        }
    }
 
  /* fork_pid != 0 for all processes, except one */
  if(fork_pid != 0)
    {
      /* Wait for my only child... */
      child_pid = wait(&status);
      printf("%d: [i=%d] child %d finished with status %d\n", getpid(), i, child_pid, WEXITSTATUS(status));
    }
  return 0;
}
