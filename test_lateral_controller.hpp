#ifndef __TEST_LATERAL_CONTROLLER_HPP__
#define __TEST_LATERAL_CONTROLLER_HPP__

/*
Test Setup:
1. Place the robot down on a level surface
2. Ensure the robot is oriented parallel to a wall
3. Ensure the robot is a distance of 10 cm from the wall
4. Ensure the imu is connected and working
5. Ensure the lateral ultrasonic is connected and working
6. Ensure the motor driver and drivetrain logic work
7. Run this test
8. Observe that the robot drives straight forward

Note:
Be ready to manually stop the robot.
This program will attempt to drive forward indefinitely.
*/

namespace test_lateral_controller
{
    void app_setup();

    void app_loop();
}

#endif