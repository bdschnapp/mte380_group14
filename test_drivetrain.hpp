#ifndef MTE380_GROUP14_TEST_DRIVETRAIN_H
#define MTE380_GROUP14_TEST_DRIVETRAIN_H

#include <Arduino.h>
#include "drivetrain.hpp"

namespace test_drivetrain
{
    /*
        This test case involves driving the robot, without sensor feedback
        to demonstrate the drivetrain class. Ensure motors are connected
        and robot is placed on the ground. Will drive forwards, turn left, 
        turn right and drive backwards before pausing then repeating.
    */
    void app_setup();

    void app_loop();
}

#endif //MTE380_GROUP14_TEST_DRIVETRAIN_H
