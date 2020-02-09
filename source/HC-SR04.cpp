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

#include "HC-SR04.h"

HC_SR04::HC_SR04(MicroBitPin& trigger, MicroBitPin& echo, MicroBitMessageBus& msgBus, uint16_t echoEventId) :
    trigger(trigger),
    echo(echo),
    msgBus(msgBus),
    start(0),
    end(0),
    distance(0),
    distanceSet(false),
    echoEventId(echoEventId)
{
    // Enable event monitoring on the echo pin
    echo.eventOn(MICROBIT_PIN_EVENT_ON_EDGE);

    // Set up listeners for the start and end events on the echo pin
    msgBus.listen(echoEventId,MICROBIT_PIN_EVT_RISE,this,&HC_SR04::echoStart,MESSAGE_BUS_LISTENER_IMMEDIATE);
    msgBus.listen(echoEventId,MICROBIT_PIN_EVT_FALL,this,&HC_SR04::echoEnd,MESSAGE_BUS_LISTENER_IMMEDIATE);  
}

void HC_SR04::determineDistance(int pulseWidthuS)
{
    // Invalidate current distance
    distanceSet = false;

    // Send a pulse
    trigger.setDigitalValue(1);
    wait_us(pulseWidthuS);
    trigger.setDigitalValue(0);
}

bool HC_SR04::distanceAvailable() const
{
    return distanceSet;
}

int HC_SR04::readDistance() const
{
    return distance;
}

void HC_SR04::echoStart(MicroBitEvent)
{
    start = us_ticker_read();
}

void HC_SR04::echoEnd(MicroBitEvent)
{
    end = us_ticker_read();

    // Distance is half the time taken to get "there" and "back"
    // multiplied by the speed of sound.
    static const float SPEED_OF_SOUND_mm_us = 0.343;
    distance = (float)(end-start)/2 * SPEED_OF_SOUND_mm_us;

    // Record tha distance is now valid
    distanceSet = true;
}
