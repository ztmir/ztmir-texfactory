/* server1.c */
#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <string.h>
#include <errno.h>
#include <process.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/netmgr.h>
#include <unistd.h>
#include <time.h>
#define SERVER_NAME "moj_serwis"
#define MY_TIMER_EVENT (_PULSE_CODE_MINAVAIL + 3)
#define SIZE 256

typedef struct {
	int code; // typ komunikatu
	char text[SIZE];	// tekst komunikatu
} ClientMessage;

typedef union
{
// wiadomosc lub impuls
ClientMessage msg;
struct _pulse pulse;
} Message;


int main(int argc, char *argv[])
{
	int chid;	// Kanal komunikacyjny
	pid_t pid;	// PID serwera
	int rcvid;	// identifikator nadawcy
	Message rmsg, rmsg2;
	struct _msg_info info;
	int status = 0;
	name_attach_t* attach;
    struct sigevent event;
    timer_t timerid;
    int coid, id;
    struct itimerspec t;

	attach = name_attach(NULL, SERVER_NAME, NAME_FLAG_ATTACH_GLOBAL);
	chid = attach->chid;

	if (chid == -1)
	{
		printf("\tS: Nie moge utworzyc kanalu: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	pid = getpid();
	// utworzenie polaczenia do samego siebie
	coid = ConnectAttach(ND_LOCAL_NODE,pid,chid,_NTO_SIDE_CHANNEL,0);
    if (coid == -1) {
    	printf( "Nie moge utworzy polaczenia: %s\n", strerror(errno) );
        return EXIT_FAILURE;
    }

	// wypelnienie struktury event
	SIGEV_PULSE_INIT( &event, coid, getprio(0), MY_TIMER_EVENT, 0);
	// utworzenie timera
	id = timer_create( CLOCK_REALTIME, &event, &timerid );
	// timer wzgledny cykliczny ktory wysle puls za 2 sek i bedzie powtarzany co 1 sek
	t.it_value.tv_sec = 2;
	t.it_value.tv_nsec = 0;
	t.it_interval.tv_sec = 4;
	t.it_interval.tv_nsec = 0;
	// t.it_interval.tv_nsec = 500000000;
	// ustaw timer
	timer_settime( timerid, 0, &t, 0);

	while(1)
	{
		/* Odebranie komunikatu */
		rcvid = MsgReceive(chid,&rmsg,sizeof(rmsg),&info);

		/* Jesli nie udalo sie pobrac wiadomosci */
		if(rcvid == -1)
		{
			printf("\tS: Nie moge odebrac wiadomosci: %s\n", strerror(errno));
			continue;                    // sprobuj odebrac inna wiadomosc
		}
		else if (rcvid == 0)
		{
			if (rmsg.pulse.code == MY_TIMER_EVENT)
			{
				printf("\tS: Impuls pochodzi od timera: %d\n",rmsg.pulse.code);
				printf("\tS: PRZETWARZANIE po otrzymaniu impulsu...\n");
			}
			else
			{
				printf("\tS: Impuls NIE pochodzi od timera, kod: %d\n",rmsg.pulse.code);
			}
			continue;
		}
		else
		{
			printf("\tS: Odebrana wiadomosc: %s z kodem %d\n", rmsg.msg.text,rmsg.msg.code);
			printf("\tS: Zakodowany identyfikator nadawcy i polaczenia: %d\n", rcvid);
			sprintf(rmsg2.msg.text,"*** %s ***",rmsg.msg.text);
			rmsg2.msg.code = rmsg.msg.code + 100; // odpowiadam kodem o 100 wiekszym

			/* odpowiedz klientowi */
			MsgReply(rcvid,status,&rmsg2,sizeof(rmsg2));
			printf("\tS: Status serwera: %d, wiadomosc odpowiedzi: %s z kodem %d\n\n",
					status,rmsg2.msg.text,rmsg2.msg.code);

			if(status == -1)
			{
				printf("\tS: Nie moge odpowiedziec: %s\n", strerror(errno));
			}
			continue;
		}

	}

	name_detach(attach, 0);
	return EXIT_SUCCESS;
}
