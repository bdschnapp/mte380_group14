#ifndef __TEST_ANGULAR_CONTROLLER_HPP__
#define __TEST_ANGULAR_CONTROLLER_HPP__

#include "angular_controller.hpp"

/*
Test Setup:
1. Place the robot down on a level surface
2. Ensure the imu is connected and working
3. Ensure the motor driver and drivetrain logic work
4. Run this test
5. Observe that the robot drive straight forward

Note:
Be ready to manually stop the robot.
This program will attempt to drive forward indefinitely.
*/

namespace test_angular_controller
{
    void app_setup();

    void app_loop();
}

#endif