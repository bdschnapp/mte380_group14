//
// Created by User on 2/22/2022.
//

#ifndef MTE380_GROUP14_APP_LOGGER_H
#define MTE380_GROUP14_APP_LOGGER_H

#include "vector.tcc"
#include "tuple.tcc"

#define LOGGER_OK 1
#define LOGGER_NOT_OK 0

#define NUM_SENSORS 10
// number of 10ms task periods before the computer reads the data
#define POLL_PERIOD 10
// extra space in buffer to account for slow wifi or other timing issues
#define SAFETY_FACTOR 2

#define VECTOR_SIZE (NUM_SENSORS * POLL_PERIOD * SAFETY_FACTOR)

namespace debug{
    class Logger {
    private:
        //Vector<float> data(VECTOR_SIZE);
        //Vector<std::string> heading(VECTOR_SIZE);
        //Vector<int> time(VECTOR_SIZE);

        //Tuple<float, Tuple<std::string, int>>

        Vector<Tuple<float, Tuple<std::string, int>>> data;
        int index;
        int ping_count;
        bool clear_data;

    public:
        void ping(int data_in); // never call this function. client side only

        Vector<Tuple<float, Tuple<std::string, int>>> get_data(); // never call this function. client side only


        void init();
        void run10ms();
        bool print_float(float data, std::string stream, int time);
    };
}



#endif //MTE380_GROUP14_APP_LOGGER_H
