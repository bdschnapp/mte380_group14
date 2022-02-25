#include "Arduino.h"
#include "dev_TB9051FTG.hpp"
#include "test_dev_TB9051FTG.hpp"

namespace test_dev_TB9051FTG
{
    actuator::TB9051FTG shield;

    void app_setup()
    {
        Serial.begin(9600);
        if (!shield.init()) {
            Serial.print("ERROR: fault while initializing motor shield");
        }
    }

    void app_loop()
    {
        for (double i = 0; i < 1; i = i + 0.01) {
            if (!shield.set_left_motor_speed(i)) {
                Serial.print("ERROR: fault while setting left motor");
            }
            delay(10);
        }
        for (double i = 1; i > 0; i = i - 0.01) {
            if (!shield.set_left_motor_speed(i)) {
                Serial.print("ERROR: fault while setting left motor");
            }
            delay(10);
        }
        delay(200);
        for (double i = 0; i < 1; i = i + 0.01) {
            if (!shield.set_right_motor_speed(i)) {
                Serial.print("ERROR: fault while setting right motor");
            }
            delay(10);
        }
        for (double i = 1; i > 0; i = i - 0.01) {
            if (!shield.set_right_motor_speed(i)) {
                Serial.print("ERROR: fault while setting right motor");
            }
            delay(10);
        }
        if (!shield.reset()) {
            Serial.print("ERROR: fault while resetting speed controllers");
        }
        delay(200);
        Serial.print("INFO: completed test cycle");

    }
}
