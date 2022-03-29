#ifndef __TEST_DEV_BNO055_HPP__
#define __TEST_DEV_BNO055_HPP__

/* 
Test Setup:
1. Follow the configuration described below.
2. Run the test.
3. Observe serial output.

HW CONFIG:
Vin: Connect to 5v
GND: Connect to ground
SDA & SCL:  Any I2C bus on the arduino (ie. for UNO, SCL = A5; SDA = A4 will work)
*/

namespace test_dev_bno055
{
    void app_setup();

    void app_loop();
}

#endif