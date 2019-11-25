#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define STEP 10

/* Funkcja wykonywana przez watek */
void* start_routine (void* arg)
{
	int i;
	pthread_t id;

	id = pthread_self();

	/* Wyswietl nr watku i krok */
	for(i = 0; i < STEP; i++)
	{
		printf("\tWatek: %d, step = %d\n", id, i);
		sleep(1);
	}
	return NULL;
}

/* Program glowny */
int main ()
{
	int i, rc;
	pthread_t id, thread_id;

	/* Utworz nowy watek, ktory bedzie wykonywal funkcje start_routine. */
	printf("Tworze watek\n");
	rc = pthread_create (&thread_id, NULL, &start_routine, NULL);
	if (rc)
		{
			printf("Blad. Kod powrotu z funkcji pthread_create(): %d\n", rc);
			exit(1);
		}

	id = pthread_self();
	/* Wyswietl nr watku i krok */
	for(i = 0; i < STEP; i++)
	{
		printf("Watek: %d, step = %d\n", id, i);
		sleep(1);
	}
	return 0;
}

