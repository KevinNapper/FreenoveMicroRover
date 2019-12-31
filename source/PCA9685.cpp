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

#include "MicroBit.h"
#include "PCA9685.h"
#include "ErrorNo.h"

PCA9685::PCA9685(MicroBitI2C& i2c, uint8_t address) :
    i2c(i2c),
    address(address)
{
    i2c.writeRegister(address,0,0);
    SetPWM(0,0);
    i2c.writeRegister(address,1,4);
    i2c.writeRegister(address,0,1);
//    fiber_sleep(5);
    uint8_t val = i2c.readRegister(address,0) & ~0x10;
    i2c.writeRegister(address,0,val);
//    fiber_sleep(5);
}

int PCA9685::SetPWM(uint16_t on, uint16_t off, int channel)
{
    if (channel < 0)
    {
        i2c.writeRegister(address,0xfa,on  & 0xFF);
        i2c.writeRegister(address,0xfb,on  >>   8);
        i2c.writeRegister(address,0xfc,off & 0xFF);
        i2c.writeRegister(address,0xfd,off >>   8);
    }
    else
    {
        i2c.writeRegister(address,0x06+4*channel,on  & 0xFF);
        i2c.writeRegister(address,0x07+4*channel,on  >>   8);
        i2c.writeRegister(address,0x08+4*channel,off & 0xFF);
        i2c.writeRegister(address,0x09+4*channel,off >>   8);
    }

    return MICROBIT_OK;
}