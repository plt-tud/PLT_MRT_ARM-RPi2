#include <stdio.h>

int main(){
	int value = f();				// call assembler-function in f.S
	printf("value: %i\n", value);	// print value

	return 0;
}
