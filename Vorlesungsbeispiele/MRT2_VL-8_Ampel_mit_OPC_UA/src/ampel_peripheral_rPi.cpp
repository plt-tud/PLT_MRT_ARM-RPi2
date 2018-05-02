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

#include "ampel_peripheral_rPi.h"


ampel_peripheral_rPi::ampel_peripheral_rPi(uint8_t redGPO, uint8_t yellowGPO, uint8_t greenGPO, uint8_t sensorGPI) : 
    redGPO(redGPO), yellowGPO(yellowGPO), greenGPO(greenGPO), sensorGPI(sensorGPI)
{
    rPi = rPi_Accessor::getInstance();
    rPi->setGPIOOutput(redGPO);
    rPi->setGPIOOutput(yellowGPO);
    rPi->setGPIOOutput(greenGPO);
    rPi->setGPIOInput(sensorGPI);
    
    rPi->setGPO(redGPO, false);
    rPi->setGPO(yellowGPO, false);
    rPi->setGPO(greenGPO, false);
}


bool ampel_peripheral_rPi::getSensor()
{
    return rPi->getGPI(sensorGPI);
}

void ampel_peripheral_rPi::setRedLight(bool setLightOn)
{
    redLight = setLightOn;
    rPi->setGPO(redGPO, setLightOn);
}

void ampel_peripheral_rPi::setYellowLight(bool setLightOn)
{
    yellowLight = setLightOn;
    rPi->setGPO(yellowGPO, setLightOn);
}

void ampel_peripheral_rPi::setGreenLight(bool setLightOn)
{
    greenLight = setLightOn;
    rPi->setGPO(greenGPO, setLightOn);
}
