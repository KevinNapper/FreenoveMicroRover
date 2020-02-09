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

#include "FreenoveMicroRover.h"

FreenoveMicroRover::FreenoveMicroRover() : 
    MicroBit(),
    pwmController(i2c,address),
    led({FreenoveMicroRoverLED(pwmController,0),
         FreenoveMicroRoverLED(pwmController,1),
         FreenoveMicroRoverLED(pwmController,2),
         FreenoveMicroRoverLED(pwmController,3)}),
    leftMotor(pwmController,0,1),
    rightMotor(pwmController,2,3),
    sounder(io.P0),
    ranger(io.P12,io.P13,messageBus,MICROBIT_ID_IO_P13)
{

}

int FreenoveMicroRover::SetLED(float brightness, float R, float G, float B, uint8_t bitField)
{
    for (int i = 0 ; i < 4 ; i++)
    {
        if (bitField & (1 << i))
        {
            led[i].Set(brightness,R,G,B);
        }
    }

    return 0;
}

int FreenoveMicroRover::SetMotors(float leftSpeed, float rightSpeed)
{
    leftMotor.Set(leftSpeed);
    rightMotor.Set(rightSpeed);
    return 0;
}

int FreenoveMicroRover::PlaySound(int frequency, int duration_ms)
{
    sounder.Play(frequency,duration_ms);
    return 0;
}

int FreenoveMicroRover::getRange()
{
    ranger.determineDistance();
    while (!ranger.distanceAvailable())
    {
        sleep(1);
    }
    return ranger.readDistance();
}
