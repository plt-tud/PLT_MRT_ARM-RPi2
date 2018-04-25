/*
 * Copyright (c) 2018 <copyright holder> <email>
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

#include "Ampel_Behaviors.h"

#include "Ampel.h"

void behavior_red(const AutomatonElement& ae, const string& ActionID)
{
    Ampel *a = static_cast<Ampel*>(ae.getHandle());
    a->setRedLight(true);
    a->setYellowLight(false);
    a->setGreenLight(false);
}

void behavior_redtogreen(const AutomatonElement& ae, const string& ActionID)
{
    Ampel *a = static_cast<Ampel*>(ae.getHandle());
    a->setRedLight(true);
    a->setYellowLight(true);
    a->setGreenLight(false);
}

void behavior_green(const AutomatonElement& ae, const string& ActionID)
{
    Ampel *a = static_cast<Ampel*>(ae.getHandle());
    a->setRedLight(false);
    a->setYellowLight(false);
    a->setGreenLight(true);
}

void behavior_greentored(const AutomatonElement& ae, const string& ActionID)
{
    Ampel *a = static_cast<Ampel*>(ae.getHandle());
    a->setRedLight(false);
    a->setYellowLight(true);
    a->setGreenLight(false);
}

void behavior_offline_check(const AutomatonElement& ae, const string& ActionID)
{
    Ampel *a = static_cast<Ampel*>(ae.getHandle());
    a->setRedLight(false);
    a->setYellowLight(true);
    a->setGreenLight(false);
}

void behavior_offline(const AutomatonElement& ae, const string& ActionID)
{
    Ampel *a = static_cast<Ampel*>(ae.getHandle());
    a->setRedLight(false);
    a->setYellowLight(false);
    a->setGreenLight(false);
}

bool guard_hasController(const AutomatonElement& ae, const string& ActionID)
{
    Ampel *a = static_cast<Ampel*>(ae.getHandle());
    return a->hasController();
}

bool guard_hasNoController(const AutomatonElement& ae, const string& ActionID)
{
    Ampel *a = static_cast<Ampel*>(ae.getHandle());
    return !(a->hasController());
}

bool guard_greenPhaseRequested(const AutomatonElement& ae, const string& ActionID)
{
    Ampel *a = static_cast<Ampel*>(ae.getHandle());
    return (a->getPhaseCommand() == PHASE_GREEN);
}

bool guard_redPhaseRequested(const AutomatonElement& ae, const string& ActionID)
{
    Ampel *a = static_cast<Ampel*>(ae.getHandle());
    return (a->getPhaseCommand() == PHASE_RED);
}
