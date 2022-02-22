#include "TimeOfFlight.hpp"

sensor::tof_init_config_s initConfig;

sensor::TimeOfFlight tof_sensor;

float distance;

void setup() {
    Serial.begin(9600);

    // wait until serial port opens for native USB devices
    while (! Serial) {
        delay(1);
    }

    Serial.println("Adafruit VL53L0X custom driver test");
    delay(100);

    initConfig.address = 0x29;
    initConfig.range_state = TOF_SHORT_RANGE;
    initConfig.schedule_period = 1;
    initConfig.shutdown_pin = 2;

    if (!tof_sensor.init(initConfig)){
        Serial.println("failed to init");
    }
}


void loop() {
    tof_sensor.run10ms();
    if(tof_sensor.get_distance(distance)){
        Serial.print(distance);
        Serial.println(" cm");
    }
    else{
        Serial.println("Error");
    }

    delay(1000);
}
