/*
 * fibonacci.c
 *
 *  Created on: 06.10.2020
 *      Author: mrt
 */

#include <stdio.h>

int main() {

	int N;

	printf("N? ");
	scanf("%i", &N);

	// We assume: N >= 2;

	// Initialize variables with values for n = 2;
	int fib_n_minus_2 = 0;
	int fib_n_minus_1 = 1;
	int fib_n = 1;

	int n;
	for (n = 2; n < N; n++) {
		fib_n_minus_2 = fib_n_minus_1;
		fib_n_minus_1 = fib_n;
		fib_n = fib_n_minus_2 + fib_n_minus_1;
	}

	printf("fib(%i) = %i\n", N, fib_n);
	return 0;

}
