//
// Wrapper class for time of flight sensors.
// Enables using multiple sensors at the same time. Currently supports 2 sensors
//

#ifndef MTE380_GROUP14_TOF_SENSORS_H
#define MTE380_GROUP14_TOF_SENSORS_H

#include "../../dev/TimeOfFlight/TimeOfFlight.hpp"

struct sensor_distance_s{
    float x;
    float y;
};

class TOF_Sensors {
public:
    TOF_Sensors();
    ~TOF_Sensors() = default;
    
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
