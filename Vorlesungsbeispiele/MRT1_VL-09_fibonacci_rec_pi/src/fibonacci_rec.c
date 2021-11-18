/*
 * fibonacci_rec.c
 *
 *  Created on: 23.11.2020
 *      Author: mrt
 */


#include <stdio.h>

const int N = 30;

int fibonacci(int n) {
	if(n == 0) return 0;
	if(n == 1) return 1;
	return fibonacci(n-1) + fibonacci(n-2);
}

int main() {
	int result = fibonacci(N);
	printf("%i\n", result);
	return 0;
}
