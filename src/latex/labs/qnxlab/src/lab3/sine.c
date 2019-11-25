#include <math.h>
#include <stdio.h>

int main()
{
	int angle_degree;
	double angle_radian, pi, value;

	/* Wydrukuj komentarz */
	printf ("\nOblicz tablice funkcji sinus...\n\n");

	/* oblicz pi */
	pi = 4.0*atan(1.0);
	printf ( " wartosc PI = %f \n\n", pi );

	printf ( " kat \n" );
	/* poczatkowa wartosc kata */
	angle_degree=0.0;
	/* petla po katach */
	while( angle_degree <= 360.0 )
	{
		angle_radian = pi * angle_degree/180.0;
		value = sin(angle_radian);
		printf(" %3d   %f \n", angle_degree, value);
		/* inkrementuj indeks */
		angle_degree = angle_degree + 10.0;
	}
	return 0;
}
