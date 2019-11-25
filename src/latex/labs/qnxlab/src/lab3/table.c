#include <stdio.h>

#define SIZE 3
int main()
{
	float x[SIZE];
	float *fp;
	int   i;
	/* inicjalizacja tablicy x */
	/* rzutowanie i na float */
	for (i = 0; i < SIZE; i++)
		x[i] = 0.5*(float)i;
	/* drukuj x */
	for (i = 0; i < SIZE; i++)
		printf("  %d  %f \n", i, x[i]);
	/* fp wskazuje na x */
	fp = x;
	/* drukuj poprzez wskaznik */
	/* *(fp+i)=x[i] */
	for (i = 0; i < SIZE; i++)
		printf("  %d  %f \n", i, *(fp+i));
	return 0;
}
