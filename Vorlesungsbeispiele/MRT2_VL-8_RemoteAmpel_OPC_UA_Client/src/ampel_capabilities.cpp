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

#include "ampel_capabilities.h"

ampel_capabilities::ampel_capabilities() : sensor(false), redLight(false), greenLight(false), yellowLight(false)
{};

ampel_capabilities::~ampel_capabilities()
{};

bool ampel_capabilities::getRedLight()
{ 
    return redLight; 
}

bool ampel_capabilities::getYellowLight()
{ 
    return yellowLight; 
}

bool ampel_capabilities::getGreenLight()
{ 
    return greenLight; 
}

bool ampel_capabilities::getSensor()
{ 
    return sensor; 
}

void ampel_capabilities::setRedLight(bool setLightOn)
{ 
    redLight = setLightOn;
    return; 
}

void ampel_capabilities::setYellowLight(bool setLightOn)
{ 
    yellowLight = setLightOn;
    return; 
}

void ampel_capabilities::setGreenLight(bool setLightOn)
{ 
    greenLight = setLightOn;
    return; 
}

void ampel_capabilities::setSensor(bool setSensorTriggered)
{
    sensor = setSensorTriggered;
}

