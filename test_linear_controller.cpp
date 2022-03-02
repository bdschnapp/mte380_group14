#include "test_linear_controller.hpp"
#include "dev_ultrasonic.hpp"

namespace test_linear_controller
{
    constexpr auto TARGET_DISTANCE = 0.1f;
    const float Kp = controllers::linear_controller::get_required_kp(0.0f);
    constexpr float linear_error_tolerance = 0.005;
    controllers::linear_controller lc(Kp, linear_error_tolerance);

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
                constexpr float steering = 0.0f;
                // younes todo need Max to finish his drivetrain code
                // drivetrain.set(gas = gas, steering = steering)
                delay(10);
            }
            else
            {
                // younes todo use Max's code to set motors to 0
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