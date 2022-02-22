#ifndef MTE380_GROUP14_TIMEOFFLIGHT_H
#define MTE380_GROUP14_TIMEOFFLIGHT_H

#include <Arduino.h>
#include <Adafruit_VL53L0X.h>

#define TOF_OK 1
#define TOF_NOT_OK 0

#define SCHEDULED 1
#define NOT_SCHEDULED 0

#define TOF_LONG_RANGE 1
#define TOF_SHORT_RANGE 0

#define NUM_PREV_DISTANCE 5

namespace sensor{

    struct tof_init_config_s{
        int schedule_period;  // how often run10ms runs
        bool range_state;  // default range
        int address;  // i2c address (default 0x29)
        int shutdown_pin;  // pin that controls the shutdown function of sensor
    };

    class TimeOfFlight {
    private:
        float distance;
        float prev_distances[NUM_PREV_DISTANCE];
        bool range_state;

        // init config struct
        tof_init_config_s init_config;

        // VL53L0X sensor object
        Adafruit_VL53L0X VL53L0X;

        // measurement object
        VL53L0X_RangingMeasurementData_t measure;

        int schedule_count;
        int schedule_period;

        // set range state
        bool set_long_range();
        bool set_short_range();

        // functions to reset or update prev_distances array
        void update_prev_distances(float cur_distance);
        void reset_prev_distances();

        // function to check prev_distances validity
        bool check_prev_distances();

        // check if sensor is scheduled to run in this cycle
        bool check_scheduled();


    public:

        // constructor and destructor
        TimeOfFlight();
        ~TimeOfFlight() = default;

        // main task
        void run10ms();

        // sets the schedule period
        void set_schedule_period(int period);

        // initialization function
        bool init(tof_init_config_s tof_init_config);

        // resets the sensor
        // TODO: configure address after shutdown
        bool reset();

        // getter and setter for the range state of the sensor
        bool set_range_state(bool range);
        bool get_range_state(bool & range);

        // getter function for distance
        // returns true if distance is valid, false if distance is invalid
        bool get_distance(float & value);

        // function to set the shutdown pin
        bool shutdown();

        // function to clear the shutdown pin
        bool enable();

        // function to set the i2c address
        bool set_address(int new_address);
    };
}


#endif //MTE380_GROUP14_TIMEOFFLIGHT_H
