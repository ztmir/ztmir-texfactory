/* client.c */
#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <string.h>
#include <errno.h>
#include <sched.h>

int main(int argc, char *argv[])
{
	int server_pid;   // PID serwera
	int server_chid;  // CHID serwera
	int coid;	// COID
	int value1;	// wysylana liczba1
	int value2 = 38; // wyslana liczba2
	int status; // status z funkcji MsgSend()

	if(argc != 4) {
		printf("K: Program musi byc wywolany z 3 argumentami, np:\n\n");
		printf("K: client 482834 1 abcdefghi    \n\n");
		printf("K: - pierwszy arg(482834): pid serwera\n");
		printf("K: - drugi arg(1): chid serwera\n");
		printf("K: - trzeci arg(5): int wysylany do serwera\n");
		exit(EXIT_FAILURE);
	}
	server_pid = atoi(argv[1]);
	server_chid = atoi(argv[2]);

	printf("K: Probuje nawiazac polaczenie z serwerem pid: %d, chid %d\n", server_pid, server_chid);
	/* Tworzenie polaczenia */
	coid = ConnectAttach(ND_LOCAL_NODE, server_pid, server_chid,_NTO_SIDE_CHANNEL,0);
	if (coid == -1)
	{
		printf("K: Nie moge utworzyc polaczenia: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	value1 = atoi(argv[3]);
	printf("K: Wysylam wiadomosc: %d\n", value1);
	//	getprio(0) pobiera priorytet biezacego procesu.
	status = MsgSendPulse(coid, getprio(0),_PULSE_CODE_MINAVAIL,value1);

	if (status == -1)
	{
		printf("K: Nie moge wyslac impulsu 1: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("K: Wysylam wiadomosc: %d\n", value2);
	status = MsgSendPulse(coid, getprio(0), _PULSE_CODE_MINAVAIL+5, value2);
	if (status == -1)
	{
		printf("K: Nie moge wyslac impulsu 2: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
