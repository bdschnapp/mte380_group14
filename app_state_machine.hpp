#ifndef MTE380_GROUP14_STATEMACHINE_HPP
#define MTE380_GROUP14_STATEMACHINE_HPP

#define PATH_LENGTH 11

#define DISTANCE_TOLERANCE 1
#define ANGULAR_TOLERANCE 1

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
        bool button;
        float imu_theta;
    };

    class MissionControl {
    private:
        int index;
        float distances[PATH_LENGTH];

    public:
        MissionControl();
        ~MissionControl() = default;

        void init(float (&input_array)[PATH_LENGTH]);

        float get_next_distance();

    };

    class StateMachine {
    private:
        state_e state;
        float distance;
        float heading;
        MissionControl path;

    public:
        bool init(float &distances_in[PATH_LENGTH]);

        bool read_e_stop();

        void run10ms(sensor_data_s sensor_data);

        // task to do while in the driving state
        void driving_task();

        // function to transition from driving to turning
        void driving_transition();

        // task to do while in the turning state
        void turning_task();

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
