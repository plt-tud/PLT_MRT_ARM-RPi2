/*
 * Copyright (c) 2013 Leon Urbas <Leon.Urbas@tu-dresden.de>
 * Chair for Process Systems Engineering
 * Technical University of Dresden
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef AUTOMATON_H_
#define AUTOMATON_H_
#include <list>
#include <iostream>
using namespace std;

#include "State.h"
#include "Transition.h"

#include <list>
class Automaton {
private:
  const State* pCurrentState; // veränderliche Adresse eines nicht veränderlichen Objects
  const std::list<Transition*> pTT;
  
  int currentStateTicks; // Anzahl ticks in aktuellem Zustand
  bool first;
public:
  Automaton(State& startState, const std::list<Transition*> pTT);
  
  void run();
};

#endif /* AUTOMATON_H_ */
