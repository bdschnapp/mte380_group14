#include "app_main.hpp"

namespace main
{
    sensor::ultrasonic_init_config_s ultrasonicFrontInitConfig;
    sensor::ultrasonic_init_config_s ultrasonicSideInitConfig;

    sensor::Ultrasonic UltrasonicFront;
    sensor::Ultrasonic UltrasonicSide;

    sensor::BNO055 bno055_imu;

    sensor::Button e_stop;

    actuator::TB9051FTG motor;

    sm::sensor_data_s sensor_data;
    sm::sensor_data_s sensor_data_debounced;

    sm::StateMachine stateMachine;

    controllers::lateral_controller lat_controller(Kp_gyro, Ki_gyro, Kp_lat_us, Ki_lat_us);
    controllers::linear_controller lin_controller(linear_Kp, linear_Ki, DISTANCE_TOLERANCE);
    controllers::pivot_controller piv_controller(Kp, ANGULAR_TOLERANCE);

    debug::Logger logger;

    long time_us;
    float delta_time;

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

         // TODO: Sensor debounce/filtering
         sensor_data_debounced = sensor_data;

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
        /* linear controller computes gas */
        lin_controller.set_target_distance(distance);
        const float gas = lin_controller.compute_gas(sensor_data_debounced.ultrasonic_front);

        /* lateral controller computes steering */
        sensor_data.imu_theta = math::transform_imu_data_to_base_frame(sensor_data.imu_theta);
        const float yaw = sensor_data.imu_theta.x;
        const float gyro_error = heading - yaw;
        /* Incorporate robot yaw to calculate lateral distance */
        const float lat_distance = sensor_data_debounced.ultrasonic_side * cos(yaw);
        const float lat_distance_error = lat_distance - distance;
        const float steering = lat_controller.compute_steering(gyro_error, lat_distance_error, delta_time, GYRO_RELIANCE);
        auto motor_speeds = drivetrain::translational_motion_convert(gas, steering);
        if (!motor.set_motor_speeds(motor_speeds.left_motor_speed, motor_speeds.right_motor_speed))
        {
            logger.println("Motor Driver Failed");
            return MOTOR_CRITICAL;
        }
    }

    fault_e main::turning_task(float heading) {
        piv_controller.set_target_yaw(heading);

        sensor_data.imu_theta = math::transform_imu_data_to_base_frame(sensor_data.imu_theta);
        const float yaw = sensor_data.imu_theta.z;

        const float pivot_power = piv_controller.compute_pivot_power(yaw);
        const auto motor_speeds = drivetrain::point_turn_convert(pivot_power);
        if (!motor.set_motor_speeds(motor_speeds.left_motor_speed, motor_speeds.right_motor_speed))
        {
            logger.println("Motor Driver Failed");
            return MOTOR_CRITICAL;
        }
        return SAR_OK;
    }

    void main::transition_to_faulted(){
        stateMachine.transition_to_faulted();
        motor.set_motor_speeds(0, 0);
        motor.disable_motors();
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

        motor.init();
    }

    void app_loop(){
        delta_time = (micros() - time_us)/100000;
        time_us = micros();
        run10ms();

        if(read_sensor_data() == SAR_CRITICAL){
            logger.println("Sensor Data Fault");
            transition_to_faulted();
        }

        // currently ignores any non-critical faults

        switch (stateMachine.run10ms(sensor_data_debounced)) {
            case sm::paused:
                stateMachine.paused_task();
            case sm::driving:
                driving_task(stateMachine.heading, stateMachine.distance);
            case sm::turning:
                if(turning_task(stateMachine.heading) == MOTOR_CRITICAL){
                    transition_to_faulted();
                }
            case sm::faulted:
                stateMachine.faulted_task();
        }
    }
}
