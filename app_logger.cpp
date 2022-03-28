#include "app_logger.hpp"

namespace debug{
    Logger::Logger() {
        muted = 0;
        Serial1.begin(9600);
    }

    void Logger::mute() {
        muted = 1;
    }

    void Logger::unmute() {
        muted = 0;
    }

    void Logger::print_ultrasonic_front(float data){
        if (!muted){
            Serial1.println("usf");
            Serial1.println(data);
        }
    }
    void Logger::print_ultrasonic_side(float data){
        if (!muted) {
            Serial1.println("uss");
            Serial1.println(data);
        }
    }


    void Logger::print_tof_t_x(float data){
        if (!muted) {
            Serial1.println("tx");
            Serial1.println(data);
        }
    }
    void Logger::print_tof_t_y(float data){
        if (!muted) {
            Serial1.println("ty");
            Serial1.println(data);
        }
    }
    void Logger::print_tof_t_z(float data){
        if (!muted) {
            Serial1.println("tz");
            Serial1.println(data);
        }
    }


    void Logger::print_tof_td_x(float data){
        if (!muted) {
            Serial1.println("tdx");
            Serial1.println(data);
        }
    }
    void Logger::print_tof_td_y(float data){
        if (!muted) {
            Serial1.println("tdy");
            Serial1.println(data);
        }
    }
    void Logger::print_tof_td_z(float data){
        if (!muted) {
            Serial1.println("tdz");
            Serial1.println(data);
        }
    }
}
