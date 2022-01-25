#include "TOF_Sensors.h"

TOF_Sensors::TOF_Sensors(tof_init_config_s tof_x_config, tof_init_config_s tof_y_config){
    x_config = tof_x_config;
    y_config = tof_y_config;
    init();
}

bool TOF_Sensors::init() {
    x_sensor = TimeOfFlight(x_config);
    y_sensor = TimeOfFlight(y_config);

    y_sensor.shutdown();

    x_sensor.set_address(x_config.address);

    delayMs(10);

    y_sensor.init(y_config);
}

void TOF_Sensors::shutdown(){
    x_sensor.shutdown();
    y_sensor.shutdown();
}

bool TOF_Sensors::reset() {
    x_sensor.reset();
    y_sensor.reset();
    if(!init())
        return TOF_NOT_OK;
    return TOF_OK;
}

void TOF_Sensors::run10ms() {
    x_sensor.run10ms();
    y_sensor.run10ms();
}

bool TOF_Sensors::get_distance(sensor_distance_s &distance_xy) {
    if(!x_sensor.get_distance(distance_xy.x))
        return TOF_NOT_OK;
    if(!y_sensor.get_distance(distance_xy.y))
        return TOF_NOT_OK;
    return TOF_OK;
}