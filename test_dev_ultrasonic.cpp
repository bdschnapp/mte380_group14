#include "test_dev_ultrasonic.hpp"
#include "app_defines.hpp"

namespace test_dev_ultrasonic {

    sensor::ultrasonic_init_config_s initConfig;

    sensor::Ultrasonic distance_sensor;

    float distance;

    void app_setup() {
        Serial.begin(9600);
        initConfig.echoPin = FRONT_ULTRASONIC_ECHO_PIN;
        initConfig.trigPin = FRONT_ULTRASONIC_TRIG_PIN;

        distance_sensor.init(initConfig);
    }

    void app_loop() {
        distance_sensor.run10ms();

        if (distance_sensor.get_distance(distance)) {
            Serial.print(distance);
            Serial.println(" m");
        } else {
            Serial.println("Error");
        }

        delay(10);
    }
}
