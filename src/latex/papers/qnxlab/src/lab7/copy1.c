#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
	if (argc < 4)
	{
		printf("Podaj nazwy plikow jako argument wywolania oraz rozmiar bufora.\n");
		printf("Przyklad wywolania:\n\t./program plik1 plik2 150");
		return EXIT_FAILURE;
	}
	int buf_size = atoi(argv[3]);
	int offset = 0;
	char buffer[buf_size];
	ssize_t bytes_read, bytes_written;
	/* Sciezki dostepu i nazwy plikow */
	char* path1 = argv[1];
	char* path2 = argv[2];
	printf("Otwieram plik o nazwie: %s\n", path1);
	/* Atrybuty dostepu do pliku. */
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	/* Otworz plik 1 */
	int fd1 = open (path1, O_RDONLY, mode);
	if (fd1 < 0)
	{
		printf("Nie moge otworzyc pliku.\n");
		return EXIT_FAILURE;
	}
	/* Utworz plik 2 */
	// int fd2 = open (path2, O_WRONLY | O_CREAT, mode);
	int fd2 = creat(path2, mode);
	printf("Czytam dane z pliku %s i zapisuje do pliku %s\n", path1, path2);
	do
	{
		bytes_read = read(fd1,buffer,buf_size);
		bytes_written = write(fd2,buffer,bytes_read);
		offset = offset + bytes_written;

	} while (bytes_read == buf_size);

	printf("Zapisano %d bajtow\n", offset);
	printf("Zamkniecie pliku.\n");
	/* Zamknij plik. */
	close(fd1);
	close(fd2);
	return EXIT_SUCCESS;
}
