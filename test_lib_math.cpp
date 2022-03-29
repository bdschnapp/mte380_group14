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

    bool test_vector_addition()
    {
        const math::Vector3f v1 = {1, 5, 10}, v2 = {4, 18.3, 8};
        const auto result = v1 + v2;
        return math::float_compare(result.x, 5) && math::float_compare(result.y, 23.3) && math::float_compare(result.z, 18);
    }

    bool test_vector_subtraction()
    {
        const math::Vector3f v1 = {1, 5, 10}, v2 = {4, 18.3, 8};
        const auto result = v1 - v2;
        return math::float_compare(result.x, -3) && math::float_compare(result.y, -13.3) && math::float_compare(result.z, 2);
    }

    bool test_lerp()
    {
        float start = 0;
        float end = 10;
        float alpha = 0.5;
        float result = math::lerp(start, end, alpha);
        return math::float_compare(result, 5.0);
    }

    bool test_unlerp()
    {
        float start = 0;
        float end = 10;
        float value = 5;
        return math::float_compare(math::unlerp(start, end, value), 0.5);
    }

    bool test_remap()
    {
        float old_start = 0;
        float old_end = 10;
        float value = 5;
        float new_start = 100;
        float new_end = 200;
        return math::float_compare(math::remap(old_start, old_end, value, new_start, new_end), 150);
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

        if (test_vector_addition())
        {
            Serial.println("INFO: vector addition unit test PASSED");
        }
        else
        {
            Serial.println("ERROR: vector addition unit test FAILED");
        }

        if (test_vector_subtraction())
        {
            Serial.println("INFO: vector subtraction unit test PASSED");
        }
        else
        {
            Serial.println("ERROR: vector subtraction unit test FAILED");
        }

        if (test_lerp())
        {
            Serial.println("INFO: lerp unit test PASSED");
        }
        else
        {
            Serial.println("ERROR:lerp unit test FAILED");
        }

        if (test_unlerp())
        {
            Serial.println("INFO: unlerp unit test PASSED");
        }
        else
        {
            Serial.println("ERROR: unlerp unit test FAILED");
        }

        if (test_remap())
        {
            Serial.println("INFO: remap unit test PASSED");
        }
        else
        {
            Serial.println("ERROR: remap unit test FAILED");
        }

        delay(5000);
    }
}