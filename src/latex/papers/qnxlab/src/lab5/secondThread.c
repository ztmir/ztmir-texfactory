#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define STEP 5
#define NUM_THREADS 4

/* Funkcja wykonywana przez watek */
void* start_routine (void* arg)
{
	int i, id;

	id = (int)arg;
	/* Wyswietl nr przekazanego watku i krok */
	for(i = 0; i < STEP; i++)
	{
		printf("\tWatek: %d, step = %d\n", id, i);
		sleep(1);
	}
	pthread_exit(NULL);
}

/* Program glowny */
int main ()
{
	int i, rc;
	pthread_t thread_id[NUM_THREADS];

	for(i = 0; i < NUM_THREADS; i++)
	{
		/* Utworz nowy watek, ktory bedzie wykonywal funkcje start_routine. */
		/* Przekaz argument i do watku */
		printf("Tworze watek nr: %d\n", i);
		rc = pthread_create (&thread_id[i], NULL, &start_routine, (void *)i);
		/* W przypadku, gdy nie uda sie utworzyc watku */
		if (rc)
		{
			printf("Blad. Kod powrotu z funkcji pthread_create(): %d\n", rc);
			exit(1);
		}
	}
	printf("Watek glowny zakonczony. Wyjscie\n");
	pthread_exit(NULL);
}
