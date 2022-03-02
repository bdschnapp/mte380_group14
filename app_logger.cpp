#include "app_logger.hpp"

namespace debug{
    void Logger::init() {
        data.resize(VECTOR_SIZE);
    }

    bool Logger::print_float(float data_in, int stream, int time) {
        Tuple<float, Tuple<std::string, int>> t;
        t.head = data_in;
        t.tail.head = stream;
        t.tail.tail = time;

        if(index < VECTOR_SIZE){
            data[index] = t;
            index++;
            return LOGGER_OK;
        }
        return LOGGER_NOT_OK;
    }

    Vector<Tuple<float, Tuple<std::string, int>>> Logger::get_data() {
        index = 0;
        return data;
    }

    void Logger::ping(int data_in) {
        ping_count++;
        return data_in;
    }
}