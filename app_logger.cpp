#include "app_logger.hpp"

namespace debug{
    Logger::Logger() {
        Serial1.begin(9600);
    }

    void Logger::print_ultrasonic_front(float data){
        Serial1.println("usf");
        Serial1.println(data);
    }
    void Logger::print_ultrasonic_side(float data){
        Serial1.println("uss");
        Serial1.println(data);
    }


    void Logger::print_tof_t_x(float data){
        Serial1.println("tx");
        Serial1.println(data);
    }
    void Logger::print_tof_t_y(float data){
        Serial1.println("ty");
        Serial1.println(data);
    }
    void Logger::print_tof_t_z(float data){
        Serial1.println("tz");
        Serial1.println(data);
    }


    void Logger::print_tof_td_x(float data){
        Serial1.println("tdx");
        Serial1.println(data);
    }
    void Logger::print_tof_td_y(float data){
        Serial1.println("tdy");
        Serial1.println(data);
    }
    void Logger::print_tof_td_z(float data){
        Serial1.println("tdz");
        Serial1.println(data);
    }
}
