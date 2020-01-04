
#include "FreenoveMicroRover.h"

FreenoveMicroRover rover;

int main()
{
    rover.init();
    rover.serial.printf("%s\r\n", rover.getName().toCharArray());

    while (true) 
    {
#if 0
        int i = 0;
        for (float b = 0 ; b < 1 ; b += 0.01)
        {
            rover.SetLED(b,
                        (double)rand() / (double)RAND_MAX,
                        (double)rand() / (double)RAND_MAX,
                        (double)rand() / (double)RAND_MAX,
                        1 << i);
            rover.SetLED(0,0,0,0,~(1 << i));
            if (++i >= 4) i = 0;
            rover.sleep(30);
        }

        rover.SetMotors(1,0);
        rover.sleep(1000);
        rover.SetMotors(-1,0);
        rover.sleep(1000);
        rover.SetMotors(0,1);
        rover.sleep(1000);
        rover.SetMotors(0,-1);
        rover.sleep(1000);
        rover.SetMotors(0,0);

        rover.PlaySound(300,1000);
        rover.PlaySound(150,1000);

        rover.io.P12.setDigitalValue(1);
        wait_us(15);
        rover.io.P12.setDigitalValue(0);
        while (rover.io.P13.getDigitalValue() == 0) {}
        uint32_t start = us_ticker_read();
        while (rover.io.P13.getDigitalValue() == 1) {}
        uint32_t end = us_ticker_read();
        uint32_t distance = ((end-start)*170)*0.0001;
        rover.serial.printf("%d %d %d\r\n", start, end, distance);
#endif
        rover.serial.printf("%d\r\n", rover.GetRange());

    }
}

