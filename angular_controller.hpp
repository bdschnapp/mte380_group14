#ifndef __ANGULAR_CONTROLLER_HPP__
#define __ANGULAR_CONTROLLER_HPP__

namespace controllers
{
    class angular_controller
    {
    private:
        PID m_pid;
        float m_target_heading;

        static constexpr auto DEFAULT_TARGET_HEADING = 0.0f;
        static constexpr auto MIN_STEERING = -100;
        static constexpr auto MAX_STEERING = 100;

    public:
        /**
         * angular_controller constructor
         * @param Kp Proportional gain for PID controller
         * @param Ki Integral gain for PID controller
         */
        angular_controller(const float Kp, const float Ki);

        ~angular_controller() = default;

        /**
         * Stores the target heading internally
         * Expected sequence of headings for course [0, -pi/2, -pi, -3pi/2, -2pi, -5pi/2, -7pi/2]
         * @param target_heading The heading to maintain [radians]. +ve is ccw. no wrap around of angles
         */
        void set_target_heading(const float target_heading);

        /**
         * Computes a steering value given the gyroscope yaw reading
         * @param gyro_yaw gyroscope yaw reading. +ve is ccw. no wrap around of angles [radians]
         * @return steering value in the range [-100, 100]. +ve steering is veering to the left
         */
        float compute_steering(float gyro_yaw) const;

        /**
         * Resets the controller by reseting the PID controller and the target heading
         */
        void reset();
    };
}

#endif