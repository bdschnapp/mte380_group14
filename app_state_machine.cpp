#include "app_state_machine.hpp"

bool StateMachine::init() {
    state = paused;

    return SM_OK;
}

void StateMachine::run10ms(sensor_data_s sensor_data) {



    switch (state) {
        case faulted:
            faulted_task();
        case paused:
            paused_task();
        case driving:
            driving_task();
        case turning:
            turning_task();
    }
}