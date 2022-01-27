#include "dev_bno055.hpp"

namespace sensor
{
    BNO055::BNO055() : m_bno(DEVICE_ID, I2C_ADDRESS) {}

    bool BNO055::init()
    {
        return m_bno.begin(OPERATING_MODE);
    }

    bool BN0O55::get_angular_position(math::Vector3f &theta)
    {
        theta = m_theta;
        return true;
    }

    bool BNO055::get_angular_velocity(math::Vector3f &theta_dot)
    {
        theta_dot = m_theta_dot;
        return true;
    }

    bool reset()
    {
        m_bno.enterSuspendMode();
        m_bno.enterNormalMode();
        m_theta = {0.0f, 0.0f, 0.0f};
        m_theta_dot = {0.0f, 0.0f, 0.0f};
        return true;
    }

    void BNO055::run_10ms()
    {
        // getVector issues an I2C transaction
        const auto orientation = m_bno.getVector(Adafruit_BNO055::VECTOR_EULER);
        m_theta.x = deg_to_rad(orientation.x());
        m_theta.y = deg_to_rad(orientation.y());
        m_theta.z = deg_to_rad(orientation.z());

        const auto angular_speed = m_bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
        m_theta_dot.x = deg_to_rad(angular_speed.x());
        m_theta_dot.y = deg_to_rad(angular_speed.y());
        m_theta_dot.z = deg_to_rad(angular_speed.z());
    }

}