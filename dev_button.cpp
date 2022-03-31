#include "dev_button.hpp"

namespace sensor{
    Button::Button() {
        value = 0;
        prev_value = 0;
    }
    void Button::init(int pin_in) {
        pin = pin_in;
        pinMode(pin, INPUT_PULLUP);
    }

    void Button::run10ms() {
        prev_value = value;
        count_high += value;

        value = digitalRead(pin);

        if((value == 0) && (prev_value == 0)){
            count_high = 0;
        }
    }

    bool Button::get_button_press(int &button_pressed) {
        button_pressed = 0;

        // detect the falling edge of a button press that lasted for more than 30ms
        if ((value == 0) && (prev_value == 1) && (count_high > 3)){
            button_pressed = 1;
            count_presses++;
        }

        // return error if button is pressed a second time
        if((button_pressed) && (count_presses > 1)){
            return BUTTON_NOT_OK;
        }

        return BUTTON_OK;
    }
}
