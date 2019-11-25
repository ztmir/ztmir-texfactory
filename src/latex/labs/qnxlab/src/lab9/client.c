/* client.c */
#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <string.h>
#include <errno.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <unistd.h>
#include <time.h>
#define SERVER_NAME "moj_serwis"
#define SIZE 256

typedef struct {
  int code; /* typ komunikatu */
  char text[SIZE];  /* tekst komunikatu */
} ClientMessage;

typedef union
{
  /* wiadomosc lub impuls */
  ClientMessage msg;
  struct _pulse pulse;
} Message;

int main(int argc, char *argv[])
{
  int coid;
  int status; /* status z funkcji MsgSend() */
  int i;
  Message smsg, rmsg;

  if(argc < 2) {
    printf("K: Program musi byc wywolany z 1 badz wiecej argumentami, np:\n\n");
    printf("K: ./client abc def ghi    \n\n");
    printf("K: - abc, def, ghi to stringi wysylane do serwera.\n");
    exit(EXIT_FAILURE);
  }

  printf("K: Lokalizuje serwer...\n");
  /* Tworzenie polaczenia */
  coid = name_open(SERVER_NAME, NAME_FLAG_ATTACH_GLOBAL);

  if (coid == -1)
    {
      printf("K: Nie moge utworzyc polaczenia: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

  for(i = 1; i < argc; i++)
    {
      strcpy(smsg.msg.text, argv[i]);
      smsg.msg.code = i;
      printf("K: Wysylam wiadomosc: %s z kodem %d\n", smsg.msg.text,smsg.msg.code);
      status = MsgSend(coid,&smsg,sizeof(smsg),&rmsg,sizeof(rmsg));

      if (status == -1)
        {
          printf("K: Nie moge wyslac wiadomosci: %s\n", strerror(errno));
          exit(EXIT_FAILURE);
        }
      printf("K: Otrzymana z serwera wiadomosc: %s z kodem %d\n", rmsg.msg.text,rmsg.msg.code);
      printf("K: Funkcja MsgSend zwrocila status: %d\n", status);
      /*delay(2000);*/
      sleep(2);
    }


  printf("K: Zamykanie polaczenia\n");
  name_close(coid);

  return EXIT_SUCCESS;
}
