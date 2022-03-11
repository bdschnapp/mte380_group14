#include "app_logger.hpp"

namespace debug{
    void Logger::print_ultrasonic_front(float data){
        Serial1.println("ultrasonic_front");
        Serial1.println(data);
    }
    void Logger::print_ultrasonic_front(float data){
        Serial1.println("ultrasonic_side");
        Serial1.println(data);
    }


    void Logger::print_tof_t_x(float data){
        Serial1.println("tof_t_x");
        Serial1.println(data);
    }
    void Logger::print_tof_t_y(float data){
        Serial1.println("tof_t_y");
        Serial1.println(data);
    }
    void Logger::print_tof_t_z(float data){
        Serial1.println("tof_t_z");
        Serial1.println(data);
    }


    void Logger::print_tof_td_x(float data){
        Serial1.println("tof_td_x");
        Serial1.println(data);
    }
    void Logger::print_tof_td_y(float data){
        Serial1.println("tof_td_y");
        Serial1.println(data);
    }
    void Logger::print_tof_td_z(float data){
        Serial1.println("tof_td_z");
        Serial1.println(data);
    }

    // I might be doing this completely wrong, this is how i would do it in C
    // intent is to be able to print any data type with 1 function
    // other option is to just creat different function for each type
    void Logger::println(void *data, debug_t data_type){
        switch (data_type) {
            case float_t:
                float write_f = *(float *)data;
                Serial1.println(write_f);

            case int_t:
                int write_i = *(int *)data;
                Serial1.println(write_i);

            case string_t:
                String write_s = String(*(String *)data);
                Serial1.println(write_s)
        }
    }
}