#ifndef __DEV_TB9051FTG_HPP__
#define __DEV_TB9051FTG_HPP__

#include "Arduino.h"
#include "DualTB9051FTGMotorShield.h"

/* HW CONFIG:
Shield placed on arduino

*/

/* Wrapper class for the Pololu TB9051 motor shield */

namespace actuator
{
    class TB9051FTG
    {
    public:
        TB9051FTG();
        ~TB9051FTG() = default;

        /**
         * Initialize the speed controllers
         * @return[bool] success of initilization
         */
        bool init();

        /**
         * Power cycle speed controllers and reset internal variables
         * @return[bool] success of reset
         */
        bool reset();

        /**
         * Set the speed of the right motor
         * @param speed double from -1 to 1 for percent motor power
         * @return[bool] success of setting speed
         */
        bool set_right_motor_speed(double speed);

        /**
         * Set the speed of the left motor
         * @param speed double from -1 to 1 for percent motor power
         * @return[bool] success of setting speed
         */
        bool set_left_motor_speed(double speed);

        /**
         * Initialize the speed controllers
         * @return[bool] success of initilization
         */
        bool disable_motors();

    private:
        DualTB9051FTGMotorShield m_shield;

        /**
         * Helper function to return if there is a fault
         * @return[bool] presence of a fault
         */
        bool get_fault();

    };
}

#endif
