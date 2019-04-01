#include "Complex.h"
#include <iostream>
#include <string>

void test(int n, const std::string& msg, Complex r, bool result) {
	std::cout << ( result ? "ok" : "not ok" ) << " ";
	std::cout << n << "-" << msg << ", got " << r;
	std::cout << std::endl;
}
int main() {
	// given
	Complex c(2,1), j(0,1), r;

	int n(0);
	// when		// then
	r = j* j; 	test(n++, "j * j == [-1  0]", r, r.Re() == -1 && r.Im() == 0);
	r = c + c; 	test(n++, "c + c == [ 4, 2]", r, r.Re() ==  4 && r.Im() == 2);
	r = c + j; 	test(n++, "c - j == [ 2, 2]", r, r.Re() ==  2 && r.Im() == 2);
	r = c * j; 	test(n++, "c * j == [-1, 2]", r, r.Re() == -1 && r.Im() == 2);
	r = c * c; 	test(n++, "c * c == [ 3, 4]", r, r.Re() ==  3 && r.Im() == 4);
	r = c * 2; 	test(n++, "c * 2 == [ 4, 2]", r, r.Re() ==  4 && r.Im() == 2);
	r = 2 * c;	test(n++, "2 * c == [ 4, 2]", r, r.Re() ==  4 && r.Im() == 2);
	r = c / j;	test(n++, "c / j == [ 1,-2]", r, r.Re() ==  1 && r.Im() ==-2);
	r = c / c;	test(n++, "c / c == [ 1, 0]", r, r.Re() ==  1 && r.Im() == 0);
}
