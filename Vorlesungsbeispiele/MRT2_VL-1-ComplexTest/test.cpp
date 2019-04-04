#include "Complex.h"
#include <iostream>
#include <string>
/* cheap test anything protocol */
void tap(int n, const std::string& msg, Complex r, bool result) {
	std::cout << ( result ? "ok " : "not ok " ) << n << " - " << msg << ", got " << r << std::endl;
}
int main() {
	int n(0);

	// given
	Complex c(2,1), j(0,1), r, d(5);

	// when									// then
				tap(n++, "Complex r    => [0 0]", r, r.Re() == 0 && r.Im() == 0);
				tap(n++, "Complex d(5) => [5 0]", d, d.Re() == 5 && d.Im() == 0);
	r = j* j; 	tap(n++, "j * j => [-1  0]", r, r.Re() == -1 && r.Im() == 0);
	r = c + c; 	tap(n++, "c + c => [ 4, 2]", r, r.Re() ==  4 && r.Im() == 2);
	r = c + j; 	tap(n++, "c - j => [ 2, 2]", r, r.Re() ==  2 && r.Im() == 2);
	r = c * j; 	tap(n++, "c * j => [-1, 2]", r, r.Re() == -1 && r.Im() == 2);
	r = c * c; 	tap(n++, "c * c => [ 3, 4]", r, r.Re() ==  3 && r.Im() == 4);
	r = c * 2; 	tap(n++, "c * 2 => [ 4, 2]", r, r.Re() ==  4 && r.Im() == 2);
	r = 2 * c;	tap(n++, "2 * c => [ 4, 2]", r, r.Re() ==  4 && r.Im() == 2);
	r = c / j;	tap(n++, "c / j => [ 1,-2]", r, r.Re() ==  1 && r.Im() ==-2);
	r = c / c;	tap(n++, "c / c => [ 1, 0]", r, r.Re() ==  1 && r.Im() == 0);

	return 0;
}
