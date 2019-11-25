#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(void)
{
  struct timespec stime;

  if(clock_gettime(CLOCK_REALTIME, &stime) == -1) {
    perror("getclock");
    return EXIT_FAILURE;
  }
  /* Dodaj jeden dzien */
  stime.tv_sec += (60*60)*24L;
  stime.tv_nsec = 0;
  if(clock_settime(CLOCK_REALTIME, &stime) == -1) {
    perror("setclock");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
