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

#ifndef RPI_ACCESSOR_H
#define RPI_ACCESSOR_H

#include <stdint.h>
#include "bcm2835.h"

class rPi_Accessor
{
private:
    static rPi_Accessor *instance;

    rPi_Accessor()  { 
        #ifdef BUILD_RPI
            bcm2835_init(); 
        #endif
    };
    ~rPi_Accessor() { 
        #ifdef BUILD_RPI
            bcm2835_close(); 
        #endif
    };    
    
public:
    rPi_Accessor(rPi_Accessor const&)   = delete;
    void operator=(rPi_Accessor const&) = delete;
    
    static rPi_Accessor* getInstance()
    {
        if (!instance) {
            instance = new rPi_Accessor();
        }
        
        return instance;
    };
    
    
    void setGPIOOutput(uint8_t GPIO);
    void setGPIOInput(uint8_t GPIO);
    void setGPO(uint8_t GPIO, bool value);
    bool getGPI(uint8_t GPIO);
};

#endif // RPI_ACCESSOR_H
