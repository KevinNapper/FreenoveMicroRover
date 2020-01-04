/*  
MIT License

Copyright (c) 2019 Kevin Napper

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

#include "HC-SR04.h"

HC_SR04::HC_SR04(MicroBitPin& trigger, MicroBitPin& echo) :
    trigger(trigger),
    echo(echo)
{

}

int HC_SR04::getDistance(int pulseWidthuS)
{
    trigger.setDigitalValue(1);
    wait_us(pulseWidthuS);
    trigger.setDigitalValue(0);

    while (echo.getDigitalValue() == 0) {}
    uint32_t start = us_ticker_read();
    while (echo.getDigitalValue() == 1) {}
    uint32_t end = us_ticker_read();

    static const float SPEED_OF_SOUND_mm_us = 0.343;
    return (float)(end-start)/2 * SPEED_OF_SOUND_mm_us;
}

