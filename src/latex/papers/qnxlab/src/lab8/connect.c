#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int coid,nd,chid;
	pid_t pid;

	nd = 0;
	coid = ConnectAttach(nd, pid, chid,_NTO_SIDE_CHANNEL,0);
	if (coid == -1)
	{
		printf("Nie moge utworzyc polaczenia: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	/* ... */
	printf("Utworzylem polaczenie o nr connect=%d\n", coid);
	ConnectDetach(coid);
	return EXIT_SUCCESS;
}
