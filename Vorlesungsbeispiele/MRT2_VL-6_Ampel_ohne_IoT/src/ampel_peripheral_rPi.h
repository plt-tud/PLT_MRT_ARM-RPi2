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

#ifndef PERIPHERAL_RPI_H
#define PERIPHERAL_RPI_H

#include "ampel_capabilities.h"
#include <stdint.h>
#include "rPi_accessor.h"

class ampel_peripheral_rPi : public ampel_capabilities
{
protected:
    uint8_t redGPO;
    uint8_t yellowGPO;
    uint8_t greenGPO;
    uint8_t sensorGPI;
    
    rPi_Accessor *rPi;
public:
    ampel_peripheral_rPi(uint8_t redGPO, uint8_t yellowGPO, uint8_t greenGPO, uint8_t sensorGPI);
    
    bool getSensor();
    void setRedLight(bool setLightOn);
    void setYellowLight(bool setLightOn);
    void setGreenLight(bool setLightOn);
};

#endif // PERIPHERAL_RPI_H
