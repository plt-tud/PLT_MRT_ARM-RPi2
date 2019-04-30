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

#include "rPi_accessor.h"


rPi_Accessor* rPi_Accessor::instance = nullptr;

void rPi_Accessor::setGPIOInput(uint8_t GPIO)
{
#ifdef BUILD_RPI
  bcm2835_gpio_fsel(GPIO,    BCM2835_GPIO_FSEL_INPT);
#endif
}

void rPi_Accessor::setGPIOOutput(uint8_t GPIO)
{
#ifdef BUILD_RPI
    bcm2835_gpio_fsel(GPIO,    BCM2835_GPIO_FSEL_OUTP);
#endif
}

bool rPi_Accessor::getGPI(uint8_t GPIO)
{
#ifdef BUILD_RPI
    return (bcm2835_gpio_lev(GPIO) == 1);
#else
#warning RPI being used for input but no RPI_BUILD Defined!
    return false;
#endif
}

void rPi_Accessor::setGPO(uint8_t GPIO, bool value)
{
#ifdef BUILD_RPI
    if (value)
        bcm2835_gpio_set(GPIO);
    else
        bcm2835_gpio_clr(GPIO);
#endif
}
