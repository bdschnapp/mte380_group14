#include "pivot_controller.hpp"
#include "lib_math.hpp"

namespace controllers
{
    pivot_controller::pivot_controller(const float Kp, const float error_tolerance) : m_pid(Kp, 0),
                                                                                      m_error_tolerance(error_tolerance),
                                                                                      m_target_heading(0.0f) {}

    void pivot_controller::set_target_yaw(const float target_yaw)
    {
        m_target_heading = target_yaw;
    }

    bool pivot_controller::target_yaw_reached(const float gyro_yaw) const
    {
        return math::float_compare(gyro_yaw, m_target_heading, m_error_tolerance);
    }

    float pivot_controller::compute_pivot_power(const float gyro_yaw) const
    {
        return math::clamp(MIN_PIVOT_POWER, MAX_PIVOT_POWER, m_pid.compute(m_target_heading - gyro_yaw));
    }

    void pivot_controller::reset()
    {
        m_pid.reset();
        m_target_heading = 0.0f;
    }

    float pivot_controller::get_required_kp(const float yaw_to_slow_down)
    {
        if (math::float_compare(yaw_to_slow_down, 0.0f) || yaw_to_slow_down < 0)
        {
            return FLT_MAX;
        }
        return MAX_PIVOT_POWER / yaw_to_slow_down;
    }

}