/*
 * Copyright (c) 2018 Chris Iatrou <Chris_Paul.Iatrou@tu-dresden.de>
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

#ifndef REMOTEAMPEL_H
#define REMOTEAMPEL_H

#include <string>
#include <mutex>

#include "Ampel_typeDefinitions.h"

#include "task.h"
#include "open62541.h"

class RemoteAmpel : public task
{
public:
  RemoteAmpel(std::string ampelUri) :  client(nullptr), serverURI(ampelUri) {};
  
  bool getRedLight();
  void setRedLight(bool setLightOn);
  
  void setYellowLight(bool setLightOn);
  bool getYellowLight();
  
  void setGreenLight(bool setLightOn);
  bool getGreenLight();
  
  void setSensor(bool setSensorTriggered);
  bool getSensor();

  void setController(bool present);
  bool hasController();

  void setPhaseCommand(ampel_phaseId command);
  ampel_phaseId getPhaseCommand();
  
protected:
  virtual void init();
  virtual void run();
  virtual void terminate();

private:
  mutex     clientMutex;
  UA_Client *client;
  std::string serverURI;
  
  void setRemoteBoolean(std::string StringNodeId, bool value);
  bool getRemoteBoolean(std::string StringNodeId);
};

#endif // REMOTEAMPEL_H
