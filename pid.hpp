#ifndef __PID_HPP__
#define __PID_HPP__

namespace controllers
{
    /*
     * A PID Controller with anti-windup and saturation awareness. (It's technically only a PI controller not a PID)
     * See beauregard's blog for decription: http://brettbeauregard.com/blog/2011/04/improving-the-beginner%e2%80%99s-pid-reset-windup/
     */
    class PID
    {
    private:
        const float m_Kp, m_Ki;
        const float m_lower_saturation, m_upper_saturation;

        float m_error_integral;

    public:
        /**
         * Constructor
         * @param Kp proportional gain
         * @param Ki integral gain
         * @param lower_saturation the lower limit of what the PID controller will output
         * @param upper_saturation the upper limit of what the PID controller will output
         */
        PID(const float Kp, const float Ki, const float lower_saturation, const float upper_saturation);
        ~PID() = default;

        /**
         * Compute the output of the PID controller
         * @param error The difference between your process variable and your feedback
         * @param delta_time Time difference between consecutive compute calls [s]
         * @return output of PID controller
         */
        float compute(const float error, const float delta_time);

        /**
         * Reset the PID controller. This makes it as if the controller has just been started.
         * Internally, it just resets the error integral
         */
        void reset();
    };
}

#endif