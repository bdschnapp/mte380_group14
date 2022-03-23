#include "dev_TB9051FTG.hpp"

namespace actuator {

	TB9051FTG::TB9051FTG() : m_shield() {};

	bool TB9051FTG::init() {
		m_shield.init();
		m_shield.enableDrivers();
		//wait 1ms for driver to enable so fault pins are not low
		delay(1);
		return !get_fault();
	}

	bool TB9051FTG::reset() {
		//enables and disables motor drivers, may help if
		//motor gets stuck in an error state
		m_shield.disableDrivers();
		delay(1);
		m_shield.enableDrivers();
		delay(1);
		return !get_fault();
	}

	bool TB9051FTG::set_left_motor_speed(double speed) {
		//pololu driver takes an int value from 400 to -400
		//the left motor is reversed
		m_shield.setM1Speed(static_cast<int> (-speed * 4) );
		return !get_fault();
	}

	bool TB9051FTG::set_right_motor_speed(double speed) {
		//pololu driver takes an int value from 400 to -400
		m_shield.setM2Speed(static_cast<int> (speed * 4) );
		return !get_fault();
	}

	bool TB9051FTG::set_motor_speeds(double l_speed, double r_speed) {
		//pololu driver takes an int value from 400 to -400
		//the left motor is reversed
		m_shield.setSpeeds(static_cast<int> (-l_speed * 4), 
						   static_cast<int> (r_speed * 4));
		return !get_fault();
	}

	bool TB9051FTG::disable_motors() {
		m_shield.disableDrivers();
		return get_fault();
	}

	bool TB9051FTG::get_fault() {
		return m_shield.getM1Fault() || m_shield.getM2Fault();
	}

} // namespace actuator