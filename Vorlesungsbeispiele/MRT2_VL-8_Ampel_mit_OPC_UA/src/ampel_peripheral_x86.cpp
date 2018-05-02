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

#include <iostream>
#include <string.h>
using namespace std;

#include "ampel_peripheral_x86.h"


static void paintScreen(bool red, bool green, bool yellow) 
{
    // cout << string( 100, '\n' ); // Generische, aber sehr bloede Methode fuer ClearScreen
    cout << "\x1B[2J\x1B[H"; // ANSI Console only... clear screen, move cursor to first position

    cout << endl;
    cout << "+---+" << endl;
    if (red)
        cout << "+ o +" << endl;
    else
        cout << "+   +" << endl;
    cout << "+---+" << endl;
    if (yellow)
        cout << "+ o +" << endl;
    else
        cout << "+   +" << endl;
    cout << "+---+" << endl;
    if (green)
        cout << "+ o +" << endl;
    else
        cout << "+   +" << endl;
    cout << "+---+" << endl;
}

ampel_peripheral_x86::ampel_peripheral_x86()
{
}
ampel_peripheral_x86::~ampel_peripheral_x86()
{
}

void ampel_peripheral_x86::setRedLight(bool setLightOn)
{
    redLight = setLightOn;
    paintScreen(redLight, greenLight, yellowLight);
}

void ampel_peripheral_x86::setYellowLight(bool setLightOn)
{
    yellowLight = setLightOn;
    paintScreen(redLight, greenLight, yellowLight);
}

void ampel_peripheral_x86::setGreenLight(bool setLightOn)
{
    greenLight = setLightOn;
    paintScreen(redLight, greenLight, yellowLight);
}
