#include "pid.hpp"
#include "lib_math.hpp"

namespace controllers
{

    PID::PID(const float Kp, const float Ki, const float lower_saturation, const float upper_saturation) : m_Kp(Kp), m_Ki(Ki),
                                                                                                         m_lower_saturation(lower_saturation),
                                                                                                         m_upper_saturation(upper_saturation),
                                                                                                         m_error_integral(0.0f) {}
    float PID::compute(const float error, const float delta_time)
    {
        m_error_integral = math::clamp(m_lower_saturation, m_upper_saturation, m_error_integral + error * delta_time);
        return math::clamp(m_lower_saturation, m_upper_saturation, m_Kp * error + m_Ki * m_error_integral);
    }

    void PID::reset()
    {
        m_error_integral = 0.0f;
    }

}