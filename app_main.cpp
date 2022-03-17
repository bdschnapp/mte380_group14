#include "app_main.hpp"

namespace main
{
    sensor::ultrasonic_init_config_s ultrasonicFrontInitConfig;
    sensor::ultrasonic_init_config_s ultrasonicSideInitConfig;

    sensor::Ultrasonic UltrasonicFront;
    sensor::Ultrasonic UltrasonicSide;

    sensor::BNO055 bno055_imu;

    sensor::Button e_stop;

    sm::sensor_data_s sensor_data;
    sm::sensor_data_s sensor_data_debounced;

    sm::StateMachine stateMachine;

    robot::drivetrain ;

    controllers::angular_controller angular_PID;
    controllers::linear_controller linear_PID;

    debug::Logger logger;

    long time_us;
    int delta_t;

    void main::run10ms(){
        e_stop.run10ms();
        UltrasonicSide.run10ms();
        UltrasonicFront.run10ms();
        bno055_imu.run_10ms();
    }

    fault_e main::read_sensor_data(){
        if(!e_stop.get_button_press(&sensor_data.button))
            return SAR_CRITICAL;

        fault_e fault = SAR_OK;
         if(!UltrasonicFront.get_distance(&sensor_data.ultrasonic_front))
             fault = US_NOT_OK;

         if(!UltrasonicSide.get_distance(&sensor_data.ultrasonic_side))
             fault = US_NOT_OK;

         if(!bno055_imu.get_angular_position(&sensor_data.imu_theta))
             fault = IMU_NOT_OK;

         if(!bno055_imu.get_angular_velocity(&sensor_data.imu_theta_dot))
             fault = IMU_NOT_OK;

         // TODO: Sensor debounce

         logger.print_ultrasonic_front(sensor_data.ultrasonic_front);
         logger.print_ultrasonic_side(sensor_data.ultrasonic_side);

         logger.print_tof_t_x(sensor_data.imu_theta.x);
         logger.print_tof_t_y(sensor_data.imu_theta.y);
         logger.print_tof_t_z(sensor_data.imu_theta.z);

         logger.print_tof_td_x(sensor_data.imu_theta_dot.x);
         logger.print_tof_td_y(sensor_data.imu_theta_dot.y);
         logger.print_tof_td_z(sensor_data.imu_theta_dot.z);

         return fault;
    }

    void main::driving_task(float heading, float distance) {

    }

    void main::turning_task(float heading, float distance) {

    }

    void main::transition_to_faulted(){
        stateMachine.transition_to_faulted();
        // TODO: shutdown all motors and any sensors that have shutdown functions
    }


    void app_setup(){
        Serial1.begin(9600);

        ultrasonicFrontInitConfig.echoPin = FRONT_ULTRASONIC_ECHO_PIN;
        ultrasonicFrontInitConfig.trigPin = FRONT_ULTRASONIC_TRIG_PIN;
        ultrasonicSideInitConfig.echoPin = SIDE_ULTRASONIC_ECHO_PIN;
        ultrasonicSideInitConfig.trigPin = SIDE_ULTRASONIC_TRIG_PIN;

        UltrasonicFront.init(ultrasonicFrontInitConfig);
        UltrasonicSide.init(ultrasonicSideInitConfig);

        bno055_imu.init()

        e_stop.init(BUTTON_PIN);

        stateMachine.init(&distances);
    }

    void app_loop(){
        delta_t = micros() - time_us;
        time_us = micros();
        run10ms();

        if(read_sensor_data() == SAR_CRITICAL){
            transition_to_faulted();
            stateMachine.faulted_task();
        }

        // currently ignores any non-critical faults

        switch (stateMachine.run10ms(sensor_data_debounced)) {
            case paused:
                stateMachine.paused_task();
            case driving:
                driving_task(stateMachine.heading, stateMachine.distance);
            case turning:
                turning_task(stateMachine.heading, stateMachine.distance);
        }
    }
}
