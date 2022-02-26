#include "test_pivot_controller.hpp"
#include "pivot_controller.hpp"
#include "dev_bno055.hpp"

namespace test_pivot_controller
{
    sensor::BNO055 imu;
    constexpr float Kp = controllers::pivot_controller::get_required_kp(math::deg_to_rad(5));
    controllers::pivot_controller pc(Kp, math::deg_to_rad(1));

    constexpr float target_headings[2] = {math::deg_to_rad(-90), 0.0f};
    uint8_t current_target_heading_index = 0;

    void app_setup()
    {
        Serial.begin(9600);
        if (!bno055_imu.init())
        {
            Serial.println("Failed to initialize IMU sensor. ABORTING TEST");
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
                // younes todo need max's code drivetrain.set_pivot(pivot_power=pivot_power);
            }
            else
            {
                ++current_target_heading_index;
                if (current_target_heading_index == 2)
                {
                    Serial.println("Pivot test done. Robot will hang forever. Restart robot to restart test");
                    // younes todo need max's code to set motors to 0
                    exit(0);
                }
            }

            delay(10);
        }
        else
        {
            Serial.println("Failed to read angular orientation from IMU");
        }
    }
}
