//
// Created by User on 2/22/2022.
//

#ifndef MTE380_GROUP14_APP_MAIN_HPP
#define MTE380_GROUP14_APP_MAIN_HPP

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <simpleRPC.h>
#include <string>

// app
#include "../../app_defines.h"
#include "../../app_state_machine.hpp"
#include "app_logger.hpp"

// dev
#include "../../dev_ultrasonic.hpp"
#include "../../dev_bno055.hpp"app_main.cpp
#include "../../dev_button.hpp"

// lib
#include "../../lib_math.hpp"

#define SAR_OK 1
#define SAR_NOT_OK 0


namespace main{
    void run10ms();

    bool read_sensor_data();

    void app_setup();

    void app_loop();
}

#endif //MTE380_GROUP14_APP_MAIN_HPP
