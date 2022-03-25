#include "test_drivetrain.hpp"
#include "drivetrain.hpp"
#include <Arduino.h>
#include "lib_math.hpp"

namespace test_drivetrain
{
    bool test_translation_motion_convert()
    {
        constexpr auto TEST_CASES = 7U;
        constexpr float gas_values[TEST_CASES] = {0, 100, 50, 100, 100, 100, 100};
        constexpr float steering_values[TEST_CASES] = {0, 0, 0, 50, -50, 100, -100};
        constexpr float expected_left_motor_speed[TEST_CASES] = {0, 100, 50, 50, 100, 0, 100};
        constexpr float expected_right_motor_speed[TEST_CASES] = {0, 100, 50, 100, 50, 100, 0};

        for (uint8_t i = 0; i < TEST_CASES; ++i)
        {
            const auto motor_speeds = drivetrain::translational_motion_convert(gas_values[i], steering_values[i]);
            if (!math::float_compare(motor_speeds.left_motor_speed, expected_left_motor_speed[i]) ||
                !math::float_compare(motor_speeds.right_motor_speed, expected_right_motor_speed[i]))
            {
                return false;
            }
        }
        return true;
    }

    bool test_point_turn_convert()
    {
        constexpr auto TEST_CASES = 5U;
        constexpr float steering_power_values[TEST_CASES] = {0, 100, -100, 50, -50};
        constexpr float expected_left_motor_speed[TEST_CASES] = {0, -100, 100, -50, 50};
        constexpr float expected_right_motor_speed[TEST_CASES] = {0, 100, -100, 50, -50};

        for (uint8_t i = 0; i < TEST_CASES; ++i)
        {
            const auto motor_speeds = drivetrain::point_turn_convert(steering_power_values[i]);
            if (!math::float_compare(motor_speeds.left_motor_speed, expected_left_motor_speed[i]) ||
                !math::float_compare(motor_speeds.right_motor_speed, expected_right_motor_speed[i]))
            {
                return false;
            }
        }
        return true;
    }

    void app_setup()
    {
        Serial.begin(9600);
    }

    void app_loop()
    {
        if (test_translation_motion_convert())
        {
            Serial.println("INFO: test_translation_motion_convert PASSED");
        }
        else
        {
            Serial.println("ERROR: test_translation_motion_convert FAILED");
        }

        if (test_point_turn_convert())
        {
            Serial.println("INFO: test_point_turn_convert PASSED");
        }
        else
        {
            Serial.println("ERROR: test_point_turn_convert FAILED");
        }

        delay(5000);
    }

}