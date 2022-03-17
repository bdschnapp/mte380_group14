#include "test_drivetrain.hpp"

namespace test_drivetrain {

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
		//initialization delay to let user position robot after connecting power
		delay(10000);

	}

	void app_loop() {
		// m_drivetrain.run10ms();
		m_drivetrain.get_motor_speeds(left, right);
		Serial.print("left: ");
		Serial.print(left);
		Serial.print("Right: ");
		Serial.print(right);
		Serial.print("\n");

		if (i < 50) {
			m_drivetrain.set_speed(0.5, 0);
			motors.set_motor_speeds(left, right);
		}
		else if (i < 100) {
			m_drivetrain.set_speed(0.5, 0.5);
			motors.set_motor_speeds(left, right);
		}
		else if (i < 150) {
			m_drivetrain.set_speed(0.5, -0.5);
			motors.set_motor_speeds(left, right);
		}
		else if (i < 200) {
			m_drivetrain.set_speed(-0.5, 0);			
			motors.set_motor_speeds(left, right);
		}
		else if (i < 300) {
			m_drivetrain.set_speed(0, 0);
			motors.set_motor_speeds(left, right);
		}
		else if (i > 500) {
			i = 0;
		}
		i++;
		delay(10);
	}
}