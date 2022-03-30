#include "app_logger.hpp"

namespace debug{

    void Logger::init()
    {
        muted = 0;
        SERIAL_INTERFACE.begin(9600);
    }

    void Logger::mute() {
        muted = 1;
    }

    void Logger::unmute() {
        muted = 0;
    }

    void Logger::print_ultrasonic_front(float data){
        if (!muted){
            SERIAL_INTERFACE.println("usf");
            SERIAL_INTERFACE.println(data);
        }
    }
    void Logger::print_ultrasonic_side(float data){
        if (!muted) {
            SERIAL_INTERFACE.println("uss");
            SERIAL_INTERFACE.println(data);
        }
    }


    void Logger::print_tof_t_x(float data){
        if (!muted) {
            SERIAL_INTERFACE.println("tx");
            SERIAL_INTERFACE.println(data);
        }
    }
    void Logger::print_tof_t_y(float data){
        if (!muted) {
            SERIAL_INTERFACE.println("ty");
            SERIAL_INTERFACE.println(data);
        }
    }
    void Logger::print_tof_t_z(float data){
        if (!muted) {
            SERIAL_INTERFACE.println("tz");
            SERIAL_INTERFACE.println(data);
        }
    }


    void Logger::print_tof_td_x(float data){
        if (!muted) {
            SERIAL_INTERFACE.println("tdx");
            SERIAL_INTERFACE.println(data);
        }
    }
    void Logger::print_tof_td_y(float data){
        if (!muted) {
            SERIAL_INTERFACE.println("tdy");
            SERIAL_INTERFACE.println(data);
        }
    }
    void Logger::print_tof_td_z(float data){
        if (!muted) {
            SERIAL_INTERFACE.println("tdz");
            SERIAL_INTERFACE.println(data);
        }
    }
}
