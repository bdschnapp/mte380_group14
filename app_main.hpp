#ifndef MTE380_GROUP14_APP_MAIN_HPP
#define MTE380_GROUP14_APP_MAIN_HPP

#include <Arduino.h>

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

    void app_setup();

    void app_loop();

    void reset_controllers();

    bool piv_complete();

    bool lin_complete();

    void smooth_ramp();

    void transition_to_faulted();

    void controller_override(int delay_ticks, float goal_lateral_distance, float heading);

}

#endif //MTE380_GROUP14_APP_MAIN_HPP
