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
        // Delay included in case motors are physically running, 
        // allows user time to position robot after connecting battery
        delay(10000);
        Serial.print("starting in 3 seconds\n");
        delay(3000);
        Serial.print("left motor positive\n");
        for (double i = 0; i < 100; ++i) {
            if (!shield.set_left_motor_speed(i)) {
                Serial.print("ERROR: fault while setting left motor\n");
            }
            delay(10);
        }
        Serial.print("left motor negative\n");

        for (double i = 100; i > 0; --i) {
            if (!shield.set_left_motor_speed(i)) {
                Serial.print("ERROR: fault while setting left motor\n");
            }
            delay(10);
        }
        delay(200);
        Serial.print("right motor positive\n");

        for (double i = 0; i < 100; ++i) {
            if (!shield.set_right_motor_speed(i)) {
                Serial.print("ERROR: fault while setting right motor\n");
            }
            delay(10);
        }
        Serial.print("right motor negative\n");

        for (double i = 100; i > 0; --i) {
            if (!shield.set_right_motor_speed(i)) {
                Serial.print("ERROR: fault while setting right motor\n");
            }
            delay(10);
        }
        if (!shield.reset()) {
            Serial.print("ERROR: fault while resetting speed controllers\n");
        }
        Serial.print("INFO: completed test cycle\n");

    }
}
