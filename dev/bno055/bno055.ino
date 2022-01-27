#include "Arduino.h"
#include "dev_bno055.hpp"

sensor::BNO055 imu;

const sensor::BNO055::Config imu_config;

void setup()
{
    Serial.begin(9600);
    imu.init(imu_config);
}

void loop()
{
    imu.run_10ms();
    math::Vector3f theta, theta_dot;
    if (imu.get_angular_position(theta))
    {
        Serial.print("INFO: angular position = {");
        Serial.print(theta.x);
        Serial.print(", ");
        Serial.print(theta.y);
        Serial.print(", ");
        Serial.print(theta.z);
        Serial.print("}");
        Serial.println();
    }
    else
    {
        Serial.println("ERROR: Failed to read angular position");
    }

    if (imu.get_angular_velocity(theta_dot))
    {
        Serial.print("INFO: angular velocity = {");
        Serial.print(theta_dot.x);
        Serial.print(", ");
        Serial.print(theta_dot.y);
        Serial.print(", ");
        Serial.print(theta_dot.z);
        Serial.print("}");
        Serial.println();
    }
    else
    {
        Serial.println("ERROR: Failed to read angular velocity");
    }

    static uin16_t reset_counter = 0;

    if ((reset_counter % 500) == 0)
    {
        Serial.println("INFO: Resetting IMU");
        imu.reset();
        reset_counter = 0;
    }
    ++reset_counter;

    delay(10);
}
