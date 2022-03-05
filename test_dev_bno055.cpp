#include "Arduino.h"
#include "dev_bno055.hpp"
#include "test_dev_bno055.hpp"

namespace test_dev_bno055
{
    sensor::BNO055 bno055_imu;

    void app_setup()
    {
        Serial.begin(9600);
        bno055_imu.init();
    }

    void app_loop()
    {
        bno055_imu.run_10ms();
        math::Vector3f theta, theta_dot;
        if (bno055_imu.get_angular_position(theta))
        {
            theta = math::transform_imu_data_to_base_frame(theta);
            Serial.print("INFO: angular position = {");
            Serial.print(math::rad_to_deg(theta.x));
            Serial.print(", ");
            Serial.print(math::rad_to_deg(theta.y));
            Serial.print(", ");
            Serial.print(math::rad_to_deg(theta.z));
            Serial.print("} ");
        }
        else
        {
            Serial.println("ERROR: Failed to read angular position");
        }

        if (bno055_imu.get_angular_velocity(theta_dot))
        {
            theta_dot = math::transform_imu_data_to_base_frame(theta_dot);
            Serial.print("INFO: angular velocity = {");
            Serial.print(math::rad_to_deg(theta_dot.x));
            Serial.print(", ");
            Serial.print(math::rad_to_deg(theta_dot.y));
            Serial.print(", ");
            Serial.print(math::rad_to_deg(theta_dot.z));
            Serial.print("}");
            Serial.println();
        }
        else
        {
            Serial.println("ERROR: Failed to read angular velocity");
        }

        delay(200);
    }
}
