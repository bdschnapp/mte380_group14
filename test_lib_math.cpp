#include "Arduino.h"
#include "lib_math.hpp"
#include "test_lib_math.hpp"

namespace test_lib_math
{

    bool test_math_deg_to_rad()
    {
        constexpr auto SAMPLES = 6;
        const float degrees[SAMPLES] = {-180.0f, -90.0f, 0.0f, 90.0f, 180.0f, 45.0f};
        const float radians[SAMPLES] = {-PI, -PI / 2.0f, 0.0f, PI / 2.0f, PI,
                                        PI / 4.0f};
        for (uint8_t i = 0; i < SAMPLES; ++i)
        {
            if (!math::float_compare(math::deg_to_rad(degrees[i]), radians[i]))
            {
                return false;
            }
        }
        return true;
    }

    bool test_math_rad_to_deg()
    {
        constexpr auto SAMPLES = 6;
        const float degrees[SAMPLES] = {-180.0f, -90.0f, 0.0f, 90.0f, 180.0f, 45.0f};
        const float radians[SAMPLES] = {-PI, -PI / 2.0f, 0.0f, PI / 2.0f, PI,
                                        PI / 4.0f};
        for (uint8_t i = 0; i < SAMPLES; ++i)
        {
            if (!math::float_compare(math::rad_to_deg(radians[i]), degrees[i]))
            {
                return false;
            }
        }
        return true;
    }

    bool test_clamp()
    {
        constexpr float lower_bound = -100.0f;
        constexpr float upper_bound = 100.0f;

        bool success = math::float_compare(math::clamp(lower_bound, upper_bound, 56.0f), 56.0f);
        success &= math::float_compare(math::clamp(lower_bound, upper_bound, 110.0f), upper_bound);
        success &= math::float_compare(math::clamp(lower_bound, upper_bound, -110.0f), lower_bound);
        return success;
    }

    void app_setup()
    {
        Serial.begin(9600);
    }

    void app_loop()
    {
        if (test_math_rad_to_deg())
        {
            Serial.println("INFO: math::deg_to_rad unit test PASSED");
        }
        else
        {
            Serial.println("ERROR: math::deg_to_rad unit test FAILED");
        }

        if (test_math_deg_to_rad())
        {
            Serial.println("INFO: math::rad_to_deg unit test PASSED");
        }
        else
        {
            Serial.println("ERROR: math::rad_to_deg unit test FAILED");
        }

        if (test_clamp())
        {
            Serial.println("INFO: math::clamp unit test PASSED");
        }
        else
        {
            Serial.println("ERROR: math::clamp unit test FAILED");
        }

        delay(5000);
    }
}