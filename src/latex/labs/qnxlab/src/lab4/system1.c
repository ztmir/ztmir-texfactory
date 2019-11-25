#include <stdio.h>
#include <stdlib.h>

int main()
{
  int rc;

  rc = system( "pwd; ls" );

  if( rc == -1 )
    {
      printf( "Nie mozna uruchomic polecenia\n" );
    }
  else
    {
      printf( "Status zakonczenia %d\n", rc );
    }
  return EXIT_SUCCESS;
}
