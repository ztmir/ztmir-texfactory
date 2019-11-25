#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	time_t time_of_day;

	time_of_day = time(NULL);
	printf("Liczba sekund od 1 stycznia 1970: %ld\n", (long int)time_of_day);
	printf("Biezaca data: %s", ctime(&time_of_day));

	return 0;
}
