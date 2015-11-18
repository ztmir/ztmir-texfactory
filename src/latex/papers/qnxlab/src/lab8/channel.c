#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int chid;

	chid = ChannelCreate(0);
	if (chid == -1)
	{
		printf("Nie moge utworzyc kanalu: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	/* ... */
	printf("Utworzylem kanal o nr CHID=%d\n", chid);
	ChannelDestroy(chid);
	return EXIT_SUCCESS;
}
