#ifndef __DEV_BNO055_HPP__
#define __DEV_BNO055_HPP__

#include "Arduino.h"
#include "lib_math.hpp"
#include "Adafruit_BNO055.h"

/* HW CONFIG:
Vin: Connect to 5v
GND: Connect to ground
SDA & SCL:  Any I2C bus on the arduino (ie. for UNO, SCL = A5; SDA = A4 will work)
*/

/* This is a thin wrapper around the Adafruit_BNO055 class
   Potential Improvements: Consider sensor calibration */

namespace sensor
{
    class BNO055
    {
    public:
        BNO055();
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
        // younes todo think some more about read failures could read the imu id every 10 ms and if that failed imu is disconnected
        bool get_angular_position(math::Vector3f &theta);

        /**
         * Get the angular velocity in units of radians/second
         * @param theta vector to store angular speed in
         * @return[bool] success of read
         */
        bool get_angular_velocity(math::Vector3f &theta_dot);

    private:
        Adafruit_BNO055 m_bno;

        math::Vector3f m_theta, m_theta_dot;

        /* Parameters that should not be reconfigured */
        // Slave address defaults to 0x28 if ADR pin is not held high
        static constexpr auto I2C_ADDRESS = 0x28;
        // Device ID as specified in data sheet
        static constexpr auto DEVICE_ID = 0xA0;
        // disregards magnetometer data when measuring relative orientation
        static constexpr auto OPERATING_MODE = Adafruit_BNO055::OPERATION_MODE_IMUPLUS;
    };
}

#endif