#ifndef __TEST_PIVOT_CONTROLLER_HPP__
#define __TEST_PIVOT_CONTROLLER_HPP__

#include "pivot_controller.hpp"

/*
Test Setup:
1. Place the robot on a flat surface
2. Ensure the imu driver is working properly
3. Ensure the motor driver and drivetrain logic work
4. Create two orthogonal axes on the ground like this: |__
5. Align the robot with the vertical axis
6. Run the program
7. The robot should rotate 90 degrees cw to the horizontal axis, wait 1 second, and then turn back
*/

namespace test_pivot_controller
{
    void app_setup();

    void app_loop();
}

#endif