#include "test_app_drivetrain.hpp"

namespace test_dev_drivetrain {

	actuator::TB9051FTG motors;
	subsystem::drivetrain(motors) m_drivetrain;

	void app_setup() {
		Serial.begin(9600);
		m_drivetrain.init();
	}

	void app_loop() {
		//Due to limitations of the speed controller shield, the arduino
		//cannot be powered by both USB and battery simultaneously.
		//Therefore, this is simply a mechanical test.
		//TODO: add logging to this test after it is implemented.
		delay(100);
		m_drivetrain.set_speed(0.5, 0);
		delay(1000);
		m_drivetrain.set_speed(0.5, -0.5);
		delay(1000);
		m_drivetrain.set_speed(0.5, 0.5);
		delay(1000);
	}
}