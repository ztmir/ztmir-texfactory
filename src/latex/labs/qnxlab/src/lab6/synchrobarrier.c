
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int a = -1234,b = 4321;  /* Wartosci przed obliczeniami */
/* Obiekt reprezentujacy bariere */
pthread_barrier_t barrier;
/* Inicjalizacja statyczna */
/* pthread_barrier_t barrier = PTHREAD_BARRIER_INITIALIZER(2); */

/* Procedura wykonywana przez watek */
void* start(void* arg)
{
	int d;

	printf("\t\t\t2: Obliczam b ...\n");
	sleep(2); /* Obliczenia zmudne, trwaja 2 sekundy */
	b = 1;
	printf("\t\t\t2: b = %d\n", b);
	printf("\t\t\t2: Obliczam d = a * b\n");

	pthread_barrier_wait(&barrier);    /* Czekaj na barierze*/
	d = a * b;
	printf("\t\t\t2: d = %d\n", d);

	/* Spodziewamy sie a=1 i b=1, wiec d = a * b = 1 * 1 = 1 */
	if (d == 1)
	{
		printf("\t\t\t2: Obliczenia przeprowadzone prawidlowo.\n");
	}
	else
	{
		printf("\t\t\t2: Rety, nie wiem co sie stalo!\n");
	}
	return NULL;
}

int main(int argc, char* argv[])
{
	pthread_t start_id;   /* identyfikator tworzonego watku */
	pthread_attr_t attr;  /* Atrybuty watku */

	int c; /* Dane lokalne watku glownego */

	/* Inicjalizuj strukture z atrybutami*/
	pthread_attr_init( &attr );

	/* Inicjalizuj bariere na dwa watki */
	pthread_barrier_init(&barrier, NULL, 2);

	/* Utworz nowy watek (nazwijmy go "start") */
	pthread_create(&start_id, &attr, start, NULL);

	printf("1: Obliczam a ...\n");
	sleep(1); /* Obliczenia zmudne, trwaja 1 sekunde */
	a = 1;
	printf("1: a = %d\n", a);
	printf("1: Obliczam c = a + b\n");

	pthread_barrier_wait(&barrier);    /* Czekaj na barierze*/
	c = a + b;
	printf("1: c = %d\n", c);

	/* Spodziewamy sie a=1 i b=1, wiec c = a + b = 1 + 1 = 2 */
	if (c == 2)
	{
		printf("1: Obliczenia przeprowadzone prawidlowo.\n");
	}
	else
	{
		printf("1: Rety, nie wiem co sie stalo!\n");
	}

	/* Czekaj na zakonczenie watku "start" */
	pthread_join(start_id, NULL);

	return 0;
}
