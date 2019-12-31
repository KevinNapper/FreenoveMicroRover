
#include "FreenoveMicroRover.h"

FreenoveMicroRover rover;

int main()
{
    rover.init();
    rover.serial.printf("%s\r\n", rover.getName().toCharArray());

    while (true) 
    {
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
    }
}

