/* client.c */
#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int server_pid;   // PID serwera
	int server_chid;  // CHID serwera
	int coid;	// COID
	char smsg[256];	// bufor na wiadomosci do wyslania
	int status; // status z funkcji MsgSend()
	int checksum;	// suma kontrolna - liczba liter w stringu

	if(argc != 4) {
		printf("K: Program musi byc wywolany z 3 argumentami, np:\n\n");
		printf("K: ./client 482834 1 abcdefghi    \n\n");
		printf("K: - pierwszy arg(482834): pid serwera\n");
		printf("K: - drugi arg(1): chid serwera\n");
		printf("K: - trzeci arg(abcdefghi): string wysylany do serwera\n");
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

	strcpy(smsg, argv[3]);
	printf("K: Wysylam wiadomosc: %s\n", smsg);

	status = MsgSend(coid,smsg,sizeof(smsg),&checksum,sizeof(checksum));

	if (status == -1)
	{
		printf("K: sNie moge wyslac wiadomosci: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("K: Otrzymana z serwera suma kontrolna: %d\n", checksum);
	printf("K: Funkcja MsgSend zwrocila status: %d\n", status);

	return EXIT_SUCCESS;
}
