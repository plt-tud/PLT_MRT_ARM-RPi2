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

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include <iostream>
using namespace std;

#include "AutomatonElement.h"
#include "State.h"

class Transition : public AutomatonElement {
private:
  Guard guardFunc;
  Behavior effectFunc;
  static const string myType;
public:
  // Konstruktur
  explicit Transition(const State& start, const State& target, Guard guardFunc=defaultGuard, Behavior effectFunc=defaultBehavior, void *handle=nullptr);
  
  const State& start;
  const State& target;
        
  // Wächterfunktion
  bool guard() const { return guardFunc(*this,"guard"); }
  // Übergangsverhalten
  void effect() const { effectFunc(*this, "effect"); }
  const string& getType() const { return myType; }
};

#endif /* TRANSITION_H_ */
