//
// Wrapper class for time of flight sensors.
// Enables using multiple sensors at the same time.
//

#ifndef MTE380_GROUP14_TOF_SENSORS_H
#define MTE380_GROUP14_TOF_SENSORS_H

#include "TimeOfFlight.h"

struct sensor_distance_s{
    float x;
    float y;
};

class TOF_Sensors {
public:
    TOF_Sensors(tof_init_config_s tof_x_config, tof_init_config_s tof_y_config);
    TimeOfFlight x_sensor;
    TimeOfFlight y_sensor;
    tof_init_config_s x_config;
    tof_init_config_s y_config;

    bool init();
    bool reset();
    void shutdown();

    void run10ms();
    bool get_distance(sensor_distance_s & distance_xy);
};


#endif //MTE380_GROUP14_TOF_SENSORS_H
