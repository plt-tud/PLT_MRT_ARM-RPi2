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

#ifndef STATE_H_
#define STATE_H_

#include <string>
#include <iostream>
using namespace std;

#include "AutomatonElement.h"

class State : public AutomatonElement {
private:
    static const string myType; // Klassenvariable
    Behavior enterFunc;
    Behavior stayFunc;
    Behavior exitFunc;

public:
    // Funktionszeigertypdefinition
  explicit State(const string& id, Behavior enterFunc=defaultBehavior, Behavior stayFunc=defaultBehavior, Behavior exitFunc=defaultBehavior, void *handle=nullptr);

    // functions just call the functions !
    inline void enter() const { enterFunc(*this, "enter"); }
    inline void stay() const { stayFunc(*this, "stay"); }
    inline void exit() const { exitFunc(*this, "exit"); }
    inline const string& getType() const { return myType; }
};
#endif /* STATE_H_ */
