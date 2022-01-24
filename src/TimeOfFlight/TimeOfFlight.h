#ifndef MTE380_GROUP14_TIMEOFFLIGHT_H
#define MTE380_GROUP14_TIMEOFFLIGHT_H

#include <Wire.h>
#include <Adafruit_VL53L0X.h>

#define TOF_OK 1
#define TOF_NOT_OK 0

#define SCHEDULED 1
#define NOT_SCHEDULED 0

#define TOF_LONG_RANGE 1
#define TOF_SHORT_RANGE 0

#define NUM_PREV_DISTANCE 5

struct tof_init_config_s{
    int schedule_period;

};

class TimeOfFlight {
private:
    float distance;
    float prev_distances[NUM_PREV_DISTANCE];
    bool range_state;

    tof_init_config_s init_config;

    Adafruit_VL53L0X sensor;
    VL53L0X_RangingMeasurementData_t measure;

    int schedule_count;
    int schedule_period;

    //set range state
    bool set_long_range();
    bool set_short_range();

    // functions to reset or update prev_distances array
    void update_prev_distances(float cur_distance);
    void reset_prev_distances();

    //function to check prev_distances validity
    bool check_prev_distances();

    // check if sensor is scheduled to run in this cycle
    bool check_scheduled();


public:
    TimeOfFlight(tof_init_config_s tof_init_config);

    void run10ms();

    void set_schedule_period(int period);

    bool init(tof_init_config_s tof_init_config);
    bool reset();

    bool set_range_state(bool range);
    bool get_range_state(bool & range);

    bool get_distance(float & value);

};


#endif //MTE380_GROUP14_TIMEOFFLIGHT_H
