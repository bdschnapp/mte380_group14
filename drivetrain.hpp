#ifndef __DRIVETRAIN_HPP__
#define __DRIVETRAIN_HPP__

namespace drivetrain
{
	struct motor_speeds
	{
		float left_motor_speed, right_motor_speed;
	};

	/**
	 * converts gas and steering values into appropriate motor speeds
	 * this function will never return -ve motor speeds. Behavior is akin
	 * to that of a car
	 * @param gas value representing gas pedal press in range [0, 100]
	 * @param steering value representing steering wheel input in range [-100, 100] (+ve is ccw)
	 * @return The corresponding left and right motor speeds each in range [0, 100]
	 */
	motor_speeds translational_motion_convert(const float gas, const float steering);

	/**
	 * computes motor speeds for point turn given a "power" constant
	 * @param turning_power sign represents direction (+ve is ccw), magnitude represents how fast to turn
	 * @return The corresponding left and right motor speeds each in range [-100, 100]
	 */
	motor_speeds point_turn_convert(const float turning_power);
}

#endif