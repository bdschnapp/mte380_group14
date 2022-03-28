#include "dev_bno055.hpp"

namespace sensor
{
    BNO055::BNO055() : m_bno(DEVICE_ID, I2C_ADDRESS), m_last_read_successful(false),
                       m_theta_previous{0, 0, 0}, m_theta_unwrapped{0, 0, 0},
                       m_offset{0, 0, 0} {}

    bool BNO055::init()
    {
        const bool ret = m_bno.begin(OPERATING_MODE);
        // TODO: Consider global bootup time
        delay(IMU_BOOTUP_MS);
        return ret;
    }

    bool BNO055::get_angular_position(math::Vector3f &theta)
    {
        theta = m_theta - m_offset;
        return m_last_read_successful;
    }

    bool BNO055::get_angular_velocity(math::Vector3f &theta_dot)
    {
        theta_dot = m_theta_dot;
        return m_last_read_successful;
    }

    math::Vector3f BNO055::unwrap_theta(const math::Vector3f &theta)
    {
        math::Vector3f theta_diff = theta - m_theta_previous;
        auto unwrap = [](float &theta_diff) -> void
        {
            if (theta_diff < -180)
            {
                theta_diff += 360;
            }
            else if (theta_diff >= 180)
            {
                theta_diff -= 360;
            }
        };

        unwrap(theta_diff.x);
        unwrap(theta_diff.y);
        unwrap(theta_diff.z);

        m_theta_unwrapped = m_theta_unwrapped + theta_diff;
        m_theta_previous = theta;

        return m_theta_unwrapped;
    }

    void BNO055::run_10ms()
    {
        // getVector issues an I2C transaction
        const auto orientation = m_bno.getVector(Adafruit_BNO055::VECTOR_EULER);
        // imu reports {x,y,z} = {y,p,r}, but yaw is rotation abt z and roll is rotation abt x
        const math::Vector3f theta_wrapped = {-orientation.z(), orientation.y(), -orientation.x()};
        m_theta = unwrap_theta(theta_wrapped);
        m_theta.x = math::deg_to_rad(m_theta.x);
        m_theta.y = math::deg_to_rad(m_theta.y);
        m_theta.z = math::deg_to_rad(m_theta.z);

        const auto angular_speed = m_bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
        m_theta_dot.z = math::deg_to_rad(-angular_speed.x());
        m_theta_dot.y = math::deg_to_rad(angular_speed.y());
        m_theta_dot.x = math::deg_to_rad(-angular_speed.z());

        /* See header for explanation of needing offset */
        static bool first_pass = true;
        if (first_pass)
        {
            m_offset = m_theta;
            first_pass = false;
        }

        // NOTE: Bypass validity checking for now since this caused false negatives
        m_last_read_successful = true;
        /*uint8_t system_status = 0, self_test_result = 0, system_error = 0;
        m_bno.getSystemStatus(&system_status, &self_test_result, &system_error);
        constexpr auto EXPECTED_SYSTEM_STATUS_VALUE = 5;
        constexpr auto EXPECTED_SELF_TEST_RESULT_VALUE = 15;
        constexpr auto EXPECTED_SYSTEM_ERROR_VALUE = 0;
        m_last_read_successful = (system_status == EXPECTED_SYSTEM_STATUS_VALUE) &&
                                 (self_test_result == EXPECTED_SELF_TEST_RESULT_VALUE) &&
                                 (system_error == EXPECTED_SYSTEM_ERROR_VALUE);*/
    }

}
