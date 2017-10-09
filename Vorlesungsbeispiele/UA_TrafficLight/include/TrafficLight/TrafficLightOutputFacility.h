/*
 * Copyright (c) 2016 Chris Iatrou <Chris_Paul.Iatrou@tu-dresden.de>
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

#ifndef TRAFFICLIGHTOUTPUTFACILITY_H
#define TRAFFICLIGHTOUTPUTFACILITY_H

#include "ua_mapped_class.h"

typedef struct TrafficLightOutputFacility_config_t 
{
  bool hasSignal;
  bool hasYellow;
  const void (*extended_setOutput)(bool red, bool yellow, bool green);
  const void (*extended_setSignal)(bool signal);
} TrafficLightOutputFacility_config;

class TrafficLightOutputFacility : ua_mapped_class
{
private:
  bool signal;
  bool red;
  bool yellow;
  bool green;
  const bool hasSignal;
  const bool hasYellow;
  
  const void (*extended_setOutput)(bool red, bool yellow, bool green);
  const void (*extended_setSignal)(bool signal);
  UA_StatusCode ua_mapSelfToNamespace();
public:
  bool getRedStatus();
  bool getYellowStatus();
  bool getGreenStatus();
  bool getHasSignal();
  bool getHasYellow();
  
  TrafficLightOutputFacility(TrafficLightOutputFacility_config config);
  TrafficLightOutputFacility(TrafficLightOutputFacility_config config, UA_Server *server, UA_NodeId baseNodeId);
  
  virtual void setSignal(bool signal);
  virtual bool getSignal();
  virtual void setOutput(bool red, bool yellow, bool green);
  virtual void toggleWarnIndicator();
  void printState();
};

#endif // TRAFFICLIGHTOUTPUTFACILITY_H
