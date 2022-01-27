#ifndef __DEV_BNO055_HPP__
#define __DEV_BNO055_HPP__

#include "Arduino.h"
#include "lib_math.hpp"
#include "Adafruit_BNO055.h"

/* This is a thin wrapper around the Adafruit_BNO055 class
   Potential Improvements: Consider sensor calibration */

namespace sensor
{
    class BNO055
    {
        BN0O55();
        ~BNO055() = default;

        /**
         * Initialize the IMU
         * @return[bool] success of initilization
         */
        bool init();

        /**
         * Power cycle IMU and reset internal variables
         * @return[bool] success of reset
         */
        bool reset();

        /**
         * Read from IMU. Issues I2C transactions
         * The IMU can produce a new reading every 10 ms
         */
        void run_10ms();

        /**
         * Get the angular position in units of radians
         * @param theta vector to store orientation in
         * @return[bool] success of read
         */
        bool get_angular_position(math::Vector3f &theta);

        /**
         * Get the angular velocity in units of radians/second
         * @param theta vector to store angular speed in
         * @return[bool] success of read
         */
        bool get_angular_velocity(math::Vector3f &theta_dot);

        // younes todo figure pin configuartion. able to connect to any i2c bus?

    private:
        Adafruit_BNO055 m_bno;

        math::Vector3f m_theta, m_theta_dot;

        /* Parameters that should not be reconfigured */
        // Slave address defaults to 0x28 if ADR pin is not held high
        static constexpr auto I2C_ADDRESS = 0x28;
        // Device ID as specified in data sheet
        static constexpr auto DEVICE_ID = 0xA0;
        // disregards magnetometer data when measuring relative orientation
        static constexpr auto OPERATING_MODE = OPERATION_MODE_IMUPLUS;
    };
}

#endif