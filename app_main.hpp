//
// Created by User on 2/22/2022.
//

#ifndef MTE380_GROUP14_APP_MAIN_HPP
#define MTE380_GROUP14_APP_MAIN_HPP

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <string>

// app
#include "app_defines.h"
#include "app_state_machine.hpp"
#include "app_logger.hpp"

// dev
#include "dev_ultrasonic.hpp"
#include "dev_bno055.hpp"
#include "dev_button.hpp"

// lib
#include "lib_math.hpp"


namespace main{
    enum fault_e{
        SAR_OK,
        SAR_NOT_OK,
        SAR_CRITICAL,
        US_NOT_OK,
        IMU_NOT_OK,
        DRIVETRAIN_NOT_OK,

    };

    void run10ms();

    fault_e read_sensor_data();

    void app_setup();

    void app_loop();

    void driving_task(float heading, float distance);

    void turning_task(float heading, float distance);

    void transition_to_faulted();
}

#endif //MTE380_GROUP14_APP_MAIN_HPP
