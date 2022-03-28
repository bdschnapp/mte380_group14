#ifndef MTE380_GROUP14_STATEMACHINE_HPP
#define MTE380_GROUP14_STATEMACHINE_HPP

#include "lib_math.hpp"
#include "app_defines.hpp"

#define SM_OK 1
#define SM_NOT_OK 0

namespace sm {

    enum state_e {
        paused,
        driving,
        turning,
        faulted
    };

    struct sensor_data_s {
        float ultrasonic_front;
        float ultrasonic_side;
        int button;
        math::Vector3f imu_theta;
        math::Vector3f imu_theta_dot;
    };

    class MissionControl {
    private:
        int index;
        float distances_internal[PATH_LENGTH];

    public:
        MissionControl();
        ~MissionControl() = default;

        void init(float (&input_array)[PATH_LENGTH]);

        float get_next_distance();

    };

    class StateMachine {
    private:
        state_e state;
        MissionControl path;

    public:
        float distance;
        float heading;

        bool init(float &distances_in[PATH_LENGTH]);

        // main function to calculate the state
        state_e run10ms(sensor_data_s sensor_data);

        // function to transition from driving to turning
        void driving_transition();

        // function to transition from turning to driving
        void turning_transition();

        // task to do while in the paused state
        void paused_task();

        // function to transition from paused to driving
        void paused_transition();

        // task to do while in the faulted state
        void faulted_task();

        // function to transition into the faulted state
        void transition_to_faulted();

    };
}


#endif //MTE380_GROUP14_STATEMACHINE_HPP
