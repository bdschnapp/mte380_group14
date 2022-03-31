#ifndef __LINEAR_CONTROLLER_HPP__
#define __LINEAR_CONTROLLER_HPP__

#include "pid.hpp"
#include <Arduino.h>

namespace controllers
{
    class linear_controller
    {
    private:
        PID m_pid;
        const float m_error_tolerance;
        float m_target_distance;
        uint8_t m_debounce;
        mutable uint8_t m_positives;
        const uint8_t m_ramp_iterations;
        uint8_t m_passes;

        static constexpr auto MIN_GAS = LINEAR_MIN_GAS;
        static constexpr auto MAX_GAS = LINEAR_MAX_GAS;
        static constexpr auto INVALID_TARGET_DISTANCE = -1.0f;

    public:
        /**
         * linear_controller constructor
         * @param Kp Proportional gain for PID controller
         * @param error_tolerance Linear distance tolerance to determine if goal distance reached [meters]
         */
        linear_controller(const float Kp, const float Ki, const float ramp_iterations, const float error_tolerance);

        ~linear_controller() = default;

        /**
         * Stores the target distance internally
         * @param target_distance The distance from the wall to drive until [meters]
         */
        void set_target_distance(const float target_distance);

        /**
         * Set the minimum number of positives before target is considered reached
         * @param debounce Number of positives before target is considered reached
         */
        void set_debounce(const uint8_t debounce);

        /**
         * Returns whether or not the robot has reached the target distance (+- tolerance specified in constructor)
         * @param front_us_reading Distance measured by the front US sensor [meters]
         * @return Whether we've reached the target distance or not
         */
        bool target_distance_reached(const float front_us_reading) const;

        /**
         * Computes a gas value given the front ultrasonic reading. +ve gas means forward
         * @param front_us_reading Distance measured by the front US sensor [meters]
         * @return gas value in the range [0, 100]
         */
        float compute_gas(const float front_us_reading);

        /**
         * Resets the controller by reseting the PID controller and the target distance
         */
        void reset();

        /**
         * Convenience function that finds a Kp given the distance we want to reach before starting to slow down
         * For example, if we want the robot to floor it until it 0.2 meters away from the wall
         * and then start slowing down linearly, the Kp we need is get_required_kp(0.2)
         * @param distance_to_slow_down Distance from wall when we stop flooring it and gradually slow down [meters]
         * @return Kp
         */
        static float get_required_kp(const float distance_to_slow_down);
    };

}

#endif
