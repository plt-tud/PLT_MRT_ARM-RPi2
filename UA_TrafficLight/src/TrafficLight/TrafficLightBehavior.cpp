/*
 * Copyright (c) 2016 Chris Iatrou <Chris_Paul.Iatrou@tu-dresden.de>
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

#include "TrafficLightBehavior.h"
#include "TrafficLight.h"
#include <iostream>

void emt_updateTransitionTimestamp(const AutomatonElement& ae, const string& action) {
  TrafficLight *tl = static_cast<TrafficLight*>(ae.getHandle());
  if (tl != nullptr)
    tl->updateLastTransitionTimestamp();
  return;
}

void bh_sensorUpdate(const AutomatonElement& ae, const string& action)
{
  bool retval;
  TrafficLight *tl = static_cast<TrafficLight*>(ae.getHandle());
  if (tl != nullptr) {
    if(tl->sensor != nullptr)
      retval = tl->sensor->readValue();
    if(tl->output != nullptr) {
      if (retval && tl->output->getHasSignal() && tl->getAutonomousSensorAcknowledge() && !tl->output->getSignal()) {
        tl->output->setSignal(retval);
        tl->output->printState();
      }
    }
  }
}

void bh_warnProblem(const AutomatonElement& ae, const string& action)
{
  TrafficLight *tl = static_cast<TrafficLight*>(ae.getHandle());
  if (tl != nullptr) {
    if (time(nullptr) - tl->getLastTransitionTimestamp() > tl->getWarnBlinkInterval()) {
      tl->updateLastTransitionTimestamp();
      if (tl->output != nullptr) {
        tl->output->toggleWarnIndicator();
        tl->output->printState();
      }
    }
  }
}

void bh_rd(const AutomatonElement& ae, const string& action)
{
  TrafficLight *tl = static_cast<TrafficLight*>(ae.getHandle());
  if (tl != nullptr) {
    if (tl->output != nullptr) {
      tl->output->setOutput(true, false, false);
      tl->output->printState();
    }
  }
}

void bh_rd_yl(const AutomatonElement& ae, const string& action)
{
  TrafficLight *tl = static_cast<TrafficLight*>(ae.getHandle());
  if (tl != nullptr) {
    if (tl->output != nullptr) {
      tl->output->setOutput(true, true, false);
      tl->output->setSignal(false);
      tl->output->printState();
    }
  }
}

void bh_gr(const AutomatonElement& ae, const string& action)
{
  TrafficLight *tl = static_cast<TrafficLight*>(ae.getHandle());
  if (tl != nullptr) {
    if (tl->output != nullptr) {
      tl->output->setOutput(false, false, true);
      tl->output->printState();
    }
  }
}

void bh_gr_yl(const AutomatonElement& ae, const string& action)
{
  TrafficLight *tl = static_cast<TrafficLight*>(ae.getHandle());
  if (tl != nullptr) {
    if (tl->output != nullptr) {
      tl->output->setOutput(false, true, false);
      tl->output->printState();
    }
  }
}

void bh_problemDetect(const AutomatonElement& ae, const string& action)
{
  TrafficLight *tl = static_cast<TrafficLight*>(ae.getHandle());
  if (tl != nullptr) {
    if (tl->output != nullptr) {
      tl->output->setOutput(false, false, false);
      tl->output->printState();
    }
  }
}

bool gd_warn(const AutomatonElement& ae, const string& action)
{
  TrafficLight *tl = static_cast<TrafficLight*>(ae.getHandle());
  if (tl != nullptr)
    return (! tl->getHasController() && tl->getNeedsController());
  return false;
}

bool gd_rdyl(const AutomatonElement& ae, const string& action)
{
  TrafficLight *tl = static_cast<TrafficLight*>(ae.getHandle());
  if (tl != nullptr)
    if (tl->getNeedsController()) 
      return tl->getHasController() && tl->getControllerRequestedMode() == RQM_GREEN;
    else
      return (tl->sensor != nullptr) && tl->sensor->readValue();
  return false;
}

bool gd_yl(const AutomatonElement& ae, const string& action)
{
  TrafficLight *tl = static_cast<TrafficLight*>(ae.getHandle());
  if (tl != nullptr)
    if (time(nullptr) - tl->getLastTransitionTimestamp() > tl->getYellowPhaseLength() )
      return true;
  return false;
}

bool gd_gryl(const AutomatonElement& ae, const string& action)
{
  TrafficLight *tl = static_cast<TrafficLight*>(ae.getHandle());
  if (tl != nullptr) {
    if (tl->getNeedsController()) {
      if (tl->getAutonomousGreenPhase()) {
        if (time(nullptr) - tl->getLastTransitionTimestamp() > tl->getAutonomousGreenPhaseLength() )
          return true;
      }
      else
        return tl->getHasController() && tl->getControllerRequestedMode() == RQM_RED;
    }
    else
      if (time(nullptr) - tl->getLastTransitionTimestamp() > tl->getAutonomousGreenPhaseLength() )
        return true;
  }
  return false;
}

bool gd_standdownWarn(const AutomatonElement& ae, const string& action)
{
  TrafficLight *tl = static_cast<TrafficLight*>(ae.getHandle());
  if (tl != nullptr)
    if (tl->getNeedsController()) 
      return tl->getHasController();
    else 
      return true;
  return false;
}
