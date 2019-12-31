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

#ifndef FREENOVE_MICRO_ROVER_H
#define FREENOVE_MICRO_ROVER_H

#include "MicroBit.h"
#include "FreenoveMicroRoverLED.h"
#include "FreenoveMicroRoverMotor.h"

class FreenoveMicroRover : public MicroBit
{
    private:
        static const uint8_t address = 0x43 << 1;
        PCA9685 pwmController;
        FreenoveMicroRoverLED led[4];
        FreenoveMicroRoverMotor leftMotor;
        FreenoveMicroRoverMotor rightMotor;

    public:

        FreenoveMicroRover();
        int SetLED(float brightness, float R, float G, float B, uint8_t bitField = 0xff);
        int SetMotors(float leftSpeed, float rightSpeed);

    static ManagedString getName() {return "FreenoveMicroRover:" + MicroBit::getName();}
};

#endif
