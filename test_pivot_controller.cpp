#include "test_pivot_controller.hpp"
#include "pivot_controller.hpp"
#include "dev_bno055.hpp"
#include "drivetrain.hpp"
#include "dev_TB9051FTG.hpp"

namespace test_pivot_controller
{
    sensor::BNO055 imu;
    const float Kp = controllers::pivot_controller::get_required_kp(math::deg_to_rad(5));
    controllers::pivot_controller pc(Kp, math::deg_to_rad(1));
    actuator::TB9051FTG motor_driver;

    const float target_headings[2] = {math::deg_to_rad(-90), 0.0f};
    uint8_t current_target_heading_index = 0;

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
    }

    void app_loop()
    {
        imu.run_10ms();
        pc.set_target_yaw(target_headings[current_target_heading_index]);

        math::Vector3f theta;
        if (imu.get_angular_position(theta))
        {
            const float yaw = theta.x;
            if (!pc.target_yaw_reached(yaw))
            {
                const float pivot_power = pc.compute_pivot_power(yaw);
                const auto motor_speeds = drivetrain::point_turn_convert(pivot_power);
                if (!motor_driver.set_motor_speeds(motor_speeds.left_motor_speed, motor_speeds.right_motor_speed))
                {
                    Serial.println("Failed to set motor speeds");
                }
            }
            else
            {
                ++current_target_heading_index;
                if (current_target_heading_index == 2)
                {
                    Serial.println("Pivot test done. Robot will hang forever. Restart robot to restart test");
                    if (!motor_driver.disable_motors())
                    {
                        Serial.println("Failed to disable motors");
                    }
                    exit(0);
                }
            }
        }
        else
        {
            Serial.println("Failed to read angular orientation from IMU");
        }
        delay(10);
    }
}
