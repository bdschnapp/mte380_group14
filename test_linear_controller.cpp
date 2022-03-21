#include "test_linear_controller.hpp"
#include "dev_ultrasonic.hpp"
#include "robot_pinout.hpp"
#include "drivetrain.hpp"
#include "dev_TB9051FTG.hpp"

namespace test_linear_controller
{
    constexpr auto TARGET_DISTANCE = 0.1f;
    const float Kp = controllers::linear_controller::get_required_kp(0.0f);
    constexpr float linear_error_tolerance = 0.005;
    controllers::linear_controller lc(Kp, linear_error_tolerance);
    actuator::TB9051FTG motor_driver;

    sensor::Ultrasonic front_us;
    void app_setup()
    {
        Serial.begin(9600);
        lc.set_target_distance(TARGET_DISTANCE);
        lc.set_debounce(0);
        if (front_us.init({FRONT_ULTRASONIC_TRIG_PIN, FRONT_ULTRASONIC_ECHO_PIN}))
        {
            Serial.println("Succesfully initialized front ultrasonic sensor");
        }
        else
        {
            Serial.println("Failed to initialize front ultrasonic sensor. ABORTING TEST");
            exit(0);
        }

        if (motor_driver.init())
        {
            Serial.println("Succesfully initialized motor driver");
        }
        else
        {
            Serial.println("Failed to initialize motor driver. ABORTING TEST");
            exit(0);
        }
    }

    void app_loop()
    {
        front_us.run10ms();
        float front_us_distance = -1.0f;
        if (front_us.get_distance(front_us_distance))
        {
            if (!lc.target_distance_reached(front_us.get_distance(front_us_distance)))
            {
                const float gas = lc.compute_gas(front_us_distance);
                constexpr float steering = 0.0f;
                const auto motor_speeds = drivetrain::translational_motion_convert(gas, steering);
                if (!motor_driver.set_motor_speeds(motor_speeds.left_motor_speed, motor_speeds.right_motor_speed))
                {
                    Serial.println("Failed to set motor speeds");
                }
                delay(10);
            }
            else
            {
                Serial.println("The robot has reached the target distance. Test is done. Robot will now hang. Restart robot to restart test");
                if (!motor_driver.disable_motors())
                {
                    Serial.println("Failed to disable motors");
                }
                exit(0);
            }
        }
        else
        {
            Serial.println("Failed to read from front ultrasonic sensor");
        }
    }
}