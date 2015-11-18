/* server.c */
#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <string.h>
#include <errno.h>
#include <process.h>

int main(int argc, char *argv[])
{
	int chid;	// Kanal komunikacyjny
	pid_t pid;	// PID serwera
	int rcvid;	// identifikator nadawcy
	struct _msg_info info;
	char rmsg[256];	// bufor na wiadomosci odpowiedzi
	int checksum;	// liczba znakow w odebranej wiadomosci
	int status = 0;

	chid = ChannelCreate(0);

	if (chid == -1)
	{
		printf("\tS: Nie moge utworzyc kanalu: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	pid = getpid();
	printf("\tS: PID serwera: %d, CHID: %d\n", pid, chid);

	while(1)
	{
		/* Odebranie komunikatu */
		rcvid = MsgReceive(chid,&rmsg,sizeof(rmsg),&info);
		printf("\tS: Odebrana wiadomosc: %s\n", rmsg);
		printf("\tS: Zakodowany identyfikator nadawcy i polaczenia: %d\n", rcvid);
		/* Jesli nie udalo sie pobrac wiadomosci */
		if(rcvid == -1)
		{
			printf("\tS: Nie moge odebrac wiadomosci: %s\n", strerror(errno));
			break;                    // sprobuj odebrac inna wiadomosc
		}

		checksum = strlen(rmsg);

		/* odpowiedz klientowi, wysylajac sume kontrolna */
		MsgReply(rcvid,status,&checksum,sizeof(checksum));
		printf("\tS: Status serwera: %d, suma kontrolna: %d\n",status,checksum);

		if(status == -1)
		{
			printf("\tS: Nie moge odpowiedziec: %s\n", strerror(errno));
		}
	}

	return EXIT_SUCCESS;
}
