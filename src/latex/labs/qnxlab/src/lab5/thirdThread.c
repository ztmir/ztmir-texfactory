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
	pthread_exit((void *)id);
}

/* The main program. */
int main ()
{
	int i, rc;
	pthread_t thread_id[NUM_THREADS];
	void* status;

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
	/* Oczekiwanie na watki potomne */
	for(i = 0; i < NUM_THREADS; i++)
	{
		rc = pthread_join(thread_id[i], &status);
		if (rc)
		{
			printf("Blad. Kod powrotu z funkcji pthread_join(): %d\n", rc);
			exit(1);
		}
		printf("Watek glowny dolaczyl watek %d o statusie %d\n", i, (int)status);
	}

	printf("Watek glowny zakonczony. Wyjscie.\n");
	pthread_exit(NULL);
}
