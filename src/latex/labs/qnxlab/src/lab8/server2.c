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
	int checksum;	// liczba znakow w odebranej wiadomosci
	int status = 0;
	struct _pulse msg;

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
		/* Odebranie impulsu */
		rcvid = MsgReceive(chid, &msg, sizeof(msg), &info);
		/* Jesli nie udalo sie pobrac wiadomosci */
		if(rcvid == -1)
		{
			printf("\tS: Nie moge odebrac wiadomosci: %s\n", strerror(errno));
			break;                    // sprobuj odebrac inna wiadomosc
		}
		else if (rcvid == 0)
		{
			printf("\tS: Odebralem impuls.\n\tS: Kod impulsu: %d, wartosc %d\n", msg.code, msg.value.sival_int);
			continue;
		}

		checksum = msg.value.sival_int;

		/* odpowiedz klientowi, jesli komunikat */
		MsgReply(rcvid,status,&checksum,sizeof(checksum));

		if(status == -1)
		{
			printf("\tS: Nie moge odpowiedziec: %s\n", strerror(errno));
		}
	}

	return EXIT_SUCCESS;
}
