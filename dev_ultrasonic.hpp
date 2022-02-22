#ifndef MTE380_GROUP14_ULTRASONIC_H
#define MTE380_GROUP14_ULTRASONIC_H

#include <Arduino.h>

#define ULTRASONIC_OK 1
#define ULTRASONIC_NOT_OK 0

#define NUM_PREV_DISTANCE 5

namespace sensor {

    struct ultrasonic_init_config_s {
        int trigPin;
        int echoPin;
    };

    class Ultrasonic {
    private:
        float distance;
        float duration;
        float prev_distances[NUM_PREV_DISTANCE];
        ultrasonic_init_config_s init_config;

        // updates the prev_distances array
        void update_prev_distances(float cur_distance);

        // resets the prev_distances array
        void reset_prev_distances();

        //function to check prev_distances validity
        bool check_prev_distances();

    public:
        // constructor and destructor
        Ultrasonic();
        ~Ultrasonic() = default;

        // initialization and reset
        bool init(ultrasonic_init_config_s ultrasonic_init_config);
        bool reset();

        // main 10ms task
        void run10ms();

        // getter function for distance. returns true if valid, false if not valid
        bool get_distance(float &value);
    };
}

#endif //MTE380_GROUP14_ULTRASONIC_H
