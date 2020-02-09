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

FreenoveMicroRover rover;

int main()
{
    rover.init();
    rover.serial.printf("%s\r\n", rover.getName().toCharArray());

    while (true) 
    {
        // If obsticles are far away then full speed
        if (rover.getRange() > 400)
        {
            rover.SetLED(1,0,1,0,0xff);
            rover.SetMotors(1,1);
            rover.sleep(50);
        }
        // If obsticles closer then slow speed
        else if (rover.getRange() > 200)
        {
            rover.SetLED(1,0,0,1,0xff);
            rover.SetMotors(0.5,0.5);
            rover.sleep(50);
        }
        // If obsticles very close then scan for avoidance
        else
        {
            rover.SetLED(1,1,0,0,0xff);
            int n = 0;
            do {
                n++;
                rover.SetMotors((n % 2)?0.5:-0.5,
                                (n % 2)?-0.5:0.5);
                rover.sleep(n*50);
                rover.SetMotors(0,0);
                rover.sleep(200);
            } while (rover.getRange() <= 200);
            rover.SetMotors((n % 2)?0.5:-0.5,
                            (n % 2)?-0.5:0.5);
            rover.sleep(50);
        }
    }
}

