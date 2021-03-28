/*
 * Accumulator.h
 *
 *  Created on: 22.03.2021
 *      Author: mrt
 */

#ifndef ACCUMULATOR_H_
#define ACCUMULATOR_H_

#include <stdlib.h>
#include <iostream>

class Accumulator {
	int num, sign;		// currently stored input which will be used for next computation
	char opn_prev;		// operation identifier (+-/*=) that will be used for next computation

	int val_accu;		// current value of accumulator (-> intermediate result)

	char *token;		// pointer to char that will be parsed next

public:
	Accumulator(char *t);
	virtual ~Accumulator();

	void toggleSign();

	void appendDigit(int num);
	void resetInput();

	void compute(char op);
	int getAccumulatorValue();

	const char *getCurrentToken();
};

#endif /* ACCUMULATOR_H_ */
