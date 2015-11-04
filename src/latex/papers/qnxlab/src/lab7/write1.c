#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define Size 5

char* timenow()
{
	/* Pobierz biezacy czas */
	time_t now = time(NULL);
	/* Przekonwertuj na string */
	char* mytime = asctime (localtime (&now));
	return mytime;
}

int main (int argc, char* argv[])
{
	int i;
	char* mytime;
	ssize_t bytes_written;
	int offset = 0;

	if (argc < 2)
	{
		printf("Podaj nazwe pliku jako argument wywolania.\n");
		return EXIT_FAILURE;
	}
	/* Sciezki dostepu i nazwy plikow */
	char* path = argv[1];
	printf("Tworze plik o nazwie: %s\n", path);
	/* Atrybuty dostepu do pliku. */
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	/* Utworz plik */
	int fd = open (path, O_WRONLY | O_CREAT, mode);
	// int fd = creat( path, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH );

	printf("Zapisuje dane do pliku");
	/* Zapisz do pliku */
	for(i = 0; i < Size; i++)
	{
		/* Pobierz czas */
		mytime = timenow();
		bytes_written = write (fd, mytime, strlen (mytime));
		offset = offset + bytes_written;
		printf(".\n");
		sleep(1);
	}

	printf("Zapisano %d bajtow\n", offset);
	printf("Zamkniecie pliku.\n");
	/* Zamknij plik. */
	close(fd);
	return EXIT_SUCCESS;
}
