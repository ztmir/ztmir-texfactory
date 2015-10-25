#include <stdio.h>
#include <process.h>
#include <unistd.h>
#include <stdlib.h>

#define CHILD 8
#define PARENT 4

int main()
{
	int child_pid;
	int i, j;
	int status;

	child_pid = fork();

	if (child_pid != 0)
	{
		/* Proces macierzysty */
		printf("M: Proces macierzysty PID = %d\n",getpid());
		for(i = 0; i < PARENT; i++)
		{
			printf("M: pracuje %d sek. ...\n", i);
			sleep(1);
		}
		printf("M: Czekam na potomny...\n");
		child_pid = wait(&status);
		printf("M: Proces potomny o PID=%d zakonczony; status: %d\n", child_pid, WEXITSTATUS(status));

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
		exit(EXIT_SUCCESS);
	}
	else if (child_pid == -1)
	{
		perror("M: Nie udalo sie utworzyc procesu potomnego...\n");
	}
    return 0;
}

