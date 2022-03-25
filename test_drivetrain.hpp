#ifndef __TEST_DRIVETRAIN_HPP__
#define __TEST_DRIVETRAIN_HPP__

/*
About:
This test involves no IO. It's just math.
The test checks the output of the drivetrain functions for a couple inputs.
The following table shows the expected values

translational_motion_convert test cases:
Gas | Steering | left_motor_speed | right_motor_speed
0   |   0      |        0         |         0
100 |   0      |        100       |         100
50  |   0      |        50        |         50
100 |   50     |        50        |         100
100 |   -50    |        100       |         50
100 |   100    |        0         |         100
100 |   -100   |        100       |         0

point_turn_convert test cases:
Steering Power  | left_motor_speed  | right_motor_speed
0               |       0           |       0
100             |       -100        |       100
-100            |       100         |       -100
50              |       -50         |       50
-50             |       50          |       -50

*/

namespace test_drivetrain
{
    void app_setup();

    void app_loop();
}

#endif