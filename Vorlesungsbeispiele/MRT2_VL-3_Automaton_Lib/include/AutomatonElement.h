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
#ifndef AUTOMATONELEMENT_H_
#define AUTOMATONELEMENT_H_

#include <string>
#include <iostream>
using namespace std;

#include "Behavior.h" // not used here, but in specializations

// AutomatonElement ist eine abstrakte Basisklasse, in der gemeinsamen Elemente der Bausteine eines
// Automaten (Zuständen und Transitionen) zusammengefasst sind.
class AutomatonElement {

protected:
  const string id; // identifier
  void *handle;

  friend ostream& operator<<(ostream& lhs, AutomatonElement& rhs);
  friend ostream& operator<<(ostream& lhs, const AutomatonElement& rhs);

public:
  AutomatonElement(const string& id, void *handle=nullptr);
  virtual ~AutomatonElement() { };
  virtual const string& getID()   const { return id; }
  virtual void *getHandle() const { return handle; }
  virtual const string& getType() const = 0;
};


inline ostream& operator<<(ostream& lhs, AutomatonElement& rhs)       { return lhs << rhs.id; }
inline ostream& operator<<(ostream& lhs, const AutomatonElement& rhs) { return lhs << rhs.id; }
#endif /* AUTOMATONELEMENT_H_ */
