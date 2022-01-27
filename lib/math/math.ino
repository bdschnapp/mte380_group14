#include "Arduino.h"
#include "lib_math.hpp"

bool test_math_rad_to_deg();
bool test_math_deg_to_rad();

void setup()
{
    Serial.begin(9600);
}

void loop()
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

    delay(5000);
}

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
