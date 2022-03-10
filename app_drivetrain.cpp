#include "app_drivetrain.hpp"

namespace subsystem {

	drivetrain::drivetrain() : m_left_motor_speed(0), m_right_motor_speed(0) {};

	bool drivetrain::init(actuator::TB9051FTG motors) {
		m_motors = motors;
		m_left_motor_speed = 0;
		m_right_motor_speed = 0;
		return m_motors.reset();
	}

	bool drivetrain::reset() {
		m_motors.reset();
		return drivetrain::init(m_motors);
	}

	void drivetrain::set_speed(double gas, double steering) {
		double l_steering = steering < 0 ? 1.0 + steering : 1.0;
		double r_steering = steering > 0 ? 1.0 - steering : 1.0;

		m_left_motor_speed = -l_steering * gas;
		m_right_motor_speed = r_steering * gas;
	}

	void drivetrain::run10ms() {
		m_motors.set_left_motor_speed(m_left_motor_speed);
		delay(1);
		m_motors.set_right_motor_speed(m_right_motor_speed);
	}

	void drivetrain::get_motor_speeds(double& left_speed, double& right_speed) {
		left_speed = m_left_motor_speed;
		right_speed = m_right_motor_speed;
	}

} // namespace subsystem