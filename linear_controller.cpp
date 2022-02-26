#include "linear_controller.hpp"
#include "lib_math.hpp"

namespace controllers
{
    linear_controller::linear_controller(const float Kp, const float error_tolerance) : m_pid(Kp, 0),
                                                                                        m_error_tolerance(error_tolerance),
                                                                                        m_target_distance(INVALID_TARGET_DISTANCE)
    {
    }

    void linear_controller::set_target_distance(const float target_distance)
    {
        m_target_distance = target_distance;
    }

    bool linear_controller::target_distance_reached(const float front_us_reading) const
    {
        // younes todo might need to add some debouncing
        return math::float_compare(front_us_reading, m_target_distance, m_error_tolerance);
    }

    float linear_controller::compute_gas(const float front_us_reading) const
    {
        // this will return 0 gas for a -ve m_target_distance
        return math::clamp(MIN_GAS, MAX_GAS, m_pid.compute(front_us_reading - m_target_distance));
    }

    void linear_controller::reset()
    {
        m_pid.reset();
        m_target_distance = INVALID_TARGET_DISTANCE;
    }

    float linear_controller::get_required_kp(const float distance_to_slow_down)
    {
        if (math::float_compare(distance_to_slow_down, 0.0f) || distance_to_slow_down < 0)
        {
            return FLT_MAX;
        }
        return MAX_GAS / distance_to_slow_down;
    }

}