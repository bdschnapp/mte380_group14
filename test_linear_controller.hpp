#ifndef __TEST_LINEAR_CONTROLLER_HPP__
#define __TEST_LINEAR_CONTROLLER_HPP__

#include "linear_controller.hpp"

/*
Test Setup:
1. Place the robot on a level surface facing a flat surface (ie. wall) more than 10cm away
2. Ensure the front ultrasonic sensor is connected and working
3. Ensure the motor driver and drivetrain logic work
4. Put some type of marking 10 cm away from the wall
5. Run the this test. The robot should drive straight forward and stop on the tape
6. Ensure the robot stops where expected

Note:
This only tests our linear controller not our angular controller. The linear controller
does not ensure the robot drives perfectly straight, this is the job of the angular controller.
For this reason, the robot might not drive perfectly straight in this test.
*/

namespace test_linear_controller
{
    void app_setup();

    void app_loop();
}

#endif