#include <stdio.h>

int num_steps = 100000;


int main ()
{
	int i;
	double x, pi, step, sum = 0.0;

	step = 1.0 / (double) num_steps;
	for (i=0; i < num_steps; i++)
	{
		x = (double)(i + 0.5) * step;
		sum = sum + 4.0 / (1.0 + x * x);
	}
	pi = step * sum;

	printf("PI = %.15f\n", pi);

	return 0;
}
