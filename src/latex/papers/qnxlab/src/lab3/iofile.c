#include <stdio.h>

int main()
{
	FILE *fp;
	int i;

	fp = fopen("foo.dat", "w");		/* otworz foo.dat do pisania */

	fprintf(fp, "\nAla ma kota\n\n");   /* tekst */
	for (i = 1; i <= 10 ; i++)
	fprintf(fp, "i = %d\n", i);

	fclose(fp);	/* zamknij plik */
	return 0;
}
