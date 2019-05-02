/*
 * Copyright (c) 2018 Chris Paul Iatrou chris_paul.iatrou@tu-dresden.de
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

#ifndef TASK_H
#define TASK_H

#include <thread>
#include <list>
#include <time.h>

using namespace std;

class task
{
    
protected:
    bool runThread;
    bool running;
    thread *t;
    
    timespec interval;
    
    list<task*> children;
    void workerThread();
    
    virtual void init();
    virtual void run() = 0;
    virtual void terminate();
    
public:
    task(struct timespec interval) : runThread(false), running(false),  interval(interval) {};
    task() : runThread(false), running(false),  interval((struct timespec) {1,0} ) {};
    virtual ~task();
    
    void start();
    void stop();
};

#endif // TASK_H
