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

        /*
         * gets the status of the button
         * button_pressed is set high only for the cycle when the button is released.
         * returns true if status is ok
         * returns false when a second press is detected. This should transition the robot to critical fault
         */
        bool get_button_press(int &button_pressed);
    };
}

#endif //MTE380_GROUP14_DEV_BUTTON_HPP
