#ifndef MTE380_GROUP14_ENCODER_H
#define MTE380_GROUP14_ENCODER_H

#include <Arduino.h>

namespace sensor {

    struct encoder_init_config_s {
        int latchPin;
        int clockPin;
        int dataPin;
    };

    class Encoder {
    private:
        

    public:
        // constructor and destructor
        Encoder();
        ~Encoder() = default;

        // initialization and reset
        bool init(encoder_init_config_s encoder_init_config);
        bool reset();

        // main 10ms task
        void run10ms();

        // getter function for distance. returns true if valid, false if not valid
        bool get_distance(float& value);
    };
} // namespace sensor

#endif //MTE380_GROUP14_ENCODER_H
