#include "Arduino.h"
#include "test_app_logger.hpp"
#include "app_logger.hpp"

namespace test_app_logger{

    debug::Logger logger;
    float data = 10.0;

    void app_setup(){
        logger.init();
        logger.println("starting logger");
    }

    void app_loop(){
        logger.println("sensor values");
        logger.print_ultrasonic_front(data);
        logger.print_ultrasonic_side(data);
        logger.print_tof_t_x(data);
        logger.print_tof_t_y(data);
        logger.print_tof_t_z(data);
        logger.print_tof_td_x(data);
        logger.print_tof_td_y(data);
        logger.print_tof_td_z(data);
        delay(10);
    }

} //namespace test_app_logger