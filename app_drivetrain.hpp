#include "arduino.h"
#include "dev_TB9051FTG.hpp"

namespace subsystem {

	class drivetrain {
		 
	public:
		drivetrain(TB9051FTG motors);
		~drivetrain();

		/**
		 * Initialize the drivetrain
		 * @return[bool] success of initilization
		 */
		bool init();

		/**
		 * reset the drivetrain
		 * @return[bool] success of reset
		 */
		bool reset();

		/**
		 * set speed of motors based on "gas" and "steering" inputs
		 * @param gas the speed to set the motors to, value from -1 to 1
		 * @param steering difference in speed of left to right motor -1.0 for left
		 *				   1.0 for right
		 */
		void set_speed(double gas, double steering);

		/**
		 * set motor controller outputs based on left and right speeds
		 * calculated by set_speed.
		 */
		void run10ms();

	private:
		TB9051FTG m_motors;

		double m_left_motor_speed;

		double m_right_motor_speed;

	}; // class drivetrain

} // namespace subsystem