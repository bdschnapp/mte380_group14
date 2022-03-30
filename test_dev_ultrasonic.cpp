#include "test_dev_ultrasonic.hpp"
#include "app_defines.hpp"

namespace test_dev_ultrasonic {

    sensor::ultrasonic_init_config_s initConfigFront;
    sensor::ultrasonic_init_config_s initConfigSide;

    sensor::Ultrasonic front_sensor;
    sensor::Ultrasonic side_sensor;

    float distance;

    void app_setup() {
        Serial.begin(9600);
        initConfigFront.echoPin = FRONT_ULTRASONIC_ECHO_PIN;
        initConfigFront.trigPin = FRONT_ULTRASONIC_TRIG_PIN;
        initConfigSide.echoPin = SIDE_ULTRASONIC_ECHO_PIN;
        initConfigSide.trigPin = SIDE_ULTRASONIC_TRIG_PIN;

        front_sensor.init(initConfigFront);
        side_sensor.init(initConfigSide);
    }

    void app_loop() {
        front_sensor.run10ms();
        side_sensor.run10ms();

        if (front_sensor.get_distance(distance)) {
            Serial.print("front: ");
            Serial.print(distance);
            Serial.print(" m  ");
        } else {
            Serial.println("Error");
        }
        if (side_sensor.get_distance(distance)) {
            Serial.print("side: ");
            Serial.print(distance);
            Serial.println(" m  ");
        } else {
            Serial.println("Error");
        }

        delay(10);
    }
}
