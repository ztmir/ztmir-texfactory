#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* Zmienna warunkowa */
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
/* Mutex */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* Watek - zarzadca */
void* manager(void *arg)
{
	for(;;) /* Petla nieskonczona */
	{
		sleep(2);
		pthread_mutex_lock(&mutex);
		printf("M: do pracy!\n");
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

/* Watek - wykonawca */
void* worker(void* arg)
{
	const char* prefix = (const char*)arg;
	int i;

	for(;;) /* Petla nieskonczona */
	{
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond ,&mutex); /* Czekaj na sygnal od zarzadcy */
		pthread_mutex_unlock(&mutex);

		/* Wykonaj swoja ciezka prace */
		printf("%s: pracuje ...\n", prefix);
		for(i=0;i<3;i++)
		{
			printf("%s:   |\n", prefix);
			sleep(1);
		}
		printf("%s: skonczylem\n", prefix);
	}
	return NULL;
}

int main(int argc, char* argv[])
{
	/* Identyfikatory watkow - wykonawcow */
	pthread_t workers[2];
	/* Atrybuty watku */
	pthread_attr_t attr;

	/* Inicjalizuj strukture z atrybutami*/
	pthread_attr_init( &attr );

	/* Tworzymy watki-wykonawcow */
	pthread_create(&workers[0], &attr, worker,"\t\tW[1]");
	pthread_create(&workers[1], &attr, worker,"\t\t\t\t\tW[2]");

	/* Sam realizuj zadanie zarzadcy */
	manager(NULL);

	/* Czekaj na zakonczenie watkow - wykonawcow */
	pthread_join(workers[0], NULL);
	pthread_join(workers[1], NULL);

    return 0;
}
