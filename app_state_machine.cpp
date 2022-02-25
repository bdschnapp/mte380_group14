#include "app_state_machine.hpp"
namespace sm{
    bool StateMachine::init(float &distances_in[PATH_LENGTH]) {
        state = paused;
        path.init(&distances_in);

        return SM_OK;
    }

    void StateMachine::run10ms(sensor_data_s sensor_data) {
        // transition conditions
        if(state != faulted){
            if (state == paused){
                if (sensor_data.button){
                    paused_transition();
                }
            }
            if (state == driving){
                if (sensor_data.ultrasonic_front < (distance + DISTANCE_TOLERANCE)){

                    // account for pit case
                    if(sensor_data.imu_theta.z == 0){
                        driving_transition();
                    }

                }
            }
            if (state == turning){
                if (sensor_data.imu_theta < (heading + ANGULAR_TOLERANCE)){
                    turning_transition();
                }
            }
        }

        // state tasks
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

    void StateMachine::transition_to_faulted() {
        state = faulted;
        // TODO: shutdown all motors and any sensors that have shutdown functions
    }

    void StateMachine::faulted_task() {
        while(1){
            delay(1);
        }
    }

    void StateMachine::paused_task() {
        // do nothing
    }

    void StateMachine::paused_transition() {
        state = driving;
        distance = path.get_next_distance();
    }

    void StateMachine::driving_task() {
        // TODO: implement driving task
    }

    void StateMachine::driving_transition() {
        state = turning;
        heading += 90;
    }

    void StateMachine::turning_task() {
        // TODO: implement turning task
    }

    void StateMachine::turning_transition() {
        state = driving;
        distance = path.get_next_distance();
    }

    void MissionControl::init(float (&input_array)[PATH_LENGTH]) {
        for(int i = 0; i < PATH_LENGTH; i++){
            distances[i] = input_array[i];
            index = 0;
        }
    }

    float MissionControl::get_next_distance() {
        index++;
        return distances[index - 1];
    }
}
