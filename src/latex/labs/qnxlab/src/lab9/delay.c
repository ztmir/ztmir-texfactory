/* pomiar1.c */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int i;
	/* Zaczekaj 1000 ms. */
	for(i=0; i < 1000; i++) {
		delay(1);
	}
	return EXIT_SUCCESS;
}
