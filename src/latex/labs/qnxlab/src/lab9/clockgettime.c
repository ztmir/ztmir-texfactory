/* zegar1.c */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MILIARD  1000000000L;

int main(int argc, char** argv)
{
  struct timespec start, stop;
  double accum;

  if(argc < 2) {
    fprintf(stderr, "brakujacy parametr\n");
    return EXIT_FAILURE;
  }

  if(clock_gettime(CLOCK_REALTIME, &start) == -1) {
    perror("clock_gettime");
    return EXIT_FAILURE;
  }

  system(argv[1]);

  if(clock_gettime(CLOCK_REALTIME, &stop) == -1) {
    perror("clock_gettime");
    return EXIT_FAILURE;
  }

  accum = (stop.tv_sec - start.tv_sec)
    + (double)(stop.tv_nsec - start.tv_nsec)
    / (double)MILIARD;
  printf("%f\n", accum);
  return EXIT_SUCCESS;
}
