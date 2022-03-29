#include "lateral_controller.hpp"
#include "lib_math.hpp"

namespace controllers
{
    lateral_controller::lateral_controller(const float Kp_gyro, const float Ki_gyro,
                                           const float Kp_lat_us, const float Ki_lat_us) : m_gyro_pid(Kp_gyro, Ki_gyro, MIN_STEERING, MAX_STEERING),
                                                                                           m_lat_us_pid(Kp_lat_us, Ki_lat_us, MIN_STEERING, MAX_STEERING) {}

    float lateral_controller::compute_steering(const float yaw_error, const float lateral_position_error,
                                               const float delta_time, const float yaw_reliance)
    {
        /* TODO: might need deadzone */
        const float yaw_contribution = math::clamp(MIN_STEERING, MAX_STEERING, m_gyro_pid.compute(yaw_error, delta_time));
        const float lateral_position_contribution = math::clamp(MIN_STEERING, MAX_STEERING, m_lat_us_pid.compute(lateral_position_error, delta_time));
        return yaw_contribution * yaw_reliance + lateral_position_contribution * (1 - yaw_reliance);
    }
}