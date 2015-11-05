#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/* zainicjalizuj tablice muteksow */
pthread_mutex_t mutex_a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_b = PTHREAD_MUTEX_INITIALIZER;

/* Jesli 1, to blokujemy drugi muteks przez pthread_mutex_trylock
 * Jesli 0, to blokujemy drugi muteks przez pthread_mutex_lock */
int asynchron = 0;

/* Funkcja raportuja bledy i status */
void err_report(int status, char* text)
{
	printf("BLAD: %s.\n\t%s\n", text, strerror(status));
	exit(EXIT_FAILURE);
}

/* Watek zamyka muteksy w kolejnosci muteks_a, muteks_b */
void* lock_forward(void* arg)
{
	int status;

	/* zajecie mutex_a */
	status = pthread_mutex_lock(&mutex_a);

	if (status)
		err_report(status, "Lock_forward: lock(&mutex_a)");
	else
		printf("Lock_forward: lock(&mutex_a)\n");
	/* zrzeczenie sie procesora na rzecz innych watkow */
	sched_yield();

	if (asynchron)
	{
		status = pthread_mutex_trylock(&mutex_b);
		printf("Lock_forward: trylock(&mutex_b)\n");
	}
	else
	{
		status = pthread_mutex_lock(&mutex_b);
		printf("Lock_forward: lock(&mutex_b)\n");
	}
	/* mutex_b jest zajety */
	if (status == EBUSY)
	{
		/* odblokowuje mutex_a */
		status = pthread_mutex_unlock(&mutex_a);
		if (status)
			err_report(status, "Lock_forward: unlock(&mutex_a)");
		else
			printf("Lock_forward: unlock(&mutex_a)\n");
	}
	else
	{
		if (status)
			err_report(status, "Lock_forward: mutex_b nie jest zajety");
	}
	sleep(1);

	printf("Lock_forward: posiadam mutex_b i mutex_a\n");
	/* Watek ma wszystkie muteksy */
	pthread_mutex_unlock(&mutex_b);
	pthread_mutex_unlock(&mutex_a);
	printf("Lock_forward: unlock(&mutex_b), unlock(&mutex_a)\n");
	pthread_exit(NULL);
	return NULL;
}

/* Watek zamyka muteksy w kolejnosci muteks_b, muteks_a */
void* lock_backward(void* arg)
{
	int status;

	/* zajecie mutex_b */
	status = pthread_mutex_lock(&mutex_b);

	if (status)
		err_report(status, "Lock_backward: lock(&mutex_b)");
	else
		printf("Lock_backward: lock(&mutex_b)\n");
	/* zrzeczenie sie procesora na rzecz innych watkow */
	sched_yield();

	if (asynchron)
	{
		status = pthread_mutex_trylock(&mutex_a);
		printf("Lock_backward: trylock(&mutex_a)\n");
	}
	else
	{
		status = pthread_mutex_lock(&mutex_a);
		printf("Lock_backward: lock(&mutex_a)\n");
	}

	/* mutex_a jest zajety */
	if (status == EBUSY)
	{
		/* odblokowuje mutex_b */
		status = pthread_mutex_unlock(&mutex_b);
		if (status)
			err_report(status, "Lock_backward: unlock(&mutex_b)");
		else
			printf("Lock_backward: unlock(&mutex_b)\n");
	}
	else
	{
		if (status)
			err_report(status, "Lock_backward: mutex_a nie jest zajety");
	}
	sleep(1);

	/* Watek ma wszystkie muteksy */
	printf("Lock_backward: posiadam mutex_a i mutex_b\n");
	pthread_mutex_unlock(&mutex_a);
	pthread_mutex_unlock(&mutex_b);
	printf("Lock_backward: unlock(&mutex_a), unlock(&mutex_b)\n");

	pthread_exit(NULL);
	return NULL;
}


int main(int argc, char* argv[])
{
	pthread_t forward, backward;
	int status;
	void* status2;

	status = pthread_create(&backward, NULL, lock_backward, NULL);
	if (status)
		err_report(status, "Utworzenie watku lock_backward");

	status = pthread_create(&forward, NULL, lock_forward, NULL);
	if (status)
		err_report(status, "Utworzenie watku lock_forward");

	status = pthread_join(backward, &status2);
	if (status)
		err_report(status, "Dolaczenie watku backward");
	status = pthread_join(forward, &status2);
	if (status)
		err_report(status, "Dolaczenie watku backward");

	printf("Dolaczanie watku backward i forward\n");
	printf("Zakonczenie programu.\n");
    	pthread_exit(NULL);
    	return 0;
}
