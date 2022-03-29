#include "app_state_machine.hpp"
namespace sm{
    bool StateMachine::init() {
        state = paused;
        path.init();

        return SM_OK;
    }

    state_e StateMachine::run10ms(sensor_data_s sensor_data) {
        // transition conditions
        if(state != faulted){
            if (state == paused){
                if (sensor_data.button){
                    paused_transition();
                }
            }
            if (state == driving){
                if (math::float_compare(sensor_data.ultrasonic_front, distance, DISTANCE_TOLERANCE)){

                    // TODO: account for pit case, if we are not on flat ground we dont turn

                    // TODO: confirm we want z theta value here

                    // flat ground case, this should happen most often
                    if(math::float_compare(sensor_data.imu_theta.z, 0, ANGULAR_TOLERANCE)){

                        // transition to turning
                        driving_transition();
                    }
                }
                // state is driving, continues to drive
            }
            if (state == turning){
                // TODO: confirm we want x theta value
                if (math::float_compare(sensor_data.imu_theta.z, heading, ANGULAR_TOLERANCE)){

                    // transition to driving
                    turning_transition();
                }
                // state is turning, continue to turn
            }
        }
        return state;
    }

    void StateMachine::transition_to_faulted() {
        state = faulted;
    }

    void StateMachine::faulted_task() {
        while(1){
            delay(1000);
        }
    }

    void StateMachine::paused_task() {
        // do nothing
    }

    void StateMachine::paused_transition() {
        state = driving;
        distance = path.get_next_distance();
    }

    void StateMachine::driving_transition() {
        state = turning;
        heading -= math::deg_to_rad(90);
    }

    void StateMachine::turning_transition() {
        state = driving;
        distance = path.get_next_distance();
    }

    StateMachine::StateMachine(){}
    MissionControl::MissionControl(){}

    void MissionControl::init() {
        for(int i = 0; i < PATH_LENGTH; i++){
            distances_internal[i] = distances[i];
        }
        index = 0;
    }

    float MissionControl::get_next_distance() {
        index++;
        if(index > PATH_LENGTH){
            return -1;
        }
        return distances_internal[index-1];
    }
}
