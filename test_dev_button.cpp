#include "test_dev_button.hpp"

namespace test_dev_button {

    sensor::Button button;
    int bp;

    void app_setup() {
        Serial.begin(9600);

        button.init(BUTTON_PIN);
    }

    void app_loop() {
        bp = 0;
        button.run10ms();

        if (!button.get_button_press(bp)){
            while(1){
                Serial.println("Faulted");
                delay(1000);
            }
        }

        if(bp){
            Serial.println("Button Pressed");
        }

        delay(10);
    }
}
