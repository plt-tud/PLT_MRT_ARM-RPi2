//============================================================================
// Name        : HelloWorld.cpp
// Author      : Leon Urbas
// Version     :
// Copyright   : just fun
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Complex.h"

Complex PT1(double w, double Kp, double T1) {
	static Complex j(0,1);
	return Kp / ( 1 + j * w * T1 );
}
int main() {
	double Kp = 1, T1 = 1000,  w;
	for (w=1; w<100; w+=3) {
		std::cout << w << ',' << PT1(w,Kp,T1) << std::endl;
	}
	return 0;
}
