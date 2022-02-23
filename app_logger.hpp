//
// Created by User on 2/22/2022.
//

#ifndef MTE380_GROUP14_APP_LOGGER_H
#define MTE380_GROUP14_APP_LOGGER_H

#include <simpleRPC.h>
#include <bitset>
#include <string>

#define NUM_SENSORS 10
// number of 10ms task periods before the computer reads the data
#define POLL_PERIOD 10
// extra space in buffer to account for slow wifi or other timing issues
#define SAFETY_FACTOR 2

#define VECTOR_SIZE (NUM_SENSORS * POLL_PERIOD * SAFETY_FACTOR)

namespace debug{
    class Logger {
    private:
        std::vector<float> data(VECTOR_SIZE);
        Vector<string> heading(VECTOR_SIZE);
        Vector<int> time(VECTOR_SIZE);

        int ping_count;

    public:
        void ping(int data); // never call this function. client side only

        void get_data(); // never call this function. client side only


        void init(std::string key, std::string secret);
        void print_float(float data, std::string stream, int time);
    };
}



#endif //MTE380_GROUP14_APP_LOGGER_H
