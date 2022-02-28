#include "app_drivetrain.hpp"

namespace subsystem {

	drivetrain::drivetrain() : m_motors(motors), m_left_motor_speed(0), m_right_motor_speed(0) {};

	bool drivetrain::init() {
		m_left_motor_speed = 0;
		m_right_motor_speed = 0;
		return m_motors.reset();
	}

	bool drivetrain::reset() {
		return drivetrain::init();
	}

	void drivetrain::set_speed(double gas, double steering) {
		double l_steering = steering < 0 ? 1.0 + steering : 1.0;
		double r_steering = steering > 0 ? 1.0 - steering : 1.0;

		m_left_motor_speed = l_steering * gas;
		m_right_motor_speed = r_steering * gas;
	}

	void drivetrain::run10ms() {
		m_motors.set_left_motor_speed(m_left_motor_speed);
		m_motors.set_right_motor_speed(m_right_motor_speed);
	}

} // namespace subsystem