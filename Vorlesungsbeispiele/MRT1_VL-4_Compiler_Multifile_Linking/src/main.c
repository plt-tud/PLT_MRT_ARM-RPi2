#include "math.h"
#include <stdio.h>

int main() {
	int x = 24;
	int y = quad(x, 2, 4, 8);

	printf("Y: %d\n", y);

	return y;
}
