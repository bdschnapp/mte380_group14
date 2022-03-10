#include "test_app_drivetrain.hpp"

namespace test_app_drivetrain {

	actuator::TB9051FTG motors;
	subsystem::drivetrain m_drivetrain;
	int i;
	double left;
	double right;

	void app_setup() {
		motors.init();
		Serial.begin(9600);
		m_drivetrain.init(motors);
		i = 0;
		delay(10000);

	}

	void app_loop() {
		m_drivetrain.run10ms();
		m_drivetrain.get_motor_speeds(left, right);
		Serial.print("left: ");
		Serial.print(left);
		Serial.print("Right: ");
		Serial.print(right);
		Serial.print("\n");

		if (i < 50) {
			m_drivetrain.set_speed(0.5, 0);
		}
		else if (i < 100) {
			m_drivetrain.set_speed(0.5, 0.5);
		}
		else if (i < 150) {
			m_drivetrain.set_speed(0.5, -0.5);
		}
		else if (i < 200) {
			m_drivetrain.set_speed(-0.5, 0);
		}
		else if (i > 300) {
			i = 0;
		}
		i++;
		delay(10);
	}
}