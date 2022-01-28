#include "main.hpp"

int i;

void setup() {
    i = 0;
}

void loop() {
    if(i ==0){
        i++;
        main();
    }
}
