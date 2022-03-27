#ifndef __TEST_TURNING_RADIUS_HPP__
#define __TEST_TURNING_RADIUS_HPP__

#include "pivot_controller.hpp"

/*
This test is for demoing to the prof on March 28
Test Setup:
1. Place the robot inside the pit
2. Ensure the imu driver is working properly
3. Ensure the motor driver and drivetrain logic work
6. Run the program
7. The robot will rotate 90 deg and stop. Ensure it did not cross the pit boundary.
*/

namespace test_turning_radius
{
    void app_setup();

    void app_loop();
}

#endif