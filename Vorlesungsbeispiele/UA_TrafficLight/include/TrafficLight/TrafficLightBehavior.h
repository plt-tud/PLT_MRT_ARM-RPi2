/*
 * Copyright (c) 2016 Chris Iatrou <Chris_Paul.Iatrou@tu-dresden.de>
 * Chair for Process Systems Engineering
 * Technical University of Dresden
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

#ifndef TRAFFICLIGHTBEHAVIOR_H
#define TRAFFICLIGHTBEHAVIOR_H

#include "AutomatonElement.h"

void bh_sensorUpdate(const AutomatonElement& ae, const string& action);
void bh_sensClrLatch(const AutomatonElement& ae, const string& action);
void emt_updateTransitionTimestamp(const AutomatonElement& ae, const string& action);

void bh_warnProblem(const AutomatonElement& ae, const string& action);

void bh_rd(const AutomatonElement& ae, const string& action);
void bh_rd_yl(const AutomatonElement& ae, const string& action);
void bh_gr(const AutomatonElement& ae, const string& action);
void bh_gr_yl(const AutomatonElement& ae, const string& action);
void bh_problemDetect(const AutomatonElement& ae, const string& action);

bool gd_warn(const AutomatonElement& ae, const string& action);
bool gd_rdyl(const AutomatonElement& ae, const string& action);
bool gd_yl(const AutomatonElement& ae, const string& action);
bool gd_gryl(const AutomatonElement& ae, const string& action);
bool gd_standdownWarn(const AutomatonElement& ae, const string& action);

#endif