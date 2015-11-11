#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <process.h>

int main(int argc, char *argv[]) {

  pid_t pid, ppid;
  struct sched_param param; /* struktura opisujaca parametry szeregowania */
  int sched;

  pid = getpid();
  ppid = getppid();
  printf("Proces potomny PID: %d\n", pid);
  printf("Proces macierzysty PPID: %d\n", ppid);
  /* pobranie parametrow */
  sched_getparam(pid, &param);

  printf("Priorytet ustawiony przy starcie procesu %d.\n", param.sched_priority);
  printf("Biezacy priorytet procesu %d.\n", param.sched_curpriority);

  sched = sched_getscheduler(pid);
  printf("Strategia szeregowania: %d\n", sched);

  param.sched_priority = 9;
  sched_setparam(pid, &param);
  sched_setscheduler(pid, SCHED_FIFO, &param);

  sched_getparam(pid, &param);

  printf("Nowy priorytet procesu %d.\n", param.sched_priority);
  printf("Biezacy priorytet procesu %d.\n", param.sched_curpriority);

  sched = sched_getscheduler(pid);
  printf("Nowa strategia szeregowania: %d\n", sched);

  return EXIT_SUCCESS;
}
