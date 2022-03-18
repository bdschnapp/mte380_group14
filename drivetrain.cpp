#include "drivetrain.hpp"
#include "lib_math.hpp"

namespace drivetrain
{
	motor_speeds translational_motion_convert(float gas, float steering)
	{
		gas = math::clamp(0.0f, 100.0f, gas);
		steering = math::clamp(-100.0f, 100.0f, steering);

		float left_motor_speed = 0.0f, right_motor_speed = 0.0f;

		if (steering >= 0)
		{
			left_motor_speed = gas * (100.0f - steering) / 100.0f;
			right_motor_speed = gas;
		}
		else
		{
			left_motor_speed = gas;
			right_motor_speed = gas * (100.0f + steering) / 100.0f;
		}

		return {left_motor_speed, right_motor_speed};
	}

	motor_speeds point_turn_convert(const float turning_power)
	{
		return {-turning_power, turning_power};
	}

}