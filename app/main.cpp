#include "main.hpp"
#include <stdlib.h>
#include <Arduino.h>

int main(){
    Serial.begin(9600);
    delay(1000);
    Serial.println("Main Started");
    delay(1000);
    Serial.println("Main Finished");
    return 0;
}
