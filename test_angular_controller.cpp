#include "test_angular_controller.hpp"
#include "dev_bno055.hpp"
#include "robot_pinout.hpp"

namespace test_angular_controller
{
    sensor::BNO055 imu;

    constexpr float Kp = 1.0f, Ki = 1.0f;
    controllers::angular_controller ac(Kp, Ki);

    void app_setup()
    {
        Serial.begin(9600);
        if (!imu.init())
        {
            Serial.println("Failed to initialize IMU sensor. ABORTING TEST");
            exit(0);
        }

        ac.set_target_heading(0.0f);
    }

    void app_loop()
    {
        imu.run_10ms();

        math::Vector3f theta;
        constexpr float delta_time = 0.01;
        if (imu.get_angular_position(theta))
        {
            const float yaw = theta.x;
            const float steering = ac.compute_steering(yaw, delta_time);
            constexpr float gas = 100.0f;
            // younes todo need max's code drivetrain.set(gas = gas, steering = steering);

            delay((int)(delta_time * 1000));
        }
        else
        {
            Serial.println("Failed to read angular orientation from IMU");
        }
    }
}
