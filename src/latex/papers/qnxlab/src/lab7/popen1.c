#include <stdio.h>
#include <unistd.h>
int main ()
{
	/* Utworz potok, uruchom funkcje wc -w, badz sort */
//	FILE* fp = popen ("wc -w", "w");
	FILE* fp = popen ("sort", "w");
	if (fp != NULL)
	{
		/* pisz do potoku */
		fprintf (fp, "To jest test.\n");
		fprintf (fp, "Hello, world.\n");
		fprintf (fp, "aaa.\n");
		fprintf (fp, "Wspanialy program...\n");
		fprintf (fp, "Koniec programu.\n");
		pclose(fp);
	}

	return 0;
}
