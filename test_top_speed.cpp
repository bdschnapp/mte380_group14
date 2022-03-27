#include "test_top_speed.hpp"
#include "dev_TB9051FTG.hpp"

namespace test_top_speed
{
    actuator::TB9051FTG motor_driver;

    constexpr auto TIME_OUT_MS = 8000;
    uint8_t start_time = 0;

    void app_setup()
    {
        Serial.begin(9600);
        Serial.println("Will floor it in 3 seconds! for a duration of 5 seconds!");
        Serial.println("Make sure the runway is clear!");
        Serial.println("BE READY TO RUN AND STOP IT");
        delay(3000);
        start_time = millis();
        motor_driver.set_motor_speeds(100, 100);
    }

    void app_loop()
    {
        if (millis() - start_time > TIME_OUT_MS)
        {
            Serial.println("Time elapsed. Robot will now hang forever.");
            motor_driver.set_motor_speeds(0, 0);
            delay(500);
            if (!motor_driver.disable_motors())
            {
                Serial.println("Failed to disable motors");
            }
            delay(200);
            exit(0);
        }
    }
}