#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/* Dane wspolne */
int b;

void* start(void* arg)
{
	/* zainicjalizuj generator liczb losowych */
	srand((unsigned int)(time(NULL)+20));
	/* wygeneruj liczbe z zakresu 1 do 3 */
	int number = rand() % 3 + 1;
	printf("\t\t\t\t2: Pracuje %d sek. ...\n",number);
	sleep(number);
	printf("\t\t\t\t2: Modyfikuje b\n");
	b = 2;
	printf("\t\t\t\t2: b = %d\n", b);
	return NULL;
}

int main(int argc, char* argv[])
{
	pthread_t start_id;   /* Identyfikator tworzonego watku */
	pthread_attr_t attr;  /* Atrybuty watku */
	int a, c; /* Dane lokalne watku glownego */
	int number; /* Przechowuje liczbe losowa */

	/* zainicjalizuj generator liczb losowych */
	srand((unsigned int)time(NULL));
	/* wygeneruj liczbe z zakresu 1 do 3 */
	number = rand() % 3 + 1;

	/* Inicjalizuj strukture z atrybutami*/
	pthread_attr_init( &attr );
	/* Utworz nowy watek (nazwijmy go "start") */
	pthread_create(&start_id, &attr, start, NULL);

	/* Inicjalizuj "a" i "b" */
	printf("1: Modyfikuje b\n");
	a = 1; b = 1;
	printf("1: a = %d, b = %d\n",a, b);

	printf("1: Pracuje %d sek. ... \n",number);
	sleep(number);

	/* Oblicz "c" i wydrukuj wynik */
	c = a + b;
	printf("1: c = a + b = %d\n",c);

	if (c == 2)
	{
		printf("1: Obliczenia przeprowadzone prawidlowo.\n");
	}
	else
	{
		printf("1: Niepoprawne obliczenia!\n");
	}
	/* Czekaj na zakonczenie watku "start" */
	pthread_join(start_id, NULL);

	return 0;
}
