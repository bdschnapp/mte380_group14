#ifndef MTE380_GROUP14_APP_MAIN_HPP
#define MTE380_GROUP14_APP_MAIN_HPP

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <string>

// app
#include "app_defines.hpp"
#include "app_state_machine.hpp"
#include "app_logger.hpp"

// dev
#include "dev_ultrasonic.hpp"
#include "dev_bno055.hpp"
#include "dev_button.hpp"
#include "dev_TB9051FTG.hpp"

// lib
#include "lib_math.hpp"

// controllers
#include "lateral_controller.hpp"
#include "linear_controller.hpp"
#include "pivot_controller.hpp"
#include "drivetrain.hpp"

namespace main{
    enum fault_e{
        SAR_OK,
        SAR_NOT_OK,
        SAR_CRITICAL,
        US_NOT_OK,
        IMU_NOT_OK,
        DRIVETRAIN_NOT_OK,
        MOTOR_CRITICAL

    };

    void run10ms();

    fault_e read_sensor_data();

    void app_setup();

    void app_loop();

    fault_e driving_task(float heading, float distance);

    fault_e turning_task(float heading);

    void transition_to_faulted();
}

#endif //MTE380_GROUP14_APP_MAIN_HPP
