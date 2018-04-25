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

#include "task.h"
#include "unistd.h"

task::~task()
{
    stop();
}
 
void task::init()
{
    return;
}

void task::run()
{
    return;
}

void task::terminate()
{
    return;
}

void task::stop()
{
    runThread = false;
    if (running) return;
    
    if (t != nullptr && t->joinable())
        t->join();
    
    t = nullptr; 
    running = false;
    return;
}

void task::workerThread()
{
    runThread = true;
    if (running) return;
    
    init();
    running=true;
    while(runThread) {
        run();
        nanosleep(&interval, NULL);
    }
    running=false;
    
    return;
}

void task::start()
{
    if (running) return;
    t = new thread(&task::workerThread, this);
    while(!running) {}
}
