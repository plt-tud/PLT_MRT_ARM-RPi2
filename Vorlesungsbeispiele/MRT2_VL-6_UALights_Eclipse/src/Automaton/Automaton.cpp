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

#include "../Automaton/Automaton.h"

Automaton::Automaton(State& startState, std::list<Transition*> pTT)
: pCurrentState(&startState), pTT(pTT), TTlength(TTlength), currentStateTicks(0), first(true) {
}

void Automaton::run() {
  currentStateTicks++;

  if (first) { pCurrentState->enter(); first=false; }

  // Über alle ausgehenden Transitionen des aktuellen Zustands
  for(std::list<Transition *>::const_iterator pTTi = pTT.begin(); pTTi != pTT.end(); pTTi++) {
    Transition *t = *(pTTi);
    if (&t->start == pCurrentState) {
      // Wenn Wächter die Transition frei gibt
      if (t->guard()) {
        pCurrentState->exit(); // Verhalten Verlassen Zustand
        t->effect(); // Verhalten Übergang
        pCurrentState = &t->target;
        currentStateTicks = 0;
        pCurrentState->enter(); // Verhalten Eintritt Zustand
        return;
      }
    }
  }
  // Wenn wir hier angekommen sind, dann hat keine Transition geschaltet
  pCurrentState->stay(); // Verhalten Verharren Zustand
}
