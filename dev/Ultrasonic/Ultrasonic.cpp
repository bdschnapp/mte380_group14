#include "Ultrasonic.hpp"

namespace sensor {

    //constructor
    Ultrasonic::Ultrasonic() {
        duration = 0;
        distance = 0;

        for (int i = 0; i < NUM_PREV_DISTANCE; i++) {
            prev_distances[i] = i;
        }
    }

    //private
    void Ultrasonic::reset_prev_distances() {
        for (int i = 0; i < NUM_PREV_DISTANCE; i++) {
            prev_distances[i] = i; // dont set all to same value, otherwise check_prev_distances will fail
        }
    }

    void Ultrasonic::update_prev_distances(float cur_distance) {
        for (int i = 0; i < NUM_PREV_DISTANCE; i++) {
            if (i == (NUM_PREV_DISTANCE - 1))
                prev_distances[i] = cur_distance;
            else
                prev_distances[i] = prev_distances[i + 1];
        }
    }

    bool Ultrasonic::check_prev_distances() {
        int count_same = 0;
        for (int i = 0; i < (NUM_PREV_DISTANCE - 1); i++) {
            if (prev_distances[i] == prev_distances[i + 1])
                count_same++;
        }
        if (count_same == (NUM_PREV_DISTANCE - 1))
            return ULTRASONIC_NOT_OK;
        return ULTRASONIC_OK;
    }

    //public
    bool Ultrasonic::init(ultrasonic_init_config_s ultrasonic_init_config) {
        init_config = ultrasonic_init_config;
        pinMode(ultrasonic_init_config.trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
        pinMode(ultrasonic_init_config.echoPin, INPUT); // Sets the echoPin as an INPUT

        // cant think of any way to check if pins are set. maybe perform a test reading?
        return ULTRASONIC_OK;
    }

    bool Ultrasonic::reset() {
        reset_prev_distances();
        if (!init(init_config)) {
            if (!init(init_config)) {
                return ULTRASONIC_NOT_OK;
            }
        }
        return ULTRASONIC_OK;
    }

    void Ultrasonic::run10ms() {
        // Clears the trigPin condition
        digitalWrite(init_config.trigPin, LOW);
        delayMicroseconds(2);
        // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
        digitalWrite(init_config.trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(init_config.trigPin, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        duration = pulseIn(init_config.echoPin, HIGH);
        // Calculating the distance
        distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
        update_prev_distances(distance);
    }

    bool Ultrasonic::get_distance(float &value) {
        if (check_prev_distances()) {
            value = distance;
            return ULTRASONIC_OK;
        }
        value = 0;
        return ULTRASONIC_NOT_OK;
    }
}