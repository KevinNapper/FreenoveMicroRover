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

#include "FreenoveMicroRoverMotor.h"

FreenoveMicroRoverMotor::FreenoveMicroRoverMotor(PCA9685& controller, uint8_t fwdChn, uint8_t revChn):
    controller(controller),
    forwardChannel(fwdChn),
    reverseChannel(revChn)
{

}

int FreenoveMicroRoverMotor::Set(float speed)
{
    if (speed > 0)
    {
        controller.SetPWM(0,4095.0*speed,forwardChannel);
        controller.SetPWM(0,0,reverseChannel);
    }
    else if (speed < 0)
    {
        controller.SetPWM(0,0,forwardChannel);
        controller.SetPWM(0,4095.0*abs(speed),reverseChannel);
    }
    else
    {
        controller.SetPWM(0,0,forwardChannel);
        controller.SetPWM(0,0,reverseChannel);
    }
    return 0;
}
