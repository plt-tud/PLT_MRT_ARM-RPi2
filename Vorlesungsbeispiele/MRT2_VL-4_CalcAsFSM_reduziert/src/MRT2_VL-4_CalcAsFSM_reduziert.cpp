#include <iostream>
#include <fstream>

#include <Automaton.h>

#include "Accumulator.h"

using namespace std;

ostream* aout = &cout;
int step = 0;

int charToInt(char op) {
	return op - '0';
}

void behavior_logState(const AutomatonElement& ae, const string& input) {
	*aout << step++ << " Exit  " << ae.getID() << " " << input << endl;
}

void behavior_toggleSign(const AutomatonElement& ae, const string& input) {
	((Accumulator *) ae.getHandle())->toggleSign();
}

void behavior_appendDigit(const AutomatonElement& ae, const string& input) {
	char token = *(((Accumulator *) ae.getHandle())->getCurrentToken());

	((Accumulator *) ae.getHandle())->appendDigit(charToInt(token));
}

void behavior_calculateResult(const AutomatonElement& ae, const string& input) {
	char token = *(((Accumulator *) ae.getHandle())->getCurrentToken());

	((Accumulator *) ae.getHandle())->compute(token);
	((Accumulator *) ae.getHandle())->resetInput();
}

/**
 * Checks if given input token is '-' (minus).
 */
bool guard_isMinus(const AutomatonElement& ae, const string& input) {
	return *(((Accumulator *) ae.getHandle())->getCurrentToken()) == '-';
}

/**
 * Checks if given input token matches [0-9] (is digit).
 */
bool guard_isDigit(const AutomatonElement& ae, const string& input) {
	char token = *(((Accumulator *) ae.getHandle())->getCurrentToken());

	return token >= '0' && token <= '9';
}

/**
 * Checks if given input token matches [+-/*=] (all supported operations).
 */
bool guard_isOpn(const AutomatonElement& ae, const string& input) {
	char token = *(((Accumulator *) ae.getHandle())->getCurrentToken());
	return token == '+' || token == '-' || token == '*' || token == '/' || token == '=';
}

int main() {
	char lexerToken;
	Accumulator accu(&lexerToken);

	State s_op_pos("op_pos", defaultBehavior, defaultBehavior, behavior_logState, &accu);
	State s_op_neg("op_neg", defaultBehavior, defaultBehavior, behavior_logState, &accu);
	State s_op_num("op_number", defaultBehavior, defaultBehavior, behavior_logState, &accu);

	std::list<Transition*> t;
	// Transitions for switching sign
	t.push_back(new Transition(s_op_pos, s_op_neg, guard_isMinus, behavior_toggleSign, &accu));
	t.push_back(new Transition(s_op_neg, s_op_pos, guard_isMinus, behavior_toggleSign, &accu));

	// Transitions for appending digits
	t.push_back(new Transition(s_op_pos, s_op_num, guard_isDigit, behavior_appendDigit, &accu));
	t.push_back(new Transition(s_op_neg, s_op_num, guard_isDigit, behavior_appendDigit, &accu));
	t.push_back(new Transition(s_op_num, s_op_num, guard_isDigit, behavior_appendDigit, &accu));

	// Transitions for calculating result
	t.push_back(new Transition(s_op_num, s_op_pos, guard_isOpn, behavior_calculateResult, &accu));


	// Example 1
	Automaton automaton1(s_op_pos, t);

	string f1 = string("+-20-3*-4=");
	for (unsigned int i = 0; i < f1.size(); i++) {
		lexerToken = f1[i];
		automaton1.run();
	}

	cout << f1 << accu.getAccumulatorValue() << endl;		// Result should be 92


	// Example 2
	Automaton automaton2(s_op_pos, t);

	string f2("+--10*+-4/-20=");
	for (unsigned int i = 0; i < f2.size(); i++) {
		lexerToken = f2[i];
		automaton2.run();
	}

	cout << f2 << accu.getAccumulatorValue() << endl;		// Result should be 2

	return 0;
}
