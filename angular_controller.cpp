#include "angular_controller.hpp"
#include "lib_math.hpp"

namespace controllers
{
    angular_controller::angular_controller(const float Kp, const float Ki)
        : m_pid(Kp, Ki), m_target_heading(DEFAULT_TARGET_HEADING) {}

    void angular_controller::set_target_heading(const float target_heading)
    {
        m_target_heading = target_heading;
    }

    float angular_controller::compute_steering(const float gyro_yaw) const
    {
        // younes todo might need deadzone
        // younes todo might need lateral ultrasonic fallback
        return math::clamp(MIN_STEERING, MAX_STEERING, m_pid.compute(m_target_heading - gyro_yaw));
    }

    void angular_controller::reset()
    {
        m_pid.reset();
        m_target_heading = DEFAULT_TARGET_HEADING;
    }

}