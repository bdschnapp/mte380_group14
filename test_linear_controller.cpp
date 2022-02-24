#include "test_linear_controller.hpp"
#include "dev_ultrasonic.hpp"
#include "robot_pinout.hpp"

/*
Test Setup:
1. Place the robot on a level surface facing a flat surface (ie. wall) more than 10cm away
2. Ensure the front ultrasonic sensor is connected and working
2. Put some type of marking 10 cm away from the wall
3. Run the this test. The robot should drive straight forward and stop on the tape
4. Ensure the robot stops where expected

Note:
This only tests our linear controller not our angular controller. The linear controller
does not ensure the robot drives perfectly straight, this is the job of the angular controller.
For this reason, the robot might not drive perfectly straight in this test.
*/

namespace test_linear_controller
{
    constexpr auto TARGET_DISTANCE = 0.1f;
    const float Kp = controllers::linear_controller::get_required_kp(0.0f);
    constexpr float linear_error_tolerance = 0.005;
    controllers::linear_controller lc(Kp, linear_error_tolerance);

    sensor::Ultrasonic front_us;
    void app_setup()
    {
        lc.set_target_distance(TARGET_DISTANCE);
        if (front_us.init({FRONT_ULTRASONIC_TRIG_PIN, FRONT_ULTRASONIC_ECHO_PIN}))
        {
            Serial.println("Succesfully initialized front ultrasonic sensor");
        }
        else
        {
            Serial.println("Failed to initialize front ultrasonic sensor");
        }
    }

    void app_loop()
    {
        front_us.run10ms();
        float front_us_distance = -1.0f;
        if (front_us.get_distance(front_us_distance))
        {
            if (!lc.target_distance_reached(front_us.get_distance()))
            {
                const float gas = lc.compute_gas(front_us_distance);
                // younes todo need Max to finish his drivetrain code
                // drivetrain.set(gas = gas, steering = 0)
                delay(10);
            }
            else
            {
                Serial.println("The robot has reached the target distance. Test is done. Robot will now hang. Restart robot to restart test");
                exit(0);
            }
        }
        else
        {
            Serial.println("Failed to read from front ultrasonic sensor");
        }
    }
}