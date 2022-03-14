#ifndef MTE380_GROUP14_APP_LOGGER_H
#define MTE380_GROUP14_APP_LOGGER_H

#include <Arduino.h>

#define DEFAULT_BAUD 9600

namespace debug{
    enum debug_t{
        float_t,
        int_t,
        string_t
    };

    class Logger {
    public:
        void init(int baud);

        void print_ultrasonic_front(float data);
        void print_ultrasonic_side(float data);

        void print_tof_t_x(float data);
        void print_tof_t_y(float data);
        void print_tof_t_z(float data);

        void print_tof_td_x(float data);
        void print_tof_td_y(float data);
        void print_tof_td_z(float data);

        template<typename T>
        void println(T data);
    };
}



#endif //MTE380_GROUP14_APP_LOGGER_H
