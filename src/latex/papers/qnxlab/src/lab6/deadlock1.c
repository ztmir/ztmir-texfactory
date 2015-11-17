#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* zainicjalizuj tablice muteksow */
pthread_mutex_t mutex_a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_b = PTHREAD_MUTEX_INITIALIZER;

/* Drukuje info o rezultacie operacji (sukces/blad).
 * Jesli status!=0 (blad) konczy dzialanie programu */
int inform(int status, const char* caller, const char* operation)
{
  if(status != 0)
    {
      printf("%s: %s: error: %s\n", caller, operation, strerror(status));
      exit(EXIT_FAILURE);
    }
  printf("%s: %s: success!\n", caller, operation);
  return status;
}

#define INFORM(cmd) inform(cmd, __func__, #cmd)

/* Watek zamyka muteksy w kolejnosci muteks_a, muteks_b */
void* lock_forward(void* unused)
{
  (void)unused;  /* nie uzywamy 'arg' w funkcji  */
  INFORM(pthread_mutex_lock(&mutex_a));
  sched_yield(); /* zrzeczenie sie CPU na rzecz innych watkow */
  sleep(1);      /* dajemy czas watkowi backward na lock(mutex_b) */
  INFORM(pthread_mutex_lock(&mutex_b));

  printf("lock_forward: zablokowalem mutex_a i mutex_b\n");

  INFORM(pthread_mutex_unlock(&mutex_b));
  INFORM(pthread_mutex_unlock(&mutex_a));
  return NULL;
}

/* Watek zamyka muteksy w kolejnosci muteks_b, muteks_a */
void* lock_backward(void* unused)
{
  (void)unused;  /* nie uzywamy 'arg' w funkcji  */
  INFORM(pthread_mutex_lock(&mutex_b));
  sched_yield(); /* zrzeczenie sie CPU na rzecz innych watkow */
  sleep(1);      /* dajemy czas watkowi forward na lock(mutex_a) */
  INFORM(pthread_mutex_lock(&mutex_a));

  printf("lock_backward: zablokowalem mutex_b i mutex_a\n");

  INFORM(pthread_mutex_unlock(&mutex_a));
  INFORM(pthread_mutex_unlock(&mutex_b));
  return NULL;
}

int main(int argc, char* argv[])
{
  pthread_t forward, backward;

  INFORM(pthread_create(&backward,NULL,lock_backward,NULL));
  INFORM(pthread_create(&forward,NULL,lock_forward,NULL));
  printf("main: utworzono watki.\n");
  printf("main: czekam na zakonczenie watkow.\n");
  INFORM(pthread_join(backward,NULL));
  INFORM(pthread_join(forward,NULL));
  printf("main: koniec programu.\n");

  return EXIT_SUCCESS;
}
