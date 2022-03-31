#include "linear_controller.hpp"
#include "lib_math.hpp"

namespace controllers
{
    linear_controller::linear_controller(const float Kp, const float Ki, const float ramp_iterations, const float error_tolerance) : m_pid(Kp, Ki, MIN_GAS, MAX_GAS),
                                                                                                                                     m_error_tolerance(error_tolerance),
                                                                                                                                     m_target_distance(INVALID_TARGET_DISTANCE),
                                                                                                                                     m_debounce(0),
                                                                                                                                     m_positives(0),
                                                                                                                                     m_ramp_iterations(ramp_iterations),
                                                                                                                                     m_passes(0)
    {
    }

    void linear_controller::set_target_distance(const float target_distance)
    {
        m_target_distance = target_distance;
    }

    void linear_controller::set_debounce(const uint8_t debounce)
    {
        m_debounce = debounce;
    }

    bool linear_controller::target_distance_reached(const float front_us_reading) const
    {
        if (math::float_compare(front_us_reading, m_target_distance, m_error_tolerance) || front_us_reading < m_target_distance)
        {
            ++m_positives;
        }
        else
        {
            m_positives = 0;
        }
        return m_positives > m_debounce;
    }

    float linear_controller::compute_gas(const float front_us_reading)
    {
        m_passes++;
        if (m_passes < m_ramp_iterations)
        {
            return m_passes * MAX_GAS / m_ramp_iterations;
        }
        // this will return 0 gas for a -ve m_target_distance
        // also since this is P controller, time step is not used in compute call
        return math::clamp(MIN_GAS, MAX_GAS, m_pid.compute(front_us_reading - m_target_distance, 0.0f));
    }

    void linear_controller::reset()
    {
        m_pid.reset();
        m_target_distance = INVALID_TARGET_DISTANCE;
        m_positives = 0;
        m_passes = 0;
    }

    float linear_controller::get_required_kp(const float distance_to_slow_down)
    {
        return MAX_GAS / distance_to_slow_down;
    }

}