#include "Ultrasonic.hpp"

//init config
sensor::ultrasonic_init_config_s initConfig;

sensor::Ultrasonic distance_sensor;

float distance;

void setup() {
    Serial.begin(9600);
    initConfig.echoPin = 2;
    initConfig.trigPin = 3;

    distance_sensor.init(initConfig);
}

void loop() {
    distance_sensor.run10ms();
    if(distance_sensor.get_distance(distance)){
      Serial.print(distance);
      Serial.println(" cm");
    }
    else{
      Serial.println("Error");
    }

    delay(10);
}
