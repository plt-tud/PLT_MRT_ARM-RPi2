/*
 * Complex.h
 *
 *  Created on: 04.04.2016
 *      Author: Leon Urbas
 */

#ifndef COMPLEX_H_
#define COMPLEX_H_
#include <iostream>

class Complex {
private:
	double real, imag;
public:
	// Constructor
	Complex(double r = 0.0, double i = 0.0);
	// getter for attributes
	double Re() const;
	double Im() const;
	// Operations
	Complex& operator+=(const Complex& rhs);
	Complex& operator-=(const Complex& rhs);
	Complex& operator*=(const Complex& rhs);
	Complex& operator/=(const Complex& rhs);
};

inline Complex operator+(const Complex& lhs, const Complex& rhs) {
	Complex cret(lhs);
	return cret += rhs;
}
inline Complex operator+(const Complex& lhs, const double rhs) {
	Complex cret(lhs), crhs(rhs,0);
	return cret += rhs;
}

inline Complex operator-(const Complex& lhs, const Complex& rhs) {
	Complex cret(lhs);
	return cret -= rhs;
}
inline Complex operator-(const Complex& lhs, const double rhs) {
	Complex cret(lhs), crhs(rhs,0);
	return cret -= rhs;
}

inline Complex operator*(const Complex& lhs, const Complex& rhs) {
	Complex cret(lhs);
	return cret *= rhs;
}
inline Complex operator*(const Complex& lhs, const double rhs) {
	Complex cret(lhs), crhs(rhs,0);
	return cret *= crhs;
}
inline Complex operator/(const Complex& lhs, const Complex& rhs) {
	Complex cret(lhs);
	return cret /= rhs;
}

inline Complex operator/(const Complex& lhs, double rhs) {
	Complex cret(lhs), crhs(rhs,0);
	return cret /= crhs;
}
inline Complex operator/(double lhs, const Complex& rhs) {
	Complex cret(lhs,0);
	return cret /= rhs;
}


std::ostream& operator<<(std::ostream& lhs, const Complex& rhs);

#endif /* COMPLEX_H_ */
