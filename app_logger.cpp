#include "app_logger.hpp"

namespace debug{
    Logger::Logger() {
        muted = 0;
        // wired logger
        if(WIRED_LOGGER){
            Serial.begin(9600);
            stream = &Serial;
        }
        // bluetooth logger
        else{
            Serial1.begin(9600);
            stream = &Serial1;
        }

    }

    void Logger::mute() {
        muted = 1;
    }

    void Logger::unmute() {
        muted = 0;
    }

    void Logger::print_ultrasonic_front(float data){
        if (!muted){
            stream->println("usf");
            stream->println(data);
        }
    }
    void Logger::print_ultrasonic_side(float data){
        if (!muted) {
            stream->println("uss");
            stream->println(data);
        }
    }


    void Logger::print_tof_t_x(float data){
        if (!muted) {
            stream->println("tx");
            stream->println(data);
        }
    }
    void Logger::print_tof_t_y(float data){
        if (!muted) {
            stream->println("ty");
            stream->println(data);
        }
    }
    void Logger::print_tof_t_z(float data){
        if (!muted) {
            stream->println("tz");
            stream->println(data);
        }
    }


    void Logger::print_tof_td_x(float data){
        if (!muted) {
            stream->println("tdx");
            stream->println(data);
        }
    }
    void Logger::print_tof_td_y(float data){
        if (!muted) {
            stream->println("tdy");
            stream->println(data);
        }
    }
    void Logger::print_tof_td_z(float data){
        if (!muted) {
            stream->println("tdz");
            stream->println(data);
        }
    }
}
