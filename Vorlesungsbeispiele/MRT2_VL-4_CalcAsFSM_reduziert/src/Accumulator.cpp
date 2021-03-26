#include "Accumulator.h"

using namespace std;

Accumulator::Accumulator(char *t) {
	token = t;
	num = 0;
	sign = 1;
	val_accu = 0;
	opn_prev = '=';
}

Accumulator::~Accumulator() {

}

void Accumulator::toggleSign() {
	sign = -sign;
}

void Accumulator::appendDigit(int digit) {
	num = num * 10 + digit;
}

/**
 * Computes new result with operation that was given in the most recent call of compute. If the method is called
 * for the first time, operation '=' (equals) will be performed, moving the currently stored digits to accu.
 *
 * Using '=' will begin a new calculation. Reusing the last result after using '=' is not supported.
 */

void Accumulator::compute(char opn_next) {

	switch (opn_prev) {
	case '+':
		val_accu = val_accu + (sign * num);
		break;
	case '-':
		val_accu = val_accu - (sign * num);
		break;
	case '*':
		val_accu = val_accu * sign * num;
		break;
	case '/':
		val_accu = val_accu / (sign * num);
		break;

	case '=':
		val_accu = sign * num;
		break;
	default:

		exit(-1);
	}

	opn_prev = opn_next;

}

int Accumulator::getAccumulatorValue() {
	return val_accu;
}

void Accumulator::resetInput() {
	num = 0;
	sign = 1;
}

/*
 * Returns char that will be parsed next.
 */

const char* Accumulator::getCurrentToken() {
	return this->token;
}
