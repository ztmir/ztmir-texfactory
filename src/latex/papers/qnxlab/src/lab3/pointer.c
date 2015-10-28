#include <stdio.h>

int main()
{
	float x, y;			/* deklaracja zmiennych */
	float *fp, *fp2;		/* fp fp2 wskazniki do typu float */

	x = 6.5;

	/* wydrukuj zawartosc i adres zmiennej x */
	printf("Zawartosc x: %f, adres x: %ld\n", x, &x);

	fp = &x;			/* fp wskazuje na lokacje zmiennej x */

	/* wydrukuj zawartosc fp */
	printf("Wartosc komorki pamieci wskazanej przez fp: %f\n", *fp);

	/* zmien zawartosc komorki pamieci wskazanej przez fp */
	*fp = 9.2;
	printf("Nowa wartosc x %f = %f \n", *fp, x);

	/* Obliczenia arytmetyczne */
	*fp = *fp + 1.5;
	printf("Wartosc koncowa x is %f = %f \n", *fp, x);
	/* Zamiana wartosci x i y */
	y = *fp;
	fp2 = fp;
	printf("Wartosc y = %f i fp2 = %f \n", y, *fp2);
	return 0;
}
