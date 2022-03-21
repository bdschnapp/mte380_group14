#ifndef __LATERAL_CONTROLLER_HPP__
#define __LATERAL_CONTROLLER_HPP__

#include "pid.hpp"

namespace controllers
{
    /* This lateral controller combines yaw and lateral distance errors
       to produce a steering value*/
    class lateral_controller
    {
    private:
        PID m_gyro_pid, m_lat_us_pid;
        static constexpr auto MIN_STEERING = -100;
        static constexpr auto MAX_STEERING = 100;

    public:
        lateral_controller(const float Kp_gyro, const float Ki_gyro, const float Kp_lat_us, const float Ki_lat_us);
        ~lateral_controller() = default;

        /**
         * Computes a steering value given the robot's gyro error and its lateral ultrasonic error
         * gyro error is defined as target heading - current heading
         * lateral ultrasonic error is defined as target lateral position - current lateral position
         * @param gyro_error difference between target robot heading and current robot heading [radians]
         * @param lat_us_error difference between current lateral position and target lateral position [m]
         * @param delta_time time difference between consecutive compute calls [s]
         * @param gyro_reliance a percentage representing the reliance on the gyro error as opposed to the lateral position error.
         *                      a value of 1 makes the lateral controller rely solely on the gyro. A value of 0.5 make the lateral
         *                      controller rely equally on both the gyro and lateral ultrasonic. Value should lie in range [0,1]
         * @return steering value in the range [-100, 100]. +ve steering is veering to the left
         */
        float compute_steering(const float gyro_error, const float lat_us_error,
                               const float delta_time, const float gyro_reliance);
    };

}

#endif