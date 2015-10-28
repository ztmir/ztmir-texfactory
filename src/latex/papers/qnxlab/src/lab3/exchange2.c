#include <stdio.h>

void exchange ( int *a, int *b );

int main()
{			
	int a, b;

	a = 5;
	b = 7;
	printf("przed zamiana w main: a = %d, b = %d\n", a, b);

	exchange(&a, &b);
	printf("po zamianie w main: ");
	printf("a = %d, b = %d\n", a, b);
	return 0;
}

void exchange ( int *a, int *b )
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
	printf(" Z funkcji exchange: ");
	printf("a = %d, b = %d\n", *a, *b);
}
