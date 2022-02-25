#ifndef MTE380_GROUP14_DEV_BUTTON_HPP
#define MTE380_GROUP14_DEV_BUTTON_HPP

#include <Arduino.h>

#define BUTTON_OK 1
#define BUTTON_NOT_OK 0

namespace sensor{
    class Button{
    private:
        int pin;
        int count_high;
        int count_presses;
        bool value;
        bool prev_value;



    public:

        Button();
        ~Button() = default;

        void init(int pin_in);

        void run10ms();

        bool get_button_press(bool &button_pressed);
    };
}

#endif //MTE380_GROUP14_DEV_BUTTON_HPP
