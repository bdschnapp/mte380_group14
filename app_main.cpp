#include "app_main.hpp"

namespace main
{
    enum fault_e{
        SAR_OK,
        SAR_NOT_OK,
        SAR_CRITICAL,
        US_NOT_OK,
        IMU_NOT_OK,
        DRIVETRAIN_NOT_OK,
        MOTOR_CRITICAL

    };

    sensor::ultrasonic_init_config_s ultrasonicFrontInitConfig;
    sensor::ultrasonic_init_config_s ultrasonicSideInitConfig;

    sensor::Ultrasonic UltrasonicFront;
    sensor::Ultrasonic UltrasonicSide;

    sensor::BNO055 bno055_imu;

    sensor::Button e_stop;

    actuator::TB9051FTG motor;

    sm::sensor_data_s sensor_data;
    sm::sensor_data_s filtered_sensor_data;

    sm::StateMachine stateMachine;

    controllers::lateral_controller lat_controller(Kp_gyro, Ki_gyro, Kp_lat_us, Ki_lat_us);
    controllers::linear_controller lin_controller(linear_Kp, linear_Ki, DISTANCE_TOLERANCE);
    controllers::pivot_controller piv_controller(pivot_Kp, ANGULAR_TOLERANCE);

    debug::Logger logger;

    long time_us;
    float delta_time;

    void run10ms(){
        e_stop.run10ms();
        UltrasonicSide.run10ms();
        UltrasonicFront.run10ms();
        bno055_imu.run_10ms();
    }

    fault_e read_sensor_data(){
        if(!e_stop.get_button_press(sensor_data.button))
           return SAR_CRITICAL;

        fault_e fault = SAR_OK;
        if(!UltrasonicFront.get_distance(sensor_data.ultrasonic_front))
            fault = US_NOT_OK;

        if(!UltrasonicSide.get_distance(sensor_data.ultrasonic_side))
            fault = US_NOT_OK;

        if(!bno055_imu.get_angular_position(sensor_data.imu_theta))
            fault = IMU_NOT_OK;

        sensor_data.imu_theta = math::transform_imu_data_to_base_frame(sensor_data.imu_theta);

        filtered_sensor_data.ultrasonic_front = math::ewma(USF_EWMA_ALPHA,
                                                           filtered_sensor_data.ultrasonic_front,
                                                           sensor_data.ultrasonic_front);

        filtered_sensor_data.ultrasonic_side = sensor_data.ultrasonic_side;
        filtered_sensor_data.imu_theta = sensor_data.imu_theta;
        filtered_sensor_data.button = sensor_data.button;

        logger.print_ultrasonic_front(filtered_sensor_data.ultrasonic_front);
        logger.print_ultrasonic_side(filtered_sensor_data.ultrasonic_side);

        // TODO: switch logger function calls to print_imu_t_x/y/z instead of print_tof_t_x/y/z
        logger.print_tof_t_x(math::rad_to_deg(filtered_sensor_data.imu_theta.x));
        logger.print_tof_t_y(math::rad_to_deg(filtered_sensor_data.imu_theta.y));
        logger.print_tof_t_z(math::rad_to_deg(filtered_sensor_data.imu_theta.z));

        return fault;
    }

    fault_e driving_task(float heading, float distance, float goal_lat_distance) {
        /* linear controller computes gas */
        lin_controller.set_target_distance(distance);
        const float gas = lin_controller.compute_gas(filtered_sensor_data.ultrasonic_front);

        /* lateral controller computes steering */
        const float yaw = filtered_sensor_data.imu_theta.z;
        const float gyro_error = heading - yaw;

        /* slow down if gyro error is too bad */
        if(math::float_compare(gyro_error, 0, LATERAL_SLOWDOWN_TOLERANCE)){
            gas = gas/4;
        }

        /* Incorporate robot yaw to calculate lateral distance */
        const float lat_distance = filtered_sensor_data.ultrasonic_side * cos(yaw);
        const float lat_distance_error = lat_distance - goal_lat_distance;
        const float steering = lat_controller.compute_steering(gyro_error, lat_distance_error, delta_time, GYRO_RELIANCE);
        auto motor_speeds = drivetrain::translational_motion_convert(gas, steering);
        if (!motor.set_motor_speeds(motor_speeds.left_motor_speed, motor_speeds.right_motor_speed))
        {
            logger.println("Motor Driver Failed");
            return MOTOR_CRITICAL;
        }
        return SAR_OK;
    }

    fault_e turning_task(float heading) {
        piv_controller.set_target_yaw(heading);

        const float yaw = filtered_sensor_data.imu_theta.z;

        const float pivot_power = piv_controller.compute_pivot_power(yaw);
        const auto motor_speeds = drivetrain::point_turn_convert(pivot_power);
        if (!motor.set_motor_speeds(motor_speeds.left_motor_speed, motor_speeds.right_motor_speed))
        {
            logger.println("Motor Driver Failed");
            return MOTOR_CRITICAL;
        }
        return SAR_OK;
    }

    void transition_to_faulted(){
        stateMachine.transition_to_faulted();
        motor.set_motor_speeds(0, 0);
        motor.disable_motors();
    }


    void app_setup(){
        Serial1.begin(9600);
        stateMachine.init();

        ultrasonicFrontInitConfig.echoPin = FRONT_ULTRASONIC_ECHO_PIN;
        ultrasonicFrontInitConfig.trigPin = FRONT_ULTRASONIC_TRIG_PIN;
        ultrasonicSideInitConfig.echoPin = SIDE_ULTRASONIC_ECHO_PIN;
        ultrasonicSideInitConfig.trigPin = SIDE_ULTRASONIC_TRIG_PIN;

        UltrasonicFront.init(ultrasonicFrontInitConfig);
        UltrasonicSide.init(ultrasonicSideInitConfig);

        if (!bno055_imu.init()){
            stateMachine.transition_to_faulted();
            logger.println("IMU Failed to initialize")
        }

        lin_controller.set_debounce(LINEAR_DEBOUNCE);
        piv_controller.set_debounce(PIVOT_DEBOUNCE)

        e_stop.init(BUTTON_PIN);

        if (!motor.init()){
            stateMachine.transition_to_faulted();
            logger.println("Motors Failed to initialize")
        }
    }

    void app_loop(){
        delta_time = (micros() - time_us)/1000000;
        time_us = micros();
        run10ms();

        if(read_sensor_data() == SAR_CRITICAL){
            logger.println("Sensor Data Fault");
            transition_to_faulted();
        }

        // currently ignores any non-critical faults

        switch (stateMachine.run10ms(filtered_sensor_data)) {
            case sm::paused:
                stateMachine.paused_task();

            case sm::driving:
                if (driving_task(stateMachine.get_heading(), stateMachine.get_distance(), stateMachine.get_lateral_distance()) == MOTOR_CRITICAL){
                    transition_to_faulted();
                }

            case sm::controller_override:
                motor.set_motor_speeds(50, 50);

            case sm::turning:
                if(turning_task(stateMachine.get_heading()) == MOTOR_CRITICAL){
                    transition_to_faulted();
                }

            case sm::faulted:
                stateMachine.faulted_task();
        }

        delayMicroseconds(10000 - (micros() - time_us));
    }

    void reset_controllers(){
        piv_controller.reset();
        lin_controller.reset();
    }

    bool piv_complete(){
        return piv_controller.target_yaw_reached(filtered_sensor_data.imu_theta.z);
    }

    bool lin_complete(){
        return lin_controller.target_distance_reached(filtered_sensor_data.ultrasonic_front);
    }

}
