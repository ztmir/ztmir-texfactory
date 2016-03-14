#include <sys/neutrino.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syspage.h>

int main( void )
{
	uint64_t cps, cycle1, cycle2, ncycles;
	double sec;

	/* pobierz czas 1 */
	cycle1=ClockCycles( );

	/* wywolanie funkcji */
	printf("Hello world!\n");

	/* pobierz czas 2 */
	cycle2=ClockCycles( );
	ncycles=cycle2-cycle1;
	printf("Liczba cykli: %lld\n", ncycles);

	/* Ile cykli procesora na sekunde */
	cps = SYSPAGE_ENTRY(qtime)->cycles_per_sec;
	printf( "Cykli na sekunde: %lld.\n",cps );

	sec=(double)ncycles/cps;
	printf("Czas wykonania operacji: %f.\n",sec);

	return EXIT_SUCCESS;
}
