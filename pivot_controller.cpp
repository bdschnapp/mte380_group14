#include "pivot_controller.hpp"
#include "lib_math.hpp"

namespace controllers
{
    pivot_controller::pivot_controller(const float Kp, const float error_tolerance) : m_pid(Kp, 0, MIN_PIVOT_POWER, MAX_PIVOT_POWER),
                                                                                      m_error_tolerance(error_tolerance),
                                                                                      m_target_heading(0.0f),
                                                                                      m_debounce(0),
                                                                                      m_positives(0) {}

    void pivot_controller::set_target_yaw(const float target_yaw)
    {
        m_target_heading = target_yaw;
    }

    void pivot_controller::set_debounce(const uint8_t debounce)
    {
        m_debounce = debounce;
    }

    bool pivot_controller::target_yaw_reached(const float gyro_yaw) const
    {
        if (math::float_compare(gyro_yaw, m_target_heading, m_error_tolerance))
        {
            ++m_positives;
        }
        else
        {
            m_positives = 0;
        }
        return m_positives > m_debounce;
    }

    float pivot_controller::compute_pivot_power(const float gyro_yaw)
    {
        // delta_time in compute call is not used since only proportional controller
        return math::clamp(MIN_PIVOT_POWER, MAX_PIVOT_POWER, m_pid.compute(m_target_heading - gyro_yaw, 0.0f));
    }

    void pivot_controller::reset()
    {
        m_pid.reset();
        m_target_heading = 0.0f;
        m_positives = 0;
    }

    float pivot_controller::get_required_kp(const float yaw_to_slow_down)
    {
        return MAX_PIVOT_POWER / yaw_to_slow_down;
    }

}