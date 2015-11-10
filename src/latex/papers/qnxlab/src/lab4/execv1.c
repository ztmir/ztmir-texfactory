#include <stdio.h>
#include <process.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
  printf("Poczatek\n");
  switch(fork())
    {
      case -1:
        printf("Blad utworzenia nowego procesu potomnego\n");
        break;
      case 0: /* proces potomny */
        execl("/bin/ls", "ls", "-a", NULL);
        printf("Blad uruchomienia procesu\n");
        exit(EXIT_FAILURE);
      default: /* proces macierzysty */
        if (wait(NULL) == -1)
          printf("Blad w oczeiwaniu na zakonczenie procesu potomnego\n");
    }
  printf("Koniec\n");
  return 0;
}
