#include "test_lateral_controller.hpp"
#include "dev_bno055.hpp"
#include "app_defines.hpp"
#include "dev_ultrasonic.hpp"
#include "lateral_controller.hpp"
#include "dev_TB9051FTG.hpp"
#include "drivetrain.hpp"

namespace test_lateral_controller
{
    sensor::BNO055 imu;
    actuator::TB9051FTG motor_driver;
    sensor::Ultrasonic lat_us;

    constexpr float Kp_gyro = 1.0f, Ki_gyro = 1.0f, Kp_lat_us = 1.0f, Ki_lat_us = 1.0f;
    controllers::lateral_controller lat_controller(Kp_gyro, Ki_gyro, Kp_lat_us, Ki_lat_us);

    constexpr float goal_lateral_distance = 0.1f, goal_yaw = 0.0f;

    /* This is a parameter you can change to experiment with different reliance ratios */
    constexpr float GYRO_RELIANCE = 0.5f;

    void app_setup()
    {
        Serial.begin(9600);
        if (imu.init())
        {
            Serial.println("Successfully initialized imu");
        }
        else
        {
            Serial.println("Failed to initialize IMU sensor. ABORTING TEST");
            exit(0);
        }
        if (motor_driver.init())
        {
            Serial.println("Succesfully initialized motor driver");
        }
        else
        {
            Serial.println("Failed to initialize motor driver. ABORTING TEST");
            exit(0);
        }
        if (lat_us.init({SIDE_ULTRASONIC_TRIG_PIN, SIDE_ULTRASONIC_ECHO_PIN}))
        {
            Serial.println("Succesfully initialized front ultrasonic sensor");
        }
        else
        {
            Serial.println("Failed to initialize front ultrasonic sensor. ABORTING TEST");
            exit(0);
        }
    }

    void app_loop()
    {
        imu.run_10ms();
        lat_us.run10ms();

        math::Vector3f theta;
        constexpr float delta_time = 0.01;
        float lat_us_distance = 0.0f;
        if (imu.get_angular_position(theta) && lat_us.get_distance(lat_us_distance))
        {
            const float yaw = theta.x;
            const float gyro_error = goal_yaw - yaw;
            const float lat_us_error = lat_us_distance - goal_lateral_distance;
            const float steering = lat_controller.compute_steering(gyro_error, lat_us_error, delta_time, GYRO_RELIANCE);
            constexpr float gas = 50.0f;

            auto motor_speeds = drivetrain::translational_motion_convert(gas, steering);

            motor_driver.set_motor_speeds(motor_speeds.left_motor_speed, motor_speeds.right_motor_speed);

            delay((int)(delta_time * 1000));
        }
        else
        {
            Serial.println("Failed to read from sensors");
        }
    }
}
