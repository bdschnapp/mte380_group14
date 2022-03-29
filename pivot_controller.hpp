#ifndef __PIVOT_CONTROLLER_HPP__
#define __PIVOT_CONTROLLER_HPP__
#include "pid.hpp"
#include <Arduino.h>

namespace controllers
{
    class pivot_controller
    {
    private:
        PID m_pid;
        const float m_error_tolerance;
        float m_target_heading;
        uint8_t m_debounce;
        mutable uint8_t m_positives;

        static constexpr auto MIN_PIVOT_POWER = -100;
        static constexpr auto MAX_PIVOT_POWER = 100;

    public:
        /**
         * pivot_controller constructor
         * @param Kp Proportional gain for PID controller
         * @param error_tolerance Yaw tolerance to determine if goal distance reached [radians]
         */
        pivot_controller(const float Kp, const float error_tolerance);

        ~pivot_controller() = default;

        /**
         * Stores the target distance internally
         * @param target_yaw The target yaw we want to achieve at the end of the pivot maneuver [radians]
         */
        void set_target_yaw(const float target_yaw);

        /**
         * Set the minimum number of positives before target is considered reached
         * @param debounce Number of positives before target is considered reached
         */
        void set_debounce(const uint8_t debounce);

        /**
         * Returns whether or not the robot has reached the target yaw (+- tolerance specified in constructor)
         * @param gyro_yaw Yaw reading from IMU [radians]
         * @return Whether we've reached the target yaw or not
         */
        bool target_yaw_reached(const float gyro_yaw) const;

        /**
         * Copmutes the pivot power given the robot's yaw
         * @param gyro_yaw Yaw reading from IMU. +ve is ccw. No wrap around of angles[radians]
         * @return pivot power in range [-100, 100]. +ve pivot power means pivot ccw
         */
        float compute_pivot_power(const float gyro_yaw);

        /**
         * Resets the controller by reseting the PID controller and the target yaw
         */
        void reset();

        /**
         * Convenience function that finds a Kp given the yaw we want to reach before starting to slow down
         * For example, if we want the robot to pivot with full power until it's 0.07 radians away from the target yaw
         * and then start slowing down linearly, the Kp we need is get_required_kp(0.07)
         * @param yaw_to_slow_down Yaw from target_yaw when we stop pivoting with full power and gradually slow down [radians]
         * @return Kp
         */
        static float get_required_kp(const float yaw_to_slow_down);
    };

}

#endif