#include "test_dev_button.hpp"

namespace test_dev_button {

    sensor::Button button;

    bool button_pressed;

    void app_setup() {
        Serial.begin(9600);

        button.init(BUTTON_TEST_PIN);
    }

    void app_loop() {
        button.run10ms();

        if (!button.get_button_press(&button_pressed)){
            while(1){
                Serial.println("Faulted");
                delay(1000);
            }
        }

        if(button_pressed){
            Serial.println("Button Pressed")
        }

        delay(10);
    }
}