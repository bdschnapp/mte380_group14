#ifndef MTE380_GROUP14_APP_LOGGER_H
#define MTE380_GROUP14_APP_LOGGER_H

#include <Arduino.h>

namespace debug{
    class Logger {
    private:
        bool muted;
    public:

        Logger();
        ~Logger() = default;

        /**
         * Sets private variable muted to 1 which suppresses serial print calls
         */
        void mute();

        /**
         * Sets private variable muted to 0 which un-suppresses serial print calls
         */
        void unmute();

        /**
         * Plots the data in the ultrasonic front plot in the python client
         * @param data, data to be plotted
         */
        void print_ultrasonic_front(float data);

        /**
         * Plots the data in the ultrasonic side plot in the python client
         * @param data, data to be plotted
         */
        void print_ultrasonic_side(float data);

        /**
         * Plots the data in the tof_t_x plot in the python client
         * @param data, data to be plotted
         */
        void print_tof_t_x(float data);
        /**
         * Plots the data in the tof_t_y plot in the python client
         * @param data, data to be plotted
         */
        void print_tof_t_y(float data);
        /**
         * Plots the data in the tof_t_z plot in the python client
         * @param data, data to be plotted
         */
        void print_tof_t_z(float data);

        /**
         * Plots the data in the tof_td_x plot in the python client
         * @param data, data to be plotted
         */
        void print_tof_td_x(float data);
        /**
         * Plots the data in the tof_td_y plot in the python client
         * @param data, data to be plotted
         */
        void print_tof_td_y(float data);
        /**
         * Plots the data in the tof_td_z plot in the python client
         * @param data, data to be plotted
         */
        void print_tof_td_z(float data);

        /**
         * default print statement, will print to python client terminal
         * @param data, data to be printed
         * type: byte, (u)char, string, (u)int, float, (u)long, (u)short, word
         */
        template<typename T>
        void println(T data) throw(){
            Serial1.println(data);
        }
    };
}



#endif //MTE380_GROUP14_APP_LOGGER_H
