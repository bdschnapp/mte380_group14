#include "dev_bno055.hpp"

namespace sensor
{
    BNO055::BNO055() : m_bno(DEVICE_ID, I2C_ADDRESS), m_last_read_successful(false) {}

    bool BNO055::init()
    {
        return m_bno.begin(OPERATING_MODE);
    }

    bool BNO055::get_angular_position(math::Vector3f &theta)
    {
        theta = m_theta;
        return m_last_read_successful;
    }

    bool BNO055::get_angular_velocity(math::Vector3f &theta_dot)
    {
        theta_dot = m_theta_dot;
        return m_last_read_successful;
    }

    bool BNO055::reset()
    {
        // Resetting the sensor is finnicky and buggy. The adafruit library does not have direct functionality
        // Manipulating the reset pin is finnicky and results in strange behavior.
        m_theta = {0.0f, 0.0f, 0.0f};
        m_theta_dot = {0.0f, 0.0f, 0.0f};
        return true;
    }

    void BNO055::run_10ms()
    {
        // getVector issues an I2C transaction
        const auto orientation = m_bno.getVector(Adafruit_BNO055::VECTOR_EULER);
        m_theta.x = math::deg_to_rad(orientation.x());
        m_theta.y = math::deg_to_rad(orientation.y());
        m_theta.z = math::deg_to_rad(orientation.z());

        const auto angular_speed = m_bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
        m_theta_dot.x = math::deg_to_rad(angular_speed.x());
        m_theta_dot.y = math::deg_to_rad(angular_speed.y());
        m_theta_dot.z = math::deg_to_rad(angular_speed.z());

        // This isn't perfect, but it'll be false if the sensor's I2C pins are disconnected
        uint8_t system_status = 0, self_test_result = 0, system_error = 0;
        m_bno.getSystemStatus(&system_status, &self_test_result, &system_error);
        constexpr auto EXPECTED_SYSTEM_STATUS_VALUE = 5;
        constexpr auto EXPECTED_SELF_TEST_RESULT_VALUE = 15;
        constexpr auto EXPECTED_SYSTEM_ERROR_VALUE = 0;
        m_last_read_successful = (system_status == EXPECTED_SYSTEM_STATUS_VALUE) &&
                                 (self_test_result == EXPECTED_SELF_TEST_RESULT_VALUE) &&
                                 (system_error == EXPECTED_SYSTEM_ERROR_VALUE);
    }

}
