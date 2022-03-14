#ifndef __DRIVETRAIN_HPP__
#define __DRIVETRAIN_HPP__

#include "Arduino.h"
#include "dev_TB9051FTG.hpp"

namespace subsystem {

	class drivetrain {
		 
	public:
		drivetrain();
		~drivetrain() = default;

		/**
		 * Initialize the drivetrain
		 * @return[bool] success of initilization
		 */
		bool init(actuator::TB9051FTG motors);

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
		 * Helper function for unit tests, lets tests access internal speed variables
		 */
		void get_motor_speeds(double& left_speed, double& right_speed);

	private:
		actuator::TB9051FTG m_motors;

		double m_left_motor_speed;

		double m_right_motor_speed;

	}; // class drivetrain

} // namespace subsystem

# endif