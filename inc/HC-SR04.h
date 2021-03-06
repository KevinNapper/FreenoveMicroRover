/*  
MIT License

Copyright (c) 2019-2020 Kevin Napper

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef HC_SR04_H
#define HC_SR04_H

#include "MicroBitIO.h"
#include "MicroBitMessageBus.h"

class HC_SR04
{
    public:

    HC_SR04(MicroBitPin& trigger, MicroBitPin& echo, MicroBitMessageBus& msgBus, uint16_t echoEventId);
    void determineDistance(int pulseWidthuS = 15);
    bool distanceAvailable() const;
    int readDistance() const;

    private:

    MicroBitPin&        trigger;
    MicroBitPin&        echo;
    MicroBitMessageBus& msgBus;
    uint32_t            start, end, distance;
    bool                distanceSet;
    uint16_t            echoEventId;

    void echoStart(MicroBitEvent e);
    void echoEnd(MicroBitEvent e);
};

#endif
