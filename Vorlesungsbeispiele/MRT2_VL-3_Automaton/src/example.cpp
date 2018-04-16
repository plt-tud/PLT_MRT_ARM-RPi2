/*
 * example.cpp
 *
 *  Created on: 16.04.2018
 *      Author: mrt
 */

#include <iostream>
#include <list>
#include <map>

#include "Automaton.h"

using namespace std;

static void behavior_red(const AutomatonElement& ae, const string& ActionID)
{
	cout << ae << ":" << ActionID << endl;
}

static void behavior_green(const AutomatonElement& ae, const string& ActionID)
{
	cout << ae << ":" << ActionID << endl;
}

int main()
{
	std::map<std::string, State*> states;

	states["red"]   = new State("red",    behavior_red,  defaultBehavior,  defaultBehavior, nullptr);
	states["green"] = new State("green",  behavior_green,  defaultBehavior,  defaultBehavior, nullptr);

	std::list<Transition*> transitions;

	transitions.push_back(new Transition(*states["red"],  *states["green"], defaultGuard, defaultBehavior, nullptr));
	transitions.push_back(new Transition(*states["green"],*states["red"],   defaultGuard, defaultBehavior, nullptr));

	Automaton  stateMachine(*states["red"], transitions);

	for (int i=0; i<100; i++ )
	{
		stateMachine.run();

	}

	cout << "bye" << endl;

	return 0;
}
