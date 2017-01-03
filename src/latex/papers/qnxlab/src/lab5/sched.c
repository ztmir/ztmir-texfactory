#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define STEP 5

/* Funkcja wykonywana przez watek */
void* start_routine (void* arg)
{
	int i;

	/* Wyswietl nr przekazanego watku i krok */
	for(i = 0; i < STEP; i++)
	{
		printf("\tStep = %d\n", i);
		sleep(1);
	}
	pthread_exit(NULL);
}

/* The main program. */
int main ()
{
	int rc;
	pthread_t thread_id;
	void* status;
	pthread_attr_t attr;
	struct sched_param param;	/* struktura opisujaca parametry szeregowania */
	int policy;

	/* pobranie parametrow procesu macierzystego */
	sched_getparam(0, &param);

	printf("Priorytet ustawiony przy starcie procesu (watku glownego) %d.\n", param.sched_priority);

	/* Zainicjalizowanie struktury atrybutow */
	pthread_attr_init(&attr);
	/* Ustawienie parametru PTHREAD_EXPLICIT_SCHED */
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	/* Pobranie strategii szeregowania */
	pthread_attr_getschedpolicy(&attr, &policy);
	/* Pobranie parametrow szeregowania */
	pthread_attr_getschedparam(&attr, &param);

	/* Wyswietl atrybuty */
	printf("Domyslna strategia %s, priorytet: %d\n", policy == SCHED_FIFO ? "FIFO" :
	( policy == SCHED_RR ? "ROUND ROBIN" :
	( policy == SCHED_SPORADIC ? "SPORADIC" :
	(policy == SCHED_OTHER ? "OTHER" :
	"unknown"))), param.sched_priority);

	/* Ustawienie strategii szeregowania */
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	param.sched_priority = 8;
	/* Ustawienie parametrow szeregowania */
	pthread_attr_setschedparam(&attr, &param);

	/* Pobranie strategii szeregowania */
	pthread_attr_getschedpolicy(&attr, &policy);
	/* Pobranie parametrow szeregowania */
	pthread_attr_getschedparam(&attr, &param);

	/* Wyswietl atrybuty */
	printf("Domyslna strategia %s, priorytet: %d\n", policy == SCHED_FIFO ? "FIFO" :
	( policy == SCHED_RR ? "ROUND ROBIN" :
	( policy == SCHED_SPORADIC ? "SPORADIC" :
	(policy == SCHED_OTHER ? "OTHER" :
	"unknown"))), param.sched_priority);

	/* Utworz nowy watek, z nowymi atrybutami. */
	printf("Tworze watek z nowymi atrybutami: \n");
	rc = pthread_create (&thread_id, &attr, &start_routine, NULL);
	/* W przypadku, gdy nie uda sie utworzyc watku */
	if (rc)
	{
		printf("Blad. Kod powrotu z funkcji pthread_create(): %d\n", rc);
		exit(1);
	}

	/* Zwolnienie atrybutow */
	pthread_attr_destroy(&attr);

	/* Oczekiwanie na watek potomny */
	rc = pthread_join(thread_id, &status);
	if (rc)
	{
		printf("Blad. Kod powrotu z funkcji pthread_join(): %d\n", rc);
		exit(1);
	}

	printf("Watek glowny dolaczyl watek potomny.\n");
	printf("Watek glowny zakonczony. Wyjscie.\n");
	pthread_exit(NULL);
}
