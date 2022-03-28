#include "dev_TB9051FTG.hpp"
#include "lib_math.hpp"

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
		m_shield.setM1Speed(remap_speed(-speed) );
		return !get_fault();
	}

	bool TB9051FTG::set_right_motor_speed(double speed) {
		//pololu driver takes an int value from 400 to -400
		m_shield.setM2Speed(remap_speed(speed) );
		return !get_fault();
	}

	bool TB9051FTG::set_motor_speeds(double l_speed, double r_speed) {
		//pololu driver takes an int value from 400 to -400
		//the left motor is reversed
		m_shield.setSpeeds(remap_speed(-l_speed), 
						   remap_speed(r_speed));
		return !get_fault();
	}

	bool TB9051FTG::disable_motors() {
		m_shield.disableDrivers();
		return get_fault();
	}

	bool TB9051FTG::get_fault() {
		return m_shield.getM1Fault() || m_shield.getM2Fault();
	}

	int TB9051FTG::remap_speed(double speed){
		bool is_negative = (speed < 0);
		int remap = static_cast<int> (math::remap(0, 100, abs(speed), 48, 400));
		if(is_negative){
			remap = remap * -1;
		}
		return remap;
	}

} // namespace actuator