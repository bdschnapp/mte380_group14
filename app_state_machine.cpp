#include "app_state_machine.hpp"
namespace sm{
    bool StateMachine::init() {
        state = paused;
        path.init(false);
        lateral_path.init(true);

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
            else if (state == driving){
                if (main::lin_complete()) {
                    driving_transition();
                }
                // state is driving, continues to drive
            }
            else if (state == turning){
                if (main::piv_complete()){

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
            digitalWrite(13, HIGH);
            delay(1000);
        }
    }

    void StateMachine::paused_task() {
        // do nothing
    }

    void StateMachine::paused_transition() {
        state = driving;
        distance = path.get_next_distance();
        lateral_distance = lateral_path.get_next_distance();
        if (distance < 0 || lateral_distance < 0)
        {
            state = faulted;
        }
        main::reset_controllers();
        //main::smooth_ramp();
    }

    void StateMachine::driving_transition() {
        state = turning;
        if (path.get_index() == PATH_LENGTH -1)
        {
            transition_to_faulted();
        }
        heading -= math::deg_to_rad(90);
        main::reset_controllers();
    }

    void StateMachine::turning_transition() {
        state = driving;
        distance = path.get_next_distance();
        lateral_distance = lateral_path.get_next_distance();

        if (path.get_index() == 3){
            main::controller_override(PIT_DELAY, lateral_distance, heading);
        }
        if((path.get_index() == 5) || (path.get_index() == 6)){
            main::controller_override(SECOND_DELAY, lateral_distance, heading);
        }
        if((path.get_index() == 7) || (path.get_index() == 8)){
            main::controller_override(THIRD_DELAY, lateral_distance, heading);
        }
        if((path.get_index() == 9) || (path.get_index() == 10)){
            main::controller_override(FOURTH_DELAY, lateral_distance, heading);
        }
        if (distance < 0 || lateral_distance < 0)
        {
            state = faulted;
        }
        main::reset_controllers();
        //main::smooth_ramp();
    }

    float StateMachine::get_distance() {
        return distance;
    }

    float StateMachine::get_heading() {
        return heading;
    }

    float StateMachine::get_lateral_distance(){
        return lateral_distance;
    }

    StateMachine::StateMachine(){}
    MissionControl::MissionControl(){}

    void MissionControl::init(bool lateral) {
        if(lateral) {
            for (int i = 0; i < PATH_LENGTH; i++) {
                distances_internal[i] = lateral_distances[i];
            }
        }
        else{
            for (int i = 0; i < PATH_LENGTH; i++) {
                distances_internal[i] = distances[i];
            }
        }
        index = 0;
    }

    float MissionControl::get_next_distance() {
        index++;
        if (index > PATH_LENGTH)
        {
            return -1.0f;
        }
        return distances_internal[index - 1];
    }

    int MissionControl::get_index(){
        return (index - 1);
    }
}
