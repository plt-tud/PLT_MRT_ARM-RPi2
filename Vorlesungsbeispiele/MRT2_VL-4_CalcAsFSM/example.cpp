//============================================================================
// Name        : CalcAsFSM.cpp
// Author      : Urbas
// Version     : 0.01
// Copyright   : use as is, no guarantees
// Description : Rechner als Automat
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

#include <stdlib.h> // atoi
// Achtung! Der Suchpfad für Include-Dateien muss für den Compiler gesetzt sein:
// Properties->C++ Build/Settings->C++ Compiler/Include
#include "Automaton.h"

// linker Operand - Wert und Vorzeichen
int lOp = 0;
int lSign = 1;
// linker Operand - Wert und Vorzeichen
int rOp = 0;
int rSign = 1;
// Operator
char op;

// Ausgabe
ostream* aout = &cout;
int step = 0;

// Hilfsroutine fürs rechnen
int calc(char o) {
	switch (o) {
	case '+':
		return lOp + rOp;
	case '-':
		return lOp - rOp;
	case '*':
		return lOp * rOp;
	case '/':
		return lOp / rOp;
	default:
		exit(-1);
	}
}

// Verhaltensdefinitionen - Setzen und Ausgabe
void behavior_lOp_Sign(const AutomatonElement& ae, const string& input) {
	lSign *= -1;
}
void behavior_rOp_Sign(const AutomatonElement& ae, const string& input) {
	rSign *= -1;
}
void behavior_lOp_Digit(const AutomatonElement& ae, const string& input) {
	lOp = lOp * 10 + *((char *) ae.getHandle()) - '0';
}
void behavior_rOp_Digit(const AutomatonElement& ae, const string& input) {
	rOp = rOp * 10 + *((char *) ae.getHandle()) - '0';
}
void behavior_Op1(const AutomatonElement& ae, const string& input) {
	lOp *= lSign;
	op = *((char *) ae.getHandle());
}
void behavior_OpN(const AutomatonElement& ae, const string& input) {
	rOp *= rSign;
	lOp = calc(op); // rechne alten operator
	rOp = 0;
	rSign = 1;
	op = *((char *) ae.getHandle()); // merke neuen operator
}
void behavior_do(const AutomatonElement& ae, const string& input) {
	rOp *= rSign;
	// rechnen und ausgeben
	cout << calc(op) << endl;
	// zurücksetzen
	rOp = 0;
	rSign = 1;
	lOp = 0;
	lSign = 1;
}

// Wächterfunktionen
bool guardMinus(const AutomatonElement& ae, const string& input) {
	return *((char *) ae.getHandle()) == '-';
}
bool guardPlus(const AutomatonElement& ae, const string& input) {
	return *((char *) ae.getHandle()) == '+';
}
bool guardDigit(const AutomatonElement& ae, const string& input) {
	return *((char *) ae.getHandle()) >= '0' && *((char *) ae.getHandle()) <= '9';
}
bool guardOp(const AutomatonElement& ae, const string& input) {
	char c = *((char *) ae.getHandle());
	return c == '+' || c == '-' || c == '*' || c == '/';
}
bool guardDo(const AutomatonElement& ae, const string& input) {
	return *((char *) ae.getHandle()) == '=';
}

// ausgabestrom für Zustandsdarstellug
void behavior_logState(const AutomatonElement& ae, const string& input) {
	*aout << step++ << " " << ae.getID() << " " << input << endl;
}

int main() {
	// define states with numeric ids for easy plotting
	// all states behave the same: logState on exit
	char lexerToken;

	State 	s0("0", defaultBehavior, defaultBehavior, behavior_logState, &lexerToken),
			s1("1", defaultBehavior, defaultBehavior, behavior_logState, &lexerToken),
			s2("2", defaultBehavior, defaultBehavior, behavior_logState, &lexerToken),
			s3("3", defaultBehavior, defaultBehavior, behavior_logState, &lexerToken),
			s4("4", defaultBehavior, defaultBehavior, behavior_logState, &lexerToken),
			s5("5", defaultBehavior, defaultBehavior, behavior_logState, &lexerToken);

	// define transitionstable with transitions
	std::list<Transition*> t;
	t.push_back(new Transition(s0, s0, guardPlus , defaultBehavior,    &lexerToken) );
	t.push_back(new Transition(s0, s1, guardMinus, behavior_lOp_Sign,  &lexerToken) );
	t.push_back(new Transition(s0, s2, guardDigit, behavior_lOp_Digit, &lexerToken) );
	t.push_back(new Transition(s1, s0, guardMinus, behavior_lOp_Sign,  &lexerToken) );
	t.push_back(new Transition(s1, s2, guardDigit, behavior_lOp_Digit, &lexerToken) );
	t.push_back(new Transition(s2, s2, guardDigit, behavior_lOp_Digit, &lexerToken) );
	t.push_back(new Transition(s2, s3, guardOp,    behavior_Op1,       &lexerToken) );
	t.push_back(new Transition(s3, s3, guardPlus,  defaultBehavior,    &lexerToken) );
	t.push_back(new Transition(s3, s4, guardMinus, behavior_rOp_Sign,  &lexerToken) );
	t.push_back(new Transition(s3, s5, guardDigit, behavior_rOp_Digit, &lexerToken) );
	t.push_back(new Transition(s4, s3, guardMinus, behavior_rOp_Sign,  &lexerToken) );
	t.push_back(new Transition(s4, s5, guardDigit, behavior_rOp_Digit, &lexerToken) );
	t.push_back(new Transition(s5, s5, guardDigit, behavior_rOp_Digit, &lexerToken) );
	t.push_back(new Transition(s5, s3, guardOp,    behavior_OpN,       &lexerToken) );
	t.push_back(new Transition(s5, s0, guardDo,    behavior_do,        &lexerToken) );

	// initialize the automaton
	Automaton a(s0, t);

	// aus zeichenkette
	string f("+-20-3*-4=");
	for (unsigned int i = 0; i < f.size(); i++) {
		lexerToken = f[i];
		a.run();
	}

	return 0;
}
