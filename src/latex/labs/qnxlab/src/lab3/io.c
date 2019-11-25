#include <stdio.h>

int main()
{
	int i, nc;

	nc = 0;
	i = getchar();
	while (i != EOF) {
		nc++;
		i = getchar();
	}
	printf("\nLiczba wczytanych liter = %d\n", nc);
	return 0;
}
